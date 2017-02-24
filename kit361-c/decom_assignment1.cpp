/*//============================================================
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
}*/

