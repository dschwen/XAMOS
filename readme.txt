XAMOS (Cross-AMOS) alpha 0.29

Cross-platform AMOS BASIC reimplementation

(C) 2012 Mequa Innovations


This project is a complete re-write of jAMOS in C++ using SDL libraries and (optional) Boost headers.
This release is alpha 0.29.

This initial release is run-only and does not feature an editor at this stage. However, it is compatible with almost all programs created with the latest jAMOS editor. All jAMOS examples (without AMAL) are running in XAMOS, often with a serious speed boost over the Java original, particularly on low-end platforms.

AMAL is now fully implemented in line with jAMOS 0.24. The AMAL subsystem for XAMOS is called XAMAL.

Source is buildable on Win32 (MinGW), Linux, AROS and MorphOS. Makefiles are included for all platforms.
SDL libraries (SDL, SDL_image, SDL_mixer and SDL_gfx) are required to build this project. Windows DLLs are included for convenience; on other platforms the SDL libraries need to be installed separately.

Binaries are included for Win32 (tested on Windows 98SE, Windows XP, Windows 7 and Windows 8 Consumer Preview) and Linux (tested on Ubuntu 12.04).
Also available for download are binaries for Linux/x64, Linux/PPC, Linux/ARM (compatible with Raspberry Pi), AROS/x86 and MorphOS/PPC.

Enjoy the latest AMOS BASIC reimplementation.


Changes:

XAMOS alpha 0.23:
- Initial release, based on jAMOS 0.23.

XAMOS alpha 0.24:
- AMAL is now implemented in line with jAMOS 0.24, including AMAL Environment Generator. All AMAL examples from jAMOS are added and runnable in XAMOS.
- Can translate AMAL (and EnvGen) code into both C++ and Java.
- Much code refactoring and debugging.
- Removed default startup sound for run-only version.
- A console-based launcher is added for launching all 40 included examples, along with a batch file.

XAMOS alpha 0.241:
- Removed the dependency on Boost (now available as a compiler option by editing the Makefile). Fallback to deprecated hash_map type is supported without Boost.
- Added the ability to build a minimal text-only build without SDL, for cross-platform testing (tested on AROS/x86 and MorphOS/PPC).
- Improved compatibility with 64-bit systems (e.g. Linux/x64).

Note: Some small modifications to the source were made since initial 0.241 release to allow for building on MorphOS. Makefiles were also updated.

XAMOS alpha 0.242:
- Replaced Plot routine with a more stable and compatible one (fixed crashes on AROS).
- Plotting now works correctly on MorphOS (Drawing.xamos, Plotter.xamos, Mandelbrot.xamos, Array.xamos).
- XAMOS -launcher now works on AROS.
- Does not attempt to use Unicode when built for Amiga-like OS's (title bar).
- Fixed random number generation on AROS (ScreenScrollingDemo.xamal, MultiChannelExample.xamal).

XAMOS alpha 0.25:
- Per-pixel collision detection is now implemented, utilising SDL_Collide routines.
- AMOS functions added: =Bob Col(), =Sprite Col(), =SpriteBob Col(), =Bobsprite Col(), =Col().
- A very simple collision example was added - more to come in future.

XAMOS alpha 0.26:
- Multiple screen support has been implemented, with a corresponding demo example.
- Fixed some bugs with collision detection.
- Added "Eater" game demo demonstrating collision detection, Abk support, AMAL and multiple screens.
- Added a XAMOS example of a simple interpreter of a certain esoteric programming language, to demonstrate Turing-completeness.

XAMOS alpha 0.27:
- Added support for graphical text (using TrueType fonts), AMOS Text instruction and Text Length() function.
- Abk sprite banks now correctly load sprite hot spots or handles.
- Icon bank support was added, with Paste Icon instruction. An icon bank is loadable from an Abk bank or folder of images.
- Can now scale Abk sprite and icon banks.
- Updated "Eater" game demo (now default, former in XAMOSOut.xamos).

XAMOS alpha 0.271:
- Fixed a memory leak when displaying graphical text.
- Hot Spot instruction is now implemented, for sprites in all formats.
- Refactored SDL code, and began work on a queue system for rainbow/screen/bob/sprite display priority.

XAMOS alpha 0.28:
- Added an experimental hardware-accelerated OpenGL frontend. Use "-useopengl" command line flag to set.
This is currently disabled by default and not yet working correctly with all examples, or on all platforms.
- Background rainbows are now operational. The rainbows example has been updated.

To use OpenGL:
> XAMOS -useopengl
Which will load the default example.

To select an example using OpenGL:
> XAMOS -launcher -useopengl

To launch the Breakout demo with OpenGL:
> XAMOS example/XAMOSOut.xamos -useopengl

On Linux/Unix use "./XAMOS ...." instead.

XAMOS alpha 0.281:
- Fixed several bugs with the OpenGL frontend - all examples now work correctly (on some platforms).
- Added command line flag to enable non-power-of-two (NPOT) textures: "-useopengl -usenpot", may be faster if supported by GPU.

XAMOS alpha 0.29:
- Added some groundwork for experimental OpenGL ES support (not yet operational).
- Now works correctly in fullscreen mode (Raspbian etc).
- You can now quit by using ESC or CTRL+C.
- A RISC OS (ARM) port of XAMOS by Chris Gransden is now available and in development.
