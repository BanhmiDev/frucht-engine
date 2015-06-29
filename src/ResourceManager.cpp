#include <frucht/resourcemanager.hpp>

namespace Frucht {

TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
    return m_textureCache.getTexture(texturePath);
}

}
