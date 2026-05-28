#include "Random.h"
#include <cstdlib>
#include <ctime>

bool Random::init = false;

void Random::SetSeed(int seed) {
	init = true;
	srand(seed);
}

int Random::Range(int left, int right) {
	Init();
	return left + rand() % (right - left + 1);
}

float Random::Range(float left, float right) {
	Init();
	return left + Next() * (right - left + 1);
}

float Random::Next() {
	Init();
	return (float)rand() / (float)RAND_MAX;
}

void Random::Init() {
	if (!init) {
		init = true;

		srand((unsigned int)time(NULL));
	}
}