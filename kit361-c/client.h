#ifndef CLIENT_H
#define CLIENT_H
#include "drawable.h"
#include "pageturner.h"
#include <tuple>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stack>

typedef enum {ONE, TWO, THREE, FOUR} Panel;
typedef enum {OctOne, OctTwo, OctThree, OctFour, OctFive, OctSix, OctSeven, OctEight} Octant;
typedef enum {Phong, Gouraud, Flat} Shading;

struct grid 
{
	int x;
	int y;
};

struct RGBColour
{
	int r = 0;
	int g = 0;
	int b = 0;
	int o = 0;
	bool hasColour = false;
};

struct RGB
{
	double r = 1;
	double g = 1;
	double b = 1;
};

// Identity matrix
struct iMatrix
{
	float matrix[4][4];

	iMatrix()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == j)
				{
					matrix[i][j] = 1.0;
				}
				else
				{
					matrix[i][j] = 0.0;
				}
			}
		}
	}
};

// Point Storage
struct point
{
	double x;
	double y;
	double z;
	double w;
};

// Storage of Vertex
struct Vertex
{
	point P;
	RGB colour;
	bool hasColour = false;
};

// Storage of a normal vector
struct Normal
{
	point P;
};

struct Face
{
	Vertex vertex_1;
	Vertex vertex_2;
	Vertex vertex_3;
};

// Triangle point storage
struct triangle
{
	point P1;
	point P2;
	point P3;
};
class Client : public PageTurner
{
public:
    Client(Drawable *drawable, char *fileName);
    void nextPage();
	// Class Helper Functions
	
	//============================================================
	// Calcuate the centre of each panel
	//
	// Returns (x,y) as the centre of the pixel
	//============================================================
	std::tuple<int, int> calculate_PanelCentre(int x1, int y1, int x2, int y2);

	//============================================================
	iMatrix multiplyMatrices(iMatrix A, iMatrix B);

	//============================================================
	point page3TransformHelper(iMatrix transformationMatrix, point P);

	//============================================================
	std::tuple<Vertex, Vertex, Vertex> setPolygonPoints(int currentIndex);

	//============================================================
	std::tuple<Vertex, Vertex> setLinePoints(int currentIndex);

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
	unsigned int calculate_LineColor();

	//============================================================
	// Unpack a colour 
	//============================================================
	RGBColour unpackColour(unsigned int currentColour);

	//============================================================
	// Pack a colour 
	//============================================================
	unsigned int packColour(RGBColour currentColour);

	//============================================================
	// Order the incoming points in terms of the highest y value
	// Sets values in a vector
	//
	// TODO: Generalize the equation for all points, possibly by storing into a vector
	// Then organize that vector
	// Returns the vector with ordered coordinates
	//============================================================
	void orderedCoordinates(int x1, int y1, int x2, int y2, int x3, int y3);

private:
    Drawable *drawable;
	std::string simpFileName;
	struct polygonCoordinates {
		int x = 0;
		int y = 0;
	};

	int currentIndex = 0;
	int newFileIndex = 0;
	int firstSimpCount = 0;
	bool firstSimp = true;
	std::vector<polygonCoordinates> orderedPolygonCoordinates;
	std::vector<std::string> parsedSimpFile;
	std::vector<std::string> parsedObjFile;

	// Stores (x,y,z,w) with a colour (r,g,b)
	std::vector<Vertex> objVertexArray;
	// Stores (nx,ny,nz)
	std::vector<Normal> objNormalArray;

	// Stores Faces which consist of 3 vertices
	std::vector<Face> objFaceArray;

	bool wire;
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
	//
	// [Feb 11 2017] Assignment 2: We will now interpolate colours
	// The DDA lindrawer function will now take two colours so
	// we can calculate and interpolate
	//============================================================
	void lineDrawer_DDA(int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);

	unsigned int Lerp(unsigned int a, unsigned int b, double t);

	//============================================================
	// Polygon Renderer
	// This class helper function will create filled polygons
	// based on the bresenham line drawing algorithm
	//============================================================
	void polygonRenderer(float x1, float y1, float x2, float y2, float x3, float y3, unsigned int color1, unsigned int color2, unsigned int color3);

	//============================================================
	// This function will do the following..
	// 1) Allocate an array of doubles to the size of the window
	// 2) Set the entire array to 200
	// 3) Compare a given z coordinate to the zBuffer array
	// 4) if z < zBuffer then write pixel
	//void zBuffer(int cx, int cy, triangle triangleToDraw);

	//============================================================
	// Rotation function
	iMatrix transformationRotate(std::string axis, double numberOfDegrees, iMatrix currentMatrix);

	//============================================================
	// Translation function
	iMatrix transformationTranslate(double translateX, double translateY, double translateZ, iMatrix currentMatrix);

	//============================================================
	// Scale function
	iMatrix transformationScale(double scaleX, double scaleY, double scaleZ, iMatrix currentMatrix);

	//============================================================
	point transformationPoint(point pointToChange, iMatrix transformationMatrix);

	//============================================================
	// Main interface to read the input simp file
	// This will also ignore comments and invalid lines
	// 
	// Returns false if the file cannot be opened
	bool simpFileOpener(std::string fileName);

	//============================================================
	// This is interpret the current line by splitting the line
	// into parts
	//
	// Returns false if the key words are invalid
	bool simpFileInterpreter(std::string currentLine);

	//============================================================
	// Transform, and render the simp file
	bool transformationInterpreter();

	//============================================================
	// Reads a obj file
	bool objFileReader(std::string fileName,bool setAmb, iMatrix currentMatrix);

	//============================================================
	// Parses through the obj file
	bool objFileInterpreter(std::string currentLine);

	//============================================================
	// Stores all the objFile vertices, vertex normals & faces
	void transformObjFile(iMatrix CTM, bool setAmb);

	//============================================================
	// CameraPerspective
	iMatrix CameraPerspective(float degrees, float zNear, float zFar, float xlow, float ylow, float xhi, float yhi, iMatrix CTM);

	//============================================================
	// Making an ambient lighting
	RGBColour setAmbient(RGB setAmbientColour, RGB currentColour);

	//============================================================
	// Unsure what this does so far
	void depthShading(Vertex P1, Vertex P2, Vertex P3, float near, float far, bool setAmb, RGB ambientColour);

	//============================================================
	void zBuffer(triangle caseThreeTriangle);

	//============================================================
	double MatrixDeterminent(iMatrix CTM, int row, int column);

	iMatrix reduceMatrix(int column, int row, iMatrix CTM);

	iMatrix transposeMatrix(iMatrix CTM);

	iMatrix inverseMatrix(iMatrix CTM);

	//============================================================
	// Possible Tests for Assignment 2
	//============================================================

	//============================================================
	// Main interface to interact with the tests
	void panelTests3(const int currentPage);
};



#endif // CLIENT_H
