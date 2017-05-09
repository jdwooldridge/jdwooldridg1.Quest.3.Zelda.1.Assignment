#include "Game.h"
#include "GraphicsDevice.h"
#include "SpriteComponent.h"

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_INITIALIZERS initializers)
{
	this->gDevice = initializers.game->getGraphicsDevice();
	this->view = initializers.game->getView();
	
	//Add the sprite to the sprite vector in the graphics device.
	gDevice->addSprite(this);
	
	//Set the texture.
	texture = initializers.game->getArtAssetLibrary()->Search(initializers.objectType).get();
	
	return true;
}

std::shared_ptr<Object> SpriteComponent::Update()
{
	return nullptr;
}

bool SpriteComponent::Finish()
{
	return true;
}
//Draw this sprite.
void SpriteComponent::Draw()
{
	texture->Draw(gDevice->getRenderer(), view, _owner->GetComponent<BodyComponent>()->getPosition(), _owner->GetComponent<BodyComponent>()->getAngle(), NULL);
}