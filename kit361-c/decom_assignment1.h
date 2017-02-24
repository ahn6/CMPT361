/*	//============================================================
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
	// start points lie in the the panel
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
	// DECOMISSIONED Possible Tests for Assignment 1
	//============================================================

	//============================================================
	// Main interface to interact with the tests
	void panelTests1(const int currentPage);

	//============================================================
	void starBurstTest(int centreX, int centreY, Panel whichPanel);

	//============================================================
	void parallelogramTest(Panel whichPanel);

	//============================================================
	void randomTest(int x0, int y0, int x1, int y1, int count);

	//============================================================
	void filledPolygonsTest(int centreX, int centreY, Panel whichPanel);

	//============================================================
	void alteredFilledPolygonsTest(int centreX, int centreY, Panel whichPanel);*/