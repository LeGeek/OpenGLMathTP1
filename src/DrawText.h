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
		DrawText(int x, int y, char * str);
		virtual ~DrawText();

		void draw();

	private:
		int x, y;
		char * string;
};

#endif /* DRAWTEXT_H_ */
