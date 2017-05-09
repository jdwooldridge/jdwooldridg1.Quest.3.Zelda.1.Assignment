
#include "Game.h"
#include "TimedLifeComponent.h";

//Initialize heatlh component.
bool TimedLifeComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	health = initializers.health;
	pDevice = initializers.game->getPhysicsDevice();
	return true;
}

bool TimedLifeComponent::Finish()
{
	return true;
}

//Decrement health and move the arrow forward. If health is less than or equal to zero, set is dead to true.
std::shared_ptr<Object> TimedLifeComponent::Update()
{
	//Move forward away from Link.
	GAME_VEC newPosition;
	GAME_FLT radians = (2.0f * PI) * pDevice->GetAngle(_owner.get()) / 360.0f - PI / 2.0f;
	GAME_FLT dx = cos(radians);
	GAME_FLT dy = sin(radians);

	newPosition.x = pDevice->GetPosition(_owner.get()).x + 2.0f*dx;
	newPosition.y = pDevice->GetPosition(_owner.get()).y + 2.0f*dy;
	
	//Decrement health and set isDead to true if health is less than or equal to zero.
	--health;
	if (health <= 0)
		_owner->setIsDead(true);
	return nullptr;
}