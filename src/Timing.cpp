#include <frucht/timing.hpp>
#include <SDL2/SDL.h>

namespace Frucht {

FpsLimiter::FpsLimiter()
{

}

void FpsLimiter::init(float maxFPS)
{
    setMaxFPS(maxFPS);
}

void FpsLimiter::setMaxFPS(float maxFPS)
{
    m_maxFPS = maxFPS;
}

void FpsLimiter::begin()
{
    m_startTicks = SDL_GetTicks();
}

float FpsLimiter::end()
{
    calculateFPS();

    float frameTicks = SDL_GetTicks() - m_startTicks;
    // Limit FPS
    if (1000.0f / m_maxFPS > frameTicks) {
        SDL_Delay((Uint32)(1000.0f / m_maxFPS - frameTicks));
    }
    
    return m_fps;
}

void FpsLimiter::calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    static float previousTicks = SDL_GetTicks();
    
    float currentTicks;
    currentTicks = SDL_GetTicks();
    
    m_frameTime = currentTicks - previousTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;
    
    previousTicks = currentTicks;

    int count;

    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;
    
    if (frameTimeAverage > 0) {
        m_fps = 1000.0f / frameTimeAverage;
    } else {
        m_fps = 60.0f;
    }

    currentFrame++;
}

}
