//---------------------------------------------------------------------
// GLUT
// Autor: Pavel Tisnovsky + Vojtech Havlicek
//
// Zakladni kostra programu pro praci s knihovnami OpenGL a GLUT.
// Program pouze otevre okno, do ktereho lze vykreslovat pomoci OpenGL.
//---------------------------------------------------------------------

#include <GL/glut.h> // hlavickovy soubor funkci GLUTu
#include <iostream>  // input/output stream pro debug

//
// Uses the standard namespace for io operations
//
using namespace std;

//ukazatele na okna
int win1, win2;

//---------------------------------------------------------------------
// Nastaveni souradneho systemu v zavislosti na velikosti okna
//---------------------------------------------------------------------
void onResize(int w, int h)             // w a h reprezentuje novou velikost okna
{
	//Trasuje
	cout << "Window resized: " << w << "\t" << h << "\n";

    glViewport(0, 0, w, h);             // viditelna oblast pres cele okno
    glMatrixMode(GL_PROJECTION);        // zacatek modifikace projekcni matice
    glLoadIdentity();                   // vymazani projekcni matice (=identita)
    glOrtho(0, w, 0, h, -1, 1);         // mapovani abstraktnich souradnic do souradnic okna
    glScalef(1, -1, 1);                 // inverze y-ove osy, aby se y zvetsovalo smerem dolu
    glTranslatef(0, -h, 0);             // posun pocatku do leveho horniho rohu
}



//---------------------------------------------------------------------
// Tato funkce je volana pri kazdem prekresleni okna
//---------------------------------------------------------------------
void onDisplay(void)
{
	int currentWindow = glutGetWindow();
	//Trasuje
	cout << "onDisplay was fired on window id:" << currentWindow  << "\n";

	//Draw grey
	if(currentWindow == win1){
		glClearColor( 0.5, 0.5, 0.5, 0.0);
	}else if(currentWindow == win2)
	{
		glClearColor( 0.5, 0.5, 1.0, 0.0);
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
        case 'x':                       // stlaceni techto klaves uzavre aplikaci
        case 'q':
        case 27:                        // 27 je kod klavesy ESC
            exit(0);
            break;
        case 'w':                       // klavesa 'w' zpusobi
            glutReshapeWindow(200, 200);// zmenseni okna
            glutPositionWindow(100, 100);
            break;
        case 'f':                       // klavesa 'f' zpusobi
            glutFullScreen();           // prepnuti na celou obrazovku
            break;
    }
}

//---------------------------------------------------------------------
// Hlavni funkce konzolove aplikace
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);              // inicializace knihovny GLUT
	glutInitWindowSize(200,200);
	
	glutInitWindowPosition(0,0);
    win1 = glutCreateWindow("Hello World, GLUT");// vytvoreni okna pro kresleni
	glutSetWindow(win1);
    glutDisplayFunc(onDisplay);         // registrace funkce volane pri prekreslovani okna
    glutReshapeFunc(onResize);          // registrace funkce volane pri zmene velikosti okna
	glutKeyboardUpFunc(onKeyboard);     // registrace funkce volane pri release tlacitka

	glutMainLoop();

    return 0;                           // navratova hodnota vracena operacnimu systemu
}



//---------------------------------------------------------------------
// Konec zdrojoveho souboru
//---------------------------------------------------------------------
