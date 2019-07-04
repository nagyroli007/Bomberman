
#include "SDL_MyWindow.hpp"
#undef main

#include "Map.h"
#include "Player.h"
#include "Bomb.h"

#include "SDL.h"
#include "SDL_image.h"

int main() {

	SDL_MyWindow window(450, 390, "Bomberman");			// Ablak objektum

	Map map(15, 13);		// Pálya
	Player player;			// Játékos

	// Ablak és játekos kirajzolása
	window.drawMap(map);
	window.drawPlayerTexture(player);

	bool end = false;			// A játék végét fogja jelezni

	SDL_Event ev;				// SDL esemény

	// Bomba, egyenlőre csak ez az egy lesz, inaktív
	Bomb bomb(false);

	while (!end) {
		// Eventek vizsgálata
		while (SDL_PollEvent(&ev))
		{
			// Ha leütött billentyű van, a megfelelő irányt elmenti
			if (ev.type == SDL_KEYDOWN)
			{
				switch (ev.key.keysym.sym) {
				// Fel
				case SDLK_w:
					player.startUp(true);
					break;
				// Balra
				case SDLK_a:
					player.startLeft(true);
					break;
				// Le
				case SDLK_s:
					player.startDown(true);
					break;
				// Jobbra
				case SDLK_d:
					player.startRight(true);
					break;
				// Space, bomba lerakás
				case SDLK_SPACE:
					if (bomb.isActive())
						break;
					// Eltárolom a játékos középponját, mert abba a blokkba kerül a bomba
					int x = (player.getPosX() + player.getWidth() / 2) / 30;
					int y = (player.getPosY() + player.getHeight() / 2) / 30;
					// Bomba létrehozása
					bomb = Bomb(x, y, 1, 40);
					// Bomba, pálya, játékos kirajzolása
					window.drawMapTexture();
					window.drawBombTexture(bomb);
					window.drawPlayerTexture(player);
					break;
				}
			}
			else if (ev.type == SDL_KEYUP)
			{
				// Ha felengedett billentyű van, akkor a megfelelő irányt elveti
				switch (ev.key.keysym.sym) {
				case SDLK_w:
					player.startUp(false);
					break;
				case SDLK_a:
					player.startLeft(false);
					break;
				case SDLK_s:
					player.startDown(false);
					break;
				case SDLK_d:
					player.startRight(false);
					break;
				}
			}
			// Ha ki akarunk lépni, X gombot meg lett nyomva
			else if (ev.type == SDL_QUIT) {
				end = true;
			}
		}
		// Ha aktív a bomba
		if (bomb.isActive()) {
			// Frissíti. Ha robban (hamissal tér vissza)
			if (!bomb.update()) {
				// Irányok eltárolása, merre mehet tobább a robbanás
				bool up = true, down = true, left = true, right = true;
				// Bomba pozíciója
				int x = bomb.getX(), y = bomb.getY();
				map.getBlock(x, y) = -1;
				// Sugárszor megvizsgálja mind a 4 oldalt
				for (int i = 1; i <= bomb.getRange(); i++) {
					// Ha mehet fel
					if (up)
						// Ha szolid blokk van, akkor a robbanás nem mehet tovább felfele
						if (map.getBlock(x, y - i) == 1)
							up = false;
						// Ha robbanható van, akkor szünjön meg
						else if (map.getBlock(x, y - i) == 2) {
							map.getBlock(x, y - i) = 0;
							window.clearBlock(x, y - i);
						}
						// Ha a játékos ott van, akkor játsza le, a meghalás animációt, és lépjen ki
						else if (player.playerIsThere(x, y - i)) {
							window.gameOverSequence(player);
							end = true;
						}
					// Ugyan az mint az előző, csak lefele
					if (down)
						if (map.getBlock(x, y + i) == 1)
							down = false;
						else if (map.getBlock(x, y + i) == 2) {
							map.getBlock(x, y + i) = 0;
							window.clearBlock(x, y + i);
						}
						else if (player.playerIsThere(x, y + i)) {
							window.gameOverSequence(player);
							end = true;
						}
					// Ugyan az mint az előző, csak balra
					if (left)
						if (map.getBlock(x - i, y) == 1)
							left = false;
						else if (map.getBlock(x - i, y) == 2) {
							map.getBlock(x - i, y) = 0;
							window.clearBlock(x - i, y);
						}
						else if (player.playerIsThere(x - i, y)) {
							window.gameOverSequence(player);
							end = true;
						}
					// Ugyan az mint az előző, csak robbra
					if (right)
						if (map.getBlock(x + i, y) == 1)
							right = false;
						else if (map.getBlock(x + i, y) == 2) {
							map.getBlock(x + i, y) = 0;
							window.clearBlock(x + i, y);
						}
						else if (player.playerIsThere(x + i, y)) {
							window.gameOverSequence(player);
							end = true;
						}
				}

				// Ha a bombán áll a játékos, akkor is legyen vége
				if (player.playerIsThere(x, y)) {
					window.gameOverSequence(player);
					end = true;
				}

				// Újrarajzolások
				if (true) {
					window.clearBomb(bomb);
					window.drawMapTexture();
					if (bomb.isActive())
						window.drawBombTexture(bomb);
					window.drawPlayerTexture(player);
				}

				// Ha nincs már több felrobbantható blokk, akkor a játékos nyert, vége a játéknak
				if (map.noMoreBlocks()) {
					window.endGameSequence(player);			// Animáció
					end = true;
				}
			}
		}
		// Ha mozogni fog valamelyik irányba
		if (player.moved() && !end) {
			player.update();						// Pozíció frissítése
			player.checkCollision(map);				// Ütközés vizsgálata, ha kell akkor az előző helyre megy vissza
			window.drawMapTexture();				// Pálya textúra kirajzol
			if (bomb.isActive())
				window.drawBombTexture(bomb);
			window.drawPlayerTexture(player);				// Játékos kirajzolása
		}
		SDL_Delay(30);								// Alvás
	}

	return 0;
}