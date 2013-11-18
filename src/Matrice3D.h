/*
 * Matrice3D.h
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef MATRICE3D_H_
#define MATRICE3D_H_

#include "TpMathException.h"

template <typename T>
class Matrice3D
{
	public:
		Matrice3D(T value = 0);
		Matrice3D(T  a11, T  a12, T  a13, T  a14,
				  T  a21, T  a22, T  a23, T  a24,
				  T  a31, T  a32, T  a33, T  a34,
				  T  a41, T  a42, T  a43, T  a44);
		virtual ~Matrice3D();

		void dot(const Matrice3D<T> & matrixB);

		const T & getValue(int row, int col) const throw(TpMathException);
		const T *  getOpenGLMatrix() const throw();

	private:
		T mat[4][4];
		void copyMatrix(T* target, T* ref);
};

#include "Matrice3D.hpp"

#endif /* MATRICE3D_H_ */
