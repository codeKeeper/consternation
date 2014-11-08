#include "consternation.h"

//Higher number implies more dense room count
const int ROOMDENSITY = 10;
const int MAX_ROOM_WIDTH = 10;
const int MAX_ROOM_HEIGHT = 10;
const int RANDOM_WALK_STEP = 5;

int** Area::makeDefaultRoom(int Width, int Height) {
	int **toReturn;

	bool Walkpoint = false;

	toReturn = new int*[Width];
	for(unsigned i = 0; i < Width; ++i) {
		toReturn[i] = new int[Height];
	}

	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j)
		{
			if (Walkpoint == false) {
				toReturn[j][i] = 2;
				Walkpoint = true;
			} else {	
				toReturn[j][i] = 1;
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

int Area::placeRoom(int width, int height, int **room, int &roomcount, int *startPoint) {
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
			roomcount++;
			startPoint[0] = tempWidth;
			startPoint[1] = tempHeight;
			return 1;
		}
	}
	return 0;
}

int Area::dfs(int x, int y, int roomCount) {

	int xTemp;
	int yTemp;
	int counter = 0;
	int **dfsMap;

	dfsMap = new int*[WIDTH];
	for(unsigned i = 0; i < WIDTH; ++i) {
		dfsMap[i] = new int[HEIGHT];
	}

	std::stack<int> toSearch;
	toSearch.push(y);
	toSearch.push(x);
	while (!toSearch.empty()) {
		xTemp = toSearch.top();
		toSearch.pop();
		yTemp = toSearch.top();
		toSearch.pop();
		if (dfsMap[xTemp][yTemp] != 1) {
			dfsMap[xTemp][yTemp] = 1;
			if (arrayArea[xTemp][yTemp] == 2) {
				counter++;
			}
			for(int i = -1; i < 2; ++i) {
				for(int j = -1; j < 2; ++j) {
					if ( !(xTemp + j < 0)
							&& !(yTemp + i < 0)
							&& !(xTemp + j >= WIDTH)
							&& !(yTemp + i >= HEIGHT)
							&& ((arrayArea[xTemp + j][yTemp + i] == 1)
								|| (arrayArea[xTemp + j][yTemp + i] == 2))  ) {
						toSearch.push(yTemp + i);
						toSearch.push(xTemp + j);
					}
				}
			}
		}
	}
	if (counter == roomCount) {
		return 1;
	}
	return 0;
}

int Area::Set(int x, int y) {
	if (arrayArea[x][y] == 2) {
		return 2;
	} else {
		return 1;
	}
}

int Area::randomWalk(int &x, int &y) {
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 3);

    int direction;
    int set;

	while (1) {
		direction = dist(mt);
		
		switch(direction) {
			case 0:
				if (!(y < RANDOM_WALK_STEP)) {
					for(unsigned i = 0; i < RANDOM_WALK_STEP; ++i) {
						set = Set(x, y);
						arrayArea[x][y] = set;
						y--;
					}
					break;
				}
			case 1:
				if (!(x >= WIDTH - RANDOM_WALK_STEP)) {
					for(unsigned i = 0; i < RANDOM_WALK_STEP; ++i) {
						set = Set(x, y);
						arrayArea[x][y] = set;
						x++;
					}
					break;
				}
			case 2:
				if (!(y >= HEIGHT - RANDOM_WALK_STEP)) {
					for(unsigned i = 0; i < RANDOM_WALK_STEP; ++i) {
						set = Set(x, y);
						arrayArea[x][y] = set;
						y++;
					}
					break;
				}
			case 3:
				if (!(x < RANDOM_WALK_STEP)) {
					for(unsigned i = 0; i < RANDOM_WALK_STEP; ++i) {
						set = Set(x, y);
						arrayArea[x][y] = set;
						x--;
					}
					break;
				}
			default:
				break;
		}
		if (arrayArea[x][y] == 1) {
			break;
		}
	}
}

int Area::connectRooms(int *startPoint, int roomCount) {
	int counter = 0;
	int x = startPoint[0];
	int y = startPoint[1];
	while (!dfs(x,y,roomCount)) {
		randomWalk(x, y);

	}
}

int Area::makeRooms() {
	int **RoomTemp;
	int widthTemp;
	int heightTemp;
	int rc = 0;
	int startp[2];

	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> Wdist(2, MAX_ROOM_WIDTH - 1);
    std::uniform_int_distribution<int> Hdist(2, MAX_ROOM_HEIGHT - 1);


	while (true) {

		widthTemp = Wdist(mt);
		heightTemp = Hdist(mt);

		RoomTemp = makeSingleRoom(1, widthTemp, heightTemp);

		if (!placeRoom(widthTemp, heightTemp, RoomTemp, rc, startp)) {
			break;
		}
	}
	connectRooms(startp, rc);
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