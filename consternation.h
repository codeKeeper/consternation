#ifndef CONSTERNATION
#define CONSTERNATION
#include <cstdlib>
#include <iostream>

using namespace std;

const int WIDTH = 100;
const int HEIGHT = 100;
const int DEPTH = 10;

class Area {
public:
	Area(int Type);
	int makeRooms();
	int** makeSingleRoom(int Type, int Width, int Height);
	int** makeDefaultRoom(int Width, int Height);
	int placeRoom(int width, int height);
	int makeForest();
	int makeBrokenRooms();
	int debugPrint();
private:
	int **arrayArea;
};

class World {
public:
	World();
	int debugPrint();
private:
	Area **TheWorld;
};

#endif
