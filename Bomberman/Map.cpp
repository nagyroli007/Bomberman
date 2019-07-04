#include "Map.h"

#include "Bomb.h"
#include <stdlib.h>

// Robbanáskor a kellő blokkok megszüntetése
void Map::explosion(Bomb bomb) {
	// Irányok, merre mehet a robbanás
	bool up = true, down = true, left = true, right = true;
	// Koordináták
	int x = bomb.getX(), y = bomb.getY();
	// i - sugár, annyit megy ki, amennyi a bomba hatótáva 
	for (int i = 1; i <= bomb.getRange(); i++) {
		// Ha meget felfele a robbanás
		if (up)
			// Ha szolid blokk, van ott, akkor a robbanás ne menjen tobább
			if (blocks[x][y - i] == 1)
				up = false;
			// Ha 
			else if (up && blocks[x][y - i] == 2) {
				blocks[x][y - i] = 0;
			}
		// Ha meget lefele a robbanás
		if (down)
			if (blocks[x][y + i] == 1)
				down = false;
			else if (down && blocks[x][y + i] == 2) {
				blocks[x][y + i] = 0;
			}
		// Ha meget balra a robbanás
		if (left)
			if (blocks[x - i][y] == 1)
				left = false;
			else if (left && blocks[x - i][y] == 2) {
				blocks[x - i][y] = 0;
			}
		// Ha meget jobbra a robbanás
		if (right)
			if (blocks[x + i][y] == 1)
				right = false;
			else if (right &&blocks[x + i][y] == 2) {
				blocks[x + i][y] = 0;
			}
	}
}

// Nincs e már több robbantható blokk
bool Map::noMoreBlocks() {
	// Koordinátákon végigmegyek
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			// Ha ven robbantható, akkor hamis
			if (blocks[x][y] == 2)
				return false;
	// Ha nem volt egy sem, akkor igaz
	return true;
}

// Pálya feltöltése a szolid (elpusztíthatatlan) blokkokkal
void Map::fillWithSolidBlocks() {
	// Felső, és alsó sor
	for (int i = 0; i < width; i++) {
		blocks[i][0] = 1;
		blocks[i][height - 1] = 1;
	}

	// Szélső oszlopok
	for (int i = 1; i < height - 1; i++) {
		blocks[0][i] = 1;
		blocks[width - 1][i] = 1;
	}

	// Végig megyek az összes pozíción, amit még nem töltöttem ez előbb fel
	for (int x = 1; x < width - 1; x++) {
		for (int y = 1; y < height - 1; y++) {
			// Ha a koordináták párosak, akkor leszen ott szolid blokk
			if (x % 2 == 0 && y % 2 == 0)
				blocks[x][y] = 1;
			// Ha nem, akkor legyen üres a blokk
			else
				blocks[x][y] = 0;
		}
	}
}

// A pálya feltöltése, robbantható blokkokkal
// n - hágy blokk legyen
void Map::fillBlocks(int n) {
	int current = 0;		// Hányar rakott le éppen
	// Három blokk lefoglalása, hogy a játékos tudjon merre menni az elején
	blocks[1][1] = 1;
	blocks[1][2] = 1;
	blocks[2][1] = 1;
	// Amíg nincs lerakva annyi amennyi kell
	while (current != n) {
		int x = rand() % width;
		int y = rand() % height;
		if (blocks[x][y] == 0)
		{
			blocks[x][y] = 2;
			current++;
		}
	}
	// Lefoglalt blokkok felszedése
	blocks[1][1] = 0;
	blocks[1][2] = 0;
	blocks[2][1] = 0;
}