// DelfinoG2Main.cpp

#include "DEM.h"

DEM d;
string filename = "mt257.dem.grd";
short CELL;
float frustX;
float frustZ;
float frustYlower = 0.0;
float frustYupper = 0.0;
float frustYmid;
float frustPROJ;
//float xEye = frustX/2.0;
float xEye = 1.0;
float yEye;
//float zEye = frustZ/2.0;
float ratio;
float zEye;
float elFactor = 1.0;
float xToORIG = 0.0;
float yToORIG;
//float zToORIG = 0.0;
float zToORIG;;
float yRot = 0.0;
float xRot = 0.0;
float zoom = 1.0;
bool displayKnots = true;
bool displayC0 = false;
bool displayC1 = false;
bool zoomIn = false;
bool zoomOut = false;
//prototypes
void menuOptions(int);
void printTitle();
void setPerspective();

void display()
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cout << xEye << " " << yEye << " " <<zEye << endl;
   gluLookAt (xEye, yEye, zEye, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   if(displayC0)
   {
      glColor3f (1, 0.871, 0);
      d.displaySplineC0(xRot, yRot, frustX, frustZ, frustYlower, frustYupper, yToORIG, zToORIG, elFactor);
   }
   else if(displayC1)
   {
      glColor3f(0.196, 0.804, 0.196);
      d.displaySplineC1(xRot, yRot, frustX, frustZ, frustYlower, frustYupper, yToORIG, zToORIG, elFactor);
   }
   else
   {
      glColor3f(0.196, 0.804, 0.6);
      d.displayKnots(xRot, yRot, frustX, frustZ, frustYlower, frustYupper, yToORIG, zToORIG, elFactor);
   }

   // if(zoomIn)
   // {
   //    glTranslatef(0.0,0.0,0.5);
   // }
   // else if(zoomOut)
   // {
   //  glTranslatef(0.0,0.0,0-0.5);
   // }
   glutSwapBuffers();
}

void init(string newGRD)
{
  //read in .grd, assign globals
	d.readIn(newGRD);
  d.getLimits(frustYlower,frustYupper);
  cout << frustYupper << "HERE"<< endl;
  CELL = d.getCellSize();
  frustX = d.getCols()*CELL;
  frustZ = d.getRows()*CELL;
  zEye = frustZ/CELL/2*CELL;
  frustYmid = (frustYupper+frustYlower)/2.0;
  yEye = frustYmid;
  yToORIG = -1*(frustYmid);
  zToORIG = frustZ;

	printTitle();
  glClearColor (0.0, 0.0, 0.098, 0.0);

    glShadeModel (GL_FLAT);

    // GET LOWER/UPPER bounds for FRUSTUM Y

    glEnable (GL_DEPTH_TEST);
    glLoadIdentity ();
    //d.print();
}

void resizeWindow(int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei) h);
   /* set up matrices for projection coordinate system */
   //glMatrixMode (GL_PROJECTION);
   
   if(frustX>frustZ)
   {
      frustPROJ = frustX;
   }
   else
   {
      frustPROJ = frustZ;
   		
   }
   ratio = (w*1.0)/(h*1.0);

   glMatrixMode (GL_PROJECTION);

   // ratio of width/height
   setPerspective();
   glMatrixMode (GL_MODELVIEW);
   
   /* reset matrices to user's coordinate system */
}

void setPerspective()
{

   gluPerspective(85.0, ratio*zoom, 0.1f, frustPROJ*2);

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
        cout << "Current Elevation: x" << elFactor << endl;
        glutPostRedisplay();
				break;
		case 4:
        if(elFactor > 1.0)
        {
          elFactor = elFactor/2; 
        }
        cout << "Current Elevation: x" << elFactor << endl;
        glutPostRedisplay();
				break;
		case 5: 
				displayC0 = false;
        displayC1 = false;
        displayKnots = true;
        elFactor = 1.0;
        cout << "\n\nCurrent Elevation: x" << elFactor << endl;
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
			 	  //yEye = ((yEye/(-1*zEye))*(zEye-5.0));
          // yEye -= 10.0;
          yEye *= 0.75;
          zEye *= 0.75;
          xEye *= 0.75;

              zoomIn = true;
              zoomOut = false;
              zoom *= 0.9;
              //frustPROJ += 10.0;
          //     glMatrixMode (GL_PROJECTION);

				      // setPerspective();
          //     glMatrixMode(GL_MODELVIEW);
          //     glLoadIdentity();
              //glutDisplayFunc(display);
              cout << zoom<<endl;
              

   			   glutPostRedisplay();
				  break;
		case '7': 
		//add in limit to zoom out
				  zEye += 0.5;
          zoomIn = false;
              zoomOut = true;
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
  cout << "                                                                             " << endl;
  cout << " File Selection:\n                                                        " << endl;                                   
  cout << " To choose a DEM from the list of sample files, include the filename as an argument"<< endl;
  cout << " when running the executable.  i.e. ~$ ./DelfinoG3 mt257.dem.grd\n" << endl;
  cout << "     - mt257.dem.grd (default) " << endl;
  cout << "     - test.grd" << endl;
  cout << "     - tucks.dem.grd\n\n" << endl;         
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
   if(argc>1)
   {
      glutCreateWindow(argv[1]);
      init(argv[1]);
      cout << "\n\nFile: " << argv[1] << endl;

   }
   else
   {
      glutCreateWindow("mt257.dem.grd");
      init(filename);
      cout << "\n\nFile: " << filename << endl;
   }
   initMenu();
   glutKeyboardFunc(keyboardInput);   // the default keyboard function of the openGL program
   glutDisplayFunc(display);        // the default display function of the openGL program
   glutReshapeFunc(resizeWindow);     // the default reshape function of the openGL program
   glutMainLoop(); 
   return 0;  
}
