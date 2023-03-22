#include "Core/engine.h"
#include "Timer/Timer.h"

signed main( int argc, char *argv[] ){
    Engine::getInstance() -> Init();
    while (Engine::getInstance() -> isRunning()){
        Engine::getInstance() -> Events();
        Engine::getInstance() -> Update();
        Engine::getInstance() -> Render();
        Timer::getInstance() -> Tick();
    }
    Engine::getInstance() -> Clean();
    return 0;
}