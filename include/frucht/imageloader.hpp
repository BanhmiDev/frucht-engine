#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>
#include <frucht/gltexture.hpp>

namespace Frucht {

class ImageLoader
{
public:
    static GLTexture loadPNG(std::string filePath);
};

}

#endif // IMAGELOADER_H
