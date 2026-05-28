#pragma once
struct Random {
private:
	static bool init;
	static void Init();

public:
	static void SetSeed(int seed);
	static int Range(int left, int right);
	static float Range(float left, float right);
	static float Next();
};
