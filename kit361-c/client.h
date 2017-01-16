#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"

class Client : public PageTurner
{
public:
    Client(Drawable *drawable);
    void nextPage();

private:
    Drawable *drawable;
    void draw_rect(int x1, int y1, int x2, int y2, unsigned int color);

	// TODO: Add stubs for each panel
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
	void panelTests(const int currentPage);
};



#endif // CLIENT_H
