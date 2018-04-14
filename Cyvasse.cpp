#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
#include "Pieces.h"
#include "Spielfeld.h"
#include "Tiles.h"
using namespace std;

int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    Spielfeld Brett(win);
    //Berg ME(win);
    SDL_Event Event;
    Brett.aufbauen(0);
    Brett.aufbauen(1);
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            Brett.getinput(Event);
            //Brett.aktualisieren();
        //    ME.aktualisieren(2,3);
            SDL_UpdateWindowSurface(win);
        }
    }
    SDL_Delay(100000);
    return 1;
}
 
