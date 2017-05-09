#pragma once

#ifndef _STRING_
#include <string>
#endif

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;

typedef struct _GAME_VEC
{
    GAME_FLT x;
    GAME_FLT y;
} GAME_VEC;

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 800;
const GAME_INT SCREEN_HEIGHT = 600;
const GAME_INT GAME_FPS = 100;
const GAME_INT FRAME_DELAY = 1000 / GAME_FPS;
//const GAME_INT LEVEL_WIDTH = 4000;
//const GAME_INT LEVEL_HEIGHT = 600;

class Game;

typedef struct _GAME_OBJECTFACTORY_INITIALIZERS
{
    std::string objectType;
    GAME_VEC position;
    GAME_FLT angle;
    bool vertical; //Will the leever move up or down?
    bool radius; //Will the octorok move in a circular motion? 
    Game* game; //For grabbing artassetlibrary, view, etc.
    GAME_INT health; //Object health.
    /*GAME_INT destructTime;//move to new AssetLibraryGame
    std::shared_ptr<ResourceManager> devices;
    std::map<GAME_DIRECTION, bool> gDirection;
    std::shared_ptr<Object> joinedObject; //only needed for joint*/
} GAME_OBJECTFACTORY_INITIALIZERS;

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_DYNAMIC };

typedef struct GAME_PHYSICS
{
	//GAME_FLT spinSpeed;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE objectShape;
	GAME_FLT density;
	GAME_FLT friction;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	//GAME_FLT force;
	bool physicsOn;
} GAME_PHYSICS;

//Event Types
enum GAME_EVENT {GAME_NA,GAME_UP,GAME_DOWN,GAME_LEFT,GAME_RIGHT,GAME_QUIT, GAME_SPACE, GAME_NUM_EVENTS};

//Constants
const GAME_FLT PI = 3.14159f;
const float fPRV = 10.0f;