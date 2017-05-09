#pragma once

//#include "SDL.h"
//#include "SDL_image.h"
//#include "View.h"
#include "Definitions.h"
//#include <iostream>

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;
class View;

class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool load(SDL_Renderer* renderer, std::string path);

	//Deallocates texture
	void free();

	//Renders texture at a certain point.
	void Draw(SDL_Renderer* renderer, View* view, GAME_VEC position, GAME_FLT angle, SDL_Rect* clip = nullptr);

	int getWidth();
	int getHeight();

private:

	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;
};