#include <iostream>

#include "tinyxml\tinyxml.h"

#include "Game.h"
#include "ComponentList.h"
#include "ObjectFactory.h"

std::shared_ptr<Object> ObjectFactory::create(TiXmlElement* lvlRoot, Game* game)
{
	std::shared_ptr<Object> newObject = std::make_shared<Object>();
	GAME_OBJECTFACTORY_INITIALIZERS initializers;
	GAME_PHYSICS physics;

	initializers.game = game;

	initializers.objectType = lvlRoot->Attribute("name");

	TiXmlElement* comp = lvlRoot->FirstChildElement("Component");
	while (comp)
	{
		if (strcmp(comp->Attribute("name"), "Slide") == 0)
		{
			comp->QueryBoolAttribute("vertical", &initializers.vertical);
			newObject->addComponent(std::make_shared<SlideBehaviorComponent>(newObject));
		}
		else if (strcmp(comp->Attribute("name"), "Circle") == 0)
		{
			comp->QueryBoolAttribute("radius", &initializers.radius);
			newObject->addComponent(std::make_shared<CircleBehaviorComponent>(newObject));
		}
		
		else if (strcmp(comp->Attribute("name"), "Input") == 0)
			newObject->addComponent(std::make_shared<PlayerInputComponent>(newObject));
		
		else if (strcmp(comp->Attribute("name"), "Sprite") == 0)
			newObject->addComponent(std::make_shared<SpriteComponent>(newObject));
		else if (strcmp(comp->Attribute("name"), "Body") == 0)
		{
			comp->QueryFloatAttribute("x", &initializers.position.x);
			comp->QueryFloatAttribute("y", &initializers.position.y);
			comp->QueryFloatAttribute("angle", &initializers.angle);
			if (strcmp(comp->Attribute("type"), "GAME_DYNAMIC") == 0)
				physics.bodyType = GAME_DYNAMIC;
			else if (strcmp(comp->Attribute("type"), "GAME_STATIC") == 0)
				physics.bodyType = GAME_STATIC;
			if (strcmp(comp->Attribute("shape"), "GAME_RECTANGLE") == 0)
				physics.objectShape = GAME_RECTANGLE;
			else if (strcmp(comp->Attribute("shape"), "GAME_CIRCLE") == 0)
				physics.objectShape = GAME_CIRCLE;
			comp->QueryFloatAttribute("density", &physics.density);
			comp->QueryFloatAttribute("friction", &physics.friction);
			comp->QueryFloatAttribute("restitution", &physics.restitution);
			comp->QueryFloatAttribute("angularDamping", &physics.angularDamping);
			comp->QueryFloatAttribute("linearDamping", &physics.linearDamping);
			comp->QueryBoolAttribute("physicsOn", &physics.physicsOn);

			initializers.game->getPhysicsAssetLibrary()->AddAsset(lvlRoot->Attribute("name"), physics);

			newObject->addComponent(std::make_shared<BodyComponent>(newObject));
		}

		comp = comp->NextSiblingElement("Component");
	}
	//Attempt to initialize the object and return it if initialization was successful.
	if (newObject->Initialize(initializers))
		return newObject;
	else
	{
		std::cout << "Object did not initialize!" << std::endl;
		return NULL;
	}
	//return std::unique_ptr<Object>();
}



//Overload of create that is used for creating arrow objects when the user presses the space bar.
std::shared_ptr<Object> ObjectFactory::create(GAME_OBJECTFACTORY_INITIALIZERS initializers, std::vector<std::shared_ptr<Component>> components)
{
	//Create pointer to new objects that are created during runtime.
	std::shared_ptr<Object> returnObj = std::make_shared<Object>();

	//Add the components to the object.
	for (auto comp : components)
		returnObj->addComponent(comp);

	GAME_PHYSICS physics;

	physics.objectShape = GAME_RECTANGLE;
	physics.bodyType = GAME_DYNAMIC;
	physics.density = 0.1f;
	physics.friction = 0.1f;
	physics.restitution = 2.0f;
	physics.angularDamping = 5.0f;
	physics.linearDamping = 0.0f;
	physics.physicsOn = true;

	initializers.game->getPhysicsAssetLibrary()->AddAsset("Arrow", physics);
	
	//Initialize the object and its components. Return the object if the initialization is successful.
	if (returnObj->Initialize(initializers))
		return returnObj;
	else
	{
		std::cout << "Object did not initialize!" << std::endl;
		return nullptr;
	}
	
	//return returnObj;
}