// Moved to Makefile:
//#ifndef USESDL
//#define USESDL
//#endif

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#ifdef USESDL
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
// Removed:
//#include <boost/unordered_map.hpp>
#endif

using namespace std;

// The SDL sprite that will move around on the screen:
class AMOS_Sprite
{
	public:
	// The X and Y offsets of the sprite:
	int x, y;

	string imagename;

	int imagenumber;

	// Initializes the variables:
	AMOS_Sprite(int x_, int y_, string imagename_);

	void setPos(int x_, int y_);
	void setImage(string imagename_);

#ifdef USESDL
	// Apply to an SDL surface:
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );

	// Shows the sprite on the screen:
	void show(SDL_Surface* _image, SDL_Surface* _screen);
	//void show(boost::unordered_map<std::string, SDL_Surface*>* _images, SDL_Surface* _screen);
#endif
};

#endif

