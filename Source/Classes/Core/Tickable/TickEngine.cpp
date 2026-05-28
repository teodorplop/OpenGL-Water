#include "TickEngine.h"

std::unordered_set<ITickable*> TickEngine::objects;

void TickEngine::RegisterObject(ITickable* obj) {
	objects.insert(obj);
}
void TickEngine::UnregisterObject(ITickable* obj) {
	objects.erase(obj);
}
void TickEngine::Tick() {
	for (ITickable* obj : objects) {
		obj->Tick();
	}
}
void TickEngine::CleanUp() {
	std::unordered_set<ITickable*> aux = objects;
	for (ITickable* obj : aux) {
		delete obj;
	}
	objects.clear();
}