#pragma once

#include <unordered_set>
#include "ITickable.h"

class TickEngine {
private:
	static std::unordered_set<ITickable*> objects;

public:
	static void RegisterObject(ITickable* obj);
	static void UnregisterObject(ITickable* obj);
	static void Tick();
	static void CleanUp();
};