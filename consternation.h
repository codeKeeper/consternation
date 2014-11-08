#ifndef CONSTERNATION
#define CONSTERNATION
#include <cstdlib>
#include <iostream>
#include <stack>
#include <random>
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 40;
const int DEPTH = 1;

class Area {
public:
	Area(int Type);
	int makeRooms();
	int** makeSingleRoom(int Type, int Width, int Height);
	int** makeDefaultRoom(int Width, int Height);
	int placeRoom(int width, int height,int **room, int &roomcount, int *startPoint);
	int connectRooms(int *startPoint, int roomCount);
	int dfs(int x, int y, int roomCount);
	int randomWalk(int &x, int &y);
	int Set(int x, int y);
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
