#include "Core/engine.h"
#include "Timer/Timer.h"
// #include <iostream>

signed main( int argc, char *argv[] ){
    Engine::GetInstance() -> Init();
    // std::cout << "post-init survival \n";
    while (Engine::GetInstance() -> isRunning()){
        Timer::getInstance() -> Tick();
        // std::cout << "alive 1 \n";
        Engine::GetInstance() -> Events();
        // std::cout << "alive 2 \n";
        // Engine::GetInstance() -> Update();
        // std::cout << "alive 3 \n";
        Engine::GetInstance() -> Render();
        // std::cout << "alive 4 \n";
    }
    Engine::GetInstance() -> Clean();
    return 0;
}