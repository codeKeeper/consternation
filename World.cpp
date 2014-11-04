#include "consternation.h"

int World::debugPrint() {
	for (unsigned i = 0; i < DEPTH; i++) {
		TheWorld[i]->debugPrint();
	}
	return 1;
}

World::World() {
	TheWorld = new Area*[DEPTH];
	for (unsigned i = 0; i < DEPTH; i++) {
		TheWorld[i] = new Area(1);
	}
}