/*
 * Matrice3D.hpp
 *
 *  Created on: 14 nov. 2013
 *      Author: legeek
 */

#ifndef MATRICE3D_HPP_
#define MATRICE3D_HPP_

#include "Matrice3D.h"

template <typename T>
inline Matrice3D<T>::Matrice3D(T value)
{
	Matrice3D(value, value, value, value,
			  value, value, value, value,
			  value, value, value, value,
			  value, value, value, value);
}

template <typename T>
inline Matrice3D<T>::Matrice3D(T  a11, T  a12, T  a13, T  a14,
							   T  a21, T  a22, T  a23, T  a24,
							   T  a31, T  a32, T  a33, T  a34,
							   T  a41, T  a42, T  a43, T  a44)
{
	mat[0][0] = a11;
	mat[0][1] = a12;
	mat[0][2] = a13;
	mat[0][3] = a14;

	mat[1][0] = a21;
	mat[1][1] = a22;
	mat[1][2] = a23;
	mat[1][3] = a24;

	mat[2][0] = a31;
	mat[2][1] = a32;
	mat[2][2] = a33;
	mat[2][3] = a34;

	mat[3][0] = a41;
	mat[3][1] = a42;
	mat[3][2] = a43;
	mat[3][3] = a44;
}

template <typename T>
inline Matrice3D<T>::~Matrice3D() {}

template <typename T>
inline void Matrice3D<T>::dot(const Matrice3D<T> & matrixB)
{
	T tmpVal;
	T tabTmp[4][4];


	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			tabTmp[i][j] = mat[i][j];

	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			tmpVal = 0.0;
			for(int k = 0; k < 4; ++k)
			{
				tmpVal += (mat[i][k])*(matrixB.getValue(k, j));
			}
			tabTmp[i][j] = tmpVal;
		}
	}

	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			mat[i][j] = tabTmp[i][j];
}

template <typename T>
inline const T * Matrice3D<T>::getOpenGLMatrix() const throw()
{
	T tabRet[16];
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			tabRet[i*4+j] = getValue(j, i);

	return tabRet;
}

template <typename T>
inline const T & Matrice3D<T>::getValue(int row, int col) const throw(TpMathException)
{
	if(row < 4 && col < 4)
		return mat[row][col];
	else
		throw TpMathException("Invalid position");
}

#endif /* MATRICE3D_HPP_ */
