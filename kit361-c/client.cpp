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

Client::Client(Drawable *drawable)
{
    this->drawable = drawable;
}

void Client::nextPage() {	
	static int pageNumber = 0;
	pageNumber++;
    std::cout << "PageNumber " << pageNumber << std::endl;
    switch(pageNumber % 9) {
    case 1:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect( 50, 50, 700, 700, 0x00000000);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    case 2:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
        break;
    case 3:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
        break;
    case 4:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
	case 5:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
	case 6:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
	case 7:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
	case 8:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(400, 400, 700, 700, 0xff00ff40);
        drawable->updateScreen();
    }
	// Assignment 1
	//panelTests1(pageNumber); // Test the specific functionality of each panel on the specific page;
	
	// Assignment 2
	panelTests2(pageNumber);

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
// Unsure what this does so far
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
		else
		{
			// Do nothing.. the only things that go in here are coordinates
		}

	}
	return true;
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
// Rotation function
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
// All possible tests that are required by Assignment 2

//============================================================
void Client::panelTests2(const int pageNumber)
{
	int xRandom = 0;
	int yRandom = 0;
	int someZ = 0;
	std::tuple<int,int> panelCenter = calculate_PanelCentre(50, 50, 700, 700);
	std::tuple<int, int> vertex1;
	std::tuple<int, int> vertex2;
	std::tuple<int, int> vertex3;
	unsigned int colourCase3 = 0;

	std::string fileName = "cube.simp";
	switch (pageNumber) {

	// Implementation of wireframe
	case 1:
		grid gridSetupRandom[10][10];
		// This stores the related points for the grid
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				gridSetupRandom[i][j].x = 100 + 60 * j;
				gridSetupRandom[i][j].y = 100 + 60 * i;

				xRandom = (rand() % 12) - 12;
				yRandom = (rand() % 12) - 12;

				gridSetupRandom[i][j].x = gridSetupRandom[i][j].x + xRandom;
				gridSetupRandom[i][j].y = gridSetupRandom[i][j].y + yRandom;
			}
		}

		// Let's draw the wireframe
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {

				// Generate two random colors
				unsigned int colour_1 = calculate_LineColor();
				unsigned int colour_2 = calculate_LineColor();
				unsigned int colour_3 = calculate_LineColor();

				// We still need to draw the end borders
				// I will do conditional statements for corner points otherwise we crash cause of access of illegal point in the array
				if (i<9) {
					lineDrawer_DDA(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, gridSetupRandom[i + 1][j].x, gridSetupRandom[i + 1][j].y, colour_1, colour_2);
				}

				if (j<9) {
					lineDrawer_DDA(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, gridSetupRandom[i][j + 1].x, gridSetupRandom[i][j + 1].y, colour_1, colour_2);
				}

				// This will draw the diagonal line
				if (i != 0 && i <= 9 && j < 9) {
					lineDrawer_DDA(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, gridSetupRandom[i - 1][j + 1].x, gridSetupRandom[i - 1][j + 1].y, colour_1, colour_2);
				}
			}
		}
		break;

	case 2:
		grid gridSetupNormal[10][10];
		// This stores the related points for the grid
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				gridSetupNormal[i][j].x = 100 + 60 * j;
				gridSetupNormal[i][j].y = 100 + 60 * i;

				xRandom = (rand() % 12) - 12;
				yRandom = (rand() % 12) - 12;

				gridSetupNormal[i][j].x = gridSetupNormal[i][j].x + xRandom;
				gridSetupNormal[i][j].y = gridSetupNormal[i][j].y + yRandom;
			}
		}

		// Render Triangles
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				orderedCoordinates(gridSetupNormal[i][j].x, gridSetupNormal[i][j].y,
					gridSetupNormal[i + 1][j + 1].x, gridSetupNormal[i + 1][j + 1].y,
					gridSetupNormal[i][j + 1].x, gridSetupNormal[i][j + 1].y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();

				orderedCoordinates(gridSetupNormal[i][j].x, gridSetupNormal[i][j].y,
					gridSetupNormal[i + 1][j + 1].x, gridSetupNormal[i + 1][j + 1].y,
					gridSetupNormal[i + 1][j].x, gridSetupNormal[i + 1][j].y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
		}
		break;

	case 3:
		// Let's attempt to make 6 triangles

		// Circle center is in the center of the panel
		colourCase3 = (0xff << 24) + ((255 & 0xff) << 16) + ((255 & 0xff) << 8) + (255 & 0xff);
		// To draw the first Triangle..
		point vertex1;
		point vertex2;
		point vertex3;
		someZ = rand() % 200;
		// 1) Vertex 1
		vertex1.x = std::get<0>(panelCenter);
		vertex1.y = std::get<1>(panelCenter) - 275;
		vertex1.z = someZ;
		// 2) Vertex 2
		vertex2.x = (275 * cos((30 * M_PI) / 180)) + std::get<0>(panelCenter);
		vertex2.y = (275 * sin((30 * M_PI) / 180)) + std::get<1>(panelCenter);
		vertex2.z = someZ;
		// 3) Vertex 3
		vertex3.x = (275 * cos((150 * M_PI) / 180)) + std::get<0>(panelCenter);
		vertex3.y = (275 * sin((150 * M_PI) / 180)) + std::get<1>(panelCenter);
		vertex3.z = someZ;

		// Let's store this triangle
		triangle caseThreeTriangle;
		caseThreeTriangle.P1 = vertex1;
		caseThreeTriangle.P2 = vertex2;
		caseThreeTriangle.P3 = vertex3;
		zBuffer(caseThreeTriangle);
		break;

	case 4:
		simpFileOpener("test.txt");
		parsedSimpFile.clear();
		break;

	case 5:
		simpFileOpener("mytest2.simp");
		parsedSimpFile.clear();
		break;

	case 6:
		simpFileOpener("test1.simp");
		parsedSimpFile.clear();
		break;

	case 7:
		simpFileOpener("test2.simp");
		parsedSimpFile.clear();
		break;

	case 8:
		simpFileOpener("test3.simp");
		break;

	default:
		break;
	}
}
