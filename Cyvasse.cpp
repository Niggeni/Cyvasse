#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
//#include "Pieces.h"
#include "Spielfeld.h"
using namespace std;


int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    Spielfeld Brett(win);
    SDL_Event Event;
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            Brett.getinput(Event);
            Brett.aktualisieren();
            SDL_UpdateWindowSurface(win);
        }
    }
    SDL_Delay(100000);
    return 1;

}
