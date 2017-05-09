#pragma once

#include "ComponentList.h"

class TimedLifeComponent : public Component
{
public:
	TimedLifeComponent(std::shared_ptr<Object> owner)
		: Component(owner)
	{ };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
	std::shared_ptr<Object> Update();
	bool Finish();
private:
	GAME_INT health;
	PhysicsDevice* pDevice;
};