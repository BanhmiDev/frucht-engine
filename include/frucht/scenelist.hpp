#ifndef SCENELIST_H
#define SCENELIST_H

#include <iostream>

namespace Frucht {

class MainGame;
class GameScene;

class SceneList {
public:
    SceneList(MainGame* game);
    
    GameScene* moveNext();
    GameScene* movePrevious();

    void setScence(int nextScene);
    void addScene(GameScene* newScene);

    void destroy();

protected:
    MainGame* m_game = nullptr;
    std::vector<GameScene*> m_scenes;
    int m_currentSceneIndex = -1;
};

}

#endif
