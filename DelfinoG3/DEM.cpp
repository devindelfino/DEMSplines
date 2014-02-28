/*
 * Filename: Delfino_A3.cpp
 *
 * Description: Adds functionality to the constructor, destructor, and methods
 *              of the DEM class. Also adds functionality to the external functions
 *              that are needed by the DEM class.
 *
 */
#include "DEM.h"

DEM::DEM(string filename)
// Initializes a DEM (Digital Elevation Model) object from a .grd file
// (parameterized contructor)
// Parameters: filename - filename - a string representing the filename (with extension) that is to be read into the DEM object
//             sortingType - a character ('q' or 's') indicating whether the elevation points are sorted using qsort() or sort()
// Precondition: The file being read in is of the correct format (correct boilerplate information, correct grid formatting, etc.)
// Postcondition: A DEM object contains all of the elevation points within a specific file in ascending order (its length is also known)
{
	data = 0;
	readIn(filename);
}

DEM::~DEM()
// Destroys the 'data' array datamember within the DEM object (dynamically allocated)
// (destructor)
// Precondtion: The program has reached its end or the destructor has been called
// Postcondition: The dynamically allocated array of elevation points within each DEM object is destroyed
{
	if(data)
	{
		for(int i = 0; i<rows; i++)
		{
			delete[] data[i];
		}

		delete[] data;
	}
}

void DEM::readIn(string filename)
// Reads in a file of elevation points and stores each point within the array datamember 'data' in the DEM object.
// (called in parameterized constructor for DEM)
// Parameters: filename - a string representing the filename (with extension) that is to be read into the DEM object
// Precondition: The input fi
//le is in the correct format, and the constructor for a DEM object has been called
// Postcondition: The elevation points within the file are stored in the DEM object, along with the number of data points
{
	string junkS;
	float junkF;
	ifstream fin;
	fin.open(filename.c_str());
	for(short i = 0; i<5; i++)
	{
		if(i == 0)
		{
			fin >> junkS >> cols;
		}
		else if(i == 1)
		{
			fin >> junkS >> rows;
		}
		else if(i == 4)
		{
			fin >> junkS >> cellsize;
		}
		else 
		{
			fin >> junkS >> junkF;
		}
	}
	size = rows*cols;
	//read in data
	data = new float*[cols];
	for(short l=0;l<cols;l++)
	{
		data[l] = new float[rows];
	}
    long i = rows-1;
    long j = 0;
    long hmr = 0;

    while(fin && i>=0)
    {
        for(j = 0; j<cols;j++)
        {
        	fin >> data[j][i];
        	hmr++;
        }
        i=i-1;
    }
    fin.close();
    if(hmr != size)
    {
    	cout << "Some of the data points in the file were not stored..." << endl;
    	size = hmr;
    }
}

long DEM::getSize()
// Gets the number of elevation points stored in the DEM object
// Precondition: A DEM object has been created and a file has been read in correctly
// Postcondition: The number of elevation points stored in the DEM is returned
{
	return size;
}

short DEM::getCols()
{
	return cols;
}

short DEM::getRows()
{
	return rows;
}

short DEM::getCellSize()
{
	return cellsize;
}

float DEM::getData(short indX, short indY)
// Gets a specific elevation point at a given index in the 'data' array of a DEM
// Parameters: index - a long integer indicating the index of the array
// Precondition: The file has been read in correctly, and index < the length of the DEM
{
	return data[indX][indY];
}

void DEM::print()
{
	long i,j;
	for(i=rows-1; i>=0; i--)
	{
		for(j=0; j<cols; j++)
		{
			cout << data[j][i] << " ";
		}
		cout << endl;
	}
}
