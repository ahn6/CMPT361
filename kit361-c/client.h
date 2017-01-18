#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include <tuple>

typedef enum {ONE, TWO, THREE, FOUR} Panel;
class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();

	// Helper Functions
	
	//============================================================
	// Calcuate the centre of each panel
	//
	// Returns (x,y) as the centre of the pixel
	//============================================================
	std::tuple<int, int> calculate_PanelCentre(int x1, int y1, int x2, int y2);

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);

	// TODO [COMPLETE]: Add stubs for each panel
	// DDA
	// Bresenham's
	// Alternating line drawers between DDA, Bresham's
	// Antialias Line Renderer

	//============================================================
	// Digital Differential Analyzer
	//============================================================
	void lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Bresenham's Algorithm
	//============================================================
	void lineDrawer_Bresenham(int x1, int y1, int x2, int y2, unsigned int color);

	//============================================================
	// Digital Differential Analyzer / Bresenham's Algorithm Alternating
	//============================================================
	void lineDrawer_Alternate(int x1, int y1, int x2, int y2, unsigned int color);

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
