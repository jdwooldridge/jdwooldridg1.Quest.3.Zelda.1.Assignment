#pragma once

#include <random>
#include <memory>

#include "Definitions.h"



class Component;
class GraphicsDevice;
class View;
class Texture;
class InputDevice;

class Object
{
public:
    Object();
    ~Object();
    bool Initialize(GAME_OBJECTFACTORY_INITIALIZERS);
    std::shared_ptr<Object> Update(GAME_FLT); 
    void addComponent(std::shared_ptr<Component>);
    template<class T>
    std::shared_ptr<T> GetComponent()
    {
        for (auto comp : components)
        {
            std::shared_ptr<T> target;
            if ((target = std::dynamic_pointer_cast<T>(comp)))
            {
                return(target);
            }
        }

        //Return NULL;
        return(std::shared_ptr<T>());
    }
	void removeComponents();
	bool getIsDead();
	void setIsDead(bool);
	std::string getObjectType() { return objectType; }

protected:

    bool initialized;
    std::vector<std::shared_ptr<Component>> components;
	bool isDead;
	std::string objectType;
};