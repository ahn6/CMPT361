#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include <tuple>

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
	std::tuple<float, float> Client::calculate_starBurstAngles(int centreX, int centreY, int count);

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
	//============================================================
	void lineDrawer_Bresenham(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Digital Differential Analyzer / Bresenham's Algorithm Alternating
	//============================================================
	void lineDrawer_Alternate(int x1, int y1, int x2, int y2, int count, unsigned int color);

	//============================================================
	// Antialias Line Renderer
	//============================================================
	void antialias_LineRenderer(int x1, int y1, int x2, int y2, unsigned int color);

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
	void randomTest(Panel whichPanel);

	//============================================================
	void filledPolygonsTest(Panel whichPanel);

	//============================================================
	void alteredFilledPolygonsTest(Panel whichPanel);




};



#endif // CLIENT_H
