#include "client.h"
# define M_PI           3.14159265358979323846  /* pi */
double zbuff[650][650];

int maxYValue(int y1, int y2, int y3) {
	int max = y1;
	if (y2 > max)
	{
		max = y2;
	}
	if (y3 > max)
	{
		max = y3;
	}
	return max;
}

Client::Client(Drawable *drawable, char *fileName)
{
    this->drawable = drawable;
	this->simpFileName = std::string(fileName);
}

void Client::nextPage() {	
	static int pageNumber = 0;
	pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;
    switch(pageNumber % 2) {
    case 1:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect( 50, 50, 700, 700, 0x00000000);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(400, 400, 700, 700, 0xff00ff40);
        drawable->updateScreen();
    }
	// Assignment 1
	//panelTests1(pageNumber); // Test the specific functionality of each panel on the specific page;
	
	// Assignment 2
	//panelTests2(pageNumber);

	// Assignment 3
	panelTests3(pageNumber);

	drawable->updateScreen();
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}

//============================================================
// Class Helper Functions
//============================================================

//============================================================
// This will calculate the centre of a specific panel
// Returns the centre of the panel (x,y)
std::tuple<int, int> Client::calculate_PanelCentre(int x1, int y1, int x2, int y2) {
	const int xDifference = std::abs(x2 + x1);
	const int yDifference = std::abs(y2 + y1);
	return std::make_tuple((xDifference / 2), (yDifference / 2));
}

//============================================================
// This will calculate the line endpoints for the starburst test
// Returns the endpoints of the specific angle (round(x),round(y))
std::tuple<float, float> Client::calculate_StarBurstAngles(int centreX, int centreY, int count)
{

	float length = 0;
	float height = 0;
	length = 125 * cos(4 * count * M_PI / 180);
	height = 125 * sin(4 * count * M_PI / 180);

	length = centreX + length;
	height = centreY + height;
	return std::make_tuple(std::round(length), std::round(height));
}

//============================================================
// This will calculate what random colour to draw for the lines.
unsigned int Client::calculate_LineColor()
{
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	unsigned int color = (0xff << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return color;
}

//============================================================
// This will unpack a 32 bit colour into Red Green Blue
RGBColour Client::unpackColour(unsigned int currentColour)
{
	RGBColour unpacked;

	unpacked.r = (currentColour >> 16)& 0xff;
	unpacked.g = (currentColour >> 8) & 0xff;
	unpacked.b = (currentColour) & 0xff;
	
	return unpacked;
}

//============================================================
// This will pack the struct into 32 bit value
unsigned int Client::packColour(RGBColour currentColour)
{
	return ((0xff << 24) + ((currentColour.r & 0xff) << 16) + ((currentColour.g & 0xff) << 8) + (currentColour.b & 0xff));
}

//============================================================
// Order the incoming points from highest Y to lowest Y
void Client::orderedCoordinates(int x1, int y1, int x2, int y2, int x3, int y3) {
	polygonCoordinates storageOfCoordinates;
	int highestYValue = maxYValue(y1, y2, y3);

	if (highestYValue == y1)
	{
		storageOfCoordinates.x = x1;
		storageOfCoordinates.y = y1;
		orderedPolygonCoordinates.push_back(storageOfCoordinates);
		if (y2 > y3)
		{
			storageOfCoordinates.x = x2;
			storageOfCoordinates.y = y2;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x3;
			storageOfCoordinates.y = y3;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
		else
		{
			storageOfCoordinates.x = x3;
			storageOfCoordinates.y = y3;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x2;
			storageOfCoordinates.y = y2;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
	}
	else if (highestYValue == y2)
	{
		storageOfCoordinates.x = x2;
		storageOfCoordinates.y = y2;
		orderedPolygonCoordinates.push_back(storageOfCoordinates);
		if (y1 > y3)
		{
			storageOfCoordinates.x = x1;
			storageOfCoordinates.y = y1;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x3;
			storageOfCoordinates.y = y3;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
		else
		{
			storageOfCoordinates.x = x3;
			storageOfCoordinates.y = y3;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x1;
			storageOfCoordinates.y = y1;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
	}
	else
	{
		storageOfCoordinates.x = x3;
		storageOfCoordinates.y = y3;
		orderedPolygonCoordinates.push_back(storageOfCoordinates);
		if (y1 > y2)
		{
			storageOfCoordinates.x = x1;
			storageOfCoordinates.y = y1;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x2;
			storageOfCoordinates.y = y2;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
		else
		{
			storageOfCoordinates.x = x2;
			storageOfCoordinates.y = y2;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);

			storageOfCoordinates.x = x1;
			storageOfCoordinates.y = y1;
			orderedPolygonCoordinates.push_back(storageOfCoordinates);
		}
	}
}

//============================================================
void Client::lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2) {

	// Assignment 2: We will now add colour interpolation
	// 1) Let's unpack both colours that are given to us
	// 2) Now we have R G B, so we will do our colour calcluation
	// 3) Repack all the colours
	// 4) draw the pixel

	RGBColour unpackedColour1 = unpackColour(color1);
	RGBColour unpackedColour2 = unpackColour(color2);

	// We want to find our y = mx + b components
	const float dx = x2 - x1;
	const float dy = y2 - y1;

	float m = dy / dx;
	float b = y1 - m*x1;

	const float diffR = unpackedColour2.r - unpackedColour1.r;
	const float diffG = unpackedColour2.g - unpackedColour1.g;
	const float diffB = unpackedColour2.b - unpackedColour1.b;

	// This will determine what case we are in
	bool slopeLessThanOne = true;

	// Vertical line
	if (x2 == x1)
	{
		if (dy > 0)
		{
			RGBColour finalColour;
			float finalRed = unpackedColour1.r;
			float finalGreen = unpackedColour1.g;
			float finalBlue = unpackedColour1.b;

			unsigned int roundRed;
			unsigned int roundGreen;
			unsigned int roundBlue;

			float dr = diffR / (y2 - y1);
			float dg = diffG / (y2 - y1);
			float db = diffB / (y2 - y1);

			for (int y = y1; y < y2; y++)
			{
				finalRed += dr;
				finalGreen += dg;
				finalBlue += db;

				roundRed = std::round(finalRed);
				roundGreen = std::round(finalGreen);
				roundBlue = std::round(finalBlue);

				finalColour.r = roundRed;
				finalColour.g = roundGreen;
				finalColour.b = roundBlue;

				unsigned int finalColourPacked = packColour(finalColour);
				drawable->setPixel(x2, y, finalColourPacked);
			}
		}
		else
		{
			for (int y = y2; y < y1; y++)
			{
				drawable->setPixel(x2, y, color1);
			}
		}
	}
	if (std::abs(m) >= 1)
	{
		slopeLessThanOne = false;
	}

	// CASE 1
	if (slopeLessThanOne)
	{
		float calculatedY = 0;
		// CASE 1a
		if (dx > 0)
		{
			float dr = diffR / (x2 - x1);
			float dg = diffG / (x2 - x1);
			float db = diffB / (x2 - x1);

			RGBColour finalColour;
			float finalRed = unpackedColour1.r;
			float finalGreen = unpackedColour1.g;
			float finalBlue = unpackedColour1.b;

			unsigned int roundRed;
			unsigned int roundGreen;
			unsigned int roundBlue;

			for (int x = x1; x < x2; x++)
			{
				finalRed += dr;
				finalGreen += dg;
				finalBlue += db;

				roundRed = std::round(finalRed);
				roundGreen = std::round(finalGreen);
				roundBlue = std::round(finalBlue);

				finalColour.r = roundRed;
				finalColour.g = roundGreen;
				finalColour.b = roundBlue;
				unsigned int finalColourPacked = packColour(finalColour);

				calculatedY = m*x + b;
				drawable->setPixel(x, std::round(calculatedY), finalColourPacked);
			}
		}
		// CASE 1b
		else
		{
			float dr = diffR / (x1 - x2);
			float dg = diffG / (x1 - x2);
			float db = diffB / (x1 - x2);

			RGBColour finalColour;
			float finalRed = unpackedColour1.r;
			float finalGreen = unpackedColour1.g;
			float finalBlue = unpackedColour1.b;

			unsigned int roundRed;
			unsigned int roundGreen;
			unsigned int roundBlue;


			for (int x = x1; x > x2; x--)
			{
				finalRed += dr;
				finalGreen += dg;
				finalBlue += db;

				roundRed = std::round(finalRed);
				roundGreen = std::round(finalGreen);
				roundBlue = std::round(finalBlue);

				finalColour.r = roundRed;
				finalColour.g = roundGreen;
				finalColour.b = roundBlue;
				unsigned int finalColourPacked = packColour(finalColour);

				calculatedY = m*x + b;
				int yValue = std::round(calculatedY);
				drawable->setPixel(x, std::round(calculatedY), finalColourPacked);
			}
		}
	}

	// CASE 2
	if (!slopeLessThanOne)
	{
		float calculatedX = 0;
		// CASE 2a
		if (dy > 0)
		{
			RGBColour finalColour;
			float finalRed = unpackedColour1.r;
			float finalGreen = unpackedColour1.g;
			float finalBlue = unpackedColour1.b;

			unsigned int roundRed;
			unsigned int roundGreen;
			unsigned int roundBlue;

			float dr = diffR / (y2 - y1);
			float dg = diffG / (y2 - y1);
			float db = diffB / (y2 - y1);

			for (int y = y1; y < y2; y++)
			{
				finalRed += dr;
				finalGreen += dg;
				finalBlue += db;

				roundRed = std::round(finalRed);
				roundGreen = std::round(finalGreen);
				roundBlue = std::round(finalBlue);

				finalColour.r = roundRed;
				finalColour.g = roundGreen;
				finalColour.b = roundBlue;
				unsigned int finalColourPacked = packColour(finalColour);

				calculatedX = (y - b) / m;
				drawable->setPixel(std::round(calculatedX), y, finalColourPacked);
			}
		}
		// CASE 2b
		else
		{
			RGBColour finalColour;
			float finalRed = unpackedColour1.r;
			float finalGreen = unpackedColour1.g;
			float finalBlue = unpackedColour1.b;

			unsigned int roundRed;
			unsigned int roundGreen;
			unsigned int roundBlue;

			float dr = diffR / (y2 - y1);
			float dg = diffG / (y2 - y1);
			float db = diffB / (y2 - y1);

			for (int y = y1; y > y2; y--)
			{
				finalRed += dr;
				finalGreen += dg;
				finalBlue += db;

				roundRed = std::round(finalRed);
				roundGreen = std::round(finalGreen);
				roundBlue = std::round(finalBlue);

				finalColour.r = roundRed;
				finalColour.g = roundGreen;
				finalColour.b = roundBlue;
				unsigned int finalColourPacked = packColour(finalColour);

				calculatedX = (y - b) / m;
				drawable->setPixel(std::round(calculatedX), y, finalColourPacked);
			}
		}
	}
}

//============================================================
void Client::polygonRenderer(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color1, unsigned int color2, unsigned int color3)
{
	float m_x1y1_x3y3 = (y3 - y1) / (x3 - x1); // Highest P -> Smallest P
	float m_x2y2_x3y3 = (y3 - y2) / (x3 - x2); // Middle P -> Smallest P
	float m_x1y1_x2y2 = (y2 - y1) / (x2 - x1);
	float b_x1y1_x3y3 = y1 - m_x1y1_x3y3*(x1); // Slope for Lowest P -> Smallest P
	float b_x2y2_x3y3 = y2 - m_x2y2_x3y3*(x2); // Slope for Middle P -> Smallest P
	float b_x1y1_x2y2 = y1 - m_x1y1_x2y2*(x1);

	int xleft = x1; // Start from highest Y
	int xright = x1; // Start from highest Y

	// Blerping
	RGBColour unpackedColour1 = unpackColour(color1);
	RGBColour unpackedColour2 = unpackColour(color2);
	RGBColour unpackedColour3 = unpackColour(color3);

	// Based on the sorting of the coordinates
	// there two possible ways to get a vertical line


	// 1) If x2 - x1 == 0 means we have a triangle 
	//
	// P3 -> + + + + + + <- P2   or similarly...   P2-> + + + + + + <- P3
	//                 +								+		  		
	//                 +								+			
	//				   ^ P1							 P1 ^
	if (x2 - x1 == 0)
	{

		// Lets assume the line is on the right side
		// The right line from P1 -> P2 is vertical
		// Slope: N/A & b-intercept: N/A
		if (x1 > x3)
		{
			const float diffR_21 = unpackedColour2.r - unpackedColour1.r;
			const float diffG_21 = unpackedColour2.g - unpackedColour1.g;
			const float diffB_21 = unpackedColour2.b - unpackedColour1.b;

			const float diffR_31 = unpackedColour3.r - unpackedColour1.r;
			const float diffG_31 = unpackedColour3.g - unpackedColour1.g;
			const float diffB_31 = unpackedColour3.b - unpackedColour1.b;

			const float diffR_32 = unpackedColour3.r - unpackedColour2.r;
			const float diffG_32 = unpackedColour3.g - unpackedColour2.g;
			const float diffB_32 = unpackedColour3.b - unpackedColour2.b;

			for (int y = y1; y >= y2; y--)
			{

				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}
		// line is on the left side
		// The left line from P1 -> P2 is vertical
		// Slope: N/A & b-intercept: N/A
		else
		{
			for (int y = y1; y >= y2; y--)
			{
				xright = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}
	}

	// If x2 - x3 == 0 then we have a triangle of the following
	//
	// P3 -> +													+ <- P3
	//		 +					or similarly..					+
	// P2 -> + + + + + + <- P1					P1 -> + + + + + + <- P2
	else if (x2 - x3 == 0)
	{
		// We should consider which side the vertical line is on
		xright = x2;
		xleft = x2;
		// The vertical line is on the left
		if (x1 > x2)
		{
			for (int y = y3; y <= y2; y++)
			{
				xright = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);

			}
		}
		// The vertical line is on the right
		else
		{
			for (int y = y3; y <= y2; y++)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);

			}
		}
	}

	else if (x1 - x3 == 0)
	{
		if (x1 < x2)
		{
			xleft = x1;
			for (int y = y1; y >= y2; y--)
			{
				xright = (y - b_x1y1_x2y2) / m_x1y1_x2y2;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}

			for (int y = y2; y >= y3; y--)
			{
				xright = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}

		else
		{
			xright = x1;
			for (int y = y1; y >= y2; y--)
			{
				xleft = (y - b_x1y1_x2y2) / m_x1y1_x2y2;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}

			for (int y = y2; y >= y3; y--)
			{
				xleft = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}
	}

	else
	{
		// If the the middle x is the same as lowest x
		float m_x1y1_x2y2 = (y2 - y1) / (x2 - x1); // Highest P -> Middle P
		int b_x1y1_x2y2 = y1 - m_x1y1_x2y2*(x1); // Slope for Lowest P -> Middle P

		// This only is conisdered when we do not have a vertical line
		// We should figure out if the middle point is on the left or right from the starting Point
		// Point 2 is on the RIGHT side
		if (x2 > x1)
		{
			// This will loop all the way to Point 2
			for (int y = y1; y >= y2; y--)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				xright = (y - b_x1y1_x2y2) / m_x1y1_x2y2;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}

			// This will loop from Point 2 to Point 3
			for (int y = y2; y >= y3; y--)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				xright = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}
		// Point 2 is on the LEFT side
		else
		{
			// This will loop all the way to Point 2
			for (int y = y1; y >= y2; y--)
			{
				xleft = (y - b_x1y1_x2y2) / m_x1y1_x2y2;
				xright = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}

			// This will loop from Point 2 to Point 3
			for (int y = y2; y >= y3; y--)
			{
				xleft = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				xright = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_DDA(std::round(xleft), y, std::round(xright), y, color1, color2);
			}
		}
	}
}

//============================================================
bool Client::simpFileOpener(std::string fileName)
{
	std::ifstream file;
	std::stringstream buffer;
	file.open(fileName.c_str());
	if (!file)
	{
		return false;
	}
	buffer << file.rdbuf();
	std::string currentLine = buffer.str();
	
	// Let's split the input file based on new lines
	std::istringstream lineToTokenize(currentLine);
	std::string token;
	std::vector<std::string> results;
	while (std::getline(lineToTokenize, token, '\n'))
	{
		results.push_back(token);
	}

	// Let's clean up our vector
	for (int i = 0; i < results.size(); i++)
	{
		simpFileInterpreter(results[i]);
	}

	transformationInterpreter();
	return true;
}

//============================================================
bool Client::simpFileInterpreter(std::string currentLine)
{
	std::vector<std::string> results;
	// Let's ignore comment lines
	if (currentLine[0] == '#')
	{
		return true;
	}
	
	if (currentLine[0] == '{')
	{
		parsedSimpFile.push_back(currentLine);
	}

	if (currentLine == "filled")
	{
		parsedSimpFile.push_back(currentLine);
	}
	if (currentLine == "wire")
	{
		parsedSimpFile.push_back(currentLine);
	}

	// Let's remove any blank spaces
	std::size_t pos = currentLine.find(" ");
	std::size_t intialPos = 0;

	// 1) Read points from simp file [DONE]
	while (pos != std::string::npos)
	{
		results.push_back(currentLine.substr(intialPos, pos - intialPos));
		intialPos = pos + 1;

		pos = currentLine.find_first_of(" (),", intialPos);

		if (pos == std::string::npos)
		{
			results.push_back(currentLine.substr(intialPos, currentLine.size()));
		}
	}

	// Let's remove blanks
	std::vector<std::string> filteredResults;
	for (std::size_t i = 0; i < results.size(); i++)
	{
		if (results[i] == "")
		{
			// Do nothing
		}
		else
		{
			filteredResults.push_back(results[i]);
		}
	}

	for (int i = 0; i < filteredResults.size(); i++)
	{
		parsedSimpFile.push_back(filteredResults[i]);
	}

	return true;
}

//============================================================
void Client::depthShading(point P1, point P2, point P3, unsigned int nearColour, unsigned int farColour)
{
	if (P1.z <= 200 && P2.z <= 200 && P3.z <= 200)
	{
		// Let's unpack the near and far colours
		RGBColour nearCol = unpackColour(nearColour);
		RGBColour farCol = unpackColour(farColour);

		// Let's determine the z adjustment to multiply onto the colours
		float z1Adujustment = P1.z / 2;
		z1Adujustment = 1 - (z1Adujustment / 100);
		float z2Adujustment = P2.z / 2;
		z2Adujustment = 1 - (z1Adujustment / 100);
		float z3Adujustment = P3.z / 2;
		z3Adujustment = 1 - (z1Adujustment / 100);

		// Let's now multiple each zAdjustment onto the colours
		RGBColour newP1;
		RGBColour newP2;
		RGBColour newP3;
		// Point 1
		newP1.r = std::round(nearCol.r * z1Adujustment);
		newP1.g = std::round(nearCol.g * z1Adujustment);
		newP1.b = std::round(nearCol.b * z1Adujustment);
		// Point 2
		newP2.r = std::round(nearCol.r * z2Adujustment);
		newP2.g = std::round(nearCol.g * z2Adujustment);
		newP2.b = std::round(nearCol.b * z2Adujustment);
		// Point 3
		newP3.r = std::round(nearCol.r * z3Adujustment);
		newP3.g = std::round(nearCol.g * z3Adujustment);
		newP3.b = std::round(nearCol.b * z3Adujustment);

		unsigned int colour_1 = packColour(newP1);
		unsigned int colour_2 = packColour(newP2);
		unsigned int colour_3 = packColour(newP3);

		polygonRenderer(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, colour_1, colour_2, colour_3);
	}
}

//============================================================
bool Client::transformationInterpreter()
{
	// Let's now define our stack for our current matrix
	// The necessary steps are 
	// 1) Take the top matrix at the top
	// 2) Transform that matrix and push that newly formed matrix on the top of the stack
	// 3) Render when required
	// 4) if } appears, we shall pop the top matrix

	std::stack<iMatrix> stackOfMatrices;
	iMatrix currentMatrix;

	// This will convert the simpFile coordinates space into
	// our screen space
	// We have to scale by (650/200 = 3.25)
	// We also have to translate by 325
	// The following matrix is a mix of Scale & Translate
	iMatrix worldCoords;
	worldCoords.matrix[0][0] = 3.25;
	worldCoords.matrix[1][1] = 3.25;
	worldCoords.matrix[0][3] = 325;
	worldCoords.matrix[1][3] = 325;

	wire = true;
	// Let's iterate through our vector
	for (int i = 0; i < parsedSimpFile.size(); i++)
	{
		// Safety: If there are blanks still we will skip these
		if (parsedSimpFile[i] == " ")
		{
			// Do nothing
		}
		else if (parsedSimpFile[i] == "{")
		{
			stackOfMatrices.push(currentMatrix);
			currentMatrix = stackOfMatrices.top();
		}
		else if (parsedSimpFile[i] == "}")
		{
			stackOfMatrices.pop();
		}
		else if (parsedSimpFile[i] == "scale")
		{
			currentMatrix = transformationScale(std::stod(parsedSimpFile[i + 1]),
												std::stod(parsedSimpFile[i + 2]),
												std::stod(parsedSimpFile[i + 3]), currentMatrix);
		}
		else if (parsedSimpFile[i] == "translate")
		{
			currentMatrix = transformationTranslate(std::stod(parsedSimpFile[i + 1]), 
													std::stod(parsedSimpFile[i + 2]), 
													std::stod(parsedSimpFile[i + 3]), currentMatrix);
		}
		else if (parsedSimpFile[i] == "rotate")
		{
			currentMatrix = transformationRotate(parsedSimpFile[i+1],
												 std::stod(parsedSimpFile[i+2]), currentMatrix);
		}
		else if (parsedSimpFile[i] == "line")
		{
			//First point
			point currentPoint_1;
			currentPoint_1.x = std::round(std::stod(parsedSimpFile[i + 1]));
			currentPoint_1.y = std::round(std::stod(parsedSimpFile[i + 2]));
			currentPoint_1.z = std::round(std::stod(parsedSimpFile[i + 3]));
			currentPoint_1.w = 1;
			//Second point
			point currentPoint_2;
			currentPoint_2.x = std::round(std::stod(parsedSimpFile[i + 4]));
			currentPoint_2.y = std::round(std::stod(parsedSimpFile[i + 5]));
			currentPoint_2.z = std::round(std::stod(parsedSimpFile[i + 6]));
			currentPoint_2.w = 1;

			point finalPoint_1 = transformationPoint(currentPoint_1, currentMatrix);
			point finalPoint_2 = transformationPoint(currentPoint_2, currentMatrix);

			if (finalPoint_1.x > 650)
			{
				finalPoint_1.x = 650;
			}
			else if (finalPoint_1.x < 50)
			{
				finalPoint_1.x = 50;
			}
			if (finalPoint_1.y > 650)
			{
				finalPoint_1.y = 650;
			}
			else if (finalPoint_1.y < 50)
			{
				finalPoint_1.y = 50;
			}
			// --
			if (finalPoint_2.x > 650)
			{
				finalPoint_2.x = 650;
			}
			else if (finalPoint_2.x < 50)
			{
				finalPoint_2.x = 50;
			}
			if (finalPoint_2.y > 650)
			{
				finalPoint_2.y = 650;
			}
			else if (finalPoint_2.y < 50)
			{
				finalPoint_2.y = 50;
			}
			if ((finalPoint_1.z || finalPoint_2.z)> 200)
			{
				// Do nothing
			}
			else
			{
				lineDrawer_DDA(finalPoint_1.x, finalPoint_1.y, finalPoint_2.x, finalPoint_2.y, calculate_LineColor(), calculate_LineColor());
			}

		}
		else if (parsedSimpFile[i] == "polygon")
		{
			//First point
			point currentPoint_1;
			currentPoint_1.x = std::round(std::stod(parsedSimpFile[i + 1]));
			currentPoint_1.y = std::round(std::stod(parsedSimpFile[i + 2]));
			currentPoint_1.z = std::round(std::stod(parsedSimpFile[i + 3]));
			currentPoint_1.w = 1;
			//Second point
			point currentPoint_2;
			currentPoint_2.x = std::round(std::stod(parsedSimpFile[i + 4]));
			currentPoint_2.y = std::round(std::stod(parsedSimpFile[i + 5]));
			currentPoint_2.z = std::round(std::stod(parsedSimpFile[i + 6]));
			currentPoint_2.w = 1;
			//Third point
			point currentPoint_3;
			currentPoint_3.x = std::round(std::stod(parsedSimpFile[i + 7]));
			currentPoint_3.y = std::round(std::stod(parsedSimpFile[i + 8]));
			currentPoint_3.z = std::round(std::stod(parsedSimpFile[i + 9]));
			currentPoint_3.w = 1;

			//multply the world CS with CurrentMatrix
			iMatrix CTM = multiplyMatrices(worldCoords, currentMatrix);

			point finalPoint_1 = transformationPoint(currentPoint_1, CTM);
			point finalPoint_2 = transformationPoint(currentPoint_2, CTM);
			point finalPoint_3 = transformationPoint(currentPoint_3, CTM);

			if (finalPoint_1.x > 650)
			{
				finalPoint_1.x = 650;
			}
			else if (finalPoint_1.x < 50)
			{
				finalPoint_1.x = 50;
			}
			if (finalPoint_1.y > 650)
			{
				finalPoint_1.y = 650;
			}
			else if (finalPoint_1.y < 50)
			{
				finalPoint_1.y = 50;
			}
			// --
			if (finalPoint_2.x > 650)
			{
				finalPoint_2.x = 650;
			}
			else if (finalPoint_2.x < 50)
			{
				finalPoint_2.x = 50;
			}
			if (finalPoint_2.y > 650)
			{
				finalPoint_2.y = 650;
			}
			else if (finalPoint_2.y < 50)
			{
				finalPoint_2.y = 50;
			}

			// --
			if (finalPoint_3.x > 650)
			{
				finalPoint_3.x = 650;
			}
			else if (finalPoint_3.x < 50)
			{
				finalPoint_3.x = 50;
			}
			if (finalPoint_3.y > 650)
			{
				finalPoint_3.y = 650;
			}
			else if (finalPoint_3.y < 50)
			{
				finalPoint_3.y = 50;
			}

			// --
			if ((finalPoint_1.z || finalPoint_2.z || finalPoint_3.z)> 200)
			{
				// Do nothing
			}
			else
			{
				triangle drawThis;
				drawThis.P1 = finalPoint_1;
				drawThis.P2 = finalPoint_2;
				drawThis.P3 = finalPoint_3;

				// Draw the newly transformed triangle

				orderedCoordinates(drawThis.P1.x, drawThis.P1.y,
					drawThis.P2.x, drawThis.P2.y,
					drawThis.P3.x, drawThis.P3.y);

				if (!wire)
				{
					depthShading(drawThis.P1, drawThis.P2, drawThis.P3, 0xffffffff, 0x00000000);
					polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
						orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
						orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, 0xffffffff, 0xffffffff, 0xffffffff);
					orderedPolygonCoordinates.clear();
				}
				else
				{
					lineDrawer_DDA(drawThis.P1.x, drawThis.P1.y, drawThis.P2.x, drawThis.P2.y, 0xffffffff, 0xffffffff);
					lineDrawer_DDA(drawThis.P1.x, drawThis.P1.y, drawThis.P3.x, drawThis.P3.y, 0xffffffff, 0xffffffff);
					lineDrawer_DDA(drawThis.P2.x, drawThis.P2.y, drawThis.P3.x, drawThis.P3.y, 0xffffffff, 0xffffffff);
				}
			}

		}
		else if (parsedSimpFile[i] == "wire")
		{
			wire = true;
		}
		else if (parsedSimpFile[i] == "filled")
		{
			wire = false;
		}
		else if (parsedSimpFile[i] == "obj")
		{
			objFileReader(parsedSimpFile[i + 1]);
		}
		else if (parsedSimpFile[i] == "camera")
		{
			float xlow = std::stod(parsedSimpFile[i + 1]);
			float ylow = std::stod(parsedSimpFile[i + 2]);
			float xhigh = std::stod(parsedSimpFile[i + 3]);
			float yhigh = std::stod(parsedSimpFile[i + 4]);
			currentMatrix = CameraPerspective(90, std::stod(parsedSimpFile[i + 5]), std::stod(parsedSimpFile[i + 6]), currentMatrix);
		}
		else if (parsedSimpFile[i] == "ambient")
		{
			RGBColour setAmb;
			setAmb.r = std::stod(parsedSimpFile[i + 1]);
			setAmb.g = std::stod(parsedSimpFile[i + 2]);
			setAmb.b = std::stod(parsedSimpFile[i + 3]);
			setAmbient(setAmb);
		}
		else if (parsedSimpFile[i] == "depth")
		{
		}
		else if (parsedSimpFile[i] == "surface")
		{
		}
		else
		{
			// Do nothing.. the only things that go in here are coordinates
		}

	}
	return true;
}

//============================================================
bool Client::objFileReader(std::string fileName)
{
	std::ifstream file;
	std::stringstream buffer;
	file.open(fileName.c_str());
	if (!file)
	{
		return false;
	}
	buffer << file.rdbuf();
	std::string currentLine = buffer.str();

	std::stringstream lineToTokenize(currentLine);
	std::string token;
	std::vector<std::string> results;
	while (std::getline(lineToTokenize, token, '\n'))
	{
		results.push_back(token);
	}

	// We will now clean up our vector
	for (int i = 0; i < results.size(); i++)
	{
		objFileInterpreter(results[i]);
	}
	transformObjFile();
}

//============================================================
bool Client::objFileInterpreter(std::string currentLine)
{
	std::vector<std::string> results;
	// Ignore comment lines
	if (currentLine[0] == '#')
	{
		return true;
	}

	// Remove any blank spaces
	std::size_t pos = currentLine.find(" ");
	std::size_t intialPos = 0;

	// Read the obj file
	while (pos != std::string::npos)
	{
		results.push_back(currentLine.substr(intialPos, pos - intialPos));
		intialPos = pos + 1;

		pos = currentLine.find_first_of(" (),", intialPos);
		if (pos == std::string::npos)
		{
			results.push_back(currentLine.substr(intialPos, currentLine.size()));
		}

	}

	// Remove blank lines
	std::vector<std::string> filteredResults;
	for (std::size_t i = 0; i < results.size(); i++)
	{
		if (results[i] == "#")
		{
			// Do nothing
		}
		else if (results[i] == "")
		{
			// Do nothing
		}
		else
		{
			parsedObjFile.push_back(results[i]);
		}
	}

	for (int i = 0; i < filteredResults.size(); i++)
	{
	parsedObjFile.push_back(filteredResults[i]);
	}
	return true;
}

//============================================================
void Client::transformObjFile()
{
	Vertex tempVertex; // Temporary place holder for a read vertex 
	Normal tempNormal; // Temporary place holder for a read Normal vertex
	Face tempFace; // Temporary place holder for a read Face

	// We know we want to store the vertex descriptions i.e
	// Vertex 1: v 1 1 1 
	// Vertex 2: v 0.5 0.05 0.5
	// We store this so we can use it for the faces
	// For Vectors
	// [0] is the first vertex
	// Where as in an obj file..
	// 1 is the first vertex

	// Let's iterate through our vector
	for (int i = 0; i < parsedObjFile.size(); i++)
	{
		// Lets always reset the colour to the highest intensity
		tempVertex.colour.r = 255;
		tempVertex.colour.g = 255;
		tempVertex.colour.b = 255;

		if (parsedObjFile[i] == " ")
		{
			// Do nothing. Safety measure.
		}
		else if (parsedObjFile[i] == "v")
		{
			// Case 1) X Y Z W R G B (i+8)
			if ((parsedObjFile[i + 8] == "v") || (parsedObjFile[i + 8] == "vn") || (parsedObjFile[i + 8] == "f") || (parsedObjFile[i + 8] == "#"))
			{
				tempVertex.P.x = std::stod(parsedObjFile[i + 1]);
				tempVertex.P.y = std::stod(parsedObjFile[i + 2]);
				tempVertex.P.z = std::stod(parsedObjFile[i + 3]);
				tempVertex.P.w = std::stod(parsedObjFile[i + 4]);
				tempVertex.colour.r = std::round(tempVertex.colour.r * std::stod(parsedObjFile[i + 5]));
				tempVertex.colour.g = std::round(tempVertex.colour.g * std::stod(parsedObjFile[i + 6]));
				tempVertex.colour.b = std::round(tempVertex.colour.b * std::stod(parsedObjFile[i + 7]));
			}
			// Case 2) X Y Z R G B (i+7)
			else if ((parsedObjFile[i + 7] == "v") || (parsedObjFile[i + 7] == "vn") || (parsedObjFile[i + 7] == "f") || (parsedObjFile[i + 7] == "#"))
			{
				tempVertex.P.x = std::stod(parsedObjFile[i + 1]);
				tempVertex.P.y = std::stod(parsedObjFile[i + 2]);
				tempVertex.P.z = std::stod(parsedObjFile[i + 3]);
				tempVertex.colour.r = std::round(tempVertex.colour.r * std::stod(parsedObjFile[i + 4]));
				tempVertex.colour.g = std::round(tempVertex.colour.g * std::stod(parsedObjFile[i + 5]));
				tempVertex.colour.b = std::round(tempVertex.colour.b * std::stod(parsedObjFile[i + 6]));
			}
			// Case 3) X Y Z W (i+5)
			else if ((parsedObjFile[i + 5] == "v") || (parsedObjFile[i + 5] == "vn") || (parsedObjFile[i + 5] == "f") || (parsedObjFile[i + 5] == "#"))
			{
				tempVertex.P.x = std::stod(parsedObjFile[i + 1]);
				tempVertex.P.y = std::stod(parsedObjFile[i + 2]);
				tempVertex.P.z = std::stod(parsedObjFile[i + 3]);
				tempVertex.P.w = std::stod(parsedObjFile[i + 4]);
				tempVertex.colour.r = 255;
				tempVertex.colour.g = 255;
				tempVertex.colour.b = 255;
			}
			// Case 4) X Y Z (i+4)
			else if ((parsedObjFile[i + 4] == "v") || (parsedObjFile[i + 4] == "vn") || (parsedObjFile[i + 4] == "f") || (parsedObjFile[i + 4] == "#"))
			{
				tempVertex.P.x = std::stod(parsedObjFile[i + 1]);
				tempVertex.P.y = std::stod(parsedObjFile[i + 2]);
				tempVertex.P.z = std::stod(parsedObjFile[i + 3]);
				tempVertex.P.w = 1;
				tempVertex.colour.r = 255;
				tempVertex.colour.g = 255;
				tempVertex.colour.b = 255;
			}
			objVertexArray.push_back(tempVertex);
		}
		else if (parsedObjFile[i] == "vn")
		{
			tempNormal.P.x = std::stod(parsedObjFile[i + 1]);
			tempNormal.P.y = std::stod(parsedObjFile[i + 2]);
			tempNormal.P.z = std::stod(parsedObjFile[i + 3]);
			objNormalArray.push_back(tempNormal);
		}
		else if (parsedObjFile[i] == "f")
		{
			// There is a chance that indices can be negative.. in that case
			// We will use the most recent vertex
			if (std::stoi(parsedObjFile[i + 1]) < 0)
			{
				tempFace.vertex_1 = objVertexArray[objVertexArray.size() - std::abs(std::stoi(parsedObjFile[i + 1]))];
			}
			else
			{
				tempFace.vertex_1 = objVertexArray[std::stoi(parsedObjFile[i + 1]) - 1];
			}
			if (std::stoi(parsedObjFile[i + 2]) < 0)
			{
				tempFace.vertex_2 = objVertexArray[objVertexArray.size() - std::abs(std::stoi(parsedObjFile[i + 2]))];
			}
			else
			{
				tempFace.vertex_2 = objVertexArray[std::stoi(parsedObjFile[i + 2]) - 1];
			}
			if (std::stoi(parsedObjFile[i + 3]) < 0)
			{
				tempFace.vertex_3 = objVertexArray[objVertexArray.size() - std::abs(std::stoi(parsedObjFile[i + 3]))];
			}
			else
			{
				tempFace.vertex_3 = objVertexArray[std::stoi(parsedObjFile[i + 3]) - 1];
			}
			objFaceArray.push_back(tempFace);
		}
		else
		{
			// Do nothing
		}
		
	}
}

//============================================================
point Client::transformationPoint(point pointToChange, iMatrix transformationMatrix)
{
	point newPoint;
	newPoint.z = 1;
	newPoint.w = 1;
	int zToChange = 1;
	int shouldBeOne = 1;
	int someW = 1;

	newPoint.x = std::round(transformationMatrix.matrix[0][0] * pointToChange.x + transformationMatrix.matrix[0][1] * pointToChange.y + transformationMatrix.matrix[0][2] * pointToChange.z + transformationMatrix.matrix[0][3]);
	newPoint.y = std::round(transformationMatrix.matrix[1][0] * pointToChange.x + transformationMatrix.matrix[1][1] * pointToChange.y + transformationMatrix.matrix[1][2] * pointToChange.z + transformationMatrix.matrix[1][3]);
	newPoint.z = std::round(transformationMatrix.matrix[2][0] * pointToChange.x + transformationMatrix.matrix[2][1] * pointToChange.y + transformationMatrix.matrix[2][2] * pointToChange.z + transformationMatrix.matrix[2][3]);
	
	return newPoint;
}

//============================================================ 
iMatrix Client::transformationRotate(std::string axis, double numberOfDegrees, iMatrix currentMatrix)
{
	iMatrix rotation;

	// Let's set the rotational matrix to our specific degree to the axis we want to rotate on
	// TODO: Fix X Y rotation
	// If it doesn't work then, just simply rotation on Z :3
	if (axis == "X")
	{
		rotation.matrix[1][0] = 0;
		rotation.matrix[1][1] = cos((numberOfDegrees * M_PI) / 180);
		rotation.matrix[1][2] = -sin((numberOfDegrees * M_PI) / 180);
		rotation.matrix[1][3] = 0;

		rotation.matrix[0][2] = 0;
		rotation.matrix[1][2] = sin((numberOfDegrees * M_PI) / 180);
		rotation.matrix[2][2] = cos((numberOfDegrees * M_PI) / 180);
		rotation.matrix[3][2] = 0;
	}
	else if (axis == "Y")
	{
		rotation.matrix[0][1] = cos((numberOfDegrees * M_PI) / 180);
		rotation.matrix[0][2] = 0;
		rotation.matrix[0][3] = sin((numberOfDegrees * M_PI) / 180);
		rotation.matrix[0][4] = 0;

		rotation.matrix[2][0] = -sin((numberOfDegrees * M_PI) / 180);
		rotation.matrix[2][1] = 0;
		rotation.matrix[2][2] = cos((numberOfDegrees * M_PI) / 180);
		rotation.matrix[2][3] = 0;
	}
	else
	{
		rotation.matrix[0][0] = cos((numberOfDegrees * M_PI) / 180);
		rotation.matrix[0][1] = -sin((numberOfDegrees * M_PI) / 180);

		rotation.matrix[1][0] = sin((numberOfDegrees * M_PI) / 180);
		rotation.matrix[1][1] = cos((numberOfDegrees * M_PI) / 180);

	}
	// Let's multiply the 2 matrices out
	// 4x4 times 4x4
	return multiplyMatrices(currentMatrix, rotation);
}

//============================================================
iMatrix Client::multiplyMatrices(iMatrix A, iMatrix B)
{
	iMatrix finalMatrix;

	for (int a = 0; a < 4; a++)
	{
		for (int b = 0; b < 4; b++)
		{
			finalMatrix.matrix[a][b] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				finalMatrix.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
			}
		}
	}
	return finalMatrix;
}

//============================================================
// Translation function
iMatrix Client::transformationTranslate(double translateX, double translateY, double translateZ, iMatrix currentMatrix)
{
	iMatrix translate;

	translate.matrix[0][3] = translateX;
	translate.matrix[1][3] = translateY;
	translate.matrix[2][3] = translateZ;
	translate.matrix[3][3] = 1;

	return multiplyMatrices(currentMatrix, translate);
}

//============================================================
// Scale function
iMatrix Client::transformationScale(double scaleX, double scaleY, double scaleZ, iMatrix currentMatrix)
{
	iMatrix scale;

	scale.matrix[0][0] = scaleX;
	scale.matrix[1][1] = scaleY;
	scale.matrix[2][2] = scaleZ;
	return multiplyMatrices(currentMatrix, scale);
}

//============================================================
// Changing Camera Perspective
iMatrix Client::CameraPerspective(float degrees, float zNear, float zFar, iMatrix CTM)
{
	iMatrix camera;
	// Setting the perspective Matrix
	// zNear = hither
	// zFar = yon
	float s = 1 / (tan(degrees * (1 / 2) * M_PI / 180));
	camera.matrix[0][0] = s;
	camera.matrix[1][1] = s;
	camera.matrix[2][2] = -zFar / (zFar - zNear);
	camera.matrix[3][2] = -zFar * zNear / (zFar - zNear);
	camera.matrix[2][3] = -1;
	camera.matrix[3][3] = 0;

	return multiplyMatrices(CTM, camera);
}

//============================================================
void Client::setAmbient(RGBColour setAmbientColour)
{

}

//============================================================
void Client::zBuffer(triangle caseThreeTriangle)
{
	for (int i = 0; i < 650; i++)
	{
		for (int j = 0; j < 650; j++)
		{
			zbuff[i][j] = 200;
		}
	}

	// The triangle given has a z value so
	if (caseThreeTriangle.P1.z != 0)
	{
		for (int i = 0; i < 6; i++)
		{
			iMatrix rotationMatrix;
			rotationMatrix = transformationRotate("Z", rand() % 120, rotationMatrix);
			point P1 = page3TransformHelper(rotationMatrix, caseThreeTriangle.P1);
			point P2 = page3TransformHelper(rotationMatrix, caseThreeTriangle.P2);
			point P3 = page3TransformHelper(rotationMatrix, caseThreeTriangle.P3);

			triangle drawThis;
			drawThis.P1 = P1;
			drawThis.P2 = P2;
			drawThis.P3 = P3;

			// Draw the newly transformed triangle
			orderedCoordinates(drawThis.P1.x, drawThis.P1.y,
				drawThis.P2.x, drawThis.P2.y,
				drawThis.P3.x, drawThis.P3.y);

			// Let's unpack the near and far colours
			RGBColour colour = unpackColour(calculate_LineColor());
			RGBColour newP1;
			if (i == 0)
			{
				newP1.r = std::round(colour.r * 1);
				newP1.g = std::round(colour.g * 1);
				newP1.b = std::round(colour.b * 1);
			}
			else if (i == 1)
			{
				newP1.r = std::round(colour.r * 0.85);
				newP1.g = std::round(colour.g * 0.85);
				newP1.b = std::round(colour.b * 0.85);
			}
			else if (i == 2)
			{
				newP1.r = std::round(colour.r * 0.7);
				newP1.g = std::round(colour.g * 0.7);
				newP1.b = std::round(colour.b * 0.7);
			}
			else if (i == 3)
			{
				newP1.r = std::round(colour.r * 0.55);
				newP1.g = std::round(colour.g * 0.55);
				newP1.b = std::round(colour.b * 0.55);
			}
			else if (i == 4)
			{
				newP1.r = std::round(colour.r * 0.4);
				newP1.g = std::round(colour.g * 0.4);
				newP1.b = std::round(colour.b * 0.4);
			}
			else if (i == 5)
			{
				newP1.r = std::round(colour.r * 0.25);
				newP1.g = std::round(colour.g * 0.25);
				newP1.b = std::round(colour.b * 0.25);
			}
			unsigned int newColour = packColour(newP1);
			polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
				orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
				orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, newColour, newColour, newColour);
			orderedPolygonCoordinates.clear();
		}
	}
}

//============================================================
point Client::page3TransformHelper(iMatrix transformationMatrix, point P)
{
	std::tuple<int,int> centre = calculate_PanelCentre(50, 50, 700, 700);

	point newPoint;
	newPoint.z = 1;
	newPoint.w = 1;
	int zToChange = 1;
	int shouldBeOne = 1;
	int someW = 1;

	int xToChange = P.x - std::get<0>(centre);
	int yToChange = P.y - std::get<1>(centre);

	newPoint.x = std::round(transformationMatrix.matrix[0][0] * xToChange + transformationMatrix.matrix[0][1] * yToChange + transformationMatrix.matrix[0][2] * zToChange + transformationMatrix.matrix[0][3] * shouldBeOne);
	newPoint.y = std::round(transformationMatrix.matrix[1][0] * xToChange + transformationMatrix.matrix[1][1] * yToChange + transformationMatrix.matrix[1][2] * zToChange + transformationMatrix.matrix[1][3] * shouldBeOne);
	newPoint.z = std::round(transformationMatrix.matrix[2][0] * xToChange + transformationMatrix.matrix[2][1] * yToChange + transformationMatrix.matrix[2][2] * zToChange + transformationMatrix.matrix[2][3] * shouldBeOne);
	someW = std::round(transformationMatrix.matrix[3][0] * xToChange + transformationMatrix.matrix[3][1] * yToChange + transformationMatrix.matrix[3][2] * zToChange + transformationMatrix.matrix[3][3] * shouldBeOne);
	
	newPoint.x += std::get<0>(centre);
	newPoint.y += std::get<1>(centre);
	return newPoint;
}

//============================================================
// All possible tests that are required by Assignment 3

//============================================================
void Client::panelTests3(const int pageNumber)
{
	simpFileOpener(simpFileName);
}
