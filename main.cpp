#include "Core/engine.h"
#include "Timer/Timer.h"

// #include <iostream>

signed main( int argc, char *argv[] ){
    Engine::getInstance() -> Init();
    while (Engine::getInstance() -> isRunning()){
        Timer::getInstance() -> Tick();
        // std::cout << "alive 1 \n";
        Engine::getInstance() -> Events();
        // std::cout << "alive 2 \n";
        Engine::getInstance() -> Update();
        // std::cout << "alive 3 \n";
        Engine::getInstance() -> Render();
        // std::cout << "alive 4 \n";
    }
    Engine::getInstance() -> Clean();
    return 0;
}