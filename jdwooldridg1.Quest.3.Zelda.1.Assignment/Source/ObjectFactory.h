#pragma once

#include "Object.h"
#include "Definitions.h"

class TiXmlElement;

class ObjectFactory
{
public:
	std::shared_ptr<Object> create(TiXmlElement*, Game*);
	std::shared_ptr<Object> create(GAME_OBJECTFACTORY_INITIALIZERS, std::vector<std::shared_ptr<Component>>);
};