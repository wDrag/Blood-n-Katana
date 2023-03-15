#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>

signed main( int argc, char *argv[] ){
    SDL_Event window1_Event;
        bool quit = 0;

//  gameloop
    while (!quit){
        if (SDL_PollEvent( &window1_Event)){
            if (window1_Event.type == SDL_QUIT){
                quit = 1;
            }
        }
    }    
    return 0;
}