#include "Player.h"

#include "Map.h"
#include "Bomb.h"

// Ütközés vizsgálata
// Ha olyan mezőbe lépett a játékos, ahol szolid blokk van, akkor vegye fel az előző pozíciójat
void Player::checkCollision(Map& map) {
	// Ha a bal felső sarka, egy blokkban van
	if (map.getBlock(posX / 30, posY / 30) > 0) {
		if (left && !right) {
			posX = prevX;
		}
		if (up && !down) {
			posY = prevY;
		}
	}
	// Ha a jobb alsó sarka, egy blokkban van
	else if (map.getBlock((posX + width) / 30, (posY + height) / 30) > 0) {
		if (!left && right) {
			posX = prevX;
		}
		if (!up && down) {
			posY = prevY;
		}
	}
	// Ha a bal alsó sarka, egy blokkban van
	if (map.getBlock(posX / 30, (posY + height) / 30) > 0) {
		if (left && !right) {
			posX = prevX;
		}
		if (!up && down) {
			posY = prevY;
		}
	}
	// Ha a jobb felső sarka, egy blokkban van
	else if (map.getBlock((posX + width) / 30, posY / 30) > 0) {
		if (!left && right) {
			posX = prevX;
		}
		if (up && !down) {
			posY = prevY;
		}
	}
}

// Pozíció frissítése
void Player::update() {
	// Előző pozíció eltárolása
	prevX = posX;
	prevY = posY;
	// Minden irányba muzduljon sebességnyivel, ha igaz az ahoz irányhoz tartozó bool változó
	posX += left * -v;
	posX += right * v;
	posY += up * -v;
	posY += down * v;
}

// A megadott blokkon van-e a játékos
bool Player::playerIsThere(int w, int h) {
	// Bal oldala
	if (posX / 30 == w)
		// Felső sarok
		if (posY / 30 == h)
			return true;
		// Alsó sarok
		else if ((posY + height) / 30 == h)
			return true;
	// Jobb oldala
	if ((posX + width) / 30 == w)
		// Felső sarok
		if (posY / 30 == h)
			return true;
		// Alsó sarok
		else if ((posY + height) / 30 == h)
			return true;
	return false;
}