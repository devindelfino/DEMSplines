// DelfinoG2Main.cpp

#include <GL/glut.h>

#include <iostream>
#include <math.h>
using namespace std;

void menuOptions(int);
void printTitle();


void display()
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glScalef (1.0, 1.0, 1.0);
	glTranslatef (5.0, 0-5.0, 0.0);
	glColor3f(0.0,0.0,1.0);
	glutWireCube(0.8);

	glutSwapBuffers();
}

void init()
{
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable (GL_DEPTH_TEST);
	glOrtho(0.0, 850.0, 0.0, 850.0, -1.0, 1.0);
	printTitle();
}

void resizeWindow(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glFrustum (-1, 1, -1, 1, 1.5, 20.0);
   // glOrtho(0.0, 850.0, 0.0, 850.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void initMenu()
{
	glutCreateMenu(menuOptions);
	glutAddMenuEntry("Display Linear Spline (C_0)",0);
	glutAddMenuEntry("Display Quadratic Spline (C_1)",1);
	glutAddMenuEntry("Turn Splines off", 2);
	glutAddMenuEntry("",0);
	glutAddMenuEntry("Increase Grid Elevation (x2)",3);
	glutAddMenuEntry("Decrease Grid Elevation (x2)",4);
	glutAddMenuEntry("Reset to Original Grid",5);
	glutAddMenuEntry("Quit",9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuOptions(int val)
{
	switch(val)
	{
		case 0: 
				break;
		case 1:
				break;
		case 2: 
				break;
		case 3: 
				break;
		case 4: 
				break;
		case 5: 
				break;
		case 9: exit(1);
				break;
	}
}

// void mouseClick(int button, int state, int x, int y)
// {
// 	//
// }

void keyboardInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '1': 	
			 	  break;
		case '7': 
				  break;
		case '8': 
				  break;
		case '2': 
				  break;
		case '4': 
				  break;
		case '6': 
				  break;
	}
}

void printTitle()
{
	cout << "\n * ========================================================================== *" << endl;
	cout << " *                                                                            *" << endl;
	cout << " *                 Splines using Digital Elevation Models                     *" << endl;
	cout << " *                                                                            *" << endl;
	cout << " * ========================================================================== *\n" << endl;
	cout << " Menu Options:\n"<< endl;
	cout << " 'Display Linear Spline'         - Displays a linear piecewise spline (C_0)" << endl;
	cout << " 'Display Linear Spline'         - Displays a quadratic piecewise spline (C_1)" << endl;
	cout << " 'Turn Splines Off'              - Clears the screen of all splines" << endl;
	cout << " 'Increase Grid Elevations' (x2) - " << endl;
	cout << " 'Decrease Grid Elevations' (x2) - " << endl;
	cout << " 'Reset to Original Grid'        - Turns splines off and resets grid elevations" << endl;
	cout << " 'Quit'                          - Exits program" << endl;

	cout << " Keyboard Instructions:\n"<< endl;
	cout << " '1' - Zoom in" << endl;
	cout << " '7' - Zoom out" << endl;
	cout << " '8' - Rotate grid about the x-axis (Vertically, Counter-Clockwise)" << endl;
	cout << " '2' - Rotate grid about the x-axis (Vertically, Clockwise)" << endl;
	cout << " '4' - Rotate grid about the y-axis (Horizontally, Counter-Clockwise)" << endl;
	cout << " '6' - Rotate grid about the y-axis (Horizontally, Clockwise)\n\n" << endl;
}

int main(int argc, char **argv)
// main function
{  
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize(800,800);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("Splines using DEM");
   init();
   initMenu();
   glutKeyboardFunc(keyboardInput);   // the default keyboard function of the openGL program
   glutDisplayFunc(display);        // the default display function of the openGL program
   glutReshapeFunc(resizeWindow);     // the default reshape function of the openGL program
   glutMainLoop(); 
   return 0;  
}
