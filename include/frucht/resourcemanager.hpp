#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <frucht/texturecache.hpp>
#include <string>

namespace Frucht {

class ResourceManager
{
public:
    static GLTexture getTexture(std::string texturePath);

private:
    static TextureCache m_textureCache;
};

}

#endif // RESOURCEMANAGER_H
