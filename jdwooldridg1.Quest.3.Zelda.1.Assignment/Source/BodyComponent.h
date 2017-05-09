#pragma once

#include <string>

//#include "Box2D.h"

#include "Component.h"

class PhysicsDevice;

class BodyComponent : public Component
{
public:
    BodyComponent(std::shared_ptr<Object> owner)
        : Component(owner)
    { };
	bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
    std::shared_ptr<Object> Update();
    bool Finish();
    GAME_VEC getPosition();
    GAME_FLT getAngle();
    GAME_VEC getStartPosition();
    void setPositionX(GAME_FLT);
    void setPositionY(GAME_FLT);
    void setAngle(GAME_FLT);
private:
	//Render position/angle members.
    GAME_VEC startPosition;
    GAME_VEC position;
    GAME_FLT angle;

	//b2BodyDef bd;
	//b2PolygonShape shape;
	//b2FixtureDef shapefd;
	//b2Body* body;

	PhysicsDevice* pDevice;
};