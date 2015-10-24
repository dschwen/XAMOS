#include "AMOS_Sprite.h"

AMOS_Sprite::AMOS_Sprite(int x_, int y_, string imagename_)
{
	x = x_;
 	y = y_;
	imagename = imagename_;
}
void AMOS_Sprite::setPos(int x_, int y_)
{
	x = x_;
 	y = y_;
}
void AMOS_Sprite::setImage(string imagename_)
{
	imagename = imagename_;
}

#ifdef USESDL
void AMOS_Sprite::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	// Holds offsets:
	SDL_Rect offset;

	// Get offsets:
	offset.x = x;
	offset.y = y;

	// Blit:
	SDL_BlitSurface( source, clip, destination, &offset );
}
void AMOS_Sprite::show(SDL_Surface* _image, SDL_Surface* _screen)
{
	// Show the SDL sprite:
	apply_surface(x, y, _image, _screen, NULL);
}

// Old version - using unordered_map in AMOS_Sprite class:
/*
void AMOS_Sprite::show(boost::unordered_map<std::string, SDL_Surface*>* _images, SDL_Surface* _screen)
{
	// Show the SDL sprite:
	if (imagename != "")
		apply_surface(x, y, (*_images)[imagename], _screen, NULL);
}
*/
#endif

