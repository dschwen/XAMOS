#include "GameEngineWrapper.h"

// To test - OpenGL ES support (move me):
#ifdef GLES
//EGLDisplay g_eglDisplay = 0;
//EGLConfig g_eglConfig = 0;
//EGLContext g_eglContext = 0;
//EGLSurface g_eglSurface = 0;
//Display *g_x11Display = NULL; // TODO

// consts
//#define COLOURDEPTH_RED_SIZE  		5
//#define COLOURDEPTH_GREEN_SIZE 		6
//#define COLOURDEPTH_BLUE_SIZE 		5
//#define COLOURDEPTH_DEPTH_SIZE		16

//static const EGLint g_configAttribs[] =
//{					  EGL_RED_SIZE,      	    COLOURDEPTH_RED_SIZE,
//					  EGL_GREEN_SIZE,    	    COLOURDEPTH_GREEN_SIZE,
//					  EGL_BLUE_SIZE,     	    COLOURDEPTH_BLUE_SIZE,
//					  EGL_DEPTH_SIZE,	    COLOURDEPTH_DEPTH_SIZE,
//					  EGL_SURFACE_TYPE,         EGL_WINDOW_BIT,
//					  EGL_RENDERABLE_TYPE,      EGL_OPENGL_ES_BIT,
//					  EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
//					  EGL_NONE
//};
#endif



// Public methods:

// Initialiser method:
GameEngineWrapper::GameEngineWrapper()
{
	keyleft = 0;
	keyright = 0;
	keyup = 0;
	keydown = 0;
	keylshift = 0;
	keyrshift = 0;
	keylctrl = 0;
	keyrctrl = 0;
	keyesc = 0;
	keyc = 0;

	mousex = 0;
	mousey = 0;
	lmouse = 0;
	rmouse = 0;
	mmouse = 0;
}

//GameEngineWrapper::GameEngineWrapper(jAMOS mygame)
//{
//}


// Removed:
//void GameEngineWrapper::prepdraw()
//{
//}
//void GameEngineWrapper::finalisedraw()
//{
//}


// From XAMOS class:
void GameEngineWrapper::demotest()
{
	bool quit = false;

#ifdef USESDL
	// The frame rate regulator:
	Timer fps;
#endif
	//cout << "DEBUG: demotest()" << endl;
	while(quit == false)
	{
#ifdef USESDL
		// Handle SDL events here:
	        // Start the frame timer:
	        fps.start();
	
	        // While there's events to handle:
	        while( SDL_PollEvent( &(event) ) )
	        {
			handle_input();
	
			// If the user has X'ed out the window:
			if( event.type == SDL_QUIT )
			{
				// Quit the program:
				quit = true;
			}
		}

		// Added: ESC or LCTRL+C to quit:
		if ((keyesc) || (keylctrl && keyc))
			quit = true;
#endif

		// XAMOS interpreter:
		for (unsigned int n=0; n<AM->g->ActiveObjects.size(); n++)
			AM->interpreter->interpret(&(AM->g->mytokens), n);

		// Run the XAMAL interpreter here:
		AM->synchro();

		// Animate sprites and bobs here (TODO - with screens):
		animatebobs();
		animatesprites();

#ifdef USESDL
		// Update OpenGL textures here if necessary:
		if (useopengl)
		{
			for (unsigned int scr=0; scr < screens.size(); scr++)
				if ((screens[scr] != NULL) && (screens_modified[scr]))
				{
					screentotexture(scr);
				}
			for (unsigned int rai=0; rai < rainbows.size(); rai++)
				if ((rainbows[rai] != NULL) && (rainbows_modified[rai]))
				{
					rainbowtotexture(rai);
				}
		}

		// Main SDL drawing:

		// Clear the framebuffer:
		if (useopengl)
			glClear(GL_COLOR_BUFFER_BIT);
		else
			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x0, 0x0, 0x0));

		// Show the rainbows here:
		for (unsigned int raindisp=0; raindisp < rainbows.size(); raindisp++)
			if (rainbows[raindisp] != NULL)
			{
				if (useopengl)
				{
					//displaywithopengl(0, AM->RainbowPos[raindisp],
					//	rainbows[raindisp]->w, rainbows[raindisp]->h, rainbows[raindisp]);
					displaytexturewithopengl(0, AM->RainbowPos[raindisp],
						rainbows[raindisp]->w, rainbows[raindisp]->h, rainbows_texture[raindisp]);
				}
				else
				{
					apply_surface(0, AM->RainbowPos[raindisp], rainbows[raindisp], screen, NULL);
				}
			}

		// Show the screens here:
		for (unsigned int screendisp=0; screendisp < screens.size(); screendisp++)
			if (screens[screendisp] != NULL)
			{
				if (useopengl)
				{
					//displaywithopengl(screenx[screendisp], screeny[screendisp],
					//	screens[screendisp]->w, screens[screendisp]->h, screens[screendisp]);
					displaytexturewithopengl(screenx[screendisp], screeny[screendisp],
						screens[screendisp]->w, screens[screendisp]->h, screens_texture[screendisp]);
				}
				else
				{
					apply_surface(screenx[screendisp], screeny[screendisp], screens[screendisp], screen, NULL);
				}
			}

		// Show the bobs here:
		for (unsigned int n=0; n<mainbob.size(); n++)
			if (mainbob[n] != NULL)
				if (string(mainbob[n]->imagename) != "")
				{
					SDL_Surface* theimage = images[mainbob[n]->imagename];
					if (useopengl)
					{
						//displaywithopengl(mainbob[n]->x, mainbob[n]->y, theimage->w, theimage->h, theimage);
						displaytexturewithopengl(mainbob[n]->x, mainbob[n]->y, theimage->w, theimage->h, images_texture[mainbob[n]->imagename]);
					}
					else
					{
						apply_surface(mainbob[n]->x, mainbob[n]->y, theimage, screen, NULL);
					}
				}

		// Show the sprites here:
		for (unsigned int n=0; n<mainsprite.size(); n++)
			if (mainsprite[n] != NULL)
				if (string(mainsprite[n]->imagename) != "")
				{
					SDL_Surface* theimage = images[mainsprite[n]->imagename];
					if (useopengl)
					{
						//displaywithopengl(mainsprite[n]->x, mainsprite[n]->y, theimage->w, theimage->h, theimage);
						displaytexturewithopengl(mainsprite[n]->x, mainsprite[n]->y, theimage->w, theimage->h, images_texture[mainsprite[n]->imagename]);
					}
					else
					{
						apply_surface(mainsprite[n]->x, mainsprite[n]->y, theimage, screen, NULL);
					}
				}

		// Update the screen:
		if (useopengl)
		{
#if defined(USESDL) && !defined(GLES)
			SDL_GL_SwapBuffers();
#endif
#if defined(USESDL) && defined(GLES)
			//eglSwapBuffers(g_eglDisplay, g_eglSurface);
#endif
		}
		else
		{
			if (SDL_Flip(screen) == -1)
				return; // -1
		}

		// Cap the frame rate:
		//if (!useopengl) // TODO - Vsync not supported on all platforms?
#if defined(USESDL) && !defined(GLES)
			if (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
				SDL_Delay(( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks());
#endif
#endif
	}
}

/*
void GameEngineWrapper::spritebanktotextures()
{
	if (!useopengl)
		return;
#ifdef USESDL
	// Iterate through the entire image bank here:
	for (unsigned int it=0; it<AM->currentspriteimages.size(); it++)
	{
		// Grab the name and image:
		string name = AM->currentspriteimages[it];

		SDL_Surface* image = NULL;
		image = images[name];
		
		// Convert to OpenGL texture;
		GLuint texture = images_texture[name];
		if (image != NULL)
		{
			texture = surfacetotexture(image->w, image->h, image, texture, true);

			// Insert in new hash table:
			images_texture[name] = texture;
		}
	}
#endif
}
*/

void GameEngineWrapper::spritebanktotextures()
{
	if (!useopengl)
		return;
#ifdef USESDL
	// Iterate through the entire image bank here:
#if defined(USESDL) && defined(USEBOOST)
	for (unordered_map<std::string, SDL_Surface*>::iterator it = images.begin(); it != images.end(); ++it)
#endif
#if defined(USESDL) && !defined(USEBOOST)
	for (hash_map<std::string, SDL_Surface*>::iterator it = images.begin(); it != images.end(); ++it)
#endif
	{
		// Grab the name and image:
		string name = it->first;
		SDL_Surface* image = it->second;
		
		// Convert to OpenGL texture;
		GLuint texture = images_texture[name];
		if (image != NULL)
		{
			texture = surfacetotexture(image->w, image->h, image, texture, true);

			// Insert in new hash table:
			images_texture[name] = texture;
		}
	}
#endif
}


void GameEngineWrapper::screentotexture(int num)
{
	if (!useopengl)
		return;
#ifdef USESDL
	SDL_Surface* image = screens[num];

	// Add to new vector:
	while ((int)screens_texture.size() <= num)
		screens_texture.push_back(0);

	// Convert to OpenGL texture;
	GLuint texture=screens_texture[num];
	if (image != NULL)
	{
		texture = surfacetotexture(image->w, image->h, image, texture, usetransparentscreens);
		screens_texture[num]=texture;
		screens_modified[num]=false;
	}
#endif
}

void GameEngineWrapper::rainbowtotexture(int num)
{
	if (!useopengl)
		return;
#ifdef USESDL
	SDL_Surface* image = rainbows[num];

	// Add to new vector:
	while ((int)rainbows_texture.size() <= num)
		rainbows_texture.push_back(0);

	// Convert to OpenGL texture;
	GLuint texture=rainbows_texture[num];
	if (image != NULL)
	{
		texture = surfacetotexture(image->w, image->h, image, texture, true);
		rainbows_texture[num]=texture;
		rainbows_modified[num]=false;
	}
#endif
}

#ifdef USESDL
// TODO - this method is very experimental and could do with a rewrite with more OpenGL knowledge!
GLuint GameEngineWrapper::surfacetotexture(int w, int h, SDL_Surface* surface, GLuint texture, bool transparent)
{
	//GLuint texture;
	GLenum texture_format;

	Uint32 wPow, hPow;
	if (usenpot)
	{
		wPow = w; hPow = h;
	}
	else
	{
		wPow = (unsigned) pow(2, ceil(log(w) / log(2)));
		hPow = (unsigned) pow(2, ceil(log(h) / log(2)));
	}

	// TODO - texture splitting on systems not supporting large textures:
	unsigned int wcrop, hcrop;
	wcrop=1; hcrop=1;
	while (wPow > maxtexturesize)
	{
		wPow >>= 1;
		wcrop <<= 1;
	}
	while (hPow > maxtexturesize)
	{
		hPow >>= 1;
		hcrop <<= 1;
	}
	if (wcrop>1 || hcrop>1)
	{
		// TODO - make multiple textures here.
	}

	SDL_Surface* alphasurface;

	if (usenpot)
	{
		// Quicker method when using non-power-of-two textures:
		alphasurface = SDL_DisplayFormatAlpha(surface);
	}
	// Convert surface to next power-of-two surface:
	else if (transparent)
	{
		// For transparent screens, sprite images, etc.
		SDL_Surface* newsurface;
		SDL_PixelFormat& fmt = *(surface->format);

		// TODO - too slow? Create power-of-two size surface:
		newsurface = SDL_CreateRGBSurface( SDL_SWSURFACE, wPow, hPow, 32, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
		Uint32 colorkey = fmt.colorkey;
		SDL_Rect rect;
		rect.x = 0; rect.y = 0;	rect.h = hPow; rect.w = wPow;
		SDL_FillRect(newsurface, &rect, colorkey);
		SDL_SetColorKey(newsurface, SDL_SRCCOLORKEY, colorkey);
		SDL_BlitSurface(surface, 0, newsurface, 0);

		// TODO - too slow?
		alphasurface = SDL_DisplayFormatAlpha(newsurface);

		SDL_FreeSurface(newsurface);
	}
	// Convert surface to next power-of-two surface:
	else
	{
		// For non-transparent screens, etc:
		SDL_Surface* newsurface;
		newsurface = SDL_DisplayFormatAlpha(surface); // TODO - why is this surface format needed?
		SDL_PixelFormat& fmt = *(newsurface->format); // TODO - why is this surface format needed?

		// TODO - too slow? Create power-of-two size surface:
		alphasurface = SDL_CreateRGBSurface( SDL_SRCALPHA, wPow, hPow, 32, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
		Uint32 alpha = SDL_MapRGBA( &fmt, 0, 0, 0, 0x0 ); // fmt.Amask - problem!
		SDL_Rect rect;
		rect.x = 0; rect.y = 0;	rect.h = hPow; rect.w = wPow;
		SDL_FillRect(alphasurface, &rect, alpha);

		SDL_SetAlpha( alphasurface, SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT );
		SDL_BlitSurface(surface, 0, alphasurface, 0);
		SDL_FreeSurface(newsurface);
	}

	GLint nOfColors = alphasurface->format->BytesPerPixel;

#if defined(USESDL) && !defined(GLES)
	// TODO - fix texture format for alternative endianness:
	if (alphasurface->format->Rmask == 0x000000ff)
		texture_format = GL_RGBA; // Does not work!
	else
 		texture_format = GL_BGRA; // Works on little-endian systems, wrong colours on big-endian e.g. PPC.
#endif
#if defined(USESDL) && defined(GLES)
	texture_format=0; // TODO - OpenGL ES
#endif
	if (texture==0)
	{
		// Create new OpenGL texture:
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, wPow, hPow, 0, texture_format, GL_UNSIGNED_BYTE, alphasurface->pixels);
	}
	else
	{
		// Modify existing OpenGL texture:
		glBindTexture(GL_TEXTURE_2D, texture);
		if (wPow>1024) // kludge
			glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, wPow, hPow, 0, texture_format, GL_UNSIGNED_BYTE, alphasurface->pixels);
		else
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, wPow, hPow, texture_format, GL_UNSIGNED_BYTE, alphasurface->pixels); // TODO
	}

	SDL_FreeSurface(alphasurface);

	return texture;
}
/*
GLuint GameEngineWrapper::surfacetotexture(int w, int h, SDL_Surface* surface)
{
	GLuint texture;
	GLenum texture_format;

	Uint32 wPow, hPow;
	if (usenpot)
	{
		wPow = w; hPow = h;
	}
	else
	{
		wPow = (unsigned) pow(2, ceil(log(w) / log(2)));
		hPow = (unsigned) pow(2, ceil(log(h) / log(2)));
	}

	// TODO - too slow?
	SDL_Surface* alphasurface = SDL_DisplayFormatAlpha(surface);

	const SDL_PixelFormat& fmt = *(screen->format);
	SDL_Surface* newsurface = SDL_CreateRGBSurface( SDL_SRCALPHA, wPow, hPow, 32, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);
	SDL_PixelFormat *format = alphasurface->format;
	// Fill surface with alpha.
	Uint32 alpha = 0;
	alpha = SDL_MapRGBA( format, 0, 0, 0, 0x77 ); // fmt.Amask - problem!
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = hPow;
	rect.w = wPow;
	int ret = SDL_FillRect(newsurface, &rect, alpha);
	//alphasurface->flags &= !SDL_SRCALPHA; // problem!
	SDL_SetAlpha( newsurface, SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT );
	ret=SDL_BlitSurface(alphasurface, 0, newsurface, 0);
	SDL_FreeSurface(alphasurface);

	GLint nOfColors = newsurface->format->BytesPerPixel;
	if (newsurface->format->Rmask == 0x000000ff)
		texture_format = GL_RGBA;
	else
 		texture_format = GL_BGRA;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// TODO - much too slow?
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, wPow, hPow, 0, texture_format, GL_UNSIGNED_BYTE, newsurface->pixels);

	SDL_FreeSurface(newsurface);

	return texture;
}
*/
#endif

// Used for OpenGL - TODO - much too slow at present:
void GameEngineWrapper::displaywithopengl(int x, int y, int w, int h, SDL_Surface* surface)
{
	if (((x+w)<0) || (x > 720) || ((y+h)<0) || (y > 576))
		return;

	Uint32 wPow, hPow;
	if (usenpot)
	{
		wPow = w; hPow = h;
	}
	else
	{
		wPow = (unsigned) pow(2, ceil(log(w) / log(2)));
		hPow = (unsigned) pow(2, ceil(log(h) / log(2)));
	}

	// TODO - much too slow
	GLuint texture = 0;
	texture = surfacetotexture(w, h, surface, texture, true);

	// TODO - use better routine:
#if defined(USESDL) && !defined(GLES)
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(x,      y,      0.0f);
	glTexCoord2i(1, 0); glVertex3f(x+wPow, y,      0.0f);
	glTexCoord2i(1, 1); glVertex3f(x+wPow, y+hPow, 0.0f); 
	glTexCoord2i(0, 1); glVertex3f(x,      y+hPow, 0.0f);
	glEnd();
	glDeleteTextures(1, &texture);
#endif
#if defined(USESDL) && defined(GLES)
	// TODO - OpenGL ES implementation
#endif
}
void GameEngineWrapper::displaytexturewithopengl(int x, int y, int w, int h, GLuint texture)
{
	if (((x+w)<0) || (x > 720) || ((y+h)<0) || (y > 576))
		return;

	Uint32 wPow, hPow;
	if (usenpot)
	{
		wPow = w; hPow = h;
	}
	else
	{
		wPow = (unsigned) pow(2, ceil(log(w) / log(2)));
		hPow = (unsigned) pow(2, ceil(log(h) / log(2)));
	}

	// TODO - texture splitting on systems not supporting large textures:
	unsigned int wcrop, hcrop;
	wcrop=1; hcrop=1;
	while (wPow > maxtexturesize)
	{
		wPow >>= 1;
		wcrop <<= 1;
	}
	while (hPow > maxtexturesize)
	{
		hPow >>= 1;
		hcrop <<= 1;
	}
	if (wcrop>1 || hcrop>1)
	{
		// TODO - display multiple textures here.
	}

	//cout << wPow << ", " << hPow << endl;

	glBindTexture(GL_TEXTURE_2D, texture);


#if defined(USESDL) && !defined(GLES)
	// TODO - use better routine:
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(x,      y,      0.0f);
	glTexCoord2i(1, 0); glVertex3f(x+wPow, y,      0.0f);
	glTexCoord2i(1, 1); glVertex3f(x+wPow, y+hPow, 0.0f); 
	glTexCoord2i(0, 1); glVertex3f(x,      y+hPow, 0.0f);
	glEnd();
#endif
#if defined(USESDL) && defined(GLES)
	// TODO - OpenGL ES implementation
/*
	// OpenGL ES friendly - TODO:
	GLfloat glverts[12] =
	{
		x,	y,	0.0f,
		x+wPow,	y, 	0.0f,
		x+wPow,	y+hPow,	0.0f,
		x,	y+hPow,	0.0f
	};
	glVertexPointer(4, GL_FLOAT, 0, glverts);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_QUADS, 0, 4);
*/
#endif
	// TODO - delete textures when not needed - possible VRAM leak.
}

// AMOS Screen instructions:
void GameEngineWrapper::screenOpen(int a, int b, int c, int d, int e)
{
    	AM->ScreenWidth[a]=b;
    	AM->ScreenHeight[a]=c;
    	AM->ScreenColors[a]=d;
    	AM->ScreenRes[a]=e;
    	AM->ScreenOffsetX[a]=0;
    	AM->ScreenOffsetY[a]=0;
    	AM->ScreenDisplayX[a]=0; //?
    	AM->ScreenDisplayY[a]=0; //?
    	AM->ScreenDisplayWidth[a]=b;
    	AM->ScreenDisplayHeight[a]=c;
    	
    	// TO DO - Cursor:
    	AM->ScreenXCur[a]=0;
    	AM->ScreenYCur[a]=0;

	//cout << "Debug: Attempting to open screen " << AM->stri(a) << endl;

	// TODO! Destroy last surface here...
	// Define the image here...
#ifdef USESDL
	// The new image for the screen:
	SDL_Surface* newImage = NULL;
	SDL_Surface* optimisedImage = NULL;

	const SDL_PixelFormat& fmt = *(screen->format);
	Uint32 flags;
	//if (useopengl)
	//	flags = SDL_HWSURFACE;
	//else
	flags = SDL_SWSURFACE;
	newImage = SDL_CreateRGBSurface(flags, b, c, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

	if (newImage != NULL)
	{
		// Create an optimised surface:
		optimisedImage = SDL_DisplayFormat(newImage);

		// Free the old surface:
		SDL_FreeSurface( newImage );
	}

	// Added - set colorkey for screen to black (0x0, 0x0, 0x0) if using transparent screens:
	if ((optimisedImage != NULL) && usetransparentscreens)
	{
		Uint32 colorkey = SDL_MapRGB(optimisedImage->format, 0x0, 0x0, 0x0);
		SDL_SetColorKey(optimisedImage, SDL_SRCCOLORKEY, colorkey);
	}

	// Added - multi-screens:
	// First expand if necessary:
	while (screens.size() <= (unsigned int)a)
		screens.push_back(NULL);
	while (screenx.size() <= (unsigned int)a)
		screenx.push_back(0);
	while (screeny.size() <= (unsigned int)a)
		screeny.push_back(0);

	screens[a] = optimisedImage;
	screenx[a] = 0;
	screeny[a] = 0;
#endif
	// Moved earlier to avoid crash with bar, screentotexture
	if (useopengl)
		while (screens_modified.size() <= (unsigned int)a)
			screens_modified.push_back(false);

	AM->screen(a); // Is this correct?
	AM->ink(0);
	AM->bar(0, 0, b, c);

	if (useopengl)
	{
		screentotexture(a);
	}
}

// Added - toggle transparency of screens:
void GameEngineWrapper::setScreenTransparency(bool a)
{
	if (a)
	{
		usetransparentscreens = true;
		for (unsigned int n=0; n < screens.size(); n++)
		{
			if (screens[n] != NULL)
			{
				// TODO - make customisable (currently black):
				Uint32 colorkey = SDL_MapRGB(screens[n]->format, 0x0, 0x0, 0x0);
				SDL_SetColorKey(screens[n], SDL_SRCCOLORKEY, colorkey);
			}
		}
	}
	else
	{
		usetransparentscreens = false;
		for (unsigned int n=0; n < screens.size(); n++)
			if (screens[n] != NULL)
				SDL_SetColorKey(screens[n], 0, 0);
	}
}

// Added - for Rainbows:
void GameEngineWrapper::openrainbow(int num, int height)
{
#ifdef USESDL
	// First of all, toggle screen transparency if appropriate:
	if (!usetransparentscreens)
		setScreenTransparency(true);

	// The new image for the rainbow:
	SDL_Surface* newImage = NULL;
	SDL_Surface* optimisedImage = NULL;

	const SDL_PixelFormat& fmt = *(screen->format);
	Uint32 flags;
	//if (useopengl)
	//	flags = SDL_HWSURFACE;
	//else
	flags = SDL_SWSURFACE;

	// TODO - allow width other than 720:
	newImage = SDL_CreateRGBSurface(flags, 720, height, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

	if (newImage != NULL)
	{
		// Create an optimised surface:
		optimisedImage = SDL_DisplayFormat(newImage);

		// Free the old surface:
		SDL_FreeSurface( newImage );
	}

	// First expand if necessary:
	while (rainbows.size() <= (unsigned int)num)
		rainbows.push_back(NULL);

	if (rainbows[num] != NULL)
		SDL_FreeSurface(rainbows[num]);

	rainbows[num] = optimisedImage;

	// Moved earlier to avoid crash:
	if (useopengl)
	{
		while (rainbows_modified.size() <= (unsigned int)num)
			rainbows_modified.push_back(num);

		rainbowtotexture(num);
	}
#endif
}
void GameEngineWrapper::rain(int t1, int t2, int t3) // Which order??? ???? number t1, line t2 = colour t3......
{
	// Sanity checks:
	if ((int)rainbows.size() <= t1)
		return;
	if (rainbows[t1] == NULL)
		return;

	//int b = ((t3&3840)/256)*16; // +1)*16)-1

	// Big-endian (?):
	//int b = ((t3 & 0x00F) * 0x11 / 0x001) + ((t3 & 0x0F0) * 0x1100 / 0x010) + ((t3 & 0xF00) * 0x110000 / 0x100);
	// Little-endian (?):
	int bb = ((t3 & 0x00F) * 0x110000 / 0x001) + ((t3 & 0x0F0) * 0x1100 / 0x010) + ((t3 & 0xF00) * 0x11 / 0x100);

	// TODO:
	//AM->ink(bb);
	//AM->draw(0, t2, AM->ScreenWidth[0], t2); // debug

	Uint8 a = 255; //(Uint8) ((bb & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((bb & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((bb & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((bb & (Uint32)0x000000ff));
	lineRGBA(rainbows[t1], 0, t2, 720, t2, r, g, b, a);

	// Added for OpenGL:
	if (useopengl)
		rainbows_modified[t1]=true;

	// Removed: From Jamagic implementation in Project Myqu:
	//Rainbows[t1].SetPixel(0, t2, GetRGB((t3&15)*16, t3&240, b)); // TODO
	////AMOS_Sys.Rainbows[t1].SetPixel(0, t2, A_PalTo24(0,t3)); // WHY DOES THIS GET $RGB MIXED UP WITH $BGR ???
}

// Load image or IFF file (supports other formats instead for now):
void GameEngineWrapper::loadIff(string a, int b)
{
#ifdef USESDL
	bool alreadyloaded = false;
	bool loaded = false;

	// TODO - load real IFF image here:

	// Now test if the file has already been loaded to the buffer:
	alreadyloaded = !(images.find(a) == images.end());

	if (!alreadyloaded)
		loaded = (load_image(a) != NULL);

	if (loaded || alreadyloaded)
	{
		// Set the background file here (removed):
		//mainsprite1->setImage(a);

		// Blit the new image to the screen:
		SDL_Rect offset;
		offset.x = 0; offset.y = 0;

		if (screens[b] != NULL)
			SDL_BlitSurface(images[a], NULL, screens[b], &offset);

		// Added for OpenGL:
		if (useopengl)
			screens_modified[b]=true;
	}
	else
	{
		cout << "Error loading image! loadIff(\"" << a << "\", " << AM->stri(b) << ")" << endl;
	}
#endif
}

// Load a Sprite bank from AMOS Basic .abk files:
int GameEngineWrapper::loadamosabk(string fileName, int bank, int scale)
{
#ifdef USESDL
	return loadAbkAndDecode(fileName, bank, (unsigned int)scale);
#else
	return 0;
#endif
}

// Moved these - wrapper methods for JGame
void GameEngineWrapper::bob(int a, double b, double c)
{
	bob(a, b, c, ibob(a));
}

void GameEngineWrapper::bob(int a, double b, double c, int d)
{
	int imagenum = d;
#ifdef USESDL
	// Bump vector:
	if (((int)mainbob.size()) < (a + 1))
	{
		unsigned int bump = 1 + a - mainbob.size();
		for (unsigned int n=0; n<bump; n++) mainbob.push_back(NULL);
	}

	// Check for flipping:
	int bobhflip = d & 0x8000;
	int bobvflip = d & 0x4000;
	d -= bobhflip;
	d -= bobvflip;
	
	string flipstr = "";
	if ((bobhflip>0) && (bobvflip>0))
		flipstr = "_hv";
	else if (bobhflip>0)
		flipstr = "_h";
	else if (bobvflip>0)
		flipstr = "_v";

	string myimage;

	if (d < (int)AM->currentspriteimages.size())
		myimage = AM->currentspriteimages[d]+flipstr;
	else
		myimage = "";

	int xhandle=0;
	int yhandle=0;
	if ((int)AM->ImageHotSpotX.size() > d)
		xhandle=AM->ImageHotSpotX[d];
	if ((int)AM->ImageHotSpotY.size() > d)
		yhandle=AM->ImageHotSpotY[d];

	if (mainbob[a] == NULL)
	{
		mainbob[a] = new AMOS_Sprite(AM->xHard(AM->currentScreen, (int)b - xhandle),
					     AM->yHard(AM->currentScreen, (int)c - yhandle),
					     myimage);
	}
	else
	{
		mainbob[a]->x = AM->xHard(AM->currentScreen, (int)b - xhandle);
		mainbob[a]->y = AM->yHard(AM->currentScreen, (int)c - yhandle);
	}

	if (mainbob[a] == NULL)
		return;

	mainbob[a]->imagenumber = imagenum;
#endif

	AM->BobX[a] = (int)b;
	AM->BobY[a] = (int)c;
	AM->BobImage[a] = imagenum;

	// Do flip - moved (old) ...
}

void GameEngineWrapper::sprite(int a, double b, double c)
{
	sprite(a, b, c, isprite(a));
}

void GameEngineWrapper::sprite(int a, double b, double c, int d)
{
	// Complete this method:
#ifdef USESDL
	int imagenum = d;
#endif

#ifdef USESDL
	// Bump vector:
	if (((int)mainsprite.size()) < (a + 1))
	{
		unsigned int bump = 1 + a - mainsprite.size();
		for (unsigned int n=0; n<bump; n++) mainsprite.push_back(NULL);
	}

	// Check for flipping:
	int spritehflip = d & 0x8000;
	int spritevflip = d & 0x4000;
	d -= spritehflip;
	d -= spritevflip;
	
	string flipstr = "";
	if ((spritehflip>0) && (spritevflip>0))
		flipstr = "_hv";
	else if (spritehflip>0)
		flipstr = "_h";
	else if (spritevflip>0)
		flipstr = "_v";

	string myimage;

	//cout << "DEBUG - sprite(" << AM->stri(a) << ", ... , ... , " << AM->stri(d) << ")" << endl;
	//cout << "DEBUG: AM->currentspriteimages: " << AM->stri(AM->currentspriteimages.size()) << endl;

	if (d < (int)AM->currentspriteimages.size())
		myimage = AM->currentspriteimages[d]+flipstr;
	else
		myimage = "";

	//cout << "DEBUG2 - sprite(" << AM->stri(a) << ", ... , ... , " << AM->stri(d) << ")" << endl;

	int xhandle=0;
	int yhandle=0;
	if ((int)AM->ImageHotSpotX.size() > d)
		xhandle=AM->ImageHotSpotX[d];
	if ((int)AM->ImageHotSpotY.size() > d)
		yhandle=AM->ImageHotSpotY[d];

	if (mainsprite[a] == NULL)
	{
		mainsprite[a] = new AMOS_Sprite((int)b - xhandle, (int)c - yhandle, myimage);
	}
	else
	{
		mainsprite[a]->x = (int)b - xhandle;
		mainsprite[a]->y = (int)c - yhandle;
	}

	if (mainsprite[a] == NULL)
		return;

	mainsprite[a]->imagenumber = imagenum;
#endif

	AM->SpriteX[a] = (int)b;
	AM->SpriteY[a] = (int)c;
	AM->SpriteImage[a] = imagenum;

	// Do flip - moved (old) ...
}



// DO THESE WORK?
double GameEngineWrapper::xbob(int a)
{
#ifdef USE_SDL
	if ((int)mainbob.size()<a)
		return 0;
	else if (mainbob[a] == NULL)
		return 0;
#endif
	return AM->BobX[a];
}
double GameEngineWrapper::ybob(int a)
{
#ifdef USE_SDL
	if ((int)mainbob.size()<a)
		return 0;
	else if (mainbob[a] == NULL)
		return 0;
#endif
	return AM->BobY[a];
}
int GameEngineWrapper::ibob(int a)
{
#ifdef USE_SDL
	if ((int)mainbob.size()<a)
		return 0;
	else if (mainbob[a] == NULL)
		return 0;
#endif
	return AM->BobImage[a];
}
double GameEngineWrapper::xsprite(int a)
{
#ifdef USESDL
	if ((int)mainsprite.size()<a)
		return 0;
	else if (mainsprite[a] == NULL)
		return 0;
#endif
	return AM->SpriteX[a];

}
double GameEngineWrapper::ysprite(int a)
{
#ifdef USESDL
	if ((int)mainsprite.size()<a)
		return 0;
	else if (mainsprite[a] == NULL)
		return 0;
#endif
	return AM->SpriteY[a];
}
int GameEngineWrapper::isprite(int a)
{
#ifdef USESDL
	if ((int)mainsprite.size()<a)
		return 0;
	else if (mainsprite[a] == NULL)
		return 0;
#endif
	return AM->SpriteImage[a];
}


// Collision detection:
int GameEngineWrapper::bobCol(unsigned int t1)
{
	// Simple collision test, 1 argument

	// Bounds checking:
	if (t1 >= mainbob.size())
		return 0;

	if (mainbob[t1] == NULL)
		return 0;

	int test = 0;
	for (unsigned int n=0; n<mainbob.size() && test==0; n++)
		if ((mainbob[n] != NULL) && (n != t1))
			test=SDL_CollidePixel(images[mainbob[t1]->imagename], mainbob[t1]->x, mainbob[t1]->y,
				images[mainbob[n]->imagename], mainbob[n]->x, mainbob[n]->y);

	AM->Coltype = 0;

	// Simple collision test, 1 argument
	if (test)
	{
		AM->Bobteststart=0; AM->Bobtestend=0;
		AM->Bobtested=t1; AM->Bobcolled=true;
		return -1;
	}
	else
	{
		AM->Bobcolled=0;
		return 0;
	}

	return 0;
}
int GameEngineWrapper::bobCol(unsigned int t1, unsigned int t2, unsigned int t3)
{
	// Bounds checking:
	if (t1 >= mainbob.size())
		return 0;
	if (t3 >= mainbob.size())
		t3 = mainbob.size() - 1;

	if (mainbob[t1] == NULL)
		return 0;

	// Complex collision test, 3 arguments..
	int t5=false; // t5 is the result.

	// Check if bobs t2 -> t3 are colliding with bob t1:
	for (unsigned int t4=t2; t4<=t3 && t5==false; t4++)
	{
		// TODO - bounds checking:
		if ((mainbob[t4] != NULL) && (t1 != t4))
			t5=SDL_CollidePixel(images[mainbob[t1]->imagename], mainbob[t1]->x, mainbob[t1]->y,
				images[mainbob[t4]->imagename], mainbob[t4]->x, mainbob[t4]->y);
	}

	AM->Coltype = 0;
	AM->Bobteststart=t2; AM->Bobtestend=t3;
	AM->Bobtested=t1; AM->Bobcolled=t5;

	return t5 ? -1 : 0;
}
int GameEngineWrapper::spriteCol(unsigned int t1)
{
	// Simple collision test, 1 argument
	// Bounds checking:
	if (t1 >= mainsprite.size())
		return 0;

	if (mainsprite[t1] == NULL)
		return 0;

	int test = 0;
	for (unsigned int n=0; n<mainsprite.size() && test==0; n++)
		if ((mainsprite[n] != NULL) && (n != t1))
			test=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
				images[mainsprite[n]->imagename], mainsprite[n]->x, mainsprite[n]->y);

	AM->Coltype = 1;

	// Simple collision test, 1 argument
	if (test)
	{
		AM->Bobteststart=0; AM->Bobtestend=0;
		AM->Bobtested=t1; AM->Bobcolled=true;
		return -1;
	}
	else
	{
		AM->Bobcolled=false;
		return 0;
	}

	return 0;
}
int GameEngineWrapper::spriteCol(unsigned int t1, unsigned int t2, unsigned int t3)
{
	// Bounds checking:
	if (t1 >= mainsprite.size())
		return 0;
	if (t3 >= mainsprite.size())
		t3 = mainsprite.size() - 1;

	if (mainsprite[t1] == NULL)
		return 0;

	// Complex collision test, 3 arguments..
	int t5=false; // t5 is the result.

	// Check if bobs t2 -> t3 are colliding with bob t1:
	for (unsigned int t4=t2; t4<=t3 && t5==false; t4++)
	{
		// TODO - bounds checking:
		if ((mainsprite[t4] != NULL) && (t1 != t4))
			t5=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
				images[mainsprite[t4]->imagename], mainsprite[t4]->x, mainsprite[t4]->y);
	}

	AM->Coltype = 1;
	AM->Bobteststart=t2; AM->Bobtestend=t3;
	AM->Bobtested=t1; AM->Bobcolled=t5;

	return t5 ? -1 : 0;
}
int GameEngineWrapper::spriteBobCol(unsigned int t1)
{
	// Simple collision test, 1 argument

	// Bounds checking:
	if (t1 >= mainsprite.size())
		return 0;

	if (mainsprite[t1] == NULL)
		return 0;

	int test = 0;
	for (unsigned int n=0; n<mainbob.size() && test==0; n++)
		if ((mainbob[n] != NULL) && (n != t1))
			test=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
				images[mainbob[n]->imagename], AM->xHard(mainbob[n]->x), AM->yHard(mainbob[n]->y));

	AM->Coltype = 2;

	// Simple collision test, 1 argument
	if (test)
	{
		AM->Bobteststart=0; AM->Bobtestend=0;
		AM->Bobtested=t1; AM->Bobcolled=true;
		return -1;
	}
	else
	{
		AM->Bobcolled=0;
		return 0;
	}

	return 0;
}
int GameEngineWrapper::spriteBobCol(unsigned int t1, unsigned int t2, unsigned int t3)
{
	// Bounds checking:
	if (t1 >= mainsprite.size())
		return 0;
	if (t3 >= mainsprite.size())
		t3 = mainsprite.size() - 1;

	if (mainsprite[t1] == NULL)
		return 0;

	// Complex collision test, 3 arguments..
	int t5=0; // t5 is the result.

	// Check if bobs t2 -> t3 are colliding with bob t1:
	for (unsigned int t4=t2; t4<=t3 && t5==false; t4++)
	{
		// TODO - bounds checking:
		if ((mainbob[t4] != NULL) && (t1 != t4))
			t5=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
				images[mainbob[t4]->imagename], AM->xHard(mainbob[t4]->x), AM->yHard(mainbob[t4]->y));
	}

	AM->Coltype = 2;
	AM->Bobteststart=t2; AM->Bobtestend=t3;
	AM->Bobtested=t1; AM->Bobcolled=t5;

	return t5 ? -1 : 0;
}
int GameEngineWrapper::bobSpriteCol(unsigned int t1)
{
	// Simple collision test, 1 argument

	// Bounds checking:
	if (t1 >= mainbob.size())
		return 0;

	if (mainbob[t1] == NULL)
		return 0;

	int test = 0;
	for (unsigned int n=0; n<mainsprite.size() && test==0; n++)
		if ((mainsprite[n] != NULL) && (n != t1))
			test=SDL_CollidePixel(images[mainbob[t1]->imagename], AM->xHard(mainbob[t1]->x), AM->yHard(mainbob[t1]->y),
				images[mainsprite[n]->imagename], mainsprite[n]->x, mainsprite[n]->y);

	AM->Coltype = 3;

	// Simple collision test, 1 argument
	if (test)
	{
		AM->Bobteststart=0; AM->Bobtestend=0;
		AM->Bobtested=t1; AM->Bobcolled=true;
		return -1;
	}
	else
	{
		AM->Bobcolled=false;
		return 0;
	}

	return 0;
}
int GameEngineWrapper::bobSpriteCol(unsigned int t1, unsigned int t2, unsigned int t3)
{
	// Bounds checking:
	if (t1 >= mainbob.size())
		return false;
	if (t3 >= mainbob.size())
		t3 = mainbob.size() - 1;

	if (mainbob[t1] == NULL)
		return false;

	// Complex collision test, 3 arguments..
	int t5=false; // t5 is the result.

	// Check if bobs t2 -> t3 are colliding with bob t1:
	for (unsigned int t4=t2; t4<=t3 && t5==false; t4++)
	{
		// TODO - bounds checking:
		if ((mainsprite[t4] != NULL) && (t1 != t4))
			t5=SDL_CollidePixel(images[mainbob[t1]->imagename], AM->xHard(mainbob[t1]->x), AM->yHard(mainbob[t1]->y),
				images[mainsprite[t4]->imagename], mainsprite[t4]->x, mainsprite[t4]->y);
	}

	AM->Coltype = 3;
	AM->Bobteststart=t2; AM->Bobtestend=t3;
	AM->Bobtested=t1; AM->Bobcolled=t5;

	return t5 ? -1 : 0;
}

int GameEngineWrapper::col(int t1)
{
	// If no collision last tested:
	if (AM->Bobcolled == false)
		return 0;

	// Bounds checking:
	unsigned int testsize;
	if ((AM->Coltype == 0) || (AM->Coltype == 3))
	{
		testsize = mainbob.size();
		if (t1 >= (int)testsize)
			return 0;
	}
	else
	{
		testsize = mainsprite.size();
		if (t1 >= (int)testsize)
			return 0;
	}

	if (t1==-1)
	{
		// Simple mode, return first colliding bob/sprite from last collision,
		// in the range last specified.
		// Find the bob index number for this:

		int test = -1;
		for (unsigned int n=0; (n < testsize) && (test == -1); n++)
		{
			switch (AM->Coltype)
			{
			case 0:
				// After Bob Col:
				if ((mainbob[n] != NULL) && (n != AM->Bobtested))
				{
					test=SDL_CollidePixel(images[mainbob[n]->imagename], mainbob[n]->x, mainbob[n]->y,
						images[mainbob[AM->Bobtested]->imagename], mainbob[AM->Bobtested]->x, mainbob[AM->Bobtested]->y) ? n : -1;

					// Is this in the range specified? If so, make it returned:
					if (test>=(int)AM->Bobteststart && test<=(int)AM->Bobtestend)
						return test;
				}
				break;
			case 1:
				// After Sprite Col:
				if ((mainsprite[n] != NULL) && (n != AM->Bobtested))
				{
					test=SDL_CollidePixel(images[mainsprite[n]->imagename], mainsprite[n]->x, mainsprite[n]->y,
						images[mainsprite[AM->Bobtested]->imagename], mainsprite[AM->Bobtested]->x, mainsprite[AM->Bobtested]->y) ? n : -1;

					// Is this in the range specified? If so, make it returned:
					if (test>=(int)AM->Bobteststart && test<=(int)AM->Bobtestend)
						return test;
				}
				break;
			case 2:
				// After Spritebob Col:
				if ((mainbob[n] != NULL) && (n != AM->Bobtested))
				{
					test=SDL_CollidePixel(images[mainbob[n]->imagename], mainbob[n]->x, mainbob[n]->y,
						images[mainsprite[AM->Bobtested]->imagename], mainsprite[AM->Bobtested]->x, mainsprite[AM->Bobtested]->y) ? n : -1;

					// Is this in the range specified? If so, make it returned:
					if (test>=(int)AM->Bobteststart && test<=(int)AM->Bobtestend)
						return test;
				}
				break;
			case 3:
				// After Bobsprite Col:
				if ((mainsprite[n] != NULL) && (n != AM->Bobtested))
				{
					test=SDL_CollidePixel(images[mainsprite[n]->imagename], mainsprite[n]->x, mainsprite[n]->y,
						images[mainbob[AM->Bobtested]->imagename], mainbob[AM->Bobtested]->x, mainbob[AM->Bobtested]->y) ? n : -1;

					// Is this in the range specified? If so, make it returned:
					if (test>=(int)AM->Bobteststart && test<=(int)AM->Bobtestend)
						return test;
				}
				break;
			}
		}

		if (test == -1)
			return 0;

		return test;
	}
	else
	{
		// Advanced mode, test if Bob/Sprite t1 involved in last collision,
		// and if Bob t1 is in the range last specified.
		if ((AM->Coltype == 0) || (AM->Coltype == 3))
		{
			if ((mainbob[t1] == NULL) || (t1 == (int)AM->Bobtested))
				return 0;
		}
		else
		{
			if ((mainsprite[t1] == NULL) || (t1 == (int)AM->Bobtested))
				return 0;
		}

		if (AM->Bobtestend==0 || ((t1>=(int)AM->Bobteststart) && (t1<=(int)AM->Bobtestend)))
		{
			int test = 0;
			switch (AM->Coltype)
			{
			case 0:
				// After Bob Col:
				test=SDL_CollidePixel(images[mainbob[t1]->imagename], mainbob[t1]->x, mainbob[t1]->y,
					images[mainbob[AM->Bobtested]->imagename], mainbob[AM->Bobtested]->x, mainbob[AM->Bobtested]->y);
				break;
			case 1:
				// After Sprite Col:
				test=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
					images[mainsprite[AM->Bobtested]->imagename], mainsprite[AM->Bobtested]->x, mainsprite[AM->Bobtested]->y);
				break;
			case 2:
				// After Spritebob Col:
				test=SDL_CollidePixel(images[mainbob[t1]->imagename], mainbob[t1]->x, mainbob[t1]->y,
					images[mainsprite[AM->Bobtested]->imagename], mainsprite[AM->Bobtested]->x, mainsprite[AM->Bobtested]->y);
				break;
			case 3:
				// After Bobsprite Col:
				test=SDL_CollidePixel(images[mainsprite[t1]->imagename], mainsprite[t1]->x, mainsprite[t1]->y,
					images[mainbob[AM->Bobtested]->imagename], mainbob[AM->Bobtested]->x, mainbob[AM->Bobtested]->y);
				break;
			}
			return test ? -1 : 0;
		}
		else
		{
			// Bob specified is out of range..
			return 0;
		}
	}
}


// Input methods:
int GameEngineWrapper::joy(int a)
{
	int out = 0;
	if (keyup)
		out |= 1;
	if (keydown)
		out |= 2;
	if (keyleft)
		out |= 4;
	if (keyright)
		out |= 8;
	if (keylshift || keyrshift || keylctrl || keyrctrl)
		out |= 16;

	return out;
}

int GameEngineWrapper::xmouse()
{
	return mousex;
}

int GameEngineWrapper::ymouse()
{
	return mousey;
}

// To do:
int GameEngineWrapper::mousekey(int t1)
{
	switch (t1)
	{
		case -1: return lmouse | rmouse | mmouse; break;
		case 0:  return lmouse; break;
		case 1:  return rmouse; break;
		case 2:  return mmouse; break;
		default: break;
	}

	return 0;	
}



void GameEngineWrapper::initspritesandbobs()
{
	// CPP - mainsprite and mainbob are already initialised as empty vectors!
}

// Added:
void GameEngineWrapper::initScreen()
{
#ifdef USESDL
	// TODO - added for old default screen:
	AM->screenOpen(0, 720, 576, 16777216, 0x8004);
	AM->loadIff("resources/back.jpg", 0);
#endif
}

void GameEngineWrapper::boboff(int a)
{
#ifdef USESDL
	if ((int)mainbob.size() > a)
		if (mainbob[a] != NULL)
			AM->bob(a, -100, -100, 1); // kludge!
#endif
}

void GameEngineWrapper::boboff()
{
#ifdef USESDL
	for (unsigned int a=0; a<mainbob.size(); a++)
		boboff(a);
#endif
}

void GameEngineWrapper::spriteoff(int a)
{
#ifdef USESDL
	if ((int)mainsprite.size() > a)
		if (mainsprite[a] != NULL)
			AM->sprite(a, -100, -100, 1); // kludge!
#endif
}

void GameEngineWrapper::spriteoff()
{
#ifdef USESDL
	for (unsigned int a=0; a<mainsprite.size(); a++)
		spriteoff(a);
#endif
}



// To improve:
void GameEngineWrapper::animatesprites()
{
#ifdef USESDL
	for (unsigned int pp=0; pp<mainsprite.size(); pp++) if (mainsprite[pp] != NULL)
	{
		int spriteimagenumber = AM->iSprite(pp);

		int spritehflip = spriteimagenumber & 0x8000;
		int spritevflip = spriteimagenumber & 0x4000;
		spriteimagenumber -= spritehflip;
		spriteimagenumber -= spritevflip;

		// First do sprites:
		if ((mainsprite[pp] == NULL) || !(spriteimagenumber >= 0 && spriteimagenumber < (int)AM->currentspriteimages.size())) 
			;
		else if ((spritehflip == 0) && (spritevflip == 0))
			mainsprite[pp]->setImage(AM->currentspriteimages[spriteimagenumber]);
		else if ((spritehflip != 0) && (spritevflip == 0))
			mainsprite[pp]->setImage(AM->currentspriteimages[spriteimagenumber]+"_h");
		else if ((spritehflip == 0) && (spritevflip != 0))
			mainsprite[pp]->setImage(AM->currentspriteimages[spriteimagenumber]+"_v");
		else if ((spritehflip != 0) && (spritevflip != 0))
			mainsprite[pp]->setImage(AM->currentspriteimages[spriteimagenumber]+"_hv");
	}
#endif
}

void GameEngineWrapper::animatebobs()
{
#ifdef USESDL
	for (unsigned int pp=0; pp<mainbob.size(); pp++) if (mainbob[pp] != NULL)
	{
		int bobimagenumber = AM->iBob(pp);

		int bobhflip = bobimagenumber & 0x8000;
		int bobvflip = bobimagenumber & 0x4000;
		bobimagenumber -= bobhflip;
		bobimagenumber -= bobvflip;

		// Now do bobs:
		if ((mainbob[pp] == NULL) || !(bobimagenumber >= 0 && bobimagenumber < (int)AM->currentspriteimages.size())) 
			;
		else if ((bobhflip == 0) && (bobvflip == 0))
			mainbob[pp]->setImage(AM->currentspriteimages[bobimagenumber]);
		else if ((bobhflip != 0) && (bobvflip == 0))
			mainbob[pp]->setImage(AM->currentspriteimages[bobimagenumber]+"_h");
		else if ((bobhflip == 0) && (bobvflip != 0))
			mainbob[pp]->setImage(AM->currentspriteimages[bobimagenumber]+"_v");
		else if ((bobhflip != 0) && (bobvflip != 0))
			mainbob[pp]->setImage(AM->currentspriteimages[bobimagenumber]+"_hv");
	}
#endif
}

// Load an SDL Mixer sound:
#ifdef USESDL
/*
Mix_Chunk* GameEngineWrapper::load_sound(std::string filename, std::string name)
{
	// First check our hash table for the sound, if present, and return it if found:

	//unordered_map<std::string, Mix_Chunk*>::const_iterator got = sounds.find(name);
	if (sounds.find(name) != sounds.end())
		return sounds[name];

	// The sound sample that's loaded:
	Mix_Chunk* loadedSound = NULL;

	// Load the sound:
	loadedSound = Mix_LoadWAV(filename.c_str());

	// Add the sound sample to the hash table:
	sounds.insert(make_pair<string, Mix_Chunk*>(name, loadedSound));

	// Return the sound sample:
	return loadedSound;
}
*/
#endif

// Moved - load an SDL image:
#ifdef USESDL
SDL_Surface* GameEngineWrapper::load_image(std::string filename)
{
	// First check our hash table for the image, if present:
	if (images.find(filename) != images.end())
		return images[filename];

	// The image that's loaded:
	SDL_Surface* loadedImage = NULL;

	// The optimised surface that will be used:
	SDL_Surface* optimisedImage = NULL;

	// Load the image:
	loadedImage = IMG_Load( filename.c_str() );

	// If the image loaded:
	if( loadedImage != NULL )
	{
		// Create an optimised surface:
		optimisedImage = SDL_DisplayFormat( loadedImage );

		// Free the old surface:
		SDL_FreeSurface( loadedImage );

		// If the surface was optimised:
		if( optimisedImage != NULL )
		{
			// Colour key surface (removed):
			//SDL_SetColorKey( optimisedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimisedImage->format, 0, 0x000, 0x000 ) );
		}
	}

	// Add the optimised image to the hash table:
	images.insert(make_pair<string, SDL_Surface*>(filename, optimisedImage));

	// Return the optimised surface:
	return optimisedImage;
}
#endif

// Added - AMOS sounds:
void GameEngineWrapper::bell()
{
#ifdef USESDL
	// Play the sound effect:
	Mix_PlayChannel(-1, bellsound, 0);
#endif
}
void GameEngineWrapper::boom()
{
#ifdef USESDL
	// Play the sound effect:
	Mix_PlayChannel(-1, boomsound, 0);
#endif
}
void GameEngineWrapper::shoot()
{
#ifdef USESDL
	// Play the sound effect:
	Mix_PlayChannel(-1, shootsound, 0);
#endif
}


// Added - more AMOS Screen instructions:
void GameEngineWrapper::screenSize(int a, int b, int c)
{
	//cout << "Debug: Doing screenSize: w=" << AM->stri(b) << ", h=" << AM->stri(c) << endl;
	AM->ScreenDisplayWidth[a] = b;
	AM->ScreenDisplayHeight[a] = c;

	// Resize and update the screen background image here:
	// TODO: C++!
	//if (jAMOS.mainsprite1.getImageName().equals(a));
	//	ma.defineImage(mainsprite1.getImageName(), "", 0, mainsprite1.getImageName(), "img_op", 0, 0, b, c);
    
    	// Re-display the screen (TO DO:)
        screenDisplay(a, AM->ScreenDisplayX[a], AM->ScreenDisplayY[a]);
}

void GameEngineWrapper::screenDisplay(int a, int b, int c)
{
	// Reposition the screen (TO DO - just one image now):
	AM->ScreenDisplayX[a]=b;
	AM->ScreenDisplayY[a]=c;

	// Set the appropriate screen number here (TO DO)

#ifdef USESDL
	//mainsprite1->setPos(AM->ScreenDisplayX[a] - AM->ScreenOffsetX[a], AM->ScreenDisplayY[a] - AM->ScreenOffsetY[a]);
	screenx[a] = AM->ScreenDisplayX[a] - AM->ScreenOffsetX[a];
	screeny[a] = AM->ScreenDisplayY[a] - AM->ScreenOffsetY[a];

	// TODO: Multiple screen support:
	// Now move all bobs of that screen accordingly:
	for (unsigned int pp=0; pp<mainbob.size(); pp++)
		// Optimise - search up to highest allocated bob number (TO DO)
		if ((mainbob[pp]) != NULL)
			// Later ensure these are moved with the appropriate screen:
			bob(pp, xbob(pp), ybob(pp), ibob(pp));
#endif
}


#ifdef USESDL
// Thanks to lazyfoo for these methods, used below:
Uint32 GameEngineWrapper::get_pixel32(SDL_Surface *surface, int x, int y)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}
void GameEngineWrapper::put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}
SDL_Surface* GameEngineWrapper::flip_surface(SDL_Surface *surface, int flags)
{
    // Flip flags:
    const int FLIP_VERTICAL = 1;
    const int FLIP_HORIZONTAL = 2;

    // Pointer to the soon to be flipped surface:
    SDL_Surface *flipped = NULL;

    Uint32 newflags;
    //if (useopengl)
    //    newflags = SDL_HWSURFACE;
    //else
    newflags = SDL_SWSURFACE;

    // If the image is color keyed:
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        flipped = SDL_CreateRGBSurface( newflags, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    // Otherwise:
    else
    {
        flipped = SDL_CreateRGBSurface( newflags, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    // If the surface must be locked:
    if( SDL_MUSTLOCK( surface ) )
    {
        // Lock the surface:
        SDL_LockSurface( surface );
    }

    // Go through columns:
    for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
    {
        // Go through rows:
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
            // Get pixel:
            Uint32 pixel = get_pixel32( surface, x, y );

            // Copy pixel:
            if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
            {
                put_pixel32( flipped, rx, ry, pixel );
            }
            else if( flags & FLIP_HORIZONTAL )
            {
                put_pixel32( flipped, rx, y, pixel );
            }
            else if( flags & FLIP_VERTICAL )
            {
                put_pixel32( flipped, x, ry, pixel );
            }
        }
    }

    // Unlock surface:
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

    // Copy color key:
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }

    // Return flipped surface:
    return flipped;
}
#endif


// Banks:
// Load a bank (folder of sprites for now)
// TO DO - faux packed pictures (with unpack).
void GameEngineWrapper::load(string a, int b)
{
	load(a, b, 1); // Added: scale=1
}
void GameEngineWrapper::load(string a, int b, int scale)
{
#ifdef USESDL
	int numsp=0;
	//cout << "Loading bank file \"" << a << "\" to bank " << AM->stri(b) << endl;

	// First check if b == 1 (sprite bank)
	if ((b == 1) || (b == 2))
	{
		// Need to initialise both:
		//AM->currentspriteimages = new vector<string>(); // Already initialised in C++
		if (b == 1)
			AM->currentspriteimages.clear(); // Added for C++
		else if (b == 2)
			AM->currenticonimages.clear(); // Added for C++

		// Added - load ABK file if appropriate:
		if (a.length() > 4)
		{
			if (AM->lower(a.substr(a.length()-4, 4)) == ".abk")
			{
				loadamosabk(a, b, scale);
				// For OpenGL (fix this for scaled ABK sprites):
				spritebanktotextures();
				return;
			}
		}

		// Load and label sprites from a folder.
		// Supports multiple extensions.
		bool filefound = false;
		do
		{
			string path = "";
			unsigned int ext;
			vector<string> extension;
			extension.push_back(".png"); extension.push_back(".gif"); extension.push_back(".jpg");

			filefound = 0; // FALSE;
			// Check each extension in turn:
			for (ext=0; (ext < extension.size()) && (filefound==false); ext++)
			{
				// Load the image if it hasn't been loaded already:

				bool notalreadyloaded = true;

				// Here check if already loaded for each extension type:
				if (b == 1)
					path = a + "/" + AM->stri(AM->currentspriteimages.size()) + extension[ext];
				else if (b == 2)
					path = a + "/" + AM->stri(AM->currenticonimages.size()) + extension[ext];

				// Now test if the file has already been loaded to the buffer:
				//cout << "Debug: Trying to load sprite image #" << stri(numsp) << " from file \"" << path << "\"" << endl;

				//if (AM->loadedspriteimages.size() > 0)
				//{
				//	for (unsigned int ind=0; ind<AM->loadedspriteimages.size(); ind++)
				//	{
				//		if (AM->loadedspriteimages[ind] == path)
				//		{
				//			alreadyloaded = true;
				//			//cout << "Success! Already loaded image identified!" << endl;
				//			break;
				//			// "path" is now the image identifier!
				//		}
				//	}
				//}

				notalreadyloaded = (images.find(a) == images.end());

				// Load the sprite image from the file if not already loaded,
				// then add the path to the loaded images string vector:
				bool loaded = false;
				if (notalreadyloaded)
				{
					path = a + "/"  + AM->stri(numsp) + extension[ext]; // AM->currentspriteimages[]
					//cout << "Debug: Need to load sprite image \"" << path <<  "\" from disk." << endl;

					loaded = load_image(path) != NULL;
					if (loaded)
					{
						//AM->loadedspriteimages.push_back(path);

						// Create duplicates of the above image for flipping:
						SDL_Surface* flip = NULL;

						Uint32 flags;
						//if (useopengl)
						//	flags = SDL_HWSURFACE;
						//else
						flags = SDL_SWSURFACE;

						flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
						if (flip != NULL)
						{
							flip = flip_surface(images[path], 2); // FLIP_HORIZONTAL
							images.insert(make_pair<string, SDL_Surface*>(path+"_h", flip));
						}
						flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
						if (flip != NULL)
						{
							flip = flip_surface(images[path], 1); // FLIP_VERTICAL
							images.insert(make_pair<string, SDL_Surface*>(path+"_v", flip));
						}
						flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
						if (flip != NULL)
						{
							flip = flip_surface(images[path], 3); // FLIP_HORIZONTAL | FLIP_VERTICAL
							images.insert(make_pair<string, SDL_Surface*>(path+"_hv", flip));
						}
					}
				}

				// Need to initialise both:
				if (loaded || !notalreadyloaded)
				{
					if (b == 1)
						AM->currentspriteimages.push_back(path);
					else if (b == 2)
						AM->currenticonimages.push_back(path);

					// Increment the number of sprite images;
					numsp++;

					filefound = 1; //TRUE;
					//cout << "Sprite successfully loaded!" << endl;
				}

				//} catch (Error e) { // optimise this (TO DO) - what type of error is thrown?
				//	cout << "Caught Error!" << endl;
				//}
			}
			//if (filefound)
			//	cout << "Going round the do while loop once more..." << endl;
		}
		while(filefound);

		//cout << "Total number of sprite images loaded: " << AM->stri(numsp) << endl;
	}

	// For OpenGL (fix this for scaled ABK sprites):
	spritebanktotextures();

	// Removed - for ABK loading - TO DO:
	//try { loadabk(a); } catch (IOException e) { }
#endif
}

// TODO:
void GameEngineWrapper::erase(int a)
{
}


// Added - drawing methods:
int GameEngineWrapper::pastebob(int x, int y, int a)
{
#ifdef USESDL
	int bobhflip = a & 0x8000;
	int bobvflip = a & 0x4000;
	a -= bobhflip;
	a -= bobvflip;
	
	string flipstr = "";
	if ((bobhflip>0) && (bobvflip>0))
		flipstr = "_hv";
	else if (bobhflip>0)
		flipstr = "_h";
	else if (bobvflip>0)
		flipstr = "_v";

	int xhandle=0;
	int yhandle=0;
	if ((int)AM->ImageHotSpotX.size() > a)
		xhandle=AM->ImageHotSpotX[a];
	if ((int)AM->ImageHotSpotY.size() > a)
		yhandle=AM->ImageHotSpotY[a];

	// Paste the bob here:
	SDL_Rect offset;
	offset.x = x - xhandle;
	offset.y = y - yhandle;

	SDL_BlitSurface(images[AM->currentspriteimages[a]+flipstr], NULL, screens[AM->currentScreen], &offset);

	// Added for OpenGL:
	if (useopengl)
		screens_modified[AM->currentScreen]=true;
#endif
	return 0;
}

int GameEngineWrapper::pasteicon(int x, int y, int a)
{
#ifdef USESDL
	int bobhflip = a & 0x8000;
	int bobvflip = a & 0x4000;
	a -= bobhflip;
	a -= bobvflip;
	
	string flipstr = "";
	if ((bobhflip>0) && (bobvflip>0))
		flipstr = "_hv";
	else if (bobhflip>0)
		flipstr = "_h";
	else if (bobvflip>0)
		flipstr = "_v";

	//int xhandle=0;
	//int yhandle=0;
	//if ((int)AM->ImageHotSpotX.size() > a)
	//	xhandle=AM->ImageHotSpotX[a];
	//if ((int)AM->ImageHotSpotY.size() > a)
	//	yhandle=AM->ImageHotSpotY[a];

	// Paste the icon here:
	SDL_Rect offset;
	offset.x = x; // - xhandle;
	offset.y = y; // - yhandle;

	SDL_BlitSurface(images[AM->currenticonimages[a]+flipstr], NULL, screens[AM->currentScreen], &offset);

	// Added for OpenGL:
	if (useopengl)
		screens_modified[AM->currentScreen]=true;
#endif
	return 0;
}

// Updated Plot routines:
int GameEngineWrapper::plot(int x, int y, int a)
{
#ifdef USESDL
	// Plot here:
	Uint32 colour = (Uint32)a;

	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;

	return pixelRGBA(screens[AM->currentScreen], (Sint16)x, (Sint16)y, r, g, b, 255);
#else
	return 0;
#endif
}
int GameEngineWrapper::plot(int x, int y)
{
#ifdef USESDL
	// Plot here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;

	return pixelRGBA(screens[AM->currentScreen], (Sint16)x, (Sint16)y, r, g, b, 255);
#else
	return 0;
#endif
}

// Old Plot routines (may be a bit faster on some platforms) - removed due to various issues:
/*
int GameEngineWrapper::plot(int x, int y, int a)
{
#ifdef USESDL
	// Plot here:
	Uint32 colour = (Uint32)a;

	//ink(a); draw(x,y,x,y); // debug

	Uint32 *bufp;
	bufp = (Uint32*)screens[AM->currentScreen]->pixels + y*screens[AM->currentScreen]->pitch/4 + x;
	*bufp = colour;
	SDL_UpdateRect(screens[AM->currentScreen], x, y, 1, 1);

	if (useopengl)
		screens_modified[AM->currentScreen]=true;

#endif
	return 0;
}
int GameEngineWrapper::plot(int x, int y)
{
#ifdef USESDL
	// Plot here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint32 *bufp;
	bufp = (Uint32*)screens[AM->currentScreen]->pixels + y*screens[AM->currentScreen]->pitch/4 + x;
	*bufp = colour;
	SDL_UpdateRect(screens[AM->currentScreen], x, y, 1, 1);

	if (useopengl)
		screens_modified[AM->currentScreen]=true;
#endif
	return 0;
}
*/

// Added: =Text Length(string):
int GameEngineWrapper::textlength(string textstring)
{
#ifdef USESDL
	int width=0;

	SDL_Color textColor = {255, 255, 255};
	SDL_Color paperColor = {0, 0, 0};
	SDL_Surface *message = NULL;
	message = TTF_RenderText_Shaded(font, textstring.c_str(), textColor, paperColor);

	// If there was an error in rendering the text:
	if (message == NULL)
	{
		cout << "ERROR rendering text to get length!" << endl;
		return -1;
	}

	width = message->w;

	// Erase rendered text from memory here:
	SDL_FreeSurface(message);

	return width;
#else
	return 0;
#endif
}
// Added: Text:
int GameEngineWrapper::text(int x, int y, string textstring)
{
#ifdef USESDL
	// Draw text here:

	// Get the text colour:
	Uint32 color = (Uint32)AM->_ink;
	//Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((color & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((color & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((color & (Uint32)0x000000ff));
	SDL_Color textColor = {r, g, b};

	// Get the background colour (currently Paper):
	Uint32 papercolor = (Uint32)AM->_paper;
	//Uint8 ap = 255; //(Uint8) ((papercolour & (Uint32)0xff000000) >> 24);
	Uint8 rp = (Uint8) ((papercolor & (Uint32)0x00ff0000) >> 16);
	Uint8 gp = (Uint8) ((papercolor & (Uint32)0x0000ff00) >> 8);
	Uint8 bp = (Uint8) ((papercolor & (Uint32)0x000000ff));
	SDL_Color paperColor = {rp, gp, bp};

	//cout << "DEBUG: Attempting to render text: font=null == " << ((font == NULL) ? "true" : "false") << endl;

	SDL_Surface *message = NULL;
	//message = TTF_RenderText_Solid(font, textstring.c_str(), textColor);
	message = TTF_RenderText_Shaded(font, textstring.c_str(), textColor, paperColor);
	SDL_SetAlpha(message, 0, SDL_ALPHA_OPAQUE);

	// If there was an error in rendering the text:
	if (message == NULL)
	{
		cout << "ERROR rendering text!" << endl;
		return 1;
	}

	//cout << "DEBUG: Attempting to blit text to screen:" << endl;

	// Apply the rendered text to the screen:
	//apply_surface(x, y, message, screens[AM->currentScreen]);
	SDL_Rect offset;
	offset.x = x; offset.y = y;
	SDL_BlitSurface(message, NULL, screens[AM->currentScreen], &offset);

	// Erase rendered text from memory here:
	SDL_FreeSurface(message);

	// Added for OpenGL:
	if (useopengl)
		screens_modified[AM->currentScreen]=true;

	// Update the screen - is this needed?
	//if (SDL_Flip( screen ) == -1)
	//	return 1;    

#endif
	return 0;
}

int GameEngineWrapper::draw(int x1, int y1, int x2, int y2)
{
#ifdef USESDL
	// Draw line here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;
	
	return lineRGBA(screens[AM->currentScreen], x1, y1, x2, y2, r, g, b, a);
#else
	return 0;
#endif
}
int GameEngineWrapper::bar(int x1, int y1, int x2, int y2)
{
#ifdef USESDL
	// Draw AMOS bar here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;

	return boxRGBA(screens[AM->currentScreen], x1, y1, x2, y2, r, g, b, a);

#else
	return 0;
#endif
}
int GameEngineWrapper::box(int x1, int y1, int x2, int y2)
{
#ifdef USESDL
	// Draw AMOS box here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;
	
	return rectangleRGBA(screens[AM->currentScreen], x1, y1, x2, y2, r, g, b, a);
#else
	return 0;
#endif
}
int GameEngineWrapper::circle(int x1, int y1, int r1)
{
#ifdef USESDL
	// Draw circle here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;
	
	return ellipseRGBA(screens[AM->currentScreen], x1, y1, r1, r1, r, g, b, a);
#else
	return 0;
#endif
}
int GameEngineWrapper::ellipse(int x1, int y1, int r1, int r2)
{
#ifdef USESDL
	// Draw line here:
	Uint32 colour = (Uint32)AM->_ink;

	Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
	Uint8 r = (Uint8) ((colour & (Uint32)0x00ff0000) >> 16);
	Uint8 g = (Uint8) ((colour & (Uint32)0x0000ff00) >> 8);
	Uint8 b = (Uint8) ((colour & (Uint32)0x000000ff));

	if (useopengl)
		screens_modified[AM->currentScreen]=true;
	
	return ellipseRGBA(screens[AM->currentScreen], x1, y1, r1, r2, r, g, b, a);
#else
	return 0;
#endif
}


// Moved from XAMOS class:
// SDL methods:
#ifdef USESDL
void GameEngineWrapper::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	// Holds offsets:
	SDL_Rect offset;

	// Get offsets:
	offset.x = x;
	offset.y = y;

	// Blit:
	SDL_BlitSurface( source, clip, destination, &offset );
}
#endif

bool GameEngineWrapper::sdlinit()
{
	// Removed - now set from XAMOS class:
	// Select use of OpenGL:
	//useopengl = true;
	// Allow non-power-of-two textures or not:
	//usenpot = false;

	// Set maximum texture size:
#ifdef __MORPHOS__
	maxtexturesize = 1024; // cludge
#else
	maxtexturesize = 16384;
#endif

#ifdef USESDL
	// Initialize all SDL subsystems:
#if defined(USESDL) && !defined(GLES)
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
#elif defined(USESDL) && defined(GLES)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
#endif
	{
		cout << "Error initialising SDL!" << endl;
		return false;
	}

	// Added - SDL_ttf:
	if (TTF_Init() == -1) 
	{
		cout << "Unable to initialize SDL_ttf: " << TTF_GetError() << endl;
		//exit(1); // return true;
	}
	font = TTF_OpenFont("resources/Default.ttf", 28);

	// Set up the screen:
	if (useopengl)
	{
#if defined(USESDL) && !defined(GLES)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL); // | SDL_RESIZABLE);
#elif defined(USESDL) && defined(GLES)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); // | SDL_RESIZABLE);
#endif
	}
	else
	{
#if defined(USESDL) && !defined(GLES)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); // | SDL_RESIZABLE);
#elif defined(USESDL) && defined(GLES)
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
#endif
	}

	// If there was an error in setting up the screen:
	if ((screen == NULL) || (font == NULL))
		return false;

	// Set up OpenGL if appropriate:
	if (useopengl)
	{
		if(initGL() == false)
			return false;
#if defined(USESDL) && !defined(__morphos__) && !defined(GLES)
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
#endif
	}
#endif

	// Set the window caption (patch - do not use Unicode on Amiga-like systems which do not support it):
#if defined(USESDL) && !defined(AMIGOID)
	SDL_WM_SetCaption( "XAMOS alpha 0.29 \u00a9 2012 Mequa Innovations", NULL ); // \u00a9
#endif
#if defined(USESDL) && defined(AMIGOID)
	SDL_WM_SetCaption( "XAMOS alpha 0.29 (C) 2012 Mequa Innovations", NULL ); // \251
#endif

	// Added - initially disable transparency on screens (for speed):
	usetransparentscreens = false;

	// If everything initialized fine:
	return true;
}

// New - initialise OpenGL subsystems:
bool GameEngineWrapper::initGL()
{
// Removed: Initialise OpenGL ES:
#if defined(USESDL) && defined(GLES) && 0
	// use EGL to initialise GLES
	g_x11Display = XOpenDisplay(NULL);
 
	if (!g_x11Display)
	{
		fprintf(stderr, "ERROR: unable to get display!\n");
		return 0;
	}
 
	g_eglDisplay = eglGetDisplay((EGLNativeDisplayType)g_x11Display);
	if (g_eglDisplay == EGL_NO_DISPLAY)
	{
		printf("Unable to initialise EGL display.\n");
		return 0;
	}
 
	// Initialise egl
	if (!eglInitialize(g_eglDisplay, NULL, NULL))
	{
		printf("Unable to initialise EGL display.\n");
		return 0;
	}
 
	// Find a matching config
	EGLint numConfigsOut = 0;
	if (eglChooseConfig(g_eglDisplay, g_configAttribs, &g_eglConfig, 1, &numConfigsOut) != EGL_TRUE || numConfigsOut == 0)
	{
		fprintf(stderr, "Unable to find appropriate EGL config.\n");
		return 0;
	}
 
	// Get the SDL window handle
	SDL_SysWMinfo sysInfo; //Will hold our Window information
	SDL_VERSION(&sysInfo.version); //Set SDL version
	if(SDL_GetWMInfo(&sysInfo) <= 0) 
	{
		printf("Unable to get window handle\n");
		return 0;
	}
 
	g_eglSurface = eglCreateWindowSurface(g_eglDisplay, g_eglConfig, (EGLNativeWindowType)sysInfo.info.x11.window, 0);
	if ( g_eglSurface == EGL_NO_SURFACE)
	{
		printf("Unable to create EGL surface!\n");
		return 0;
	}
 
	// Bind GLES and create the context
	eglBindAPI(EGL_OPENGL_ES_API);
	EGLint contextParams[] = {EGL_CONTEXT_CLIENT_VERSION, 1, EGL_NONE};		// Use GLES version 1.x
	g_eglContext = eglCreateContext(g_eglDisplay, g_eglConfig, NULL, NULL);
	if (g_eglContext == EGL_NO_CONTEXT)
	{
		printf("Unable to create GLES context!\n");
		return 0;
	}
 
	if (eglMakeCurrent(g_eglDisplay,  g_eglSurface,  g_eglSurface, g_eglContext) == EGL_FALSE)
	{
		printf("Unable to make GLES context current\n");
		return 0;
	}
#endif
#if defined(USESDL)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, 720, 576);
	glClear(GL_COLOR_BUFFER_BIT);

#if defined(USESDL) && !defined(GLES)
	// Initialize Projection Matrix:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, 720, 576, 0.0f, -1.0f, 1.0f);
#endif
#if defined(USESDL) && defined(GLES)
	// TODO - OpenGL ES implementation (replacement for glMatrixMode()
	// TODO - OpenGL ES implementation (replacement for glLoadIdentity)
	// TODO - OpenGL ES implementation (replacement for glOrtho)
#endif

#if defined(USESDL) && !defined(GLES)
	// Initialize Modelview Matrix:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#endif
#if defined(USESDL) && defined(GLES)
	// TODO - OpenGL ES implementation (replacement for glMatrixMode()
	// TODO - OpenGL ES implementation (replacement for glLoadIdentity)
#endif

	// Check for error:
	GLenum error = glGetError();
	if( error != GL_NO_ERROR )
	{
#if defined(USESDL) && !defined(GLES)
		cout << "Error initializing OpenGL! " << gluErrorString(error) << endl;
#endif
#if defined(USESDL) && defined(GLES)
		// TODO - OpenGL ES implementation (replacement for gluErrorString()?)
#endif
		return false;
	}
#endif
	return true;
}

// TODO - remove this eventually!
bool GameEngineWrapper::load_files()
{
#ifdef USESDL
	// Load the background image:
	load_image("resources/Back.jpg");
#endif
	return true;
}
void GameEngineWrapper::clean_up()
{
// Removed - experimental/testing only:
#if defined(USESDL) && defined(GLES) && 0
	eglMakeCurrent(g_eglDisplay, NULL, NULL, EGL_NO_CONTEXT);
	eglDestroySurface(g_eglDisplay, g_eglSurface);
	eglDestroyContext(g_eglDisplay, g_eglContext);
	g_eglSurface = 0;
	g_eglContext = 0;
	g_eglConfig = 0;
	eglTerminate(g_eglDisplay);
	g_eglDisplay = 0;
        XCloseDisplay(g_x11Display);
        g_x11Display = NULL;
#endif

#ifdef USESDL
	// Free the surfaces (TODO):
	//SDL_FreeSurface(mysurface);

	// Free the sound samples (TODO):
	//Mix_FreeChunk(jamos);
#endif
	// This part is win32 only!
#if defined(__WIN32__) && defined(USESDL)
	fclose (stdout);
	fclose (stderr);
#endif

#ifdef USESDL
	// Quit SDL_TTF after closing the font (TODO - more fonts):
	TTF_CloseFont(font);
	TTF_Quit();

	// Quit SDL (can be slow?)
	SDL_Quit();
#endif
}
void GameEngineWrapper::handle_input()
{
#ifdef USESDL
 	// If a key was pressed:
	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_UP: keyup = 1; break;
			case SDLK_DOWN: keydown = 1; break;
			case SDLK_LEFT: keyleft = 1; break;
			case SDLK_RIGHT: keyright = 1; break;
			case SDLK_LSHIFT: keylshift = 1; break;
			case SDLK_LCTRL: keylctrl = 1; break;
			case SDLK_RSHIFT: keyrshift = 1; break;
			case SDLK_RCTRL: keyrctrl = 1; break;
			case SDLK_ESCAPE: keyesc = 1; break;
			case SDLK_c: keyc = 1; break;
			default: break;
		}
	}
	// If a key was released:
	if(event.type == SDL_KEYUP)
	{
		switch(event.key.keysym.sym)
 		{
			case SDLK_UP: keyup = 0; break;
			case SDLK_DOWN: keydown = 0; break;
			case SDLK_LEFT: keyleft = 0; break;
			case SDLK_RIGHT: keyright = 0; break;
			case SDLK_LSHIFT: keylshift = 0; break;
			case SDLK_LCTRL: keylctrl = 0; break;
			case SDLK_RSHIFT: keyrshift = 0; break;
			case SDLK_RCTRL: keyrctrl = 0; break;
			case SDLK_ESCAPE: keyesc = 0; break;
			case SDLK_c: keyc = 0; break;
			default: break;
		}
	}
	// If the mouse moved:
	if(event.type == SDL_MOUSEMOTION)
	{
		mousex = event.motion.x;
		mousey = event.motion.y;
	}
	// If a mouse button was pressed:
	if( event.type == SDL_MOUSEBUTTONDOWN )
	{
		switch(event.button.button)
		{
			case SDL_BUTTON_LEFT: lmouse = 1; break;
			case SDL_BUTTON_RIGHT: rmouse = 1; break;
			case SDL_BUTTON_MIDDLE: mmouse = 1; break;
			default: break;
		}
	}
	// If a mouse button was released:
	if( event.type == SDL_MOUSEBUTTONUP )
	{
		switch(event.button.button)
		{
			case SDL_BUTTON_LEFT: lmouse = 0; break;
			case SDL_BUTTON_RIGHT: rmouse = 0; break;
			case SDL_BUTTON_MIDDLE: mmouse = 0; break;
			default: break;
		}
	}
#endif
}

// Note: Clears framebuffer, NOT currentScreen!
void GameEngineWrapper::cls()
{
#ifdef USESDL
	// Fill the screen black:
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x0, 0x0, 0x0 ) );
#endif
}

void GameEngineWrapper::initsimpleconsole()
{
#if defined(__WIN32__) && defined(USESDL)
	// This part is win32 only!
	FILE* useconsole = NULL;
	useconsole = freopen( "CON", "wt", stdout );
	if (useconsole != NULL);
		useconsole = freopen( "CON", "wt", stderr );
	if (useconsole == NULL)
		;
#endif
}
void GameEngineWrapper::initsdlstuff()
{
#ifdef USESDL
	screen = NULL;

	// The screen attributes:
	SCREEN_WIDTH = 720;
	SCREEN_HEIGHT = 576;
	SCREEN_BPP = 32;

	// The frame rate:
	FRAMES_PER_SECOND = 60;

	// The surfaces
	screen = NULL;

	// Initialise:
	if (sdlinit() == false)
		return; // 1;

	// Display splash screen:
	SDL_Surface* splashopt = NULL;
	SDL_Surface* splash = IMG_Load("resources/XAMOS.jpg");

	if (splash != NULL)
		splashopt = SDL_DisplayFormat(splash);

	if ((splashopt != NULL) && (screen != NULL))
	{
		int y = (SCREEN_HEIGHT / 2) - (166 / 2);
		if (useopengl)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			displaywithopengl(0, y, splashopt->w, splashopt->h, splashopt);
#if defined(USESDL) && defined(GLES)
			//eglSwapBuffers(g_eglDisplay, g_eglSurface);
#endif
#if defined(USESDL) && !defined(GLES)
			SDL_GL_SwapBuffers();
#endif
		}
		else
		{
			apply_surface(0, y, splashopt, screen, NULL);
			SDL_Flip(screen);
		}
		SDL_FreeSurface(splashopt);
	}
#endif
}
void GameEngineWrapper::initsdlaudio()
{
#ifdef USESDL
	// Initialize SDL_mixer:
	if( Mix_OpenAudio( 48000, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 ) // 4096
		return; // false;

	// Load the sound:
	////load_sound("resources/XAMOS.wav", "XAMOS");
	//load_sound("resources/bell.wav", "Bell");
	//load_sound("resources/boom.wav", "Boom");
	//load_sound("resources/shoot.wav", "Shoot");

	// Load the sound samples:
	//xamossound = Mix_LoadWAV("resources/XAMOS.wav");
	xamossound = NULL;
	bellsound = Mix_LoadWAV("resources/bell.wav");
	boomsound = Mix_LoadWAV("resources/boom.wav");
	shootsound = Mix_LoadWAV("resources/shoot.wav");

	// Play the sound effect (removed - annoying with run-only!):
	//Mix_PlayChannel(-1, xamossound, 0);
	////Mix_PlayChannel(-1, sounds["XAMOS"], 0);
#endif
}



// Added - Abk decoder:
unsigned long GameEngineWrapper::getcolor(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned long out = 0;

#if 1 // BIG_ENDIAN(?)
	out +=   b & 0xff;
	out += ((g & 0xff) << 8);
	out += ((r & 0xff) << 16);
#else
	out += ((b & 0xff) << 24);
	out += ((g & 0xff) << 16);
	out += ((r & 0xff) << 8);
#endif

	return out;
}
unsigned char GameEngineWrapper::getnextbyte(char* buffer, long unsigned int* bufferpos)
{
	unsigned char out = buffer[*bufferpos];
	(*bufferpos)++;
	return out;
}
int GameEngineWrapper::loadAbkAndDecode(string name_, int bank, unsigned int scale)
{
#ifdef USESDL
	/* Added: */
	const char* name;

	char *buffer;
	unsigned long ***image;
	/* unsigned long ***image32; */
	unsigned long *xsize;
	unsigned long *ysize;
	unsigned long *bitplanes;
	long int *xhandle;
	long int *yhandle;
	unsigned long *palette;
	unsigned long *colorpalette;

	//unsigned int scale = 1;

	unsigned long bufferpos = 0;
	int usehalfbright = 1;
	int usefilebuffer = 1;
	/* int spriteloaded = 0; */
	/* int icon = 0; */
	unsigned int numobjects = 0;
	unsigned long bitplane = 0;



	FILE *file;
	unsigned long fileLen;

	/* Added: */
	name = name_.c_str();

	/* Open file */
	file = fopen(name, "rb");
	if (!file)
	{
		cerr << "Unable to open file " << name << endl;
		return 1;
	}
	
	/* Get file length */
	fseek(file, 0, SEEK_END);
	fileLen=ftell(file);
	fseek(file, 0, SEEK_SET);

	/* Allocate memory */
	buffer=(char*)malloc(sizeof(char) * (fileLen + 1));
	if (!buffer)
	{
		cerr << "Memory error!" << endl;
		fclose(file);
		return 1;
	}

	/* Read file contents into buffer */
	size_t fsize;
	fsize = fread(buffer, fileLen, 1, file);
	if (fsize == 0)
		;

	fclose(file);


	/* Now decode the file: */

	char charfield = 0;
	char str[10];

	unsigned int foundbank = 0;
	unsigned int a, obj, bitmap, x, y, bit, bitnum;
	unsigned long entry;
	unsigned int red, green, blue;
	unsigned int index;

	/* First check the first 4 characters: */
	for (a=0; a<4; a++)
	{
		charfield = getnextbyte(buffer, &bufferpos);
		str[a] = charfield;
	}
	str[4]=0;

	if (strlen(str)==4 && strcmp(str, "AmSp")==0)
	{
		/*cout << "AMOS Sprite Bank" << endl;*/
		foundbank = 1;
		/* icon = 0; */
	}
	else if (strlen(str)==4 && strcmp(str, "AmIc")==0)
	{
		/*cout << "AMOS Icon Bank" << endl;*/
		foundbank = 1;
		/* icon = 1; */
	}
	else if (strlen(str)==4)
	{
		if (strlen(str)==4 && strcmp(str, "AmBk")==0)
			cout << "Error: Wrong type of AMOS Bank. Only Sprite/Object/Bob and Icon type are supported." << endl;
		else
			cout << "Error: Not an AMOS bank." << endl;

		foundbank = 0;
		/*parent.abkfile.closebinaryfile(parent.abkfile.in);*/
		return 1;
	}

	/* Exit if bank not found: */
	if (!foundbank)
		;/*(parent.abkfile).closebinaryfile((parent.abkfile).in);*/

	str[0] = 0;

	/* Now try to find the number of objects: */
	numobjects = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos));
	/*cout << "Number of Objects: " << AM->stri(numobjects) << endl;*/

	image = (unsigned long***)malloc(sizeof(unsigned long**) * numobjects);
	xsize = (unsigned long*)malloc(sizeof(unsigned long) * numobjects);
	ysize = (unsigned long*)malloc(sizeof(unsigned long) * numobjects);
	bitplanes = (unsigned long*)malloc(sizeof(unsigned long) * numobjects);
	xhandle = (long*)malloc(sizeof(long) * numobjects);
	yhandle = (long*)malloc(sizeof(long) * numobjects);

	/* Now parse each object in turn to get its details: */
	for (obj=0; obj<numobjects; obj++)
	{
		xsize[obj] = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos)) << 4;
		ysize[obj] = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos));
		bitplanes[obj] = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos));
		xhandle[obj] = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos));
		yhandle[obj] = (getnextbyte(buffer, &bufferpos)<<8)|(getnextbyte(buffer, &bufferpos));

		//cout << "For Object " << AM->stri(obj) << ": X_Size= << " << AM->stri(xsize[obj]) << ", Y_Size=" << AM->stri(ysize[obj])
		//	<< ", Bitplanes=" << AM->stri(bitplanes[obj]) << ", X_Hot_Spot=" << AM->stri(xhandle[obj]) << ", Y_Hot_Spot=" << AM->stri(yhandle[obj]) << endl;

		// Added - scaling:
		//xsize[obj] *= scale; // needed for loop - and below
		//ysize[obj] *= scale;
		xhandle[obj] *= scale;
		yhandle[obj] *= scale;

		/* Allocate an array to hold the converted bitmap: */
		image[obj] = NULL;
		image[obj] = (unsigned long**) malloc(sizeof(unsigned long*) * xsize[obj]);
		for (x=0; x<xsize[obj]; x++)
			image[obj][x] = (unsigned long*) malloc(sizeof(unsigned long) * ysize[obj]);

		/*cout << "Image size: " << AM->stri(xsize[obj]) << ", " << AM->stri(ysize[obj]) << endl;*/

		/* Clear the buffer: */
		for (x=0; x<xsize[obj]; x++)
			for (y=0; y<ysize[obj]; y++)
				image[obj][x][y] = 0;

		/* Now parse the bitmap itself: */
		for (bitplane=0; bitplane<bitplanes[obj]; bitplane++)
		{
			/* Clear the bitmap - add each bit on in turn: */
			bitmap = 0;

			/* Parse the X and Y here: */
			for (y=0; y<ysize[obj]; y++)
			{
				for (x=0; x<xsize[obj]; x+=16)
				{
					bit=0;

					/* Grab the 16-bit bitmap segment here: */
					bitmap = ((unsigned)getnextbyte(buffer, &bufferpos) << 8)|((unsigned)getnextbyte(buffer, &bufferpos));

					/* Now parse and manipulate the bits and convert to chunky byte format: */
					for (bitnum=0; bitnum<16; bitnum++)
					{
						/* Get least significant bit: */
						bit = bitmap & 1;

						/* Shift down: */
						bitmap = ((unsigned)bitmap) >> 1;

						/* Now add to the chunky paletted buffer: */
						image[obj][x+(15 - bitnum)][y] |= (bit << bitplane);
					}
				}
			}
		}
	}

	/* Finally after all objects are processed, get the sprite palette details. */
	/* This is always 32 colours: */

	/* Create extra indexes if using half bright mode: */
	if (usehalfbright)
	{
		palette = (unsigned long*)malloc(sizeof(unsigned long) * 64);
		colorpalette = (unsigned long*)malloc(sizeof(unsigned long) * 64);
	}
	else
	{
		palette = (unsigned long*)malloc(sizeof(unsigned long) * 32);
		colorpalette = (unsigned long*)malloc(sizeof(unsigned long) * 32);
	}

	/* Note: Always uses 32 colours for the sprite palette. */
	for (index=0; index<32; index++)
	{
		entry = ((getnextbyte(buffer, &bufferpos) << 8 ) + getnextbyte(buffer, &bufferpos));
		palette[index]=entry;

		/*cout << "Colour " << AM->stri(index) << ": " << AM->stri(entry) << endl;*/

		/* Now get the red, green and blue values */
		/* Bitwise AND to separate colour entries: */
		red   = (unsigned)(entry & 0xF00) >> 8;
		green = (unsigned)(entry & 0x0F0) >> 4;
		blue  = (unsigned)(entry & 0x00F);

		/* Added: For 64 colour mode - 6 bitplanes on sprite images: Do the old-skool palette half-bright (may incur rounding): */
		/* If the 24-bit/32-bit buffer need be dropped, this may work as a fall-back - but then implement EHB directly (TO DO): */
		if (usehalfbright)
			palette[index + 32] = (((unsigned)red>>1) * 0x100) + (((unsigned)green>>1) * 0x10) + ((unsigned)blue>>1);

		/* Multiply by 0x11 (17) to scale 0xFFF to 0xFFFFFF */
		/* Multiply by 0x11 (17) to convert 0xF (15) into 0xFF (255): */
		red   *= 0x11;
		green *= 0x11;
		blue  *= 0x11;
		colorpalette[index]=getcolor(red, green, blue);

		/* Added: For 64 colour mode: Do the half-bright 24-bit/32-bit palette index (if appropriate): */
		/* Note that this uses true 24-bit brightness halving. */
		if (usehalfbright)
			colorpalette[index + 32]=getcolor(((unsigned)red)>>1, ((unsigned)green)>>1, ((unsigned)blue)>>1);
	}

	/* The file can be closed now if not using a buffer (otherwise it is closed earlier): */
	if (!usefilebuffer)
		; /*(abkfile).closebinaryfile(abkfile.in); */

	/* Before drawing the image, create a 32-bit 2D array: */
	/*
	image32 = (unsigned long***)malloc(sizeof(unsigned long**) * numobjects);
	for (obj=0; obj<numobjects; obj++)
	{
		image32[obj] = NULL;
		image32[obj] = (unsigned long**) malloc(sizeof(unsigned long*) * xsize[obj]);
		for (x=0; x<xsize[obj]; x++)
		{
			image32[obj][x] = (unsigned long*) malloc(sizeof(unsigned long) * ysize[obj]);
		}
	}
	*/
	/* Create a 24-bit/32-bit Color image array: */
	/*for (obj=0; obj<numobjects; obj++)
		for (y=0; y<ysize[obj]; y++)
			for (x=0; x<xsize[obj]; x++)
				image32[obj][x][y] = colorpalette[image[obj][x][y]];
	*/

	/* Close the raw file buffer here: */
	free(buffer);

	/*spriteloaded = 1; */

	// Cludge: Add null image:
    	//AM->loadedspriteimages.push_back("null");
	if (bank == 1)
	    	AM->currentspriteimages.push_back("null");
	else if (bank == 2)
		AM->currenticonimages.push_back("null");

    	// Draw a sprite image using the sprite palette:
    	for (unsigned int spritenum=0; spritenum<numobjects; spritenum++)
	{
		// Create the image here:
		string path = string(name)+"/"+AM->str(spritenum);

		// Create a new SDL surface:
		SDL_Surface* newImage = NULL;
		SDL_Surface* optimisedImage = NULL;

		const SDL_PixelFormat& fmt = *(screen->format);
		Uint32 flags;
		//if (useopengl)
		//	flags = SDL_HWSURFACE;
		//else
		flags = SDL_SWSURFACE;
		newImage = SDL_CreateRGBSurface(flags, xsize[spritenum]*scale, ysize[spritenum]*scale, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

		if(newImage != NULL)
		{
			// Create an optimised surface:
			optimisedImage = SDL_DisplayFormat(newImage);

			// Free the old surface:
			SDL_FreeSurface(newImage);
		}

		if (optimisedImage == NULL)
			return 1;

		// Add the transparent mask:
		Uint32 mycolour = (Uint32)colorpalette[0];
		Uint8 r = (Uint8) ((mycolour & (Uint32)0x00ff0000) >> 16);
		Uint8 g = (Uint8) ((mycolour & (Uint32)0x0000ff00) >> 8);
		Uint8 b = (Uint8) ((mycolour & (Uint32)0x000000ff));
		if (bank == 1)
			SDL_SetColorKey(optimisedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimisedImage->format, r, g, b));

		// Clear the surface here:
		SDL_FillRect(optimisedImage, &optimisedImage->clip_rect, SDL_MapRGB(optimisedImage->format, r, g, b));

		//cout << "DEBUG: r=" << AM->stri(r) << ", g=" << AM->stri(g) << ", b=" << AM->stri(b) << ", rgb=" << AM->stri((int)SDL_MapRGB(optimisedImage->format, r, g, b)) << endl;

		// Plot to the surface here:
	    	for (unsigned int y=0; y<ysize[spritenum]; y++)
		{
			for (unsigned int x=0; x<xsize[spritenum]; x++)
			{
				int paletteindex = image[spritenum][x][y];
				if (paletteindex > 0)
				{
					Uint32 mycolour = (Uint32)colorpalette[paletteindex];

					Uint8 a = 255; //(Uint8) ((colour & (Uint32)0xff000000) >> 24);
					Uint8 r = (Uint8) ((mycolour & (Uint32)0x00ff0000) >> 16);
					Uint8 g = (Uint8) ((mycolour & (Uint32)0x0000ff00) >> 8);
					Uint8 b = (Uint8) ((mycolour & (Uint32)0x000000ff));

					// Allow for scale:
	    				for (unsigned int l=0; l<scale; l++)
					{
						lineRGBA(optimisedImage,
							x * scale, y * scale + l, x * scale + (scale - 1), y * scale + l,
							r, g, b, a);
					}
	    			}
			}
		}

		// Now insert the sprite image into our hash table:
		images.insert(make_pair<string, SDL_Surface*>(path, optimisedImage));

		// Create duplicates of the above image for flipping:
		SDL_Surface* flip = NULL;
		flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
		if (flip != NULL)
		{
			flip = flip_surface(images[path], 2); // FLIP_HORIZONTAL
			images.insert(make_pair<string, SDL_Surface*>(path+"_h", flip));
		}
		flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
		if (flip != NULL)
		{
			flip = flip_surface(images[path], 1); // FLIP_VERTICAL
			images.insert(make_pair<string, SDL_Surface*>(path+"_v", flip));
		}
		flip = SDL_ConvertSurface(images[path], images[path]->format, flags);
		if (flip != NULL)
		{
			flip = flip_surface(images[path], 3); // FLIP_HORIZONTAL | FLIP_VERTICAL
			images.insert(make_pair<string, SDL_Surface*>(path+"_hv", flip));
		}

    		// Add the fake path to the vector of sprite image names:
    		//AM->loadedspriteimages.push_back(path);
		if (bank == 1)
	    		AM->currentspriteimages.push_back(path);
		else if (bank == 2)
			AM->currenticonimages.push_back(path);

		// Added - set the hot spot here:
		if (bank == 1)
		{
			while (AM->ImageHotSpotX.size() <= (spritenum + 1))
				AM->ImageHotSpotX.push_back(0);
			while (AM->ImageHotSpotY.size() <= (spritenum + 1))
				AM->ImageHotSpotY.push_back(0);
			AM->ImageHotSpotX[spritenum + 1] = (int)xhandle[spritenum];
			AM->ImageHotSpotY[spritenum + 1] = (int)yhandle[spritenum];
			//cout << "Debug: Loading abk hot spots: (" << AM->ImageHotSpotX[spritenum+1] << ", " << AM->ImageHotSpotY[spritenum+1] << ") spritenum=" << spritenum << endl;
			//AM->ImageHotSpotX[spritenum] = 0; // debug
			//AM->ImageHotSpotY[spritenum] = 0; // debug
		} // Is this needed for icons?
	}

	// Debug:
	//cout << "Debug: Current sprite images:" << endl;
	//for (unsigned int n=0; n<AM->currentspriteimages.size(); n++)
	//	cout << AM->stri(images[AM->currentspriteimages[n]] != NULL) << " " << AM->stri(AM->currentspriteimages[n]) << endl;

	// TODO - clean up here!
#endif
	return 0;
}

