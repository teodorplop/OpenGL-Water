#pragma once
class TimeFrame {
private:
	static float lastUpdate;
	static float lastFPSCheck;
	static int frames;

public:
	static float deltaTime, fps;
	static void Update(float time);
};
