#include <math.h>

namespace MatrixGenerator
{
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
}
