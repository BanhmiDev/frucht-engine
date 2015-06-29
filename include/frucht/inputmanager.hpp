#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

namespace Frucht {

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void update();

    void keyPress(unsigned int keyID);
    void keyRelease(unsigned int keyID);

    bool isKeyDown(unsigned int keyID);
    bool isKeyPressed(unsigned int keyID);

    void setMouseCoords(float x, float y);
    
    glm::vec2 getMouseCoords() const { return m_mouseCoords; }

private:
    bool wasKeyDown(unsigned int keyID);

    std::unordered_map<unsigned int, bool> m_keyMap;
    std::unordered_map<unsigned int, bool> m_previousKeyMap;

    glm::vec2 m_mouseCoords;
};

}

#endif // INPUTMANAGER_H
