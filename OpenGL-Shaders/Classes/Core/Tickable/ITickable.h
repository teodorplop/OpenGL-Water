#pragma once

class ITickable {
	friend class TickEngine;

protected:
	virtual void Tick() = 0;

public:
	ITickable();
	virtual ~ITickable();
};