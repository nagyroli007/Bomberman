#pragma once

#include "Map.h"
#include "Bomb.h"

class Player
{
	int posX, posY;					// Pozíció
	int prevX, prevY;				// Előző pozíció
	int width = 17, height = 20;	// Méret
	bool up, down, left, right;		// Irányok, merre kell mennie
	int v;							// Sebesség

public:
	Player(int x = 31, int y = 31) : posX(x), posY(y) {
		v = 3;			// Sebesség
		up = false; down = false; right = false; left = false;	// Irányok nullázása
	}

	// Getter függvények
	int getPosX() { return posX; }
	int getPosY() { return posY; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getUp() { return up; }
	bool getDown() { return down; }
	bool getLeft() { return left; }
	bool getRight() { return right; }

	// Ütközés vizsgálata
	// Ha olyan mezőbe lépett a játékos, ahol szolid blokk van, akkor vegye fel az előző pozíciójat
	void checkCollision(Map& map);

	// Irányok beállítása (true - megy abba az irányba, false - ne menjen abba)
	void startUp(bool moving) { up = moving; }
	void startDown(bool moving) { down = moving; }
	void startLeft(bool moving) { left = moving; }
	void startRight(bool moving) { right = moving; }

	// Pozíció frissítése
	void update();

	// Fog-e mozdulni a játékos
	// Akkor tér vissza igazzal, ha valamelyik tengelyen csak egy irány igan
	bool moved() { 	return (up ^ down) || (left ^ right); }

	 // A megadott blokkon van-e a játékos
	bool playerIsThere(int w, int h);
};