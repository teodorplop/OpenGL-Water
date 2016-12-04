#include "TimeFrame.h"

float TimeFrame::lastUpdate = 0.0f;
float TimeFrame::lastFPSCheck = 0.0f;
int TimeFrame::frames = 0;

float TimeFrame::deltaTime = 0.0f;
float TimeFrame::fps = 0.0f;

void TimeFrame::Update(float time) {
	++frames;

	deltaTime = time - lastUpdate;
	lastUpdate = time;

	if (time - lastFPSCheck >= 1.0f) {
		fps = (float)frames / (time - lastFPSCheck);
		lastFPSCheck = time;
		frames = 0;
	}
}