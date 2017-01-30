Author: Aaron Nguyen 301254559
Last Modified: January 30 2017

CMPT 361 - Assignment 1

//=======================
// Compile Notes
//=======================

// Windows Operating System
The attached code was implemented on Microsoft Visual Studio 2015 with the Qt VS add-on, downloaded from: https://marketplace.visualstudio.com/items?itemName=havendv.QtPackage

// Linux Operating System
The attached code was also tested on the Linux Operating system with QtCreater (Version is same as CSIL computers).

1) Open the qtqt.pro project file
2) Some of the methods in this project requires C++11 in Qt Creator. I've made sure that this project file does include C++11, but in the event that it is not included..
   a) Open the qtqt.pro in the text editor
   b) Somewhere near the top (ex: Under "TEMPLATE = app") include the following "CONFIG += c++11"
   c) Save & recompile
3) Add all the headers and .cpp files
4) Run
//===============================================================================================


//=======================
// Implementation
//=======================

//-----------------------
// Algorithms
//-----------------------

// DDA Algorithm
The DDA uses y = mx + b as its main calculation for plotting
There happens to be 2 major cases with 2 sub cases
1) If slope is less than 1
   We want to increment the next pixel by calculating y and incrementing x by 1
		a) If dx is > 0, this means we know that the endpoint X is greater than the centre X
		which means we can do our Y calculation while increasing x to the endpoint.
		ex: centre (200,200), endpoint (300,x(300)) - Keep increasing X and calculating Y
	
		b) If dx is < 0, this means we know that the endpoint X is less than the centre X
		which means we can do our Y calculation while decreasing x to the endpoint.
		ex: centre(200,200), endpoint (-300,x(-300)) - Keep decreasing X and calculating Y
2) if our slope is greater than one
   We cannot do increments on x and more because if we have a very steep slope, we will miss pxiels
   So we want to increment the next pixel by calculating x and incrementing y by 1
		a) If dy is > 0, this means we know that the endpoint Y is greater than the centre Y
		which means we can do our X calculation while increasing Y to the endpoint.
		ex: centre (200,200), endpoint (y(300),300) - Keep increasing Y and calculating X
		b) If dy is < 0, this means we know that the endpoint Y is less than the centre Y
		which means we can do our X calculation while decreasing Y to the endpoint.
		ex: centre (200,200), endpoint (y(-300),-300) - Keep decreasing Y and calculating X
		
// Bresenham
Bresenham algorithm is simply taking decision parameters (t2, err)
and deciding whether to increment x alone or y & x
In simple terms, if the err which is calculated by 2*dy - dx
	1) err < 0 then err = err + 2*dy (Only increment x)
	2) err > 0 then err = err + t2 (x and y increment)
	
The method that is implemented considers all octants which is split into 2 major parts
	1) If (y2 - y1 > 0) --> Octants: 1 2 3 4
	2) if (y2 - y1 < 0) --> Octants: 5 6 7 8
	Lines in each octant are then calculated and drawned based on 
	the incremental steps (dx or dy) and where the end points and 
	start points lie in the the panel
	
// Digital Differential Analyzer / Bresenham's Algorithm Alternating
Just a combination of both DDA and Bresenham's algorithm. First line will always be DDA then Bresenham
This is determined by caching the number of lines being drawn. count % 2

// AntiAlias


//-----------------------
// Tests
//-----------------------

Each test (page) is seperated in their own helper function (ex: starBurstTest(..), parallelogramTest(..), etc)

// Page 1: starBurstTest(..)
This test had similar implementation for each panel
1) Calculate the centre of each panel
2) Calculate the end coordinates of each angle (90 lines in total)
3) Draw these lines using each algorithm

// Page 2: parallelogramTest(..)
This test had similar implementation for each panel
1) Determine the beginning coordinates of each panel (x,y)
2) Then simply add on the extra points required to form the parallogram to the beginning coordinates of each panel
3) Draw these lines using each algorithm

// Page 3: randomTest(..)
This test had similar implementation for each panel
1) Create 2 random points between 0-299
2) Calculate where those two points lie within the respected panel
   (ex: Panel One: (50,50) Random point: (30,100) ActualPointInPanelOne: (80, 150))
3) Calculate the random colour by generating a random value from 0-255 for Red, Green, Blue channel bits and returning
   color = (0xff << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff) for the random colour
4) Draw the lines using each algorithm

// Page 4: filledPolygonTest(..)
The main task of this test was to create a function that can create triangles (polygons) using our line algorithm. 
The helper function created to generate a triangle uses the Bresenham line drawer and horizontal scan lines.
1) Organize the three coordinates from highest Y value to lowest Y value
2) The general idea of horizontal scan lines is to start from the highest Y value then..
	a) Increment Y
	b) calculate the x left value using x = (y - b) / m (LEFT SIDE)
	c) calculate the x right value using x = (y - b) / m (RIGHT SIDE)
	d) Draw a horizontal line from x left to x right using the same Y value
3)Consider some corner cases. Vertical lines give us an undefined slope. So we don't need to figure out the x left/x right, the following list is the cases I considered
	a) 2 cases - Do we have a left or right verical line? - based on that, we can determine which side can stay constant in terms of x
Some more information may be commented inside the polygonRenderer(..) function in terms of corner cases

//Panel One
1) Similar to Page 1, we will determine the coordinates of each angle
2) Sort the vertices based on Y
3) Draw the triangle

//Panel Two
The grid that is set up is calculated as follows
The panel starts at (400,50)
The panel ends at (700,350)
Total panel size: 300
Outside Margins: 15
Each square is 30 pixels
1) Store all these points in a 2D array
2) We can now draw the associated triangles as we have information of all points in our array

//Panel Three
Similar setup as Panel two
1) Store all the points in a 2D array
2) generate a random value from [-12,12]
3) Add that value to that respected coordinate
4) All points should be accounted for, so we simply draw the triangles based on the points in the array

//Panel Four
1) Generate 3 random points between 0-299
2) Calculate where those three points lie within the respected panel
3) Draw the associated triangle

// Page 5: alteredFilledPolygonTest(..)
Same as Page 4, but change in opacity

//=======================
// Attempted
//=======================
	





