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

#define GLEW_STATIC
#include "textfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <GL/glew.h> // header file of GLEW;
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
void openGLDrawScene();
int openGLInit(GLvoid);
char *textFileRead(char *);
void setShaders();

//

GLuint p, v, f;

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
	cout << "Image Processing Using GPU \n\nCreated by Vojtech Havlicek & Daniel Greening (2012)\nSupervised by Lionel Fachkamps\nImperial College\n---\nOutput:\n";
	/**
	Prepares GLUT
	*/
    glutInit(&argc, argv);              // inicializace knihovny GLUT
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W,H);
	glutInitWindowPosition(200,200);

	/**
	Create the new Window
	*/
    win1 = glutCreateWindow("Image Processing Project");// vytvoreni okna pro kresleni
	glutDisplayFunc(openGLDrawScene);         // registrace funkce volane pri prekreslovani okna
	glutIdleFunc(openGLDrawScene);

	openGLInit();

	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		cout << "Shaders supported" << "\n";
	}

	
	/**
	Starts the main GLUT loop
	*/
	setShaders();
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
GLuint testShader;
float a = 0.0;
void openGLDrawScene() 
{
	/**
	Entry Point Here
	*/
	testShader = glCreateShader(GL_VERTEX_SHADER);

	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ???
	
	glutSolidTeapot(0.5);
	glRotatef(a, 1.0f, 1.0f, 1.0f);
	a+= 0.0001;

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex2f(-0.5,-0.5);
		//glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(0.5,0.0);
		glColor3f(0.0f,1.0f,1.0f);
		glVertex2f(0.0,0.5);
	glEnd();

	glutSwapBuffers();
}

void setShaders() {

	char *vs,*fs;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);	

	vs = textFileRead("minimal.vert");
	fs = textFileRead("minimal.frag");

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	p = glCreateProgram();

	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
	glUseProgram(p);
}