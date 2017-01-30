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
		draw_rect( 50,  50, 350, 350, 0x00000000);
		draw_rect(400, 50, 700, 350, 0x00000000);
		draw_rect(50, 400, 350, 700, 0x00000000);
		draw_rect(400, 400, 700, 700, 0x00000000);
        drawable->updateScreen();   // you must call this to make the display change.
        break;
    case 2:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 350, 350, 0x00000000);
		draw_rect(400, 50, 700, 350, 0x00000000);
		draw_rect(50, 400, 350, 700, 0x00000000);
		draw_rect(400, 400, 700, 700, 0x00000000);
		drawable->updateScreen();
        break;
    case 3:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 350, 350, 0x00000000);
		draw_rect(400, 50, 700, 350, 0x00000000);
		draw_rect(50, 400, 350, 700, 0x00000000);
		draw_rect(400, 400, 700, 700, 0x00000000);
		drawable->updateScreen();
        break;
    case 4:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 350, 350, 0x00000000);
		draw_rect(400, 50, 700, 350, 0x00000000);
		draw_rect(50, 400, 350, 700, 0x00000000);
		draw_rect(400, 400, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
	case 5:
		draw_rect(0, 0, 750, 750, 0xffffffff);
		draw_rect(50, 50, 350, 350, 0x00000000);
		draw_rect(400, 50, 700, 350, 0x00000000);
		draw_rect(50, 400, 350, 700, 0x00000000);
		draw_rect(400, 400, 700, 700, 0x00000000);
		drawable->updateScreen();
		break;
    default:
        draw_rect(0, 0, 750, 750, 0xffffffff);
        draw_rect(400, 400, 700, 700, 0xff00ff40);
        drawable->updateScreen();
    }
	panelTests(pageNumber); // Test the specific functionality of each panel on the specific page;
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
int Client::calculate_LineColor()
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	int color = (0xff << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return color;
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
void Client::lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color) {

	// We want to find our y = mx + b components
	const float dx = x2 - x1;
	const float dy = y2 - y1;
	float m = dy / dx;
	float b = y1 - m*x1;

	// This will determine what case we are in
	bool slopeLessThanOne = true;

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
			for (int x = x1; x < x2; x++)
			{
				calculatedY = m*x + b;
				drawable->setPixel(x, std::round(calculatedY), color);
			}
		}
		// CASE 1b
		else
		{
			for (int x = x1; x > x2; x--)
			{
				calculatedY = m*x + b;
				drawable->setPixel(x, std::round(calculatedY), color);
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
			for (int y = y1; y < y2; y++)
			{
				calculatedX = (y - b) / m;
				drawable->setPixel(std::round(calculatedX), y, color);
			}
		}
		// CASE 2b
		else
		{
			for (int y = y1; y > y2; y--)
			{
				calculatedX = (y - b) / m;
				drawable->setPixel(std::round(calculatedX), y, color);
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
		lineDrawer_DDA(x1, y1, x2, y2, color);
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
void Client::polygonRenderer(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color)
{
	float m_x1y1_x3y3 = (y3 - y1) / (x3 - x1); // Highest P -> Smallest P
	float m_x2y2_x3y3 = (y3 - y2) / (x3 - x2); // Middle P -> Smallest P
	float b_x1y1_x3y3 = y1 - m_x1y1_x3y3*(x1); // Slope for Lowest P -> Smallest P
	float b_x2y2_x3y3 = y2 - m_x2y2_x3y3*(x2); // Slope for Middle P -> Smallest P

	int xleft = x1; // Start from highest Y
	int xright = x1; // Start from highest Y

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
			for (int y = y1; y >= y2; y--)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
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
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
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
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);

			}
		}
		// The vertical line is on the right
		else
		{
			for (int y = y3; y <= y2; y++)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);

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
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
			}

			// This will loop from Point 2 to Point 3
			for (int y = y2; y >= y3; y--)
			{
				xleft = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				xright = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
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
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
			}

			// This will loop from Point 2 to Point 3
			for (int y = y2; y >= y3; y--)
			{
				xleft = (y - b_x2y2_x3y3) / m_x2y2_x3y3;
				xright = (y - b_x1y1_x3y3) / m_x1y1_x3y3;
				lineDrawer_Bresenham(std::round(xleft), y, std::round(xright), y, color);
			}
		}
	}
}

//============================================================
// All possible tests that is required by the assignment
// Currently placed here.. because it outputs something
// TODO: Figure out how to output the tests properly
// 
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
			lineDrawer_DDA(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffffffff);
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
						   yPanel + yEnd_1 + i, 0xffffffff);
			lineDrawer_DDA(xPanel + xStart_2 + i,
						   yPanel + yStart_2, 
						   xPanel + xEnd_2 + i, 
						   yPanel + yEnd_2, 0xffffffff);
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
				   xPanel + y1, color);
	
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
								orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, 0xffffffff);
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
									orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor());
					orderedPolygonCoordinates.clear();

					orderedCoordinates(gridSetupNormal[i][j].x, gridSetupNormal[i][j].y,
									   gridSetupNormal[i + 1][j + 1].x, gridSetupNormal[i + 1][j + 1].y,
									   gridSetupNormal[i + 1][j].x, gridSetupNormal[i + 1][j].y);
					polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
						orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
						orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor());
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
									orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor());
					orderedPolygonCoordinates.clear();

					orderedCoordinates(gridSetupRandom[i][j].x, gridSetupRandom[i][j].y,
									   gridSetupRandom[i + 1][j + 1].x, gridSetupRandom[i + 1][j + 1].y,
									   gridSetupRandom[i + 1][j].x, gridSetupRandom[i + 1][j].y);
					polygonRenderer(orderedPolygonCoordinates[0].x, orderedPolygonCoordinates[0].y,
									orderedPolygonCoordinates[1].x, orderedPolygonCoordinates[1].y,
									orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor());
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
								orderedPolygonCoordinates[2].x, orderedPolygonCoordinates[2].y, calculate_LineColor());
				orderedPolygonCoordinates.clear();
			}
		}
}

//============================================================
void Client::alteredFilledPolygonsTest(Panel whichPanel) {
	// TODO: Implement altered version of filled polygons
}

void Client::panelTests(const int pageNumber) {

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
		alteredFilledPolygonsTest(ONE);
		alteredFilledPolygonsTest(TWO);
		alteredFilledPolygonsTest(THREE);
		alteredFilledPolygonsTest(FOUR);
		break;

	case 6:
		// [OPTIONAL] TODO: Implement positive attributes of polygon or line rendering
		break;

	default:
		break;
	}
}


