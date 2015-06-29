#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

namespace Frucht {

struct GLTexture {
    GLuint id;
    int width;
    int height;
};

}

#endif // GLTEXTURE_H
