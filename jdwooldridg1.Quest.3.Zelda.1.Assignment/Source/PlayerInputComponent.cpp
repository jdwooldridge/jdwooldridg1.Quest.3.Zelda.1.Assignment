#include "InputDevice.h";
#include "PhysicsDevice.h"
#include "Game.h"
#include "PlayerInputComponent.h"

//Initialize the input component.
bool PlayerInputComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	iDevice = initializers.game->getInputDevice();
	view = initializers.game->getView();
	pDevice = initializers.game->getPhysicsDevice();
	
	game = initializers.game;
	//for (int i = 0; i < GAME_NUM_EVENTS; ++i)
	//{
	//	GAME_EVENT event = static_cast<GAME_EVENT>(i);
	//	controlPressed[event] = true;
	//}
	return true;
}
//Update Link's position.
std::shared_ptr<Object> PlayerInputComponent::Update()
{
	GAME_VEC linearVelocity;
	GAME_FLT angularVelocity;
	GAME_VEC force;
	GAME_VEC updatedPosition;
	std::shared_ptr<Object> objectToReturn = std::make_shared<Object>(); //If the player presses space, this should become an object that is an arrow.

	//Move forwards.
	if (iDevice->GetEvent(GAME_UP))
	{
		linearVelocity.x = (float)cosf((pDevice->GetAngle(_owner.get())*PI / 180) - (PI / 2)) * 2.0f;
		linearVelocity.y = (float)sinf((pDevice->GetAngle(_owner.get())*PI / 180) - (PI / 2)) * 2.0f;
		pDevice->SetLinearVelocity(_owner.get(), linearVelocity);
		force = pDevice->GetLinearVelocity(_owner.get());
		updatedPosition.x = pDevice->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = pDevice->GetPosition(_owner.get()).y + force.y;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
	}
	//Move backwards.
	if (iDevice->GetEvent(GAME_DOWN))
	{
		linearVelocity.x = (float)cosf((pDevice->GetAngle(_owner.get())*PI / 180) + (PI / 2)) * 2.0f;
		linearVelocity.y = (float)sinf((pDevice->GetAngle(_owner.get())*PI / 180) + (PI / 2)) * 2.0f;
		pDevice->SetLinearVelocity(_owner.get(), linearVelocity);
		force = pDevice->GetLinearVelocity(_owner.get());
		updatedPosition.x = pDevice->GetPosition(_owner.get()).x + force.x;
		updatedPosition.y = pDevice->GetPosition(_owner.get()).y + force.y;
		pDevice->SetTransform(_owner.get(), updatedPosition, pDevice->GetAngle(_owner.get()));
	}
	//Move left.
	if (iDevice->GetEvent(GAME_LEFT))
	{
		pDevice->SetAngularVelocity(_owner.get(), 2.0f);
		angularVelocity = pDevice->GetAngularVelocity(_owner.get());
		pDevice->SetAngle(_owner.get(), pDevice->GetAngle(_owner.get()) - angularVelocity);
	}
	//Move right.
	if (iDevice->GetEvent(GAME_RIGHT))
	{
		pDevice->SetAngularVelocity(_owner.get(), 2.0f);
		angularVelocity = pDevice->GetAngularVelocity(_owner.get());
		pDevice->SetAngle(_owner.get(), pDevice->GetAngle(_owner.get()) + angularVelocity);
	}
	//Fire an arrow.
	if (iDevice->GetEvent(GAME_SPACE))
	{
		GAME_OBJECTFACTORY_INITIALIZERS initializers;

		initializers.game = game;

		std::vector<std::shared_ptr<Component>> components;

		components.push_back(std::make_shared<SpriteComponent>(objectToReturn));

		components.push_back(std::make_shared<TimedLifeComponent>(objectToReturn));
		initializers.health = 50;

		components.push_back(std::make_shared<BodyComponent>(objectToReturn));
		initializers.objectType = "Arrow";
		initializers.position.x = _owner->GetComponent<BodyComponent>()->getPosition().x;
		initializers.position.y = _owner->GetComponent<BodyComponent>()->getPosition().y;
		initializers.angle = _owner->GetComponent<BodyComponent>()->getAngle();

		std::shared_ptr<ObjectFactory> objectFactory;
		objectToReturn = objectFactory->create(initializers, components);
		return objectToReturn;

	}

	//BORDER SCROLLING

	GAME_INT borderDistance = 30;

	//Shift screen to the left if Link is close to the left of the screen
	if (_owner->GetComponent<BodyComponent>()->getPosition().x - view->getPosition().x < borderDistance)
	{
			view->setPositionX(view->getPosition().x - 1);
			_owner->GetComponent<BodyComponent>()->setPositionX(view->getPosition().x + borderDistance);
	}
	//Shift screen to the right if Link is close to the right of the screen.
	if (_owner->GetComponent<BodyComponent>()->getPosition().x  - view->getPosition().x > SCREEN_WIDTH - borderDistance)
	{
		view->setPositionX(view->getPosition().x + 1);
		_owner->GetComponent<BodyComponent>()->setPositionX((SCREEN_WIDTH + view->getPosition().x) - borderDistance);
	}
	//Shift screen up if Link is close to the top of the screen.
	if (_owner->GetComponent<BodyComponent>()->getPosition().y - view->getPosition().y < borderDistance)
	{
		view->setPositionY(view->getPosition().y - 1);
		_owner->GetComponent<BodyComponent>()->setPositionY(view->getPosition().y + borderDistance);
	}
	//Shift screen down if Link is close to the top of the screen.
	if (_owner->GetComponent<BodyComponent>()->getPosition().y - view->getPosition().y > SCREEN_HEIGHT - borderDistance)
	{
		view->setPositionY(view->getPosition().y + 1);
		_owner->GetComponent<BodyComponent>()->setPositionY((SCREEN_HEIGHT + view->getPosition().y) - borderDistance);
	}

	return nullptr;
}

bool PlayerInputComponent::Finish()
{
	return true;
}