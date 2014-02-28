/* Name: Devin Delfino
 * Date: 
 * Filename: DEM.h
 */

#ifndef Dem
#define Dem

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class DEM { // (Digital Elevation Model)
private:
	float** data;				// a float pointer, will later be set to an array of floats (all elevation points in a file)
	long size;				// the number of elevation points in a DEM
	short cols;
	short rows;
	short cellsize;
	void readIn(string);		// builds the datamember 'data' from a file being read in
public:
	//constructors
	DEM(string);			// parameterized contructor

	//destructors
	~DEM();						// destroys the dynamically allocated 'data' datamember
	void print();
	short getCellSize();
	//methods
	 long getSize();			// returns the size of the DEM
	 short getCols();
	 short getRows();
	// float getMax();				// returns the maximum elevation of the DEM
	// float getMin();				// returns the minimum elevation of the DEM
	// float getAverage();			// returns the mean elevation of the DEM
	// float getMedian();			// returns the median elevation of the DEM
	float getData(short,short);		// returns the elevation point at a particular index of the array
};

#endif