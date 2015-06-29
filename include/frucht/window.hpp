#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Frucht {

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4, RESIZABLE = 0x8};

class Window
{
public:
    Window();
    ~Window();
    
    int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
    void swapBuffer();

    int getScreenWidth() { m_screenWidth; }
    int getScreenHeight() { m_screenHeight; }

private:
    SDL_Window* m_sdlWindow;

    int m_screenWidth;
    int m_screenHeight;
};

}

#endif // WINDOW_H
