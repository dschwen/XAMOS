#ifndef GAMEENGINEWRAPPER_H
#define GAMEENGINEWRAPPER_H

// Change this to build without SDL (moved to Makefile):
//#ifndef USESDL
//#define USESDL
//#endif

// Added - to use Boost (moved to Makefile):
//#ifndef USEBOOST
//#define USEBOOST
//#endif

#include <string>
#include <vector>

//#define GLES // debug test - OpenGL ES support (not yet complete or working)

// Added for SDL (and Boost for now):
#if defined(USESDL) && !defined(GLES)
#include "SDL/SDL.h" // Core SDL
#include "SDL/SDL_opengl.h" // Added - OpenGL support!
#endif

// To test - OpenGL ES support:
#if defined(USESDL) && defined(GLES)
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <SDL/SDL_syswm.h>
#endif

#ifdef USESDL
#include "SDL/SDL_image.h" // SDL extension
#include "SDL/SDL_mixer.h" // SDL extension
#include "SDL/SDL_gfxPrimitives.h" // SDL extension
#include "SDL/SDL_ttf.h" // SDL extension - added
#include "Timer.h" // Custom Timer class using SDL
#include "SDL_collide.h" // Added - SDL_collide (in local directory)
#endif

#if defined(USESDL) && defined(USEBOOST)
// Use Boost hash table datatype. TODO: Test unordered_map without Boost (C++11).
#include <boost/unordered_map.hpp>
using namespace boost;
#endif

#if defined(USESDL) && !defined(USEBOOST)
// Deprecated:
#include <ext/hash_map>

// TODO - allow hash_map for other compilers besides G++
using namespace __gnu_cxx;

// Added - fix for hash_map using std::string:
namespace __gnu_cxx //std
{
	template<> struct hash< std::string >
	{
		size_t operator()( const std::string& x ) const
		{
			return hash< const char* >()( x.c_str() );
		}
	};
}
#endif

// Added - detect all Amiga-like systems:
#if !defined(AMIGOID) && (defined(__AROS__) || defined(__MORPHOS__) || defined(__amigaos__) || defined (__amigaos4__))
#define AMIGOID
#endif

using namespace std;

#include "AMOS_System.h"
class AMOS_System;

#ifdef USESDL
#include "AMOS_Sprite.h"
class AMOS_Sprite;
#endif

class GameEngineWrapper
{
	// From jAMOS - need to be implemented:
	// jAMOS* ma;
	
	// From jAMOS - need to be implemented:
	// Used to hold the simulated AMOS Sprites and Bobs:
	//AMOS_Sprite mainsprite[];
	//AMOS_Sprite mainbob[];

	// From jAMOS - need to be implemented:
	// Added:
	//java.awt.image.BufferedImage buf = null;
	//java.awt.Graphics gg = null;

public:
	GameEngineWrapper();
	//GameEngineWrapper(jAMOS mygame);

	AMOS_System* AM;

	// Moved to public:
#ifdef USESDL
	vector<AMOS_Sprite*> mainsprite;
	vector<AMOS_Sprite*> mainbob;
#endif

	// Added - from XAMOS class:
	void demotest();

	void spritebanktotextures();
	void screentotexture(int num);
	void rainbowtotexture(int num);

#ifdef USESDL
	GLuint surfacetotexture(int w, int h, SDL_Surface* surface, GLuint texture, bool transparent);
#endif

	// Used for OpenGL:
	void displaywithopengl(int x, int y, int w, int h, SDL_Surface* surface);
	void displaytexturewithopengl(int x, int y, int w, int h, GLuint texture);

// Added for SDL:
#if defined(USESDL) && defined(USEBOOST)
	// Hash table for images:
	unordered_map<std::string, SDL_Surface*> images;

	// Hash table for OpenGL textures of the above:
	unordered_map<std::string, GLuint> images_texture;

	// Hash table for sounds:
	//unordered_map<std::string, Mix_Chunk*> sounds;
#endif
#if defined(USESDL) && !defined(USEBOOST)
	// Warning - deprecated type!
	// Hash table for images:
	hash_map<std::string, SDL_Surface*> images;

	// Hash table for OpenGL textures of the above:
	hash_map<std::string, GLuint> images_texture;

	// Hash table for sounds:
	//hash_map<std::string, Mix_Chunk*> sounds;

#endif

#ifdef USESDL
	// Added - ttf font:
	TTF_Font *font;

	// Added - sounds not in a hash table:
	Mix_Chunk* xamossound;
	Mix_Chunk* bellsound;
	Mix_Chunk* boomsound;
	Mix_Chunk* shootsound;

	// Added: vector for SDL surfaces of multiple AMOS-style screens:
	vector<SDL_Surface*> screens;
	vector<int> screenx;
	vector<int> screeny;

	// OpenGL textures for the above:
	vector<GLuint> screens_texture;
	vector<int> screens_modified;

	bool usetransparentscreens;

	// Added: vector for SDL surfaces of multiple AMOS-style rainbows:
	vector<SDL_Surface*> rainbows;

	// OpenGL textures for the above:
	vector<GLuint> rainbows_texture;
	vector<int> rainbows_modified;

	// Older - TODO - screens (1 for now):
	//AMOS_Sprite* mainsprite1;

	// The screen attributes:
	int SCREEN_WIDTH; // = 720;
	int SCREEN_HEIGHT; // = 576;
	int SCREEN_BPP; // = 32;

	// The frame rate:
	int FRAMES_PER_SECOND; // = 60;

	// The event structure
	SDL_Event event;

	// SDL surface for the screen to display on:
	SDL_Surface* screen;

	bool useopengl;
	bool usenpot;
	Uint32 maxtexturesize;
#endif

	// Key input:
	int keyleft;
	int keyright;
	int keyup;
	int keydown;
	int keylshift;
	int keyrshift;
	int keylctrl;
	int keyrctrl;
	int keyesc;
	int keyc;

	// Mouse input:
	int mousex, mousey, lmouse, rmouse, mmouse;

	// AMOS Screen instructions:
	void screenOpen(int a, int b, int c, int d, int e);
	void setScreenTransparency(bool a);

	// Added - for rainbows:
	void openrainbow(int num, int height);
	void rain(int t1, int t2, int t3);

	// Load image or IFF file (supports other formats instead for now):
	void loadIff(string a);
	void loadIff(string a, int b);

	// Load a Sprite bank from AMOS Basic .abk files:
	int loadamosabk(string fileName, int bank, int scale);

	// Moved these - wrapper methods for JGame
	void bob(int a, double b, double c);
	void bob(int a, double b, double c, int d);
	void sprite(int a, double b, double c);
	void sprite(int a, double b, double c, int d);

	// Bob/sprite access methods:
	double xbob(int a);
	double ybob(int a);
	int ibob(int a);
	double xsprite(int a);
	double ysprite(int a);
	int isprite(int a);

	// Collision detection:
	int bobCol(unsigned int t1);
	int bobCol(unsigned int t1, unsigned int t2, unsigned int t3);
	int spriteCol(unsigned int t1);
	int spriteCol(unsigned int t1, unsigned int t2, unsigned int t3);
	int spriteBobCol(unsigned int t1);
	int spriteBobCol(unsigned int t1, unsigned int t2, unsigned int t3);
	int bobSpriteCol(unsigned int t1);
	int bobSpriteCol(unsigned int t1, unsigned int t2, unsigned int t3);
	int col(int t1);


	int joy(int a);
	int xmouse();
	int ymouse();

	// To do:
	int mousekey(int t1);

	void initspritesandbobs();
	void initScreen(); // added
	void boboff(int a);
	void boboff();
	void spriteoff(int a);
	void spriteoff();

	// To improve:
	void animatesprites();
	void animatebobs();

	// Removed // Moved (now public):
	//void prepdraw();
	//void finalisedraw();

#ifdef USESDL
	// Moved - load an SDL image:
	SDL_Surface* load_image(std::string filename);

	// Load an SDL Mixer sound sample (disabled for now - not currently used):
	//Mix_Chunk* load_sound(std::string filename, std::string name);
#endif

	// Added - AMOS sounds:
	void bell();
	void boom();
	void shoot();

	// Added - more AMOS Screen instructions:
	void screenSize(int a, int b, int c);
	void screenDisplay(int a, int b, int c);

#ifdef USESDL
	// Thanks to lazyfoo for these methods, used below:
	Uint32 get_pixel32(SDL_Surface *surface, int x, int y);
	void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
	SDL_Surface* flip_surface(SDL_Surface *surface, int flags);
#endif

	// Banks:
	// Load a bank (folder of sprites for now)
	// TO DO - faux packed pictures (with unpack).
	void load(string a, int b);
	void load(string a, int b, int scale);
	void erase(int a);

	// Added - Text:
	int text(int x, int y, string textstring);
	int textlength(string textstring);

	// Added - drawing methods:
	int pastebob(int x, int y, int a);
	int pasteicon(int x, int y, int a);
	int plot(int x, int y, int a);
	int plot(int x, int y);
	int draw(int x1, int y1, int x2, int y2);
	int bar(int x1, int y1, int x2, int y2);
	int box(int x1, int y1, int x2, int y2);
	int circle(int x1, int y1, int r1);
	int ellipse(int x1, int y1, int r1, int r2);

	// Added - Abk decoder:
	unsigned long getcolor(unsigned int r, unsigned int g, unsigned int b);
	unsigned char getnextbyte(char* buffer, long unsigned int* bufferpos);
	int loadAbkAndDecode(string name_, int bank, unsigned int scale);

	// Moved - SDL methods from XAMOS class:
#ifdef USESDL
	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
#endif
	void cls();
	void handle_input();
	bool sdlinit();
	bool initGL();
	void initsimpleconsole();
	void initsdlstuff();
	void initsdlaudio();
	bool load_files();
	void clean_up();
};
#endif

