/*
 * DrawText.h
 *
 *  Created on: 18 nov. 2013
 *      Author: legeek
 */

#ifndef DRAWTEXT_H_
#define DRAWTEXT_H_

#include <GL/glut.h>

class DrawText
{
	public:
		DrawText(void * font = GLUT_BITMAP_9_BY_15, int x = 0, int y = 0, char * str = '\0', GLfloat red = 0.0, GLfloat green = 0.0, GLfloat blue = 0.0);
		virtual ~DrawText();

		void setPosition(int x, int y);
		void setText(char * str);
		void setColor(GLfloat red, GLfloat green, GLfloat blue);
		void setFont(void * newFont);

		int getX() const;
		int getY() const;
		GLfloat getRed() const;
		GLfloat getGreen() const;
		GLfloat getBlue() const;
		char * getString() const;
		void * getFont() const;

		void draw();

	private:
		int x, y;
		GLfloat r, g, b;
		char * string;
		void * font;
};

#include "DrawText.hpp"

#endif /* DRAWTEXT_H_ */
