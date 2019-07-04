#pragma once

class Bomb
{
	bool active;			// Le van e rakva
	int posX, posY;			// Pozíció
	int timeLeft;			// Hátralevő idő (egység)
	int range;

public:
	// Konsturkto
	// Pozíciót, hatótávolságot, (és időt) vár
	Bomb(int x, int y, int r, int t = 15) : posX(x), posY(y), timeLeft(t), range(r) {
		active = true;			// Aktív, le van rakva
	}

	// Indításhoz, ekkor még nincs lerakva, nem aktív
	Bomb(bool a = false) { active = a; }

	// Hátrelevő idő frissítése
	// Ha lejárt az ideje, akkor inaktív lesz, main kezeli a robbanást
	bool update() {
		timeLeft--;
		if (timeLeft == 0) {
			active = false;
			return false;
		}
		return true;
	}

	// Getter függvények
	bool isActive() { return active; }
	int getX() { return posX; }
	int getY() { return posY; }
	int getRange() { return range; }
};

