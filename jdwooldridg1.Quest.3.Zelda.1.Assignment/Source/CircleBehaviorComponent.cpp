#include <random>

#include "BodyComponent.h"
#include "CircleBehaviorComponent.h"
#include "Game.h"

bool CircleBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	aDelta = Component::turnRate(engine);
	radius = initializers.radius;
	if (radius)
	{
		sDelta = 1.0f;
	}
	pDevice = initializers.game->getPhysicsDevice();
	return true;
}

std::shared_ptr<Object> CircleBehaviorComponent::Update()
{
	//Rotate in a circle.
	if (radius)
	{
		GAME_VEC newPosition;
		GAME_FLT radians = (2.0f * PI) * pDevice->GetAngle(_owner.get()) / 360.0f - PI / 2.0f;
		GAME_FLT dx = cos(radians);
		GAME_FLT dy = sin(radians);
		
		newPosition.x = pDevice->GetPosition(_owner.get()).x + sDelta*dx;
		newPosition.y = pDevice->GetPosition(_owner.get()).y + sDelta*dy;
		GAME_FLT newAngle = pDevice->GetAngle(_owner.get()) + aDelta;
		pDevice->SetTransform(_owner.get(), newPosition, newAngle);

	}
	//Rotate in place.
	else
	{
		GAME_FLT angleVelocity = pDevice->SetAngularVelocity(_owner.get(), aDelta);
		pDevice->SetAngle(_owner.get(), pDevice->GetAngle(_owner.get()) + angleVelocity);
	}
	return nullptr;
}
bool CircleBehaviorComponent::Finish()
{
	return false;
}
