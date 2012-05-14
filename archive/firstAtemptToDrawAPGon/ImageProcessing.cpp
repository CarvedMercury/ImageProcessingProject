//---------------------------------------------------------------------
//
// Imperial College London
//
// Project: Image Processing Using GPU 
//
// Author: Vojtech Havlicek, Daniel Greening
//
// The original code for GLUT initialization was adapted from 
// Pavel Tisnovsky's tutorial at Root.cz
// 
//---------------------------------------------------------------------

#include <GL/glut.h> // header file of GLUT functions
#include <iostream>  // input/output stream for debug

//
// Uses the standard namespace for io operations
//
using namespace std;

// Pointers to application window
int win1;

// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
float W = 512.0;
float H = 512.0;

/**
Functions
*/
//Function identifiers
int openGLDrawScene(GLvoid);
int openGLInit(GLvoid);
//---------------------------------------------------------------------
// Settings of the coords based on the window size, if resized.
//---------------------------------------------------------------------
void onResize(int w, int h)             // w & h are the dimensions of window
{
	//trace to console
	cout << "Window resized: " << w << "\t" << h << "\n";
	W = w;
	H = h;
    glViewport(0, 0, w, h);             // visible area across the whole window
    glMatrixMode(GL_PROJECTION);        // modification matrix beginning
    glLoadIdentity();                   // vymazani projekcni matice (=identita)
    glOrtho(0, w, 0, h, -1, 1);         // mapovani abstraktnich souradnic do souradnic okna
    glScalef(1, -1, 1);                 // inverze y-ove osy, aby se y zvetsovalo smerem dolu
    glTranslatef(0, -h, 0);             // posun pocatku do leveho horniho rohu
}

//---------------------------------------------------------------------
// Tato funkce je volana pri kazdem prekresleni okna
// This function is called on every refresh of the window.
//---------------------------------------------------------------------
void onDisplay(void)
{
	int currentWindow = glutGetWindow();
	//Trasuje
	cout << "onDisplay was fired on window id:" << currentWindow  << "\n";

	//Draw grey
	if(currentWindow == win1){ // if window which fired onDisplay is the first one, redraw
		cout<<"Window "<< win1 << " was redrawn" << "\n";
		openGLDrawScene();
	}

	//Draw White
	glClear(GL_COLOR_BUFFER_BIT);       // vymazani bitovych rovin barvoveho bufferu
	glFlush();                          // provedeni a vykresleni zmen
}

//
// Funkce vstupu klavesnice
//
void onKeyboard(unsigned char key, int x, int y)
{
	key=(key>'A' && key<='Z') ? key+'a'-'A':key; // prevod na mala pismena
    switch (key) {
		
		//--- EXIT CASES
        case 'x':                       // stlaceni techto klaves uzavre aplikaci
        case 'q':
        case 27:                        // 27 je kod klavesy ESC
            exit(0);
        break;
        
		//----------------------------------
		case 'f':  // klavesa 'f' zpusobi
			if(!fullscreen){
				fullscreen = true;
				glutFullScreen();           // prepnuti na celou obrazovku
			}else{
				glutReshapeWindow(W, H);// zmenseni okna
				glutPositionWindow(200, 200);
				fullscreen = false;
			}

        break;
    }
}

//---------------------------------------------------------------------
// Hlavni funkce konzolove aplikace
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
	/**
	Prepares GLUT
	*/
    glutInit(&argc, argv);              // inicializace knihovny GLUT
	glutInitWindowSize(W,H);
	glutInitWindowPosition(200,200);

	/**
	Prepares openGL
	*/
	openGLInit();

	/**
	Create the new Window
	*/
    win1 = glutCreateWindow("Image Processing Project");// vytvoreni okna pro kresleni
	glutSetWindow(win1);
    glutDisplayFunc(onDisplay);         // registrace funkce volane pri prekreslovani okna
    glutReshapeFunc(onResize);          // registrace funkce volane pri zmene velikosti okna
	glutKeyboardUpFunc(onKeyboard);     // registrace funkce volane pri release tlacitka

	/**
	Starts the main GLUT loop
	*/
	glutMainLoop(); //starts the main loop of the app.

    return 0;                           // navratova hodnota vracena operacnimu systemu
}


/**
Initialization function for openGL. Setups the OpenGL in the beginning.
Check if it does not collide with GLUT initialization.
*/

int openGLInit(GLvoid)
{
	glShadeModel(GL_SMOOTH); //Enables smooth shading
	
	glClearColor(0.5f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Make perspective corrections
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return 0;
}

//-----------------------------------------------------------------------------------------
//
//	An entry point function for all OpenGL drawing. Called at onDisplay.
//
int openGLDrawScene(GLvoid) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the screen and depth buffers
	glMatrixMode(GL_PROJECTION); //Select the projection matrix? Next 2 lines will affect the matrix.
	glLoadIdentity(); //Resets the projection matrix.
	gluPerspective(30.0f,(GLfloat)W/(GLfloat)H,0.1f,100.0f); // sets the perspective

	glMatrixMode(GL_MODELVIEW); // Select the modelview Matrix ?? (What it means?).
	/** NeHe >>
		The new transformation will affect the modelview matrix (matrix storing information about how to redraw the objects)
	*/
	
	glLoadIdentity();
	/**
	Draws a triangle
	*/
	cout << "Triangle drawing";

	glTranslatef(-1.5f,0.0f,-6.0f);

	glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, - 1.0f, 0.0f);
	glEnd();
	

	return 0;
}

