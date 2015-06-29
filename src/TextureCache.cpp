#include <iostream>
#include <frucht/texturecache.hpp>
#include <frucht/imageloader.hpp>

namespace Frucht {

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(std::string texturePath)
{
    // Lookup texture in map
    std::map<std::string, GLTexture>::iterator mit = m_textureMap.find(texturePath);
    
    // Key not found, add texture
    if (mit == m_textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        
        std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
        m_textureMap.insert(newPair);
        
        return newTexture;
    }

    return mit->second;
}

}
