#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>


// extract map data from file
void bitMapExtraction(int* y, int* x, int** bitMap, const char* mapPath);

void loadMapBlocks(const char* grassPath, const char* dirtPath, Texture2D* grass, Texture2D* dirt);

// loads the map
void loadMap(FILE* mapFile, int* bitMap, int y, int x);

// gives the map size
void getMapSize(FILE* mapFile, int* y, int* x);

void printMapData(int* bitMap, int y, int x);

void drawMap(int bitMap[], int y, int x,  Texture2D grass, Texture2D dirt ,int TILESIZE);

