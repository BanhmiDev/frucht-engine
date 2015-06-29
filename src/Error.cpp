#include <iostream>
#include <frucht/error.hpp>
#include <SDL2/SDL.h>

namespace Frucht {

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    SDL_Quit();
    exit(1);
}

}
