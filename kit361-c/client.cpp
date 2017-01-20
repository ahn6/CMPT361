#include <iostream>
#include <cmath>
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
std::tuple<float, float> Client::calculate_starBurstAngles(int centreX, int centreY, int count)
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
// This will determine the specific octant we are currently in
// based on the coordinates given
//Returns the specific Octant
//============================================================
Octant Client::calculate_Octant(int dx, int dy)
{
	if ((std::abs(dy) / std::abs(dx)) > 1)
	{
		if (dx > 0)
		{
			if (dy > 0)
			{
				return OctTwo;
			}
			else
			{
				return OctSeven;
			}
		}
		else
		{
			if (dy > 0)
			{
				return OctThree;
			}
			else
			{
				return OctSix;
			}
		}
	}
	else
	{
		if (dx > 0)
		{
			if (dy > 0)
			{
				return OctOne;
			}
			else
			{
				return OctEight;
			}
		}
		else
		{
			if (dy > 0)
			{
				return OctFour;
			}
			else
			{
				return OctFive;
			}
		}
	}
}

// This will convert the given coordinate based on the octant
//Returns the converted coordinates (x,y)
std::tuple<int, int> Client::convertToOctantOne(int convertedX, int convertedY, Octant whichOctant) {
	switch (whichOctant) {
	case (OctOne):
		std::make_tuple(convertedX, convertedY);
		break;
	case(OctTwo):
		return std::make_tuple(convertedY, convertedX);
		break;
	case(OctThree):
		return std::make_tuple(convertedY, convertedX*(-1));
		break;
	case(OctFour):
		std::make_tuple(convertedX*(-1), convertedY);
		break;
	case(OctFive):
		return std::make_tuple(convertedX*(-1), convertedY*(-1));
		break;
	case(OctSix):
		return std::make_tuple(convertedY*(-1), convertedX*(-1));
		break;
	case(OctSeven):
		return std::make_tuple(convertedY*(-1), convertedX);
		break;
	case(OctEight):
		return std::make_tuple(convertedX, convertedY*(-1));
		break;
	default:
		break;
	}
	// Should not reach here
	return std::make_tuple(convertedX, convertedY);
}

//============================================================
// This will convert the given coordinate from Octant One to its respected octant
//
//Returns the converted coordinates (x,y)
std::tuple<int, int> Client::convertFromOctantOne(int convertedX, int convertedY, Octant whichOctant) {
	
	switch (whichOctant) {
	case (OctOne):
		std::make_tuple(convertedX, convertedY);
		break;
	case(OctTwo):
		return std::make_tuple(convertedY, convertedX);
		break;
	case(OctThree):
		return std::make_tuple(convertedY*(-1), convertedX);
		break;
	case(OctFour):
		std::make_tuple(convertedX*(-1), convertedY);
		break;
	case(OctFive):
		return std::make_tuple(convertedX*(-1), convertedY*(-1));
		break;
	case(OctSix):
		return std::make_tuple(convertedY*(-1), convertedX*(-1));
		break;
	case(OctSeven):
		return std::make_tuple(convertedY, convertedX*(-1));
		break;
	case(OctEight):
		return std::make_tuple(convertedX, convertedY*(-1));
		break;
	default:
		break;
	}
	// Should not reach here
	return std::make_tuple(convertedX, convertedY);
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
	// To determine the octants, there should be 11 per octant + 2 edage cases
	// 11 * 8 + 2 = 90 lines
	//TODO: Implement
	int dx = x2 - x1; 
	int dy = y2 - y1;
	Octant whichOctant = calculate_Octant(dx, dy);
	// Characteristics of Octant I
	// 1) Will always have a slope less  than 1
	// 2) Beginning point x < Endpoint x
	// 3) Beginning point y > Endpoint y
	std::tuple <int, int> convertedCoordinates = convertToOctantOne(x2, y2, whichOctant);

	int tempDx = std::get<0>(convertedCoordinates) - x1;
	int tempDy = std::get<1>(convertedCoordinates) - y1;

	const int twoDx = 2 * tempDx;
	const int twoDy = 2 * tempDy;

	const int t2 = twoDy - twoDx;
	int error = twoDy - dx;

	int y = y1;
	drawable->setPixel(x1, y, color);
	for (int x = x1 + 1; x < x2; x++)
	{
		if (error >= 0)
		{
			error = error + t2;
			y = y + 1; // increase y by 1
		}
		else
		{
			error = error + twoDy;
		}
		std::tuple <int, int> revertedCoordinates = convertToOctantOne(x, y, whichOctant);
		drawable->setPixel(std::get<0>(revertedCoordinates), std::get<1>(revertedCoordinates), color);
	}

}

//============================================================
void Client::lineDrawer_Alternate(int x1, int y1, int x2, int y2, unsigned int color) {

	//TODO: Implement
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
	// TODO: Implement "starburst" test
	// TODO: Figure out how far out the lines of the starburst should go
	// Start at centre
	//
	// Create 90 lines that are equally spaced in angle around the centre
	// i.e: 0 degress, 4 degrees, 8 degrees etc.
	for (int i = 0; i <= 90; i++)
	{
		std::tuple<float, float> linesToCreate = calculate_starBurstAngles(centreX, centreY, i);
		switch (whichPanel) {

		case (ONE):
			lineDrawer_DDA(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffccccff);
			break;

		case (TWO):
			lineDrawer_Bresenham(centreX, centreY, std::get<0>(linesToCreate), std::get<1>(linesToCreate), 0xffccccff);
			break;
		}
	}
}

//============================================================
void Client::parallelogramTest(Panel whichPanel) {
	// TODO: Implement the "parallelogram" test
}

//============================================================
void Client::randomTest(Panel whichPanel) {
	// TODO: Implement the "random" test
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

	// TODO: Create seperate functions that does all testing

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
		// Determine the center of the each panel
		// 1: std::tuple<int, int> centerOfPanels()? Do we need to show our calculations through coding
		// 2: Calculate the centers of each panel on paper then set them as constants [Easier]

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
		randomTest(ONE);
		randomTest(TWO);
		randomTest(THREE);
		randomTest(FOUR);
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


