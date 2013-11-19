/*
 * DrawText.hpp
 *
 *  Created on: 18 nov. 2013
 *      Author: legeek
 */

#ifndef DRAWTEXT_HPP_
#define DRAWTEXT_HPP_

#include "DrawText.h"

#include <iostream>

inline DrawText::DrawText(int posX, int posY, char * str, GLfloat red, GLfloat green, GLfloat blue) : x(posX), y(posY), r(red), g(green), b(blue), string(str) {}
inline DrawText::~DrawText() {}

inline void DrawText::setText(char * str) { string = str; }
inline void DrawText::setPosition(int newX, int newY)
{
	x = newX;
	y = newY;
}
inline void DrawText::setColor(GLfloat red, GLfloat green, GLfloat blue)
{
	r = red;
	g = green;
	b = blue;
}

inline char * DrawText::getString() const { return string; }
inline GLfloat DrawText::getRed() const { return r; }
inline GLfloat DrawText::getGreen() const { return g; }
inline GLfloat DrawText::getBlue() const { return b; }
inline int DrawText::getX() const { return x; }
inline int DrawText::getY() const { return y; }

inline void DrawText::draw()
{
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	for(int i = 0; string[i] != '\0'; ++i)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

#endif /* DRAWTEXT_HPP_ */
