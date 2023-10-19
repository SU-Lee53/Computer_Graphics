#pragma once


Coord AdjustMouseCoordinate(Coord coord);

char* filetobuf(const char* filename);

Coord GetRandomCoord();

RGB GetRandomRGB();

void DrawAxis();

void SetBackground(RGB rgb);