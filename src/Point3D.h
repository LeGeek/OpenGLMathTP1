/*
 * Point3D.h
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include "Matrice3D.h"

enum Point3DValue
{
	X_VALUE = 0,
	Y_VALUE,
	Z_VALUE,
	W_VALUE
};

template <typename T>
class Point3D
{
	public:
		Point3D(T x, T y, T z, T w);
		virtual ~Point3D();

		const Point3D<T> dot(const Matrice3D<T> & m);

		const T & getValue(Point3DValue val) const;

	private:
		T point[4];
};

#include "Point3D.hpp"

#endif /* POINT3D_H_ */
