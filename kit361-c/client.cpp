#include "client.h"
# define M_PI           3.14159265358979323846  /* pi */

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
	// TODO [COMPLETE]: We must create 5 pages that consist of 4 panels each
	// Each Panel must be 300x300 pixels with 50 pixel gaps.
	// Use black & white background
	// black: 0x00000000
	// white: 0xffffffff
    switch(pageNumber % 6) {
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
void Client::lineDrawer_Bresenham(int x1, int y1, int x2, int y2, unsigned int color) {

	// We will determine the coordinates octant before we do anything
	// Our algorithm will deal with the coordinates only on Octant I
	//
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx < 0)
	{
		dx = dx * (-1);
	}

	if (dy < 0)
	{
		dy = dy * (-1);
	}

	int twoDx = 0;
	int twoDy = 0;
	int t2 = 0;
	int err = 0;
	int y = y1;
	int x = x1;

	drawable->setPixel(x1, y, color);

	// This is considering that the lines are in the upper octants
	if (y2 - y1 >= 0)
	{
		twoDx = 2 * dx;
		twoDy = 2 * dy;

		// If twoDy is less than twoDx
		// Then we traverse on x to get the most pixels
		if (twoDy < twoDx)
		{
			t2 = twoDy - twoDx;
			err = twoDy - dx;

			// Octant: 1
			if (x2 - x1 >= 0)
			{
				for (int x = x1 + 1; x <= x2; x++)
				{
					if (err >= 0)
					{
						err = err + t2;
						y = y + 1;
					}
					else
					{
						err = err + twoDy;
					}
					drawable->setPixel(x, y, color);
				}
			}
			// Octant: 4
			else
			{
				for (int x = x1 - 1; x >= x2; x--)
				{
					if (err >= 0)
					{
						err = err + t2;
						y = y + 1;
					}
					else
					{
						err = err + twoDy;
					}
					drawable->setPixel(x, y, color);
				}
			}
		}

		// If twoDy is greater than twoDx
		// Then we traverse on y to get the most pixels
		else
		{
			t2 = twoDx - twoDy;
			err = twoDx - dy;

			// Octant 2;
			if (x2 - x1 >= 0)
			{
				for (int y = y1 + 1; y < y2; y++)
				{
					if (err >= 0)
					{
						err = err + t2;
						x = x + 1;
					}
					else
					{
						err = err + twoDx;
					}
					drawable->setPixel(x, y, color);
				}
			}
			// Octant 3
			else
			{
				for (int y = y1 + 1; y < y2; y++)
				{
					if (err >= 0)
					{
						err = err + t2;
						x = x - 1; // increase y by 1
					}
					else
					{
						err = err + twoDx;
					}
					drawable->setPixel(x, y, color);
				}
			}
		}
	} // End of y2 - y1
	
	// Now we consider the lower octants
	// Pretty much the same as above but instead of incrementing 
	// after err >= 0, we will decrement for all cases
	else
	{
		twoDx = 2 * dx;
		twoDy = 2 * dy;

		// If twoDy is less than twoDx
		// Then we traverse on x to get the most pixels
		if (twoDy < twoDx)
		{
			t2 = twoDy - twoDx;
			err = twoDy - dx;

			// Octant: 8
			if (x2 - x1 >= 0)
			{
				for (int x = x1 + 1; x <= x2; x++)
				{
					if (err >= 0)
					{
						err = err + t2;
						y = y - 1;
					}
					else
					{
						err = err + twoDy;
					}
					drawable->setPixel(x, y, color);
				}
			}
			// Octant: 5
			else
			{
				for (int x = x1 - 1; x >= x2; x--)
				{
					if (err >= 0)
					{
						err = err + t2;
						y = y - 1;
					}
					else
					{
						err = err + twoDy;
					}
					drawable->setPixel(x, y, color);
				}
			}
		}

		// If twoDy is greater than twoDx
		// Then we traverse on y to get the most pixels
		else
		{
			t2 = twoDx - twoDy;
			err = twoDx - dy;

			// Octant 7
			if (x2 - x1 >= 0)
			{
				for (int y = y1 - 1; y >= y2; y--)
				{
					if (err >= 0)
					{
						err = err + t2;
						x = x + 1;
					}
					else
					{
						err = err + twoDx;
					}
					drawable->setPixel(x, y, color);
				}
			}
			// Octant 6
			else
			{
				for (int y = y1 - 1; y >= y2; y--)
				{
					if (err >= 0)
					{
						err = err + t2;
						x = x - 1; // increase y by 1
					}
					else
					{
						err = err + twoDx;
					}
					drawable->setPixel(x, y, color);
				}
			}
		}
	}
}

//============================================================
void Client::lineDrawer_Alternate(int x1, int y1, int x2, int y2, int count, unsigned int color) {
	if (count % 2 == 0)
	{
		lineDrawer_DDA(x1, y1, x2, y2, color, 0xffffffff);
	}
	else
	{
		lineDrawer_Bresenham(x1, y1, x2, y2, color);
	}
}

//============================================================
void Client::antialias_LineRenderer(int x1, int y1, int x2, int y2, unsigned int color) {
	//TODO: Implement
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

			point newPoint_1 = transformationPoint(currentPoint_1, currentMatrix);
			point newPoint_2 = transformationPoint(currentPoint_2, currentMatrix);

			lineDrawer_DDA(newPoint_1.x, newPoint_1.y, newPoint_2.x, newPoint_2.y, calculate_LineColor(), calculate_LineColor());

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

			//Transform the point
			point newPoint_1 = transformationPoint(currentPoint_1, currentMatrix);
			point newPoint_2 = transformationPoint(currentPoint_2, currentMatrix);
			point newPoint_3 = transformationPoint(currentPoint_3, currentMatrix);

			point finalPoint_1 = transformationPoint(newPoint_1, worldCoords);
			point finalPoint_2 = transformationPoint(newPoint_2, worldCoords);
			point finalPoint_3 = transformationPoint(newPoint_3, worldCoords);

			triangle drawThis;
			drawThis.P1 = finalPoint_1;
			drawThis.P2 = finalPoint_2;
			drawThis.P3 = finalPoint_3;


			// Draw the newly transformed triangle
			orderedCoordinates(drawThis.P1.x, drawThis.P1.y,
				drawThis.P2.x, drawThis.P2.y,
				drawThis.P3.x, drawThis.P3.y);

			polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
				orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
				orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
			orderedPolygonCoordinates.clear();
			//polygonRenderer
		}
		else if (parsedSimpFile[i] == "wire")
		{
			//TODO
		}
		else if (parsedSimpFile[i] == "filled")
		{
			//polygonRenderer
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
	point Pc;
	Pc.x = 325;
	Pc.y = 325;

	point newPoint;
	newPoint.z = 1;
	newPoint.w = 1;
	int zToChange = 1;
	int shouldBeOne = 1;
	int someW = 1;

	newPoint.x = std::round(transformationMatrix.matrix[0][0] * pointToChange.x + transformationMatrix.matrix[0][1] * pointToChange.y + transformationMatrix.matrix[0][2] * zToChange + transformationMatrix.matrix[0][3] * shouldBeOne);
	newPoint.y = std::round(transformationMatrix.matrix[1][0] * pointToChange.x + transformationMatrix.matrix[1][1] * pointToChange.y + transformationMatrix.matrix[1][2] * zToChange + transformationMatrix.matrix[1][3] * shouldBeOne);
	newPoint.z = std::round(transformationMatrix.matrix[2][0] * pointToChange.x + transformationMatrix.matrix[2][1] * pointToChange.y + transformationMatrix.matrix[2][2] * zToChange + transformationMatrix.matrix[2][3] * shouldBeOne);
	someW = std::round(transformationMatrix.matrix[3][0] * pointToChange.x + transformationMatrix.matrix[3][1] * pointToChange.y + transformationMatrix.matrix[3][2] * zToChange + transformationMatrix.matrix[3][3] * shouldBeOne);
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
	return multiplyMatrices(rotation, currentMatrix);
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

	return multiplyMatrices(translate, currentMatrix);
}

//============================================================
// Scale function
iMatrix Client::transformationScale(double scaleX, double scaleY, double scaleZ, iMatrix currentMatrix)
{
	iMatrix scale;

	scale.matrix[0][0] = scaleX;
	scale.matrix[1][1] = scaleY;
	scale.matrix[2][2] = scaleZ;
	return multiplyMatrices(scale,currentMatrix);
}

//============================================================
/*void Client::zBuffer(int cx, int cy, triangle triangleToDraw)
{
	//double zbuff[650][650] = { 0 };

	//for (int i = 0; i < 650; i++)
	//{
	//	for (int j = 0; j < 650; j++)
	//	{
	//		zbuff[i][j] = 0;
	//	}
	//}
	int degreeToRotate = rand() % 120;

	point centrePoint;
	centrePoint.x = cx;
	centrePoint.y = cy;

	// Transform all three points
	point P1 = transformationRotate(degreeToRotate, triangleToDraw.P1, centrePoint);
	point P2 = transformationRotate(degreeToRotate, triangleToDraw.P2, centrePoint);
	point P3 = transformationRotate(degreeToRotate, triangleToDraw.P3, centrePoint);

	// Store this all into a triangle struct
	triangle drawThis;
	drawThis.P1 = P1;
	drawThis.P2 = P2;
	drawThis.P3 = P3;

	// Draw the newly transformed triangle
	orderedCoordinates(drawThis.P1.x, drawThis.P1.y,
					   drawThis.P2.x, drawThis.P2.y,
					   drawThis.P3.x, drawThis.P3.y);
	polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
	orderedPolygonCoordinates.clear();

	iMatrix rotation;

	// Let's set the rotational matrix to our specific degree
	rotation.matrix[0][0] = cos((numberOfDegrees * M_PI) / 180);
	rotation.matrix[1][0] = -sin((numberOfDegrees * M_PI) / 180);
	rotation.matrix[2][0] = 0;
	rotation.matrix[0][1] = sin((numberOfDegrees * M_PI) / 180);
	rotation.matrix[1][1] = cos((numberOfDegrees * M_PI) / 180);
	rotation.matrix[2][1] = 0;
	rotation.matrix[0][2] = 0;
	rotation.matrix[1][2] = 0;
	rotation.matrix[2][2] = 1;

	// Let's attempt to multiply the point onto the matrix
	// RotationMatrix * Point

	point newPoint;
	float shouldBeOne = 1;
	float newShouldBeOne = 0;

	int xToRotate = P.x - Pc.x;
	int yToRotate = P.y - Pc.y;

	newPoint.x = std::round(rotation.matrix[0][0] * xToRotate + rotation.matrix[1][0] * yToRotate + rotation.matrix[2][0] * shouldBeOne);
	newPoint.y = std::round(rotation.matrix[0][1] * xToRotate + rotation.matrix[1][1] * yToRotate + rotation.matrix[2][1] * shouldBeOne);
	newShouldBeOne = std::round(rotation.matrix[0][2] * xToRotate + rotation.matrix[1][2] * yToRotate + rotation.matrix[2][2] * shouldBeOne);

	newPoint.x += Pc.x;
	newPoint.y += Pc.y;

	return newPoint;
}*/

//============================================================
// All possible tests that are required by Assignment 2

//============================================================
void Client::panelTests2(const int pageNumber)
{
	int xRandom = 0;
	int yRandom = 0;

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
				//drawable->setPixel(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, 0xffffffff);
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
		// 1) Vertex 1
		vertex1.x = std::get<0>(panelCenter);
		vertex1.y = std::get<1>(panelCenter) - 275;
		// 2) Vertex 2
		vertex2.x = (275 * cos((30 * M_PI) / 180)) + std::get<0>(panelCenter);
		vertex2.y = (275 * sin((30 * M_PI) / 180)) + std::get<1>(panelCenter);
		// 3) Vertex 3
		vertex3.x = (275 * cos((150 * M_PI) / 180)) + std::get<0>(panelCenter);
		vertex3.y = (275 * sin((150 * M_PI) / 180)) + std::get<1>(panelCenter);

		// Let's store this triangle
		triangle caseThreeTriangle;
		caseThreeTriangle.P1 = vertex1;
		caseThreeTriangle.P2 = vertex2;
		caseThreeTriangle.P3 = vertex3;

		//zBuffer(std::get<0>(panelCenter), std::get<1>(panelCenter), caseThreeTriangle);
		for (int i = 0; i < 5; i++)
		{
			//zBuffer(std::get<0>(panelCenter), std::get<1>(panelCenter), caseThreeTriangle);
		}
		//drawable->setPixel(std::get<0>(panelCenter), std::get<1>(panelCenter) - 275, colourCase3);
		//drawable->setPixel(std::get<0>(vertex1), std::get<1>(vertex1), colourCase3);
		//drawable->setPixel(std::get<0>(vertex2), std::get<1>(vertex2), colourCase3);
		//drawable->setPixel(std::get<0>(vertex3), std::get<1>(vertex3), colourCase3);

		//transformationRotate(90, std::get<0>(vertex1), std::get<1>(vertex1));
		//transformationRotate(90, std::get<0>(vertex2), std::get<1>(vertex2));
		//transformationRotate(90, std::get<0>(vertex3), std::get<1>(vertex3));
		break;

	case 4:
		simpFileOpener(fileName);
		break;

	case 5:
		break;

	case 6:
		// [OPTIONAL] TODO: Implement positive attributes of polygon or line rendering
		break;

	default:
		break;
	}
}







//============================================================
// All possible tests that is required by the assignment 1
// Currently placed here.. because it outputs something
// Panel One: DDA
// Panel Two: Bresenham
// Panel Three: Alternating
// Panel Four: AntiAlias

//============================================================
void Client::starBurstTest(int centreX, int centreY, Panel whichPanel) {
	// Create 90 lines that are equally spaced in angle around the centre
	// i.e: 0 degress, 4 degrees, 8 degrees etc.

	for (int i = 0; i <= 90; i++)
	{
		int color = calculate_LineColor();
		std::tuple<float, float> linesToCreate = calculate_StarBurstAngles(centreX, centreY, i);
		switch (whichPanel) {

		case (ONE):
			lineDrawer_DDA(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffffffff, 0xffffffff);
			break;
		case (TWO):
			lineDrawer_Bresenham(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffffffff);
			break;
		case (THREE):
			lineDrawer_Alternate(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), i, 0xffffffff);
			break;
		case (FOUR):
			antialias_LineRenderer(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffffffff); // TODO
			break;
		}
	}
}

//============================================================
void Client::parallelogramTest(Panel whichPanel) {
	// TODO: Implement the "parallelogram" test
	const int xStart_1 = 20;
	const int yStart_1 = 80;
	const int xEnd_1 = 150;
	const int yEnd_1 = 150;
	
	const int xStart_2 = 160;
	const int yStart_2 = 270;
	const int xEnd_2 = 240;
	const int yEnd_2 = 40;

	int xPanel = 0;
	int yPanel = 0;

	for (int i = 0; i <= 50; i++)
	{
		int color = calculate_LineColor();
		switch (whichPanel) {
		case (ONE):
			xPanel = 50;
			yPanel = 50;
			lineDrawer_DDA(xPanel + xStart_1, 
						   yPanel + yStart_1 + i, 
						   xPanel + xEnd_1, 
						   yPanel + yEnd_1 + i, 0xffffffff, 0xffffffff);
			lineDrawer_DDA(xPanel + xStart_2 + i,
						   yPanel + yStart_2, 
						   xPanel + xEnd_2 + i, 
						   yPanel + yEnd_2, 0xffffffff, 0xffffffff);
			break;
		case (TWO):
			xPanel = 400;
			yPanel = 50;
			lineDrawer_Bresenham(xPanel + xStart_1,
				yPanel + yStart_1 + i,
				xPanel + xEnd_1,
				yPanel + yEnd_1 + i, 0xffffffff);
			lineDrawer_Bresenham(xPanel + xStart_2 + i,
				yPanel + yStart_2,
				xPanel + xEnd_2 + i,
				yPanel + yEnd_2, 0xffffffff);
			break;
		case(THREE):
			xPanel = 50;
			yPanel = 400;
			lineDrawer_Alternate(xPanel + xStart_1,
				yPanel + yStart_1 + i,
				xPanel + xEnd_1,
				yPanel + yEnd_1 + i, i, 0xffffffff);
			lineDrawer_Alternate(xPanel + xStart_2 + i,
				yPanel + yStart_2,
				xPanel + xEnd_2 + i,
				yPanel + yEnd_2, i, 0xffffffff);
			break;
		case(FOUR):
			xPanel = 400;
			yPanel = 400;
			antialias_LineRenderer(xPanel + xStart_1,
								   yPanel + yStart_1 + i,
								   xPanel + xEnd_1,
								   yPanel + yEnd_1 + i, 0xffffffff);
			antialias_LineRenderer(xPanel + xStart_2 + i,
								   yPanel + yStart_2,
								   xPanel + xEnd_2 + i,
								   yPanel + yEnd_2, 0xffffffff);
			break;
		}
	}

}

//============================================================
void Client::randomTest(int x0, int y0, int x1, int y1, int count) {

	int color = calculate_LineColor();
	int xPanel = 0;
	int yPanel = 0;

	// First Panel
	xPanel = 50;
	yPanel = 50;
	lineDrawer_DDA(xPanel + x0, 
				   yPanel + y0, 
				   xPanel + x1, 
				   xPanel + y1, color, 0xffffffff);
	
	// Second Panel
	xPanel = 400;
	yPanel = 50;
	lineDrawer_Bresenham(xPanel + x0, 
					     yPanel + y0,
						 xPanel + x1, 
						 yPanel + y1, color);

	// Third Panel
	xPanel = 50;
	yPanel = 400;
	lineDrawer_Alternate(xPanel + x0,
						 yPanel + y0,
						 xPanel + x1,
						 yPanel + y1, count, color);

	// Forth Panel
	xPanel = 400;
	yPanel = 400;
	antialias_LineRenderer(xPanel + x0,
						   yPanel + y0,
						   xPanel + x1,
						   yPanel + y1, color);
}

//============================================================
void Client::filledPolygonsTest(int centreX, int centreY, Panel whichPanel) {

	// Panel 3 stuff
	int xRandom = 0;
	int yRandom = 0;

	// Panel 4 stuff
	int xPanel = 400;
	int yPanel = 400;


		switch (whichPanel) {
		case(ONE):
			for (int i = 0; i <= 90; i++)
			{
				int color = calculate_LineColor();
				std::tuple<float, float> P3 = calculate_StarBurstAngles(centreX, centreY, i);
				std::tuple<float, float> P2 = calculate_StarBurstAngles(centreX, centreY, i + 1);
				orderedCoordinates(centreX, centreY, std::get<0>(P3), std::get<1>(P3), std::get<0>(P2), std::get<1>(P2));
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
								orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
								orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, color, calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
			break;
		case(TWO):
			// The panel starts at 400, 50
			// The panel ends at 700, 350
			// Total panel size: 300
			// Margins will be 15
			// 10 rows/columns make 30 per block
			// TODO: Fix sorting order

			grid gridSetupNormal[10][10];

			// This stores the related points for the grid
			for (int i = 0; i <= 9; i++) {
				for (int j = 0; j <= 9; j++) {
					gridSetupNormal[i][j].x = 415 + 30 * j;
					gridSetupNormal[i][j].y = 65 + 30 * i;
					//drawable->setPixel(gridSetup[i][j].x, gridSetup[i][j].y, 0xffffffff);
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
		case (THREE):
			grid gridSetupRandom[10][10];
			// This stores the related points for the grid
			for (int i = 0; i <= 9; i++) {
				for (int j = 0; j <= 9; j++) {
					gridSetupRandom[i][j].x = 65 + 30 * j;
					gridSetupRandom[i][j].y = 415 + 30 * i;

					xRandom = (rand() % 12) - 12;
					yRandom = (rand() % 12) - 12;

					gridSetupRandom[i][j].x = gridSetupRandom[i][j].x + xRandom;
					gridSetupRandom[i][j].y = gridSetupRandom[i][j].y + yRandom;
					drawable->setPixel(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, 0xffffffff);
				}
			}

			// Render these triangles
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					orderedCoordinates(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y,
									   gridSetupRandom[i + 1][j + 1].x, gridSetupRandom[i + 1][j + 1].y,
						               gridSetupRandom[i][j + 1].x, gridSetupRandom[i][j + 1].y);
					polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
									orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
									orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
					orderedPolygonCoordinates.clear();

					orderedCoordinates(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y,
									   gridSetupRandom[i + 1][j + 1].x, gridSetupRandom[i + 1][j + 1].y,
									   gridSetupRandom[i + 1][j].x, gridSetupRandom[i + 1][j].y);
					polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
									orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
									orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
					orderedPolygonCoordinates.clear();
				}
			}
			break;
		case(FOUR):
			srand(time(NULL));
			for (int i = 0; i <= 20; i++)
			{
				int P1_x = rand() % 299;
				int P1_y = rand() % 299;

				int P2_x = rand() % 299;
				int P2_y = rand() % 299;

				int P3_x = rand() % 299;
				int P3_y = rand() % 299;

				orderedCoordinates(xPanel + P1_x, yPanel + P1_y, 
								   xPanel + P2_x, yPanel + P2_y,
								   xPanel + P3_x, yPanel + P3_y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
								orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
								orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
		}
}

//============================================================
void Client::alteredFilledPolygonsTest(int centreX, int centreY, Panel whichPanel) {
	// Panel 3 stuff
	int xRandom = 0;
	int yRandom = 0;

	// Panel 4 stuff
	int xPanel = 400;
	int yPanel = 400;

	int r = 255; //rand() % 255;
	int g = 255; //rand() % 255;
	int b = 255;// rand() % 255;
	double opacity = 0.14;
	switch (whichPanel) {
	case(ONE):
		for (int i = 0; i <= 90; i++)
		{
			std::tuple<float, float> P3 = calculate_StarBurstAngles(centreX, centreY, i);
			std::tuple<float, float> P2 = calculate_StarBurstAngles(centreX, centreY, i + 1);
			orderedCoordinates(centreX, centreY, std::get<0>(P3), std::get<1>(P3), std::get<0>(P2), std::get<1>(P2));
			polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
				orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
				orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, 0xffffffff, calculate_LineColor(), calculate_LineColor());
			orderedPolygonCoordinates.clear();
		}
		break;
	case(TWO):
		// The panel starts at 400, 50
		// The panel ends at 700, 350
		// Total panel size: 300
		// Margins will be 15
		// 10 rows/columns make 30 per block
		// TODO: Fix sorting order

		grid gridSetupNormal[10][10];

		// This stores the related points for the grid
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				gridSetupNormal[i][j].x = 415 + 30 * j;
				gridSetupNormal[i][j].y = 65 + 30 * i;
				//drawable->setPixel(gridSetup[i][j].x, gridSetup[i][j].y, 0xffffffff);
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
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, 0xffffffff, calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();

				orderedCoordinates(gridSetupNormal[i][j].x, gridSetupNormal[i][j].y,
					gridSetupNormal[i + 1][j + 1].x, gridSetupNormal[i + 1][j + 1].y,
					gridSetupNormal[i + 1][j].x, gridSetupNormal[i + 1][j].y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, 0xffffffff, calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
		}
		break;
	case (THREE):
		grid gridSetupRandom[10][10];
		// This stores the related points for the grid
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				gridSetupRandom[i][j].x = 65 + 30 * j;
				gridSetupRandom[i][j].y = 415 + 30 * i;

				xRandom = (rand() % 12) - 12;
				yRandom = (rand() % 12) - 12;

				gridSetupRandom[i][j].x = gridSetupRandom[i][j].x + xRandom;
				gridSetupRandom[i][j].y = gridSetupRandom[i][j].y + yRandom;
				//drawable->setPixel(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y, 0xffffffff);
			}
		}

		// Render these triangles
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				orderedCoordinates(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y,
					gridSetupRandom[i + 1][j + 1].x, gridSetupRandom[i + 1][j + 1].y,
					gridSetupRandom[i][j + 1].x, gridSetupRandom[i][j + 1].y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();

				orderedCoordinates(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y,
					gridSetupRandom[i + 1][j + 1].x, gridSetupRandom[i + 1][j + 1].y,
					gridSetupRandom[i + 1][j].x, gridSetupRandom[i + 1][j].y);
				polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
					orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
					orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
		}
		break;
	case(FOUR):
		srand(time(NULL));
		for (int i = 0; i <= 20; i++)
		{
			int P1_x = rand() % 299;
			int P1_y = rand() % 299;

			int P2_x = rand() % 299;
			int P2_y = rand() % 299;

			int P3_x = rand() % 299;
			int P3_y = rand() % 299;

			orderedCoordinates(xPanel + P1_x, yPanel + P1_y,
				xPanel + P2_x, yPanel + P2_y,
				xPanel + P3_x, yPanel + P3_y);
			polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
				orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
				orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor(), calculate_LineColor(), calculate_LineColor());
			orderedPolygonCoordinates.clear();
		}
	}
}

void Client::panelTests1(const int pageNumber) {

	// PanelOne: (50,50) & (350,350)
	// PanelTwo: (400,50) & (700,350)
	// PanelThree: (50, 400) & (350,700)
	// PanelFour: (400,400) & (700,700)
	const std::tuple<int, int> panelOne = calculate_PanelCentre(50, 50, 350, 350);
	const std::tuple<int, int> panelTwo = calculate_PanelCentre(400, 50, 700, 350);
	const std::tuple<int, int> panelThree = calculate_PanelCentre(50, 400, 350, 700);
	const std::tuple<int, int> panelFour = calculate_PanelCentre(400, 400, 700, 700);

	switch (pageNumber) {
		
	case 1:
		starBurstTest(std::get<0>(panelOne),std::get<1>(panelOne), ONE);
		starBurstTest(std::get<0>(panelTwo), std::get<1>(panelTwo), TWO);
		starBurstTest(std::get<0>(panelThree), std::get<1>(panelThree), THREE);
		starBurstTest(std::get<0>(panelFour), std::get<1>(panelFour), FOUR);
		break;
	
	case 2:
		parallelogramTest(ONE);
		parallelogramTest(TWO);
		parallelogramTest(THREE);
		parallelogramTest(FOUR);
		break;
	
	case 3:
		srand(time(NULL));
		for (int i = 0; i <= 30; i++)
		{
			int beginRandomX = rand() % 299;
			int beginRandomY = rand() % 299;
			int endRandomX = rand() % 299;
			int endRandomY = rand() % 299;
			randomTest(beginRandomX, beginRandomY, endRandomX, endRandomY, i);
		}
		break;

	case 4:
		filledPolygonsTest(std::get<0>(panelOne), std::get<1>(panelOne), ONE);
		filledPolygonsTest(std::get<0>(panelTwo), std::get<1>(panelTwo), TWO);
		filledPolygonsTest(std::get<0>(panelThree), std::get<1>(panelThree), THREE);
		filledPolygonsTest(std::get<0>(panelFour), std::get<1>(panelFour), FOUR);
		break;
		
	case 5:
		alteredFilledPolygonsTest(std::get<0>(panelOne), std::get<1>(panelOne), ONE);
		alteredFilledPolygonsTest(std::get<0>(panelTwo), std::get<1>(panelTwo), TWO);
		alteredFilledPolygonsTest(std::get<0>(panelThree), std::get<1>(panelThree), THREE);
		alteredFilledPolygonsTest(std::get<0>(panelFour), std::get<1>(panelFour), FOUR);
		break;

	case 6:
		// [OPTIONAL] TODO: Implement positive attributes of polygon or line rendering
		break;

	default:
		break;
	}
}


