#include "ComponentList.h"

#include "Object.h"

Object::Object()
{
	initialized = false;
}

Object::~Object()
{

}
//Initialize an object.
bool Object::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	objectType = initializers.objectType;
	isDead = false;
	//Initialize every component. If one fails to initialize, then fail the object initialization.
	for (auto comp : components)
	{
		initialized = comp->Initialize(initializers);
		if (!initialized)
			return false;
	}
	return true;
}
//Update every component in the object. Return any objects created by the component, which will be added to the objects vector.
std::shared_ptr<Object> Object::Update(GAME_FLT)
{
	std::shared_ptr<Object> objectReturn = nullptr;
	for (auto comp : components)
		objectReturn = comp->Update();
	return objectReturn;
}

void Object::addComponent(std::shared_ptr<Component> component)
{
	components.push_back(component);
}

void Object::removeComponents()
{
	components.clear();
}

//Set isDead.
void Object::setIsDead(bool isDead)
{
	this->isDead = isDead;
}
//Retrieve isDead.
bool Object::getIsDead()
{
	return isDead;
}