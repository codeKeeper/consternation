#include "consternation.h"

//Higher number implies more dense room count
const int ROOMDENSITY = 10;
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

int Area::placeRoom(int width, int height, int **room) {
	int tempWidth;
	int tempHeight;
	int found = 1;

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> Wdist(0, WIDTH - width - 1);
    std::uniform_int_distribution<int> Hdist(0, HEIGHT - height - 1);

	for(unsigned i = 0; i < ROOMDENSITY; ++i) {
		tempWidth = Wdist(mt);
		tempHeight = Hdist(mt);

		found = 1;
		for(unsigned j = 0; j < height; ++j) {
			for(unsigned k = 0; k < width; ++k) {
				if (arrayArea[tempWidth + k][tempHeight + j] != 0 
						&& room[k][j] != 0) {
					found = 0;
				}
			}
		}
		if (found) {
			for(unsigned j = 0; j < height; ++j) {
				for(unsigned k = 0; k < width; ++k) {
					arrayArea[tempWidth + k][tempHeight + j] = room[k][j];
				}
			}
			return 1;
		}
	}
	return 0;
}

int Area::makeRooms() {
	int **RoomTemp;
	int widthTemp;
	int heightTemp;

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> Wdist(3, MAX_ROOM_WIDTH - 1);
    std::uniform_int_distribution<int> Hdist(3, MAX_ROOM_HEIGHT - 1);

	while (true) {

		widthTemp = Wdist(mt);
		heightTemp = Hdist(mt);

		RoomTemp = makeSingleRoom(1, widthTemp, heightTemp);

		if (!placeRoom(widthTemp, heightTemp, RoomTemp)) {
			break;
		}
	}
	return 0;
}

int Area::debugPrint() {
	cout << "\n";
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