#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include <frucht/gltexture.hpp>

namespace Frucht {

class TextureCache
{
public:
    TextureCache();
    ~TextureCache();
    
    GLTexture getTexture(std::string texturePath);

private:
    std::map<std::string, GLTexture> m_textureMap;
};

}

#endif // TEXTURECACHE_H
