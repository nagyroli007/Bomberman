#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"

#include <string>

class SDL_MyWindow {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;

	SDL_Texture* mapTexture;		// Pálya textúrája, háttér
	SDL_Texture* playerImg = NULL;	// Játékos textúrája
	SDL_Texture* bombImg = NULL;	// Bomba textúrája
	
	char playerDirection = 'r';		// Merre megy éppen a játékos
	int playerTexturePhase = 0;		// Animációhoz számláló

public:
	/** MyWindow construkora
	* Kap méretet és fejléc címet
	*/
	SDL_MyWindow(int w = 600, int h = 400, const char* title = "title"): width(w), height(h) {
		// Inicializálás
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		// Window renderer létrehozása
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		// Pálya textúra létrehozása
		mapTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);		// Zöld szín
		SDL_SetRenderTarget(renderer, mapTexture);				
		SDL_RenderClear(renderer);								// Töltse ki az ablakot
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
		// Töltse be a képeket (játékos, bomba)
		playerImg = IMG_LoadTexture(renderer, "bomberman.png");
		bombImg = IMG_LoadTexture(renderer, "bomb.png");

		SDL_RenderPresent(renderer);							// Töltse be a változásokat
	}

	// Dekonstruktor
	// Textúrák, renderer és ablak elpusztítása
	~SDL_MyWindow() {
		SDL_DestroyTexture(playerImg);
		SDL_DestroyTexture(bombImg);
		SDL_DestroyTexture(mapTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	// Bomba betöltése a képernyőre
	void drawBombTexture(Bomb bomb) {
		// Cél négyszög
		SDL_Rect r;
		r.w = 26; r.h = 26; r.x = bomb.getX() * 30 + 2; r.y = bomb.getY() * 30 + 2;
		// Forrás nyégyszög (a képen)
		SDL_Rect s; 
		s.x = 0; s.y = 0; s.w = 256; s.h = 244;
		// Betöltés
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, bombImg, NULL, &r);
		SDL_RenderPresent(renderer);
	}

	// Játékos betöltése a képernyőre
	void drawPlayerTexture(Player player) {
		SDL_SetRenderTarget(renderer, NULL);
		// s - forrás, d - cél négyzet
		SDL_Rect s, d;
		s.w = 60; s.h = 80;
		d.x = player.getPosX(); d.y = player.getPosY(); d.w = player.getWidth(); d.h = player.getHeight();
		// Irány megváltoztatása ha kell
		// Akkor változik meg egy irány, ha nincs legyomva az amerre megy, és bármelyik másik le van nyomva
		if (playerDirection == 'r' && !player.getRight()) {
			if (player.getLeft()) {
				playerDirection = 'l';
				playerTexturePhase = 0;
			}
			else if (player.getUp() && !player.getDown()) {
				playerDirection = 'u';
				playerTexturePhase = 0;
			}
			else if (!player.getUp() && player.getDown()) {
				playerDirection = 'd';
				playerTexturePhase = 0;
			}
		}
		else if (playerDirection == 'l' && !player.getLeft()) {
			if (player.getRight()) {
				playerDirection = 'r';
				playerTexturePhase = 0;
			}
			else if (player.getUp() && !player.getDown()) {
				playerDirection = 'u';
				playerTexturePhase = 0;
			}
			else if (!player.getUp() && player.getDown()) {
				playerDirection = 'd';
				playerTexturePhase = 0;
			}
		}
		else if (playerDirection == 'u' && !player.getUp()) {
			if (player.getDown()) {
				playerDirection = 'd';
				playerTexturePhase = 0;
			}
			else if (player.getRight() && !player.getLeft()) {
				playerDirection = 'r';
				playerTexturePhase = 0;
			}
			else if (!player.getRight() && player.getLeft()) {
				playerDirection = 'l';
				playerTexturePhase = 0;
			}
		}
		else if (playerDirection == 'd' && !player.getDown()) {
			if (player.getUp()) {
				playerDirection = 'u';
				playerTexturePhase = 0;
			}
			else if (player.getRight() && !player.getLeft()) {
				playerDirection = 'r';
				playerTexturePhase = 0;
			}
			else if (!player.getRight() && player.getLeft()) {
				playerDirection = 'l';
				playerTexturePhase = 0;
			}
		}
		// Hány frame-enként változzon a kép, animáció miatt
		int time = 7;
		// Irány, és frame alapján változzon a forrás pozíciója (változik, mit tölt be)
		if (playerDirection == 'r') {
			if (playerTexturePhase < time * 1) {
				s.x = 410; s.y = 51;
			}
			else if (playerTexturePhase < time * 2) {
				s.x = 142; s.y = 51;
			}
			else if (playerTexturePhase < time * 3) {
				s.x = 274; s.y = 51;
			}
			else if (playerTexturePhase < time * 4) {
				s.x = 142; s.y = 51;
			}
			else
				playerTexturePhase = -1;
			playerTexturePhase++;
		}
		else if (playerDirection == 'l') {
			if (playerTexturePhase < time * 1) {
				s.x = 343; s.y = 50;
			}
			else if (playerTexturePhase < time * 2) {
				s.x = 74; s.y = 51;
			}
			else if (playerTexturePhase < time * 3) {
				s.x = 206; s.y = 51;
			}
			else if (playerTexturePhase < time * 4) {
				s.x = 74; s.y = 51;
			}
			else
				playerTexturePhase = -1;
			playerTexturePhase++;
		}
		else if (playerDirection == 'u') {
			if (playerTexturePhase < time * 1) {
				s.x = 480; s.y = 182;
			}
			else if (playerTexturePhase < time * 2) {
				s.x = 824; s.y = 51;
			}
			else if (playerTexturePhase < time * 3) {
				s.x = 688; s.y = 316;
			}
			else if (playerTexturePhase < time * 4) {
				s.x = 824; s.y = 51;
			}
			else
				playerTexturePhase = -1;
			playerTexturePhase++;
		}
		else if (playerDirection == 'd') {
			if (playerTexturePhase < time * 1) {
				s.x = 552; s.y = 182;
			}
			else if (playerTexturePhase < time * 2) {
				s.x = 755; s.y = 51;
			}
			else if (playerTexturePhase < time * 3) {
				s.x = 892; s.y = 182;
			}
			else if (playerTexturePhase < time * 4) {
				s.x = 755; s.y = 51;
			}
			else
				playerTexturePhase = -1;
			playerTexturePhase++;
		}

		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
	}

	// Pálya kirajzolása
	void drawMap(Map& map) {
		SDL_SetRenderTarget(renderer, mapTexture);
		// Ha van egy pozícióban blokk, akkor oda rajzol egy négyzetet
		for (int x = 0; x < map.getWidth(); x++) {
			for (int y = 0; y < map.getHeight(); y++) {
				if (map.getBlock(x, y) == 1) {
					SDL_Rect r;
					r.x = x * 30; r.y = y * 30; r.w = 30; r.h = 30;
					SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);	// Sötét szürke szín
					SDL_RenderFillRect(renderer, &r);
					r.x += 3; r.y += 3; r.w = 24; r.h = 24;
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 255);	// Szürke szín
					SDL_RenderFillRect(renderer, &r);
				}
				else if (map.getBlock(x, y) == 2) {
					SDL_Rect r;
					r.x = x * 30 + 1; r.y = y * 30 + 1; r.w = 28; r.h = 28;
					SDL_SetRenderDrawColor(renderer, 171, 171, 171, 255);	// Sötét szürke szín
					SDL_RenderFillRect(renderer, &r);
					SDL_RenderFillRect(renderer, &r);
				}
			}
		}
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
	}

	// Az eltárolt pálya textúrát rajzolja ki
	void drawMapTexture() {
		SDL_Rect r; r.x = 0; r.y = 0; r.w = 450, r.h = 390;
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, mapTexture, NULL, &r);
		SDL_RenderPresent(renderer);
	}	

	// Blokk letörlése a pálya textúráról
	void clearBlock(int x, int y) {
		// Törlendő blokk négyzete
		SDL_Rect r;
		r.x = x * 30; r.y = y * 30; r.w = 30; r.h = 30;
		SDL_SetRenderTarget(renderer, mapTexture);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
	}

	// Bomba letörlése
	void clearBomb(Bomb bomb) {
		// Bomba négyszöge
		SDL_Rect r;
		r.w = 26; r.h = 26; r.x = bomb.getX() * 30 + 2; r.y = bomb.getY() * 30 + 2;

		SDL_SetRenderTarget(renderer, mapTexture);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);	// Fekete szín
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
	}

	// Játék végén levő animáció
	// Megáll, vár a játékos. Ugrik egyet, vár még egy kicsit (majd kikapcsol a játék a main-ben)
	void endGameSequence(Player player) {
		SDL_SetRenderTarget(renderer, NULL);
		// Forrás, cél négyszögek
		SDL_Rect s, d;
		s.w = 60; s.h = 80;
		d.x = player.getPosX(); d.y = player.getPosY(); d.w = player.getWidth(); d.h = player.getHeight();

		drawMapTexture();

		s.x = 755; s.y = 50;
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(1500);
		drawMapTexture();

		s.x = 961; s.y = 51;
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(185);
		drawMapTexture();

		s.x = 888; s.y = 51;
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(185);
		drawMapTexture();

		s.x = 961; s.y = 51;
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(185);
		drawMapTexture();

		s.x = 755; s.y = 50;
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(1500);
	}

	// Game over animáció
	void gameOverSequence(Player player) {
		SDL_SetRenderTarget(renderer, NULL);
		// Forrás, cél négyszögek
		SDL_Rect s, d;
		s.x = 888; s.y = 51;  s.w = 60; s.h = 80;
		d.x = player.getPosX(); d.y = player.getPosY(); d.w = player.getWidth(); d.h = player.getHeight();

		drawMapTexture();
		SDL_RenderCopy(renderer, playerImg, &s, &d);
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
	}
};
