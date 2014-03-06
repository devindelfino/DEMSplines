// DelfinoG2Main.cpp

#include "DEM.h"

DEM d("mt257.dem.grd");
short CELL = d.getCellSize();
float frustX = d.getCols()*CELL;
float frustZ = d.getRows()*CELL;
float frustYlower = 0.0;
float frustYupper = 0.0;
float frustYmid;
float frustPROJ;
//float xEye = frustX/2.0;
float xEye = 0.0;
float yEye = frustYmid;
//float zEye = frustZ/2.0;
float ratio;
float zEye = 0-frustZ/CELL/2*CELL;
float elFactor = 1.0;
bool rotateHORZ = false;
bool rotateVERT = false;
float xToORIG = 0.0;
float yToORIG = -1*(frustYmid);
//float zToORIG = 0.0;
float zToORIG = frustZ;
float yRot = 0.0;
float xRot = 0.0;
float zoom = 1.0;
bool displayKnots = true;
bool displayC0 = false;
bool displayC1 = false;

//prototypes
void menuOptions(int);
void printTitle();

void display()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //
   glLoadIdentity ();
   gluLookAt (xEye, yEye*zoom, zEye*zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glColor3f (1, 0.871, 0);
  
   if(displayC0)
   {
      d.displaySplineC0(xRot, yRot, frustX, frustZ, frustYlower, frustYupper, yToORIG, zToORIG, elFactor);
   }
   else if(displayC1)
   {
    //
   }
   else
   {
      d.displayKnots(xRot, yRot, frustX, frustZ, frustYlower, frustYupper, yToORIG, zToORIG, elFactor);
   }

   glutSwapBuffers();
}

void init()
{
	
	printTitle();
	glClearColor (0.8, 0.8, 0.8, 0.0);
  glClearColor (0.0, 0.0, 0.098, 0.0);

    glShadeModel (GL_FLAT);

    // GET LOWER/UPPER bounds for FRUSTUM Y
    d.getLimits(frustYlower,frustYupper);
    cout << frustYlower << endl;
    cout << frustYupper << endl;
    //yEye = frustYupper+CELL;
    frustYmid = (frustYupper+frustYlower)/2.0;
    glEnable (GL_DEPTH_TEST);
    glLoadIdentity ();
    //d.print();
}

void resizeWindow(int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei) h);
   /* set up matrices for projection coordinate system */
   glMatrixMode (GL_PROJECTION);
   
   if(frustX>frustZ)
   {
      frustPROJ = frustX;
   }
   else
   {
      frustPROJ = frustZ;
   		
   }
   ratio = (w*1.0)/(h*1.0);

   // ratio of width/height
   gluPerspective(85.0/zoom, ratio, 0.1f, frustPROJ*2);
   //glFrustum(0-(frustPROJ/2.0)-10, (frustPROJ/2.0)+10, frustYlower-10, frustYlower+frustPROJ+10, 20, 20+(frustPROJ));
   

   //glOrtho(0-(frustPROJ/2.0)-10, (frustPROJ/2.0)+10, frustYlower-10, frustYlower+frustPROJ+10, 20, 20+(frustPROJ));
   //glFrustum(0-(frustPROJ)-10, (frustPROJ)+10, frustYlower-10, frustYlower+frustPROJ*2+10, 20, 20+(frustPROJ));
   // glOrtho(0-(frustPROJ/2.0)-10, (frustPROJ/2.0)+10, frustYlower-10, frustYlower+frustPROJ+10, 20, 20+(frustPROJ));
   
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
        displayC0 = true;
        displayC1 = false;
        displayKnots = false;
        glutPostRedisplay();
				break;
		case 1:
        displayC0 = false;
        displayC1 = true;
        displayKnots = false;
        glutPostRedisplay();
				break;
		case 2: 
        displayC0 = false;
        displayC1 = false;
        displayKnots = true;
        glutPostRedisplay();
				break;
		case 3:
        elFactor = elFactor*2; 
        glutPostRedisplay();
				break;
		case 4:
        if(elFactor > 1.0)
        {
          elFactor = elFactor/2; 
        }
        glutPostRedisplay();
				break;
		case 5: 
				displayC0 = false;
        displayC1 = false;
        displayKnots = true;
        elFactor = 1.0;
        glutPostRedisplay();
        break;
		case 9: 
        exit(1);
				break;
	}
}

void keyboardInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '1': 	
		//add in limit to zoom in
			 	  //zEye -= 10;
          zoom += 1.0;
              //frustPROJ += 10.0;
				 
              cout << "zoom in"<<endl;
              

   			   glutPostRedisplay();
				  break;
		case '7': 
		//add in limit to zoom out
				  zEye += 0.5;
              cout << "zoom out"<<endl;
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
   				  yRot -= 2.0;
   				  glutPostRedisplay();
				  break;
		case '6': 

				  yRot += 2.0;
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
	cout << " 'Display Quadratic Spline'      - Displays a quadratic piecewise spline (C_1)" << endl;
	cout << " 'Turn Splines Off'              - Clears the screen of all splines" << endl;
	cout << " 'Increase Grid Elevations' (x2) - Increases Grid Elevation Points by a factor of 2" << endl;
	cout << " 'Decrease Grid Elevations' (x2) - Decreases Grid Elevation Points by a factor of 2" << endl;
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
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
