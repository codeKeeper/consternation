#include "consternation.h"

//Higher number implies more dense room count
const int ROOMDENSITY = 3;
const int MAX_ROOM_WIDTH = 10;
const int MAX_ROOM_HEIGHT = 10;

int** Area::makeDefaultRoom(int Width, int Height) {
	int **toReturn;

	toReturn = new int*[Width];
	for(unsigned i = 0; i < Width; ++i) {
		toReturn[i] = new int[Height];
	}

	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j)
		{
			if (i ==0 || j == 0 || i == Height-1 || j == Width-1) {
				toReturn[j][i] = 1;
			} else {
				toReturn[j][i] = 2;
			}
		}
	}
	return toReturn;
}

int** Area::makeSingleRoom(int Type, int Width, int Height) {
	switch(Type) {
		case 1:
			return makeDefaultRoom(Width, Height);
			break;
		default:
			return makeDefaultRoom(Width, Height);
			break;

	}
	return NULL;
}

int Area::placeRoom(int width, int height) {
	int tempWidth;
	int tempHeight;
	for(unsigned i = 0; i < ROOMDENSITY; ++i) {
		tempWidth = rand() % (WIDTH - width);
		tempHeight = rand() % (HEIGHT - height);

		for(unsigned j = 0; j < height; ++j) {
			for(unsigned k = 0; k < width; ++k) {
			}
		}
	}
	return 0;
}

int Area::makeRooms() {
	int **RoomTemp;
	int widthTemp;
	int heightTemp;

	widthTemp = rand() % MAX_ROOM_WIDTH;
	heightTemp = rand() % MAX_ROOM_HEIGHT;

	while (true) {

		RoomTemp = makeSingleRoom(1, widthTemp, heightTemp);

		if (!placeRoom(widthTemp, heightTemp)) {
			break;
		}
	}
	return 0;
}

int Area::debugPrint() {
	for(unsigned i = 0; i < HEIGHT; ++i) {
		for(unsigned j = 0; j < WIDTH; ++j) {
			cout << arrayArea[j][i] << " ";
		}
		cout << "\n";
	}
	return 1;
}

Area::Area(int Type) {
	arrayArea = new int*[WIDTH];
	for (unsigned i = 0; i < WIDTH; i++) {
		arrayArea[i] = new int[HEIGHT];
	}

	switch(Type) {
		case 1:
			makeRooms();
			break;
		case 2:
			//makeForst();
			break;
		case 3:
			//makeBrokenRooms();
		default:
			//makeRooms();
			break;

	}
}