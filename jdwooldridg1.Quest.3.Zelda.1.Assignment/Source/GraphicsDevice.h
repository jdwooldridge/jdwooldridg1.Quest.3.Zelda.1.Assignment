/*
* Author:	Keith Bush
*			UALR
*
* Date:		January 31, 2015
*
* File:		GraphicsDevice.h
*
* Purpose:	Declaration of the SDL GraphicsDevice class
*/

#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

//#include "SDL.h"
//#include "SDL_image.h"
#include "Definitions.h"
//#include "SpriteComponent.h"

#ifndef _VECTOR_
    #include <vector>
#endif // !_VECTOR_

struct SDL_Renderer;
struct SDL_Windows;

class SpriteComponent;

class GraphicsDevice
{

public:
    GraphicsDevice(Uint32, Uint32);
    ~GraphicsDevice();

    bool Initialize(bool);
    bool ShutDown();

    void Begin();
    void Present();
    void Draw();

    SDL_Renderer* getRenderer();
    void addSprite(SpriteComponent*);

private:

    //Window(s) to display graphics
    SDL_Window* screen;
    SDL_Renderer* renderer;

    //Parameter
    const Uint32 SCREEN_WIDTH;
    const Uint32 SCREEN_HEIGHT;

    std::vector<SpriteComponent*> sprites;

};

#endif