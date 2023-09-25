#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "Utills.h"

Coord AdjustMouseCoordinate(Coord coord)
{
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
	GLint height = glutGet(GLUT_WINDOW_HEIGHT);

	coord.x = (coord.x - (width / 2)) / (width / 2);
	coord.y = -1 * (coord.y - (height / 2)) / (height / 2);

	return coord;
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}
