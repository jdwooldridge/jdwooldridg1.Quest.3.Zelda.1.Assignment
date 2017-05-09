#include <random>

#include "Game.h"
#include "SlideBehaviorComponent.h"

bool SlideBehaviorComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers) 
{
	vertical = initializers.vertical;
	aDelta = Component::distance(engine);
	posNeg = 1;
	pDevice = initializers.game->getPhysicsDevice();
	return true;
}


std::shared_ptr<Object>  SlideBehaviorComponent::Update()
{
	GAME_VEC updatedPosition = pDevice->GetPosition(_owner.get());
	if (vertical)
	{
		//Zero out the velocities.
		pDevice->SetAngularVelocity(_owner.get(), 0.0f);
		pDevice->SetLinearVelocity(_owner.get(), { 0 , 0 });

		//Change the position and update it in the physics world.
		updatedPosition.y = pDevice->GetPosition(_owner.get()).y +  1 * posNeg;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
		// if we have gone far enough. . . switch directions
		if ( updatedPosition.y > _owner -> GetComponent<BodyComponent>() -> getStartPosition().y + aDelta || updatedPosition.y < _owner->GetComponent<BodyComponent>()->getStartPosition().y - aDelta)
		{
			posNeg *= -1;
		}
	}
	else //Update the horizontal position.
	{
		//Zero out the velocities.
		pDevice->SetAngularVelocity(_owner.get(), 0.0f);
		pDevice->SetLinearVelocity(_owner.get(), { 0 , 0 });

		//Change the position and update it in the physics world.
		updatedPosition.x = pDevice->GetPosition(_owner.get()).x + 1 * posNeg;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
		
		// if we have gone far enough. . . switch directions
		if (updatedPosition.x > _owner->GetComponent<BodyComponent>()->getStartPosition().x + aDelta || updatedPosition.x < _owner->GetComponent<BodyComponent>()->getStartPosition().x - aDelta)
		{
			posNeg *= -1;
		}
	}
	return nullptr;
}

bool SlideBehaviorComponent::Finish()
{
	return true;
}