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

#include "Matrice3D.h"
#include "Point3D.h"

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600

#define ROTATE_VALUE		1
#define TRANSLATE_VALUE 	0.05
#define SCALE_UP 			1.01
#define SCALE_DOWN 			0.99

using namespace std;

Point3D<GLfloat> posCam(0.0, 0.0, -5.0, 1.0);
Point3D<GLfloat> * tabColor[12];
Point3D<GLfloat> * tabVertex[12];

bool keyRotUpXPushed = false;
bool keyRotDownXPushed = false;
bool keyRotUpYPushed = false;
bool keyRotDownYPushed = false;

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

enum axe
{
	X = 0,
	Y,
	Z
};

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

Matrice3D<GLfloat> genTranslate(GLfloat unit, axe up)
{


	return  Matrice3D<GLfloat>(1.0, 0.0, 0.0, (up == X ? unit : 0.0),
							   0.0, 1.0, 0.0, (up == Y ? unit : 0.0),
							   0.0, 0.0, 1.0, (up == Z ? unit : 0.0),
							   0.0, 0.0, 0.0, 1.0);
}

Matrice3D<GLfloat> genRotate(GLfloat deg, axe angle)
{
	deg = (deg*3.14159265)/180;
	switch(angle)
	{
		case X:
			return Matrice3D<GLfloat>(1.0f, 0.0f, 0.0f, 0.0f,
									  0.0f, cos(deg), -sin(deg), 0.0f,
									  0.0f, sin(deg), cos(deg), 0.0f,
									  0.0f, 0.0f, 0.0f, 1.0f);
			break;
		case Y:

			return Matrice3D<GLfloat>(cos(deg), 0.0f, sin(deg), 0.0f,
									  0.0f, 1.0f, 0.0f, 0.0f,
									  -sin(deg), 0.0f, cos(deg), 0.0f,
									  0.0f, 0.0f, 0.0f, 1.0f);
			break;

		case Z:
			return Matrice3D<GLfloat>(cos(deg), -sin(deg), 0.0f, 0.0f,
									  sin(deg), cos(deg), 0.0f, 0.0f,
									  0.0f, 0.0f, 1.0f, 0.0f,
									  0.0f, 0.0f, 0.0f, 1.0f);
			break;

		default:
			break;
	}

	throw TpMathException("Invalid angle");
}

void initTabVertex()
{
	tabColor[0] = new Point3D<GLfloat>(1.0f, 0.0f, 0.0f, 0.0f);
	tabVertex[0] = new Point3D<GLfloat>(0.0f, 1.0f, 0.0f, 0.0f);
	tabColor[1] = new Point3D<GLfloat>(0.0f,1.0f,0.0f, 0.0f);
	tabVertex[1] = new Point3D<GLfloat>(-1.0f,-1.0f, 1.0f, 0.0f);
	tabColor[2] = new Point3D<GLfloat>(0.0f,0.0f,1.0f, 0.0f);
	tabVertex[2] = new Point3D<GLfloat>( 1.0f,-1.0f, 1.0f, 0.0f);
	tabColor[3] = new Point3D<GLfloat>(1.0f,0.0f,0.0f, 0.0f);
	tabVertex[3] = new Point3D<GLfloat>( 0.0f, 1.0f, 0.0f, 0.0f);
	tabColor[4] = new Point3D<GLfloat>(0.0f,0.0f,1.0f, 0.0f);
	tabVertex[4] = new Point3D<GLfloat>( 1.0f,-1.0f, 1.0f, 0.0f);
	tabColor[5] = new Point3D<GLfloat>(0.0f,1.0f,0.0f, 0.0f);
	tabVertex[5] = new Point3D<GLfloat>( 1.0f,-1.0f, -1.0f, 0.0f);
	tabColor[6] = new Point3D<GLfloat>(1.0f,0.0f,0.0f, 0.0f);
	tabVertex[6] = new Point3D<GLfloat>( 0.0f, 1.0f, 0.0f, 0.0f);
	tabColor[7] = new Point3D<GLfloat>(0.0f,1.0f,0.0f, 0.0f);
	tabVertex[7] = new Point3D<GLfloat>( 1.0f,-1.0f, -1.0f, 0.0f);
	tabColor[8] = new Point3D<GLfloat>(0.0f,0.0f,1.0f, 0.0f);
	tabVertex[8] = new Point3D<GLfloat>(-1.0f,-1.0f, -1.0f, 0.0f);
	tabColor[9] = new Point3D<GLfloat>(1.0f,0.0f,0.0f, 0.0f);
	tabVertex[9] = new Point3D<GLfloat>( 0.0f, 1.0f, 0.0f, 0.0f);
	tabColor[10] = new Point3D<GLfloat>(0.0f,0.0f,1.0f, 0.0f);
	tabVertex[10] = new Point3D<GLfloat>(-1.0f,-1.0f,-1.0f, 0.0f);
	tabColor[11] = new Point3D<GLfloat>(0.0f,1.0f,0.0f, 0.0f);
	tabVertex[11] = new Point3D<GLfloat>(-1.0f,-1.0f, 1.0f, 0.0f);
}

void initGl()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

void rotation()
{
	if(keyRotUpXPushed)
		applyMatrixToVertices(genRotate(ROTATE_VALUE, X));

	if(keyRotDownXPushed)
		applyMatrixToVertices(genRotate(-ROTATE_VALUE, X));

	if(keyRotUpYPushed)
		applyMatrixToVertices(genRotate(ROTATE_VALUE, Y));

	if(keyRotDownYPushed)
		applyMatrixToVertices(genRotate(-ROTATE_VALUE, Y));
}

void translation()
{
	if(keyZPushed)
		posCam.dot(genTranslate(-TRANSLATE_VALUE, Y));

	if(keySPushed)
		posCam.dot(genTranslate(TRANSLATE_VALUE, Y));

	if(keyQPushed)
		posCam.dot(genTranslate(-TRANSLATE_VALUE, X));

	if(keyDPushed)
		posCam.dot(genTranslate(TRANSLATE_VALUE, X));

	if(keyEPushed)
		posCam.dot(genTranslate(-TRANSLATE_VALUE, Z));

	if(keyAPushed)
		posCam.dot(genTranslate(TRANSLATE_VALUE, Z));
}

void scaling()
{
	if(keyPlusPushed)
		applyMatrixToVertices(genScale(SCALE_UP, SCALE_UP, SCALE_UP));

	if(keyMinusPushed)
		applyMatrixToVertices(genScale(SCALE_DOWN, SCALE_DOWN, SCALE_DOWN));

	if(keyIPushed)
		applyMatrixToVertices(genScale(SCALE_UP, 1.0, 1.0));

	if(keyKPushed)
		applyMatrixToVertices(genScale(SCALE_DOWN, 1.0, 1.0));

	if(keyOPushed)
		applyMatrixToVertices(genScale(1.0, SCALE_UP, 1.0));

	if(keyLPushed)
		applyMatrixToVertices(genScale(1.0, SCALE_DOWN, 1.0));

	if(keyPPushed)
		applyMatrixToVertices(genScale(1.0, 1.0, SCALE_UP));

	if(keyMPushed)
		applyMatrixToVertices(genScale(1.0, 1.0, SCALE_DOWN));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();

	gluLookAt(posCam.getValue(X_VALUE), posCam.getValue(Y_VALUE), posCam.getValue(Z_VALUE), 0.0, 0.0, 100.0, 0.0, 1.0, 0.0);

	translation();
	rotation();
	scaling();

    glBegin(GL_TRIANGLES);
    	for(unsigned i = 0; i < sizeof(tabVertex) / sizeof(tabVertex[0]); ++i)
    	{
    		glColor3f(tabColor[i]->getValue(X_VALUE),
					  tabColor[i]->getValue(Y_VALUE),
					  tabColor[i]->getValue(Z_VALUE));
    		glVertex3f(tabVertex[i]->getValue(X_VALUE),
					   tabVertex[i]->getValue(Y_VALUE),
					   tabVertex[i]->getValue(Z_VALUE));
    	}
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)WIDTH_SCREEN/(GLfloat)HEIGHT_SCREEN,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void specialKeyboardDown(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			keyRotUpXPushed = true;
			break;

		case GLUT_KEY_DOWN:
			keyRotDownXPushed = true;
			break;

		case GLUT_KEY_LEFT:
			keyRotUpYPushed = true;
			break;

		case GLUT_KEY_RIGHT:
			keyRotDownYPushed = true;
			break;

		default:
			cerr << "[Keyboard Special] key = " << key << " x = " << x << " y = " << y << endl;
			break;
	}
}

void specialKeyboardUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			keyRotUpXPushed = false;
			break;

		case GLUT_KEY_DOWN:
			keyRotDownXPushed = false;
			break;

		case GLUT_KEY_LEFT:
			keyRotUpYPushed = false;
			break;

		case GLUT_KEY_RIGHT:
			keyRotDownYPushed = false;
			break;

		default:
			cerr << "[Keyboard Special] key = " << key << " x = " << x << " y = " << y << endl;
			break;
	}
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

		default:
			cerr << "[Keyboard Down] key = '" << key << "' (" << (int)(key) << ") x = " << x << " y = " << y << endl;
			break;
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


		case 'r':
		case 'R':
			initTabVertex();
			break;

		default:
			cerr << "[Keyboard Up] key = '" << key << "' (" << (int)(key) << ") x = " << x << " y = " << y << endl;
			break;
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
	glutSpecialFunc(specialKeyboardDown);
	glutSpecialUpFunc(specialKeyboardUp);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutIgnoreKeyRepeat(1);
	glutMainLoop();

	return 0;
}
