#include "Core/engine.h"

signed main( int argc, char *argv[] ){
    Engine::getInstance() -> Init();
    while (Engine::getInstance() -> isRunning()){
        Engine::getInstance() -> Events();
        Engine::getInstance() -> Update();
        Engine::getInstance() -> Render();
    }
    Engine::getInstance() -> Clean();
    return 0;
}