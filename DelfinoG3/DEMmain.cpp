

#include "DEM.h"

int main()
{
	string filename = "test.grd";
	DEM d(filename);
	d.print();
	cout << endl << d.getData(0,0) << ", " << d.getData(9,9) << endl;

	d.generateSplineC0();
}	