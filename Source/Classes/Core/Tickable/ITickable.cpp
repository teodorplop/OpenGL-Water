#include "ITickable.h"
#include "TickEngine.h"

ITickable::ITickable() {
	TickEngine::RegisterObject(this);
}
ITickable::~ITickable() {
	TickEngine::UnregisterObject(this);
}