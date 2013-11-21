/*
 * Point3D.hpp
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef POINT3D_HPP_
#define POINT3D_HPP_

#include "Point3D.h"

#include <iostream>

template <typename T>
GLfloat Point3D<T>::lastColor[3] = {0.0, 0.0, 0.0};

template <typename T>
inline Point3D<T>::Point3D(T x, T y, T z, T w)
{
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = w;

	color[0] = lastColor[0];
	color[1] = lastColor[1];
	color[2] = lastColor[2];
}

template <typename T>
inline Point3D<T>::Point3D(T x, T y, T z, T w, GLfloat red, GLfloat green, GLfloat blue)
{
	point[0] = x;
	point[1] = y;
	point[2] = z;
	point[3] = w;

	color[0] = lastColor[0] = red;
	color[1] = lastColor[1] = green;
	color[2] = lastColor[2] = blue;
}

template <typename T>
inline Point3D<T>::~Point3D() {}

template <typename T>
inline const T & Point3D<T>::getValue(Point3DValue val) const { return point[val]; }

template <typename T>
inline const GLfloat Point3D<T>::getColor(Point3DColor val) const { return color[val]; }

template <typename T>
inline const Point3D<T> Point3D<T>::dot(const Matrice3D<T> & m)
{
	T tmpPts[4];
	T tmpVal;

	for(int i = 0; i < 4; ++i)
		tmpPts[i] = point[i];

	for(int i = 0; i < 4; ++i)
	{
		tmpVal = 0;
		for(int j = 0; j < 4; ++j)
		{
			tmpVal += point[j]*m.getValue(i, j);
		}
		tmpPts[i] = tmpVal;
	}

	return Point3D<T>(tmpPts[0], tmpPts[1], tmpPts[2], tmpPts[3]);
}


#endif /* POINT3D_HPP_ */
