#pragma once


#include "Component.h"


class CircleBehaviorComponent : public Component
{
public:
    CircleBehaviorComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };

	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::shared_ptr<Object> Update();
	bool Finish();
private:
	GAME_FLT aDelta;
	bool radius;
	GAME_FLT sDelta;
	PhysicsDevice* pDevice;
	//GAME_VEC center;
};