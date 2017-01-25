#include "client.h"

# define M_PI           3.14159265358979323846  /* pi */

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
	return std::make_tuple(length, height);
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
			lineDrawer_DDA(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), color);
			break;
		case (TWO):
			lineDrawer_Bresenham(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), color);
			break;
		case (THREE):
			lineDrawer_Alternate(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), i, color);
			break;
		case (FOUR):
			antialias_LineRenderer(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), color); // TODO
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
						   yPanel + yEnd_1 + i, color);
			lineDrawer_DDA(xPanel + xStart_2 + i,
						   yPanel + yStart_2, 
						   xPanel + xEnd_2 + i, 
						   yPanel + yEnd_2, color);
			break;
		case (TWO):
			xPanel = 400;
			yPanel = 50;
			lineDrawer_Bresenham(xPanel + xStart_1,
				yPanel + yStart_1 + i,
				xPanel + xEnd_1,
				yPanel + yEnd_1 + i, color);
			lineDrawer_Bresenham(xPanel + xStart_2 + i,
				yPanel + yStart_2,
				xPanel + xEnd_2 + i,
				yPanel + yEnd_2, color);
			break;
		case(THREE):
			xPanel = 50;
			yPanel = 400;
			lineDrawer_Alternate(xPanel + xStart_1,
				yPanel + yStart_1 + i,
				xPanel + xEnd_1,
				yPanel + yEnd_1 + i, i, color);
			lineDrawer_Alternate(xPanel + xStart_2 + i,
				yPanel + yStart_2,
				xPanel + xEnd_2 + i,
				yPanel + yEnd_2, i, color);
			break;
		case(FOUR):
			xPanel = 400;
			yPanel = 400;
			antialias_LineRenderer(xPanel + xStart_1,
								   yPanel + yStart_1 + i,
								   xPanel + xEnd_1,
								   yPanel + yEnd_1 + i, color);
			antialias_LineRenderer(xPanel + xStart_2 + i,
								   yPanel + yStart_2,
								   xPanel + xEnd_2 + i,
								   yPanel + yEnd_2, color);
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
void Client::filledPolygonsTest(Panel whichPanel) {
	// TODO: Implement filled polygons
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
		filledPolygonsTest(ONE);
		filledPolygonsTest(TWO);
		filledPolygonsTest(THREE);
		filledPolygonsTest(FOUR);
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


