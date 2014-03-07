/*
 * Filename: Delfino_A3.cpp
 *
 * Description: Adds functionality to the constructor, destructor, and methods
 *              of the DEM class. Also adds functionality to the external functions
 *              that are needed by the DEM class.
 *
 */
#include "DEM.h"

DEM::DEM()
// Initializes a DEM (Digital Elevation Model) object from a .grd file
// (parameterized contructor)
// Parameters: filename - filename - a string representing the filename (with extension) that is to be read into the DEM object
//             sortingType - a character ('q' or 's') indicating whether the elevation points are sorted using qsort() or sort()
// Precondition: The file being read in is of the correct format (correct boilerplate information, correct grid formatting, etc.)
// Postcondition: A DEM object contains all of the elevation points within a specific file in ascending order (its length is also known)
{
	data = 0;
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
	if(!fin)
	{
		cout << "Warning! File not found!" << endl;
		exit(1);
	}
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

void DEM::getLimits(float& min, float& max)
{
	min = data[0][0];
	max = data[0][0];

	long i,j;
	for(i=rows-1; i>=0; i--)
	{
		for(j=0; j<cols; j++)
		{
			if(data[j][i] < min)
			{
				min = data[j][i];
			}
			else if(data[j][i] > max)
			{
				max = data[j][i];
			}
		}
		
	}
}

void DEM::displayKnots(float xRot, float yRot, float frustX, float frustZ, float frustYlower, float frustYupper, float yToORIG, float zToORIG, float elFactor, float zoom)
{
   float frustY = (frustYupper-frustYlower)/2.0;
   long i, j = 0;
  	
	while(j < cols)
   {
 		glLoadIdentity();
      glTranslatef(0.0, 0.0, zoom);
   		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
   		glRotatef(xRot, 1.0, 0.0, 0.0);
   		glRotatef(yRot, 0.0, 1.0, 0.0);
   		glTranslatef(0.0, yToORIG, zToORIG);
   		glTranslatef(0.0, (frustYlower+frustY)*elFactor*-1, 0.0);
   		i = 0;
   		glBegin(GL_POINTS);
   			
   		   while(i < rows)
   		   {
   			   glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   //glFlush();

        
   			   i++;

   		   }
   		glEnd();
   		// glFlush();
   		j++;
   }
   cout << "Displaying Knots..." << endl;
}

void DEM::displaySplineC0(float xRot, float yRot, float frustX, float frustZ, float frustYlower, float frustYupper, float yToORIG, float zToORIG, float elFactor, float zoom)
{
   float frustY = (frustYupper-frustYlower)/2.0;

   long i, j = 0;
  
	while(j < cols)
   {
 		glLoadIdentity();
      glTranslatef(0.0, 0.0, zoom);
   		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
   		glRotatef(xRot, 1.0, 0.0, 0.0);
   		glRotatef(yRot, 0.0, 1.0, 0.0);
   		glTranslatef(0.0, yToORIG, zToORIG);
   		glTranslatef(0.0, (frustYlower+frustY)*elFactor*-1, 0.0);

   		i = 0;
   		glBegin(GL_LINE_STRIP);
   			
   		   while(i < rows)
   		   {
   			   glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   
   			   //glFlush();
   			   i++;
   		   }
   		glEnd();
   		// glFlush();

   		j++;
   }

   j = 0, i = 0;
   while(i < rows)
   {
 		glLoadIdentity();
      glTranslatef(0.0, 0.0, zoom);
   		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
   		glRotatef(xRot, 1.0, 0.0, 0.0);
   		glRotatef(yRot, 0.0, 1.0, 0.0);
   		glTranslatef(0.0, yToORIG, zToORIG);
   		glTranslatef(0.0, (frustYlower+frustY)*elFactor*-1, 0.0);

   		j = 0;
   		glBegin(GL_LINE_STRIP);
   			
   		   while(j < cols)
   		   {
   			   glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   //glFlush();
   			   j++;
   		   }
   		glEnd();
   		// glFlush();
      
   		i++;
   }
   cout << "Displaying Piece-wise Linear Spline (C_0)" << endl;

}

void DEM::displaySplineC1(float xRot, float yRot, float frustX, float frustZ, float frustYlower, float frustYupper, float yToORIG, float zToORIG, float elFactor, float zoom)
{
   float frustY = (frustYupper*elFactor-frustYlower*elFactor)/2.0;
   
   long i, j = 0;
  	double interpEL, a, b, c, slope, subX;
  	short index=0;
	while(j < cols)
   {
 		glLoadIdentity();
      glTranslatef(0.0, 0.0, zoom);
   		glTranslatef(0.0, -1*yToORIG*elFactor, -1*zToORIG);
   		glRotatef(xRot, 1.0, 0.0, 0.0);
   		glRotatef(yRot, 0.0, 1.0, 0.0);
   		glTranslatef(0.0, yToORIG*elFactor, zToORIG);
   		glTranslatef(0.0, (frustYlower+frustY)*elFactor*-1, 0.0);

   		i = 0;
   		glBegin(GL_LINE_STRIP);
   			
   		   while(i < (rows-1)*cellsize+1)
   		   {
   		   		if(i==0)
   		   		{
   		   			// cout << "ELEVATION: " << getData(j, i) << endl;

   			   		glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i);
   			   		i += cellsize;

   			   		//calculate slope for the first piece of the quadratic spline
   			   		slope = ((elFactor*getData(j,index+1))-((elFactor*getData(j,index))))/(((index+1)*cellsize)-((index)*cellsize));

   		   		}
            // else if(getData(j,i/cellsize) == getData(j, (i+cellsize)/cellsize))
            // {
            //   glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i);
            //   i += cellsize;

            //   //calculate slope for the first piece of the quadratic spline
            //   slope = ((elFactor*getData(j,index+1))-((elFactor*getData(j,index))))/(((index+1)*cellsize)-((index)*cellsize));
            // }
   		   		else if(i%cellsize==0)
   		   		{
   		   			index = i/cellsize;
   		   			// cout << "ELEVATION: " << getData(j, index) << endl;

   		   			subX = i;
   		   			//display point at knot
   			   		glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,index)), (-1*(rows*cellsize/2))-i);
   			   		
   			   		if(index != rows-1)
   			   		{
   			   			// calculate quadratic formula for next 9 interpolated points
   			   			// calculate slope at current knot ----------------------------
   			   			// cout << slope << endl;
   			   			c = elFactor*getData(j, index);
   			   			b = slope;
   			   			a = ((elFactor*getData(j,index+1)) - b*((index+1)*cellsize-subX) - c)/(((index+1)*cellsize-subX)*((index+1)*cellsize-subX));
					// cout << "a: " << a << endl;
   		   			// cout << "b: " << b << endl;
   		   			// cout << "c: " << c << endl;
   			   			//calculate slope for next piece
   			   			slope = 2*a*(((index+1)*cellsize)-subX) + b;
   			   		}
  					i++;
   		   		}
   		   		else
   		   		{
   		   			//interpolate elevation using quadratic formula
   		   			interpEL = (a*((i-subX)*(i-subX)))+(b*(i-subX))+c;
   		   			glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*interpEL), (-1*(rows*cellsize/2))-i);
   			   		i++;
              //cout << "X: " << -1*(frustY-frustYlower*elFactor)+(elFactor*interpEL) << endl;
   		   		}
   			   //glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   
   			   //glFlush();
   			   // i++;
   		   }
   		glEnd();
   		glFlush();
   		
   		j++;
   }

  i = 0;
  j = 0; 
  index = 0;
  while(i < rows)
   {
 		glLoadIdentity();
      glTranslatef(0.0, 0.0, zoom);
   		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
   		glRotatef(xRot, 1.0, 0.0, 0.0);
   		glRotatef(yRot, 0.0, 1.0, 0.0);
   		glTranslatef(0.0, yToORIG, zToORIG);
   		glTranslatef(0.0, (frustYlower+frustY)*elFactor*-1, 0.0);

   		j = 0;

   		glBegin(GL_LINE_STRIP);
   			
   		   while(j < (cols-1)*cellsize+1)
   		   {
   		   		// cout << "("<<j <<", "<<i<<")"<<endl;
   		   		if(j==0)
   		   		{
   		   			index = j;
   		   			// cout << "ELEVATION: " << getData(j, i) << endl;

   			   		glVertex3f((-1*(cols*cellsize/2))+j, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   		j = cellsize;

   			   		//calculate slope for the first piece clearof the quadratic spline
   			   		slope = ((elFactor*getData(index+1,i))-((elFactor*getData(index,i))))/(((index+1)*cellsize)-((index)*cellsize));

   		   		}
   		   		else if(j%cellsize==0)
   		   		{
   		   			index = j/cellsize;
   		   			// cout << "ELEVATION: " << getData(index, i) << endl;

   		   			subX = j;
   		   			//display point at knot
   			   		glVertex3f((-1*(cols*cellsize/2))+j, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(index, i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   		
   			   		if(index != cols-1)
   			   		{
   			   			// calculate quadratic formula for next 9 interpolated points
   			   			// calculate slope at current knot ----------------------------
   			   			// cout << slope << endl;
   			   			c = elFactor*getData(index, i);
   			   			b = slope;
   			   			a = ((elFactor*getData(index+1, i)) - b*((index+1)*cellsize-subX) - c)/(((index+1)*cellsize-subX)*((index+1)*cellsize-subX));
					// cout << "a: " << a << endl;
   		   			// cout << "b: " << b << endl;
   		   			// cout << "c: " << c << endl;
   			   			//calculate slope for next piece
   			   			slope = 2*a*(((index+1)*cellsize)-subX) + b;
   			   		}
  					j++;
   		   		}
   		   		else
   		   		{
   		   			//interpolate elevation using quadratic formula
   		   			interpEL = (a*((j-subX)*(j-subX)))+(b*(j-subX))+c;
   		   			glVertex3f((-1*(cols*cellsize/2))+j, -1*(frustY-frustYlower*elFactor)+(elFactor*interpEL), (-1*(rows*cellsize/2))-i*cellsize);
   			   		j++;

   		   		}
   			   //glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor*0.5)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   
   			   //glFlush();
   			   // i++;
   		   }
   		glEnd();
   		glFlush();
   		i++;
   }
   cout << "Displaying Piece-wise Quadratic Spline (C_1)" << endl;

}

// void DEM::displaySplineC1(float xRot, float yRot, float frustX, float frustZ, float frustYlower, float frustYupper, float yToORIG, float zToORIG, float elFactor)
// {
//    float frustY = (frustYupper-frustYlower)/2.0;

//    long i, j = 0;
//   	float interpEL, a, b, c, slope, subX;
//   	short interpoint=0;
// 	while(j < cols)
//    {
//  		glLoadIdentity();
//    		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
//    		glRotatef(xRot, 1.0, 0.0, 0.0);
//    		glRotatef(yRot, 0.0, 1.0, 0.0);
//    		glTranslatef(0.0, yToORIG, zToORIG);
//    		glTranslatef(0.0, frustY*elFactor*-1, 0.0);

//    		i = 0;
//    		glBegin(GL_LINE_STRIP);
   			
//    		   while(i < rows)
//    		   {
//    		   		if(i==0)
//    		   		{
//    		   			cout << "ELEVATION: " << getData(j, i) << endl;
//    		   			glBegin(GL_LINE_STRIP);
//    			   		glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i);

//    			   		//calculate slope for the first piece of the quadratic spline
//    			   		slope = ((elFactor*getData(j,i+1))-((elFactor*getData(j,i))))/(((i+1)*cellsize)-((i)*cellsize));

//    		   		}
//    		   		else
//    		   		{
   		   			
//    		   			cout << "ELEVATION: " << getData(j, i) << endl;

//    		   			subX = i;
//    		   			//display point at knot
//    			   		glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i);
   			   		
//    			   		if(i != rows-1)
//    			   		{
//    			   			// calculate quadratic formula for next 9 interpolated points
//    			   			// calculate slope at current knot ----------------------------
//    			   			cout << slope << endl;
//    			   			c = elFactor*getData(j, i);
//    			   			b = slope;
//    			   			a = (elFactor*getData(j,i+1)*(((i+1)*cellsize-subX)*((i+1)*cellsize-subX)))-b*((i+1)*cellsize-subX)-c;
// 					cout << "a: " << a << endl;
//    		   			cout << "b: " << b << endl;
//    		   			cout << "c: " << c << endl;
//    			   			//calculate slope for next piece
//    			   			slope = 2*a*(((i+1)*cellsize)-subX) + b;

//    			   			for(short l=1; l<cellsize;l++)
//    			   			{
//    			   				interpoint = (i*cellsize)+l;
//    			   				interpEL = (a*((interpoint-subX)*(interpoint-subX)))+(b*(interpoint-subX))+c;
//    		   		        	glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*interpEL), (-1*(rows*cellsize/2))-i);
   			   			
//    			   			}
//    			   		}
  					
//    		   		}
//    		   		// else
//    		   		// {
//    		   		// 	//interpolate elevation using quadratic formula
//    		   		// 	interpEL = (a*((i-subX)*(i-subX)))+(b*(i-subX))+c;
//    		   		// 	glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*interpEL), (-1*(rows*cellsize/2))-i);
   			   		

//    		   		// }
//    			   //glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
   			   
//    			   //glFlush();
//    			   i++;
//    		   }
//    		glEnd();
//    		glFlush();
//    		break;
//    		j++;
//    }

//    // j = 0, i = 0;
//    // while(i < cols)
//    // {
//  		// glLoadIdentity();
//    // 		glTranslatef(0.0, -1*yToORIG, -1*zToORIG);
//    // 		glRotatef(xRot, 1.0, 0.0, 0.0);
//    // 		glRotatef(yRot, 0.0, 1.0, 0.0);
//    // 		glTranslatef(0.0, yToORIG, zToORIG);
//    // 		glTranslatef(0.0, frustY*elFactor*-1, 0.0);

//    // 		j = 0;
//    // 		glBegin(GL_LINE_STRIP);
   			
//    // 		   while(j < rows)
//    // 		   {
//    // 			   glVertex3f((-1*(cols*cellsize/2))+j*cellsize, -1*(frustY-frustYlower*elFactor)+(elFactor*getData(j,i)), (-1*(rows*cellsize/2))-i*cellsize);
//    // 			   //glFlush();
//    // 			   j++;
//    // 		   }
//    // 		glEnd();
//    // 		glFlush();
//    // 		i++;
//    // }
// }