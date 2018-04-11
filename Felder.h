#ifndef FELDER_H
#define FELDER_H
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
class Feld{
    protected:
        SDL_Surface *surf;
        SDL_Surface *Tiles;
        SDL_Rect source;
        SDL_Rect dest;
        int Feld_x;
        int Feld_y;
    public:
        int Typ;
        Feld(int, int,SDL_Window*);
        void aktualisieren();
};
Feld::Feld(int x,int y,SDL_Window *win){
    Feld_x = x;
    Feld_y = y;
    surf = SDL_GetWindowSurface(win);
    Tiles = IMG_Load("Sources/Landschaft/Landschaft.png");
}
void Feld::aktualisieren(){
    dest = {x:Feld_x*128+448,y:Feld_y*128+28,w:128,h:128};
    SDL_BlitSurface(Tiles,&source,surf,&dest);
}
class Berg :public Feld{
public:
    Berg(int x, int y,SDL_Window* win) : Feld(x,y,win){
        Typ = 1;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
};
class Wasser :public Feld{
public:
    Wasser(int x, int y,SDL_Window* win) : Feld(x,y,win){
        Typ = 2;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
};
class Wald :public Feld{
public:
    Wald(int x, int y,SDL_Window* win) : Feld(x,y,win){
        Typ = 3;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
};
class Grass :public Feld{
public:
    Grass(int x, int y,SDL_Window* win) : Feld(x,y,win){
        Typ = 4;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
};
class Festung :public Feld{
public:
    Festung(int x, int y,SDL_Window* win) : Feld(x,y,win){
        Typ = 5;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
};

#endif
