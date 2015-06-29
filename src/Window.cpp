#include <frucht/window.hpp>
#include <frucht/error.hpp>

namespace Frucht {

Window::Window()
{
}

Window::~Window()
{
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    
    // Flags @https://wiki.libsdl.org/SDL_WindowFlags
    Uint32 flags = SDL_WINDOW_OPENGL;
    
    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    } 
    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }
    if (currentFlags & RESIZABLE) {
        flags |= SDL_WINDOW_RESIZABLE;
    }

    m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
    
    if (m_sdlWindow == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(m_sdlWindow);
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initialize glew!");
    }
 
    std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glClearColor(0.0f, 0.5f, 0.4f, 1.0f);
    
    // Transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vsync off
    SDL_GL_SetSwapInterval(0);

    return 0;
}

void Window::swapBuffer()
{
    //glFlush();
    SDL_GL_SwapWindow(m_sdlWindow);
    //glFinish();
}

}
