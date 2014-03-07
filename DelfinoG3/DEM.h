/* Name: Devin Delfino
 * Date: 
 * Filename: DEM.h
 */

#ifndef Dem
#define Dem

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class DEM { // (Digital Elevation Model)
private:
	float** data;				// a float pointer, will later be set to an array of floats (all elevation points in a file)
	long size;				// the number of elevation points in a DEM
	short cols;
	short rows;
	short cellsize;
public:
	//constructors
	DEM();			// parameterized contructor
	void readIn(string);		// builds the datamember 'data' from a file being read in

	//destructors
	~DEM();						// destroys the dynamically allocated 'data' datamember

	//methods
	long getSize();			// returns the size of the DEM
	void print();
	short getCellSize();
	short getCols();
	short getRows();
	void displayKnots(float, float, float, float, float, float, float, float, float, float);
	void displaySplineC0(float, float, float, float, float, float, float, float, float, float);
	void displaySplineC1(float, float, float, float, float, float, float, float, float, float);
	
	void getLimits(float&,float&);

	float getData(short,short);		// returns the elevation point at a particular index of the array
};

#endif