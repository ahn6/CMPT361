#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include <tuple>
#include <iostream>
#include <cmath>
#include <ctime>

typedef enum {ONE, TWO, THREE, FOUR} Panel;
typedef enum {OctOne, OctTwo, OctThree, OctFour, OctFive, OctSix, OctSeven, OctEight} Octant;
class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();

	// Class Helper Functions
	
	//============================================================
	// Calcuate the centre of each panel
	//
	// Returns (x,y) as the centre of the pixel
	//============================================================
	std::tuple<int, int> calculate_PanelCentre(int x1, int y1, int x2, int y2);

	//============================================================
	// This will calculate the line endpoints for the starburst test
	//
	// Returns the endpoints of the specific angle (round(x),round(y))
	//============================================================
	std::tuple<float, float> calculate_StarBurstAngles(int centreX, int centreY, int count);

	//============================================================
	// Calcuate the color values for the lines
	//
	//============================================================
	int calculate_LineColor();

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Digital Differential Analyzer
	//
	// The DDA uses y = mx + b as its main calculation for plotting
	// There happens to be 2 major cases with 2 sub cases
	// 1) If slope is less than 1
	//    We want to increment the next pixel by calculating y and 
	//    incrementing x by 1
	//    a) If dx is > 0, this means we know that the endpoint X is greater than the centre X
	//		 which means we can do our Y calculation while increasing x to the endpoint.
	//		 ex: centre (200,200), endpoint (300,x(300)) - Keep increasing X and calculating Y
	//    b) If dx is < 0, this means we know that the endpoint X is less than the centre X
	//       which means we can do our Y calculation while decreasing x to the endpoint.
	//		 ex: centre(200,200), endpoint (-300,x(-300)) - Keep decreasing X and calculating Y
	//
	// 2) if our slope is greater than one
	//    We cannot do increments on x and more because if we have a very steep slope, we will miss pxiels
	//    So we want to increment the next pixel by calculating x and incrementing y by 1
	//    a) If dy is > 0, this means we know that the endpoint Y is greater than the centre Y
	//		 which means we can do our X calculation while increasing Y to the endpoint.
	//		 ex: centre (200,200), endpoint (y(300),300) - Keep increasing Y and calculating X
	//    b) If dy is < 0, this means we know that the endpoint Y is less than the centre Y
	//		 which means we can do our X calculation while decreasing Y to the endpoint.
	//		 ex: centre (200,200), endpoint (y(-300),-300) - Keep decreasing Y and calculating X
	//============================================================
	void lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Bresenham's Algorithm
	//
	// Bresenham algorithm is simply taking decision parameters (t2, err)
	// and deciding whether to increment x alone or y & x
	// In simple terms, if the err which is calculated by 2*dy - dx
	// 1) err < 0 then err = err + 2*dy (Only increment x)
	// 2) err > 0 then err = err + t2 (x and y increment)
	// 
	// The method that is implemented considers all octants
	// which is split into 2 major parts
	// 1) If (y2 - y1 > 0) --> Octants: 1 2 3 4
	// 2) if (y2 - y1 < 0) --> Octants: 5 6 7 8
	// Lines in each octant are then calculated and drawned based on 
	// the incremental steps (dx or dy) and where the end points and 
	// start points lie in the the panel/
	//============================================================
	void lineDrawer_Bresenham(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Digital Differential Analyzer / Bresenham's Algorithm Alternating
	//
	// Just a combination of both DDA and Bresenham's algorithm
	// First line will always be DDA then Bresenham
	// This is determined by caching the number of lines being drawn
	// count % 2
	//============================================================
	void lineDrawer_Alternate(int x1, int y1, int x2, int y2, int count, unsigned int color);

	//============================================================
	// Antialias Line Renderer
	//============================================================
	void antialias_LineRenderer(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Polygon Renderer
	// This class helper function will create filled polygons
	// based on the bresenham line drawing algorithm
	//============================================================
	void polygonRenderer(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color);

	//============================================================
	// Possible Tests
	//============================================================

	//============================================================
	// Main interface to interact with the tests
	void panelTests(const int currentPage);

	//============================================================
	void starBurstTest(int centreX, int centreY, Panel whichPanel);

	//============================================================
	void parallelogramTest(Panel whichPanel);

	//============================================================
	void randomTest(int x0, int y0, int x1, int y1, int count);

	//============================================================
	void filledPolygonsTest(int centreX, int centreY, Panel whichPanel);

	//============================================================
	void alteredFilledPolygonsTest(Panel whichPanel);




};



#endif // CLIENT_H
