#pragma once

#include "Bomb.h"
#include <stdlib.h>

class Map
{
	int width, height;			// Pálya mérete
	int** blocks;				// 2d-s mátrix a blokkokhoz

public:
	// Konstruktor, lefoglalja a szükséges memóriát, és feltölti blokkokkal
	Map(int w, int h) : width(w), height(h) {
		blocks = new int* [width];
		for (int i = 0; i < width; i++) {
			blocks[i] = new int[height];
		}
		// Feltöltés
		fillWithSolidBlocks();
		fillBlocks(48);
	}

	// Destruktor, felszabadítja a lefoglalt területeket
	~Map() {
		for (int i = 0; i < width; i++) {
			delete[] blocks[i];
		}
		delete[] blocks;
	}

	// Getter függvények
	int& getBlock(int w, int h) { return blocks[w][h]; }
	int getWidth() { return width; }
	int getHeight() { return height; }

	// Robbanáskor a kellő blokkok megszüntetése
	void explosion(Bomb bomb);

	// Nincs e már több robbantható blokk
	bool noMoreBlocks();

private:
	// Pálya feltöltése a szolid (elpusztíthatatlan) blokkokkal
	void fillWithSolidBlocks();

	// A pálya feltöltése, robbantható blokkokkal
	void fillBlocks(int n = 10);
};

