//============================================================================
// Name        : tpMath.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#include <GL/glut.h>

#include <cmath>
#include <cstdio>

#include "Matrice3D.h"
#include "Point3D.h"
#include "DrawText.h"

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600

#define ROTATE_VALUE		1
#define TRANSLATE_VALUE 	0.05
#define SCALE_VALUE 		0.01

using namespace std;

Point3D<GLfloat> * tabVertex[24];
Point3D<GLfloat> tmpPoint(0.0, 0.0, 0.0, 0.0);

Matrice3D<GLfloat> matTransfo(1.0, 0.0, 0.0, 0.0,
						   0.0, 1.0, 0.0, 0.0,
						   0.0, 0.0, 1.0, 0.0,
						   0.0, 0.0, 0.0, 1.0);

GLfloat transX = 0, transY = 0, transZ = 0;
GLfloat rotX = 0, rotY = 0, rotZ = 0;
GLfloat scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;

bool key8Pushed = false;
bool key2Pushed = false;
bool key4Pushed = false;
bool key6Pushed = false;
bool key7Pushed = false;
bool key9Pushed = false;

bool keyZPushed = false;
bool keyQPushed = false;
bool keySPushed = false;
bool keyDPushed = false;
bool keyEPushed = false;
bool keyAPushed = false;

bool keyPlusPushed = false;
bool keyMinusPushed = false;
bool keyIPushed = false;
bool keyKPushed = false;
bool keyOPushed = false;
bool keyLPushed = false;
bool keyPPushed = false;
bool keyMPushed = false;

DrawText textBot[] = {	DrawText(GLUT_BITMAP_9_BY_15, 5, HEIGHT_SCREEN - 31, (char*)"(Z/S   Q/D   A/E) = (Tx  Ty  Tz)", 1.0, 1.0, 1.0),
						DrawText(GLUT_BITMAP_9_BY_15, 5, HEIGHT_SCREEN - 16, (char*)"(Up/Down/8/2   Left/Right/4/6   7/9) = (Rx  Ry  Rz)", 1.0, 1.0, 1.0),
						DrawText(GLUT_BITMAP_9_BY_15, 5, HEIGHT_SCREEN - 1, (char*)"(I/K   O/L   P/M) = (Sx  Sy  Sz)    |    +/- : Scale Homogène", 1.0, 1.0, 1.0),
						DrawText(GLUT_BITMAP_9_BY_15, 5, 15, (char*)"FPS : XX", 1.0, 1.0, 1.0)};
char * tmp = new char[50];


void applyMatrixToVertices(const Matrice3D<GLfloat> & mat)
{
	for(unsigned i = 0; i < sizeof(tabVertex) / sizeof(tabVertex[0]); ++i)
			tabVertex[i]->dot(mat);
}

Matrice3D<GLfloat> genScale(GLfloat sX, GLfloat sY, GLfloat sZ)
{
	return Matrice3D<GLfloat>(sX, 0.0, 0.0, 0.0,
							  0.0, sY, 0.0, 0.0,
							  0.0, 0.0, sZ, 0.0,
							  0.0, 0.0, 0.0, 1.0);
}

Matrice3D<GLfloat> genTranslate(GLfloat tX, GLfloat tY, GLfloat tZ)
{
	return  Matrice3D<GLfloat>(1.0, 0.0, 0.0, tX,
							   0.0, 1.0, 0.0, tY,
							   0.0, 0.0, 1.0, tZ,
							   0.0, 0.0, 0.0, 1.0);
}

Matrice3D<GLfloat> genRotate(GLfloat deg, GLfloat coefX, GLfloat coefY, GLfloat coefZ)
{
	if(!deg)
		return Matrice3D<GLfloat>(1.0, 0.0, 0.0, 0.0,
								  0.0, 1.0, 0.0, 0.0,
								  0.0, 0.0, 1.0, 0.0,
								  0.0, 0.0, 0.0, 1.0);

	deg = (deg*3.14159265)/180;
	return Matrice3D<GLfloat>(coefX + coefY*cos(deg) + coefZ*cos(deg), 	coefZ*-sin(deg), 							coefY*sin(deg), 						 0.0,
							  coefZ*sin(deg), 							coefY + coefX*cos(deg) + coefZ*cos(deg), 	coefX*-sin(deg), 						 0.0,
							  coefY*-sin(deg), 							coefX*sin(deg), 							coefZ + coefX*cos(deg) + coefY*cos(deg), 0.0,
							  0.0, 										0.0, 										0.0, 									 1.0);
}

void initTabVertex()
{
	tabVertex[0] = new Point3D<GLfloat>( 1.0f, 1.0f,-1.0f, 1.0, 0.0, 1.0, 0.0);
	tabVertex[1] = new Point3D<GLfloat>(-1.0f, 1.0f,-1.0f, 1.0);
	tabVertex[2] = new Point3D<GLfloat>(-1.0f, 1.0f, 1.0f, 1.0);
	tabVertex[3] = new Point3D<GLfloat>( 1.0f, 1.0f, 1.0f, 1.0);

	tabVertex[4] = new Point3D<GLfloat>( 1.0f,-1.0f, 1.0f, 1.0, 1.0, 0.5, 0.0);
	tabVertex[5] = new Point3D<GLfloat>(-1.0f,-1.0f, 1.0f, 1.0);
	tabVertex[6] = new Point3D<GLfloat>(-1.0f,-1.0f,-1.0f, 1.0);
	tabVertex[7] = new Point3D<GLfloat>( 1.0f,-1.0f,-1.0f, 1.0);

	tabVertex[8] = new Point3D<GLfloat>( 1.0f, 1.0f, 1.0f, 1.0, 1.0, 0.0, 0.0);
	tabVertex[9] = new Point3D<GLfloat>(-1.0f, 1.0f, 1.0f, 1.0);
	tabVertex[10] = new Point3D<GLfloat>(-1.0f,-1.0f, 1.0f, 1.0);
	tabVertex[11] = new Point3D<GLfloat>( 1.0f,-1.0f, 1.0f, 1.0);

	tabVertex[12] = new Point3D<GLfloat>( 1.0f,-1.0f,-1.0f, 1.0, 1.0, 1.0, 0.0);
	tabVertex[13] = new Point3D<GLfloat>(-1.0f,-1.0f,-1.0f, 1.0);
	tabVertex[14] = new Point3D<GLfloat>(-1.0f, 1.0f,-1.0f, 1.0);
	tabVertex[15] = new Point3D<GLfloat>( 1.0f, 1.0f,-1.0f, 1.0);

	tabVertex[16] = new Point3D<GLfloat>(-1.0f, 1.0f, 1.0f, 1.0, 0.0, 0.0, 1.0);
	tabVertex[17] = new Point3D<GLfloat>(-1.0f, 1.0f,-1.0f, 1.0);
	tabVertex[18] = new Point3D<GLfloat>(-1.0f,-1.0f,-1.0f, 1.0);
	tabVertex[19] = new Point3D<GLfloat>(-1.0f,-1.0f, 1.0f, 1.0);

	tabVertex[20] = new Point3D<GLfloat>( 1.0f, 1.0f,-1.0f, 1.0, 1.0, 0.0, 1.0);
	tabVertex[21] = new Point3D<GLfloat>( 1.0f, 1.0f, 1.0f, 1.0);
	tabVertex[22] = new Point3D<GLfloat>( 1.0f,-1.0f, 1.0f, 1.0);
	tabVertex[23] = new Point3D<GLfloat>( 1.0f,-1.0f,-1.0f, 1.0);
}

void initValue()
{
	transX = transY = transZ = 0;
	rotX = rotY = rotZ = 0;
	scaleX = scaleY = scaleZ = 1.0;
}

void initGl()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void rotation()
{
	if(key8Pushed)
		rotX += ROTATE_VALUE;
	else if(key2Pushed)
		rotX -= ROTATE_VALUE;

	if(key4Pushed)
		rotY += ROTATE_VALUE;
	else if(key6Pushed)
		rotY -= ROTATE_VALUE;

	if(key7Pushed)
		rotZ += ROTATE_VALUE;
	else if(key9Pushed)
		rotZ -= ROTATE_VALUE;
}

void translation()
{
	if(keyQPushed)
		transX += TRANSLATE_VALUE;
	else if(keyDPushed)
		transX -= TRANSLATE_VALUE;

	if(keyZPushed)
		transY += TRANSLATE_VALUE;
	else if(keySPushed)
		transY -= TRANSLATE_VALUE;

	if(keyEPushed)
		transZ += TRANSLATE_VALUE;
	else if(keyAPushed)
		transZ -= TRANSLATE_VALUE;
}

void scaling()
{
	if(keyPlusPushed)
	{
		scaleX += SCALE_VALUE;
		scaleY += SCALE_VALUE;
		scaleZ += SCALE_VALUE;
	}
	else if(keyMinusPushed)
	{
		scaleX -= SCALE_VALUE;
		scaleY -= SCALE_VALUE;
		scaleZ -= SCALE_VALUE;
	}

	if(keyIPushed)
		scaleX += SCALE_VALUE;
	else if(keyKPushed)
		scaleX -= SCALE_VALUE;

	if(keyOPushed)
		scaleY += SCALE_VALUE;
	else if(keyLPushed)
		scaleY -= SCALE_VALUE;

	if(keyPPushed)
		scaleZ += SCALE_VALUE;
	else if(keyMPushed)
		scaleZ -= SCALE_VALUE;
}

void display2D()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, WIDTH_SCREEN, HEIGHT_SCREEN, 0, -1.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i < 4; ++i)
		textBot[i].draw();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	long beginTime = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 100.0, 0.0, 1.0, 0.0);

	translation();
	rotation();
	scaling();

	matTransfo.loadIdentity();
	matTransfo.dot(genTranslate(transX, transY, transZ));
	matTransfo.dot(genRotate(rotX, 1.0, 0.0, 0.0));
	matTransfo.dot(genRotate(rotY, 0.0, 1.0, 0.0));
	matTransfo.dot(genRotate(rotZ, 0.0, 0.0, 1.0));
	matTransfo.dot(genScale(scaleX, scaleY, scaleZ));

    glBegin(GL_QUADS);
    	for(unsigned i = 0; i < sizeof(tabVertex) / sizeof(tabVertex[0]); ++i)
    	{
    		glColor3f(tabVertex[i]->getColor(RED_VALUE),
    				  tabVertex[i]->getColor(GREEN_VALUE),
    				  tabVertex[i]->getColor(BLUE_VALUE));

    		tmpPoint = tabVertex[i]->dot(matTransfo);
    		glVertex3f(tmpPoint.getValue(X_VALUE),
    				   tmpPoint.getValue(Y_VALUE),
    				   tmpPoint.getValue(Z_VALUE));
    	}
	glEnd();

	display2D();

	glutSwapBuffers();
	glutPostRedisplay();

	sprintf(tmp, "FPS : %.0f", 1.0 / ((glutGet(GLUT_ELAPSED_TIME) - beginTime)/1000.0));
	textBot[3].setText(tmp);
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardDown(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27: //ESC
			exit(0);
			break;

		case 'z':
		case 'Z':
			keyZPushed = true;
			break;

		case 's':
		case 'S':
			keySPushed = true;
			break;

		case 'q':
		case 'Q':
			keyQPushed = true;
			break;

		case 'd':
		case 'D':
			keyDPushed = true;
			break;

		case 'a':
		case 'A':
			keyAPushed = true;
			break;

		case 'e':
		case 'E':
			keyEPushed = true;
			break;

		case 'i':
		case 'I':
			keyIPushed = true;
			break;

		case 'k':
		case 'K':
			keyKPushed = true;
			break;

		case 'o':
		case 'O':
			keyOPushed = true;
			break;

		case 'l':
		case 'L':
			keyLPushed = true;
			break;

		case 'p':
		case 'P':
			keyPPushed = true;
			break;

		case 'm':
		case 'M':
			keyMPushed = true;
			break;

		case '+':
			keyPlusPushed = true;
			break;

		case '-':
			keyMinusPushed = true;
			break;

		case '8':
			key8Pushed = true;
			break;

		case '2':
			key2Pushed = true;
			break;

		case '6':
			key6Pushed = true;
			break;

		case '4':
			key4Pushed = true;
			break;

		case '7':
			key7Pushed = true;
			break;

		case '9':
			key9Pushed = true;
			break;

		default:
			cerr << "[Keyboard Down] key = '" << key << "' (" << (int)(key) << ") x = " << x << " y = " << y << endl;
			return;
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'z':
		case 'Z':
			keyZPushed = false;
			break;

		case 's':
		case 'S':
			keySPushed = false;
			break;

		case 'q':
		case 'Q':
			keyQPushed = false;
			break;

		case 'd':
		case 'D':
			keyDPushed = false;
			break;

		case 'a':
		case 'A':
			keyAPushed = false;
			break;

		case 'e':
		case 'E':
			keyEPushed = false;
			break;

		case 'i':
		case 'I':
			keyIPushed = false;
			break;

		case 'k':
		case 'K':
			keyKPushed = false;
			break;

		case 'o':
		case 'O':
			keyOPushed = false;
			break;

		case 'l':
		case 'L':
			keyLPushed = false;
			break;

		case 'p':
		case 'P':
			keyPPushed = false;
			break;

		case 'm':
		case 'M':
			keyMPushed = false;
			break;

		case '+':
			keyPlusPushed = false;
			break;

		case '-':
			keyMinusPushed = false;
			break;

		case '8':
			key8Pushed = false;
			break;

		case '2':
			key2Pushed = false;
			break;

		case '6':
			key6Pushed = false;
			break;

		case '4':
			key4Pushed = false;
			break;

		case '7':
			key7Pushed = false;
			break;

		case '9':
			key9Pushed = false;
			break;

		case 'r':
		case 'R':
			initValue();
			break;


		case 'f':
			glutFullScreen();
			break;

		case 'F':
			glutPositionWindow(10, 10);
			break;

		default:
			cerr << "[Keyboard Up] key = '" << key << "' (" << (int)(key) << ") x = " << x << " y = " << y << endl;
			return;
	}
}

void specialKeyboardDown(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			key8Pushed = true;
			break;

		case GLUT_KEY_DOWN:
			key2Pushed = true;
			break;

		case GLUT_KEY_LEFT:
			key4Pushed = true;
			break;

		case GLUT_KEY_RIGHT:
			key6Pushed = true;
			break;

		default:
			return;
	}
}

void specialKeyboardUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			key8Pushed = false;
			break;

		case GLUT_KEY_DOWN:
			key2Pushed = false;
			break;

		case GLUT_KEY_LEFT:
			key4Pushed = false;
			break;

		case GLUT_KEY_RIGHT:
			key6Pushed = false;
			break;

		default:
			return;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(WIDTH_SCREEN, HEIGHT_SCREEN);
	glutCreateWindow(argv[0]);

	initGl();
	initTabVertex();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyboardDown);
	glutSpecialUpFunc(specialKeyboardUp);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();

	return 0;
}
