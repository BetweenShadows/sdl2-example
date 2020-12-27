#include "util.hpp"

int RandInt(int a, int b) {
	return rand() % b + a;
}

SDL_Color GetRandomColor() {
	Uint8 r = RandInt(0, 255);
	Uint8 g = RandInt(0, 255);
	Uint8 b = RandInt(0, 255);
	Uint8 a = 1;
	return SDL_Color {r, g, b, a };
}