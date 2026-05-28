#pragma once

#include <string>

class HeightMapGenerator {
public:
	static float smooth;
	static int persistence;
	static void Generate(const char* filename, int width, int height, int octaves, int seed = 0);

private:
	static float** GenerateWhiteNoise(int width, int height, int seed);
	static float** GenerateSmoothNoise(float** whiteNoise, int width, int height, int octave);
	static float Interpolate(float a, float b, float alpha);
	static void SaveHeightMap(float** perlinNoise, int width, int height, std::string filename);
};
