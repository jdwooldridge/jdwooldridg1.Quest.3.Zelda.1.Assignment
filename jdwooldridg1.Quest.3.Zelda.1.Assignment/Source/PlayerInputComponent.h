#pragma once

#include <map>

#include "ComponentList.h"

class InputDevice;
class PhysicsDevice;
class Game;

class PlayerInputComponent : public Component
{
public:
    PlayerInputComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers);
	std::shared_ptr<Object> Update();
	bool Finish();
private:
	InputDevice* iDevice;
	PhysicsDevice* pDevice;
	View* view;
	Game* game;
	//std::map<GAME_EVENT, bool> controlPressed;
};