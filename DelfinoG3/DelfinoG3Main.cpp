// DelfinoG2Main.cpp

#include <GL/glut.h>
#include "DEM.h"
#include <iostream>
#include <math.h>
using namespace std;

DEM d("test.grd");
float yRot = 0.0;
float xRot = 0.0;
float xEye = 0.0;
float yEye = 0.0;
float zEye = 5.0;
void menuOptions(int);
void printTitle();

void display()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //
   glLoadIdentity ();
   gluLookAt (xEye, yEye, zEye, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glScalef (1.0, 1.0, 1.0);

   /* draw a red cube in center of volume */
   glColor3f (0.2, 0.2, 1.0);
   glRotatef(yRot, 0.0, 1.0, 0.0);
   glRotatef(xRot, 1.0, 0.0, 0.0);
   glutWireTeapot (0.8);
   
   glScalef (0.5, 0.5, 0.5);
   glTranslatef(0-(d.getRows()/2), 0, 0-(d.getCols()/2));
   glBegin(GL_LINE_STRIP);
     glVertex3f(0, d.getData(0,0), 0);
     glVertex3f(0, d.getData(0,1), 1);
     glVertex3f(0, d.getData(0,2), 2);
   glEnd();
   glFlush();
}

void init()
{
	// glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	// glClearColor(0.8, 0.8, 0.8, 0.0);
	// glShadeModel (GL_FLAT);
	// glEnable (GL_DEPTH_TEST);
 //    glFrustum (-1, 1, -1, 1, 1.5, 20.0);

	// //glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	printTitle();
    // glLoadIdentity();
	glClearColor (0.8, 0.8, 0.8, 0.0);
    glShadeModel (GL_FLAT);
    glEnable (GL_DEPTH_TEST);
    glLoadIdentity ();
    d.print();
}

void resizeWindow(int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei) h);
   /* set up matrices for projection coordinate system */
   glMatrixMode (GL_PROJECTION);
   glFrustum (-1, 1, -1, 1, 1.6, 30.0);

   /* reset matrices to user's coordinate system */
   glMatrixMode (GL_MODELVIEW);
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

void menuOptions(int choice)
{
	switch(choice)
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

void keyboardInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '1': 	
		//add in limit to zoom in
			 	  zEye += 0.5;
   				  glutPostRedisplay();
				  break;
		case '7': 
		//add in limit to zoom out
				  zEye -= 0.5;
   				  glutPostRedisplay();
				  break;
		case '8': 
				  xRot -= 2.0;
   				  glutPostRedisplay();
				  break;
		case '2': 
				  xRot += 2.0;
   				  glutPostRedisplay();
				  break;
		case '4': 
   				  yRot += 2.0;
   				  glutPostRedisplay();
				  break;
		case '6': 
				  yRot -= 2.0;
   				  glutPostRedisplay();
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
	cout << " 'Display Quadratic Spline'         - Displays a quadratic piecewise spline (C_1)" << endl;
	cout << " 'Turn Splines Off'              - Clears the screen of all splines" << endl;
	cout << " 'Increase Grid Elevations' (x2) - " << endl;
	cout << " 'Decrease Grid Elevations' (x2) - " << endl;
	cout << " 'Reset to Original Grid'        - Turns splines off and resets grid elevations" << endl;
	cout << " 'Quit'                          - Exits program\n\n" << endl;

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
