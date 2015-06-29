#include <frucht/inputmanager.hpp>

namespace Frucht {

InputManager::InputManager() : m_mouseCoords(0.0f)
{

}

InputManager::~InputManager()
{

}

void InputManager::update()
{
    // Copy to previous keymap
    for (auto& it : m_keyMap) {
        m_previousKeyMap[it.first] = it.second;
    }
}

void InputManager::keyPress(unsigned int keyID)
{
    // set to true even if not in map
    m_keyMap[keyID] = true;
}

void InputManager::keyRelease(unsigned int keyID)
{
    m_keyMap[keyID] = false;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
    auto it = m_previousKeyMap.find(keyID);
    if (it != m_previousKeyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
    bool isPressed;
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
        return true;
    }
    return false;
}

void InputManager::setMouseCoords(float x, float y)
{
    m_mouseCoords.x = x;
    m_mouseCoords.y = y;
}


}
