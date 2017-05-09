#pragma once
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "View.h"

#include "Definitions.h"
class ObjectFactory;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool Initialize(GAME_INT SCREEN_WIDTH, GAME_INT SCREEN_HEIGHT, std::string assetPath);
	bool Shutdown();

	//Device Getters
	GraphicsDevice* GetGraphicsDevice() { return gDevice.get(); }
	InputDevice* GetInputDevice() { return iDevice.get(); }
	PhysicsDevice* GetPhysicsDevice() { return pDevice.get(); }

	//Device Setters
	ArtAssetLibrary* GetArtLibrary() { return aLibrary.get(); }
	PhysicsAssetLibrary* GetPhysicsLibrary() { return pLibrary.get(); }

	//ObjectFactor Getter
	ObjectFactory* GetObjectFactory() { return factory.get(); }

	//Other Getters
	GAME_INT GetFPS() { return GAME_FPS; }
	GAME_VEC GetCityCorner() { return cityCorner; }
	GAME_LEVEL GetLevel() { return level; }
	bool GetLoadBasement() { return loadBasement; }

	//Device Setters
	void SetGraphicsDevice(std::shared_ptr<GraphicsDevice> gDevice) { this->gDevice = gDevice; }
	void SetInputDevice(std::shared_ptr<InputDevice> iDevice) { this->iDevice = iDevice; }
	void SetPhysicsDevice(std::shared_ptr<PhysicsDevice> pDevice) { this->pDevice = pDevice; }
	void SetSoundDevice(std::shared_ptr<SoundDevice> sDevice) { this->sDevice = sDevice; }

	//Library Setters
	void SetArtLibrary(std::shared_ptr<ArtAssetLibrary> aLibrary) { this->aLibrary = aLibrary; }
	void SetPhysicsLibrary(std::shared_ptr<PhysicsAssetLibrary> pLibrary) { this->pLibrary = pLibrary; }

	//Other Setters
	void SetFPS(GAME_INT fps) { GAME_FPS = fps; }
	void SetCityCorner(GAME_VEC cityCorner) { this->cityCorner = cityCorner; }
	void SetLoadBasement(bool loadBasement) { this->loadBasement = loadBasement; }

protected:
	//Devices
	std::shared_ptr<GraphicsDevice> gDevice;
	std::shared_ptr<InputDevice> iDevice;
	std::shared_ptr<PhysicsDevice> pDevice;

	//LIbraries
	std::shared_ptr<ArtAssetLibrary> aLibrary;
	std::shared_ptr<PhysicsAssetLibrary> pLibrary;

	std::shared_ptr<ObjectFactory> factory;

	GAME_INT GAME_FPS;
	GAME_VEC cityCorner;
	bool loadBasement;
};

#endif