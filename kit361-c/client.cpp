#include <iostream>
#include <cmath>
#include "client.h"

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
}

void Client::draw_rect(int x1, int y1, int x2, int y2, unsigned int color) {
    for(int x = x1; x<x2; x++) {
        for(int y=y1; y<y2; y++) {
            drawable->setPixel(x, y, color);
        }
    }
}

//============================================================
// How does DDA work?
// 1) Plots initial points
// 2) (x, round(y)) = ROUND(y)

void Client::lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color) {

	//TODO: Implement
	const int dx = x2 - x1;
	const int dy = y2 - y1;
	float y = y1;

	// This is only for slope less than one. (Does this mean in octant I?)
	float Yincrement = std::abs(dy) / std::abs(dx);
	for (int x = x1; x < x2; x++)
	{
		drawable->setPixel(x, std::round(y), 0xffffffff);
		y = y + Yincrement;
	}
	
	// What happens if slope is greater than one.
}

//============================================================
void Client::lineDrawer_Bresenham(int x1, int y1, int x2, int y2, unsigned int color) {

	//TODO: Implement
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

void Client::panelTests(const int pageNumber) {

	// TODO: Create seperate functions that does all testing
	switch (pageNumber) {
		
	case 1:
		// TODO: Implement "starburst" test
		// Determine the center of the each panel
		// 1: std::tuple<int, int, int, int> centerOfPanels()? Do we need to show our calculations through coding
		// 2: Calculate the centers of each panel on paper then set them as constants [Easier]
		break;
	
	case 2:
		// TODO: Implement the "parallelogram" test
		break;
	
	case 3:
		// TODO: Implement the "random" test
		break;

	case 4:
		// TODO: Implement filled polygons
		break;
		
	case 5:
		// TODO: Implement altered version of filled polygons
		break;

	case 6:
		// [OPTIONAL] TODO: Implement positive attributes of polygon or line rendering
		break;

	default:
		break;
	}
}


