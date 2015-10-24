#include "Timer.h"

#ifdef USESDL
#include "SDL/SDL.h"
#endif

// The SDL timer:
Timer::Timer()
{
    // Initialize the variables:
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}
void Timer::start()
{
#ifdef USESDL
    // Start the timer
    started = true;

    // Unpause the timer
    paused = false;

    // Get the current clock time
    startTicks = SDL_GetTicks();
#endif
}
void Timer::stop()
{
    // Stop the timer
    started = false;

    // Unpause the timer
    paused = false;
}
void Timer::pause()
{
#ifdef USESDL
    // If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        // Pause the timer
        paused = true;

        // Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
#endif
}
void Timer::unpause()
{
#ifdef USESDL
    // If the timer is paused
    if( paused == true )
    {
        // Unpause the timer
        paused = false;

        // Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        // Reset the paused ticks
        pausedTicks = 0;
    }
#endif
}
int Timer::get_ticks()
{
#ifdef USESDL
    // If the timer is running
    if( started == true )
    {
        // If the timer is paused
        if( paused == true )
        {
            // Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            // Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }
#endif

    // If the timer isn't running
    return 0;
}
bool Timer::is_started()
{
    return started;
}
bool Timer::is_paused()
{
    return paused;
}

