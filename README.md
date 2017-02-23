# Author
Aaron Nguyen 

# CMPT 361 - Assignment 1: Polygon and Line Renderer

## Compile Notes
### On Windows
This program was implemented on Microsoft Visual Studio 2015 with the Qt VS add-on, downloaded from: https://marketplace.visualstudio.com/items?itemName=havendv.QtPackage

### On Linux
This program was also tested on Ubuntu with QtCreater (Version is same as SFU CSIL computers).

#### Build steps
1) Open the qtqt.pro project file 
2) Some of the methods in this project requires C++11 in Qt Creator. I've made sure that this project file does include C++11, but in the event that it is not included.. 
a) Open the qtqt.pro in the text editor 
b) Somewhere near the top (ex: Under "TEMPLATE = app") include the following "CONFIG += c++11" 
c) Save & recompile 
3) Add all the headers and .cpp files 
4) Run 


## Implementation

### Algorithms

#### Digital Analyzer Algorithm (DDA)
The DDA uses the y-intercept equation y = mx + b as its main calculation for plotting. There are 2 major cases with 2 sub cases each:

1) __If slope is less than 1__, iterate on x while calculate and round up y in every iteration

    a) If __dx > 0__, the endpoint x is greater than the initial point x0 so y calculation cane be done        while increasing x to the endpoint. 
    ex: initial point (200,200), endpoint (300,250))

    b) If __dx < 0__, the endpoint x is less than the initial point x0 so y calculation can be done while     decreasing x to the endpoint.
    ex: initial point(200,200), endpoint (-100,250)
    
2) __if slope is greater than 1__, iterate on y while calculate and round up x in every iteration

    a) If __dy is > 0__, the endpoint y is greater than the initial point y0 so x calculation cane be done        while increasing y to the endpoint.  
    ex: centre (200,200), endpoint (250,300)
    
    b) If dy is < 0, the endpoint y is less than the initial point y0 so x calculation can be done while     decreasing y to the endpoint. 
    ex: centre (200,200), endpoint (250,-100)

####  Bresenham Algorithm
Bresenham algorithm takes decision parameters (t2, err) and deciding whether to increment x alone or y & x. Unlike DDA, Bresenham does not use floating point variables so its run time is a lot faster. In simple terms, if the err which is calculated by 2dy - dx 
1) __err < 0__ then __err = err + 2dy__ (Only increment x) 
2) __err > 0__ then __err = err + t2__ (x and y increment)

The method that is implemented considers all 8 octants is split into 2 major parts 
1) __If (y2 - y1 > 0)__ --> Octants: 1 2 3 4 2)
2) __If (y2 - y1 < 0)__ --> Octants: 5 6 7 8 

Lines in each octant are then calculated and drawned based on the incremental steps (dx or dy) and where the end points and start points lie in the the panel

## Tests

Each test page is seperated in their own helper function (ex: starBurstTest(..), parallelogramTest(..), etc)

### Page 1: starBurstTest(..) 
This test had similar implementation for each panel 
1) Calculate the centre of each panel
2) Calculate the end coordinates of each angle (90 lines in total) 
3) Draw these lines using DDA, Bresenham algorithms, and alternating between these 2 for the third panel

### Page 2: parallelogramTest(..) 
This test had similar implementation for each panel 
1) Determine the beginning coordinates of each panel (x,y) 
2) Add on the extra points required to form the parallogram to the beginning coordinates of each panel 
3) Draw these lines using each algorithm

### Page 3: randomTest(..) 
This test had similar implementation for each panel 
1) Create 2 random points between 0-299 
2) Calculate where those two points lie within the respected panel (ex: Panel One: (50,50) Random point: (30,100) ActualPointInPanelOne: (80, 150)) 
3) Calculate the random colour by generating a random unsigned value from 0-255 for Red, Green, Blue channel bits and returning color = (0xff << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff) for the random colour 
4) Draw the lines using each algorithm

### Page 4: filledPolygonTest(..) 
The main task of this test was to create a function that can create triangles (polygons) using our line algorithm. The helper function created to generate a triangle uses the Bresenham line drawer and horizontal scan lines. 
1) Organize the three coordinates from highest Y value to lowest Y value 
2) The general idea of horizontal scan lines is to start from the highest Y value then
a) Increment Y 
b) Calculate the x left value using x = (y - b) / m (LEFT SIDE) 
c) Calculate the x right value using x = (y - b) / m (RIGHT SIDE) 
d) Draw a horizontal line from x left to x right using the same Y value 

Consider some corner cases. Vertical lines gives an undefined slope. So we don't need to figure out the x left/x right, the following list is the cases I considered - Is there a left or right verical line? If there is, we can determine which side to stay constant in terms of x.
Some more information are commented inside the polygonRenderer(..) function in terms of corner cases.

### Page 5: alteredFilledPolygonTest(..) 
Same as Page 4, but change in opacity.


-------------------------

Each page consists of 4 panels and each panel uses a different redering algorithm
### Panel One 
1) Similar to Page 1, we will determine the coordinates of each angle 
2) Sort the vertices based on Y 
3) Draw the triangle

### Panel Two 
The grid that is set up is calculated as follows The panel starts at (400,50) The panel ends at (700,350) Total panel size is 300x300 pixels and outside Margin is 15 pixels. Each square is 30x30 pixels 
1) Store all these points in a 2D array 
2) Draw the associated triangles as we have information of all points in our array

### Panel Three
Similar setup as Panel two 
1) Store all the points in a 2D array 
2) generate a random value in the range of [-12,12] 
3) Add that value to that respected coordinate 
4) All points should be accounted for, so we simply draw the triangles based on the points in the array

### Panel Four
1) Generate 3 random points in the range of [0,299]
2) Calculate where those three points lie within the respected panel
3) Draw the associated triangle
