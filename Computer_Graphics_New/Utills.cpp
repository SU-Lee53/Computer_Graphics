#include "pch.h"
#include "Utills.h"

GL_Coord AdjustMouseCoordinate(GL_Coord coord)
{
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
	GLint height = glutGet(GLUT_WINDOW_HEIGHT);

	coord.x = (coord.x - (width / 2)) / (width / 2);
	coord.y = -1 * (coord.y - (height / 2)) / (height / 2);

	return coord;
}