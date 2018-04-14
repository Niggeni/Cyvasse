#ifndef TILES_H
#define TILES_H

#include"IMG.h"
using namespace std;



class Feld{
    protected:
        SDL_Surface *surf;

        SDL_Window *win;
        SDL_Rect source;
    public:
        int Typ;
        bool Auswahl;
        Feld(SDL_Window*);
        virtual ~Feld(){};
        void aktualisieren(int,int);
        virtual Feld * clone() { return new Feld(win); };
};
Feld::Feld(SDL_Window *winvar){
    win = winvar;
    surf = SDL_GetWindowSurface(win);

    Auswahl = false;

}
void Feld::aktualisieren(int Feld_x, int Feld_y){
    SDL_Rect dest = {x:Feld_x*128+448,y:Feld_y*128+28,w:128,h:128};
    SDL_BlitSurface(Tiles,&source,surf,&dest);
    if (Auswahl){
        SDL_BlitSurface(Auswahlpic,NULL,surf,&dest);
    }
}

class Berg :public Feld{
public:
    Berg(SDL_Window* win) : Feld(win){
        Typ = 0;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
    virtual Berg * clone() { return new Berg(win); };
};
class Wasser :public Feld{
public:
    Wasser(SDL_Window* win) : Feld(win){
        Typ = 1;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
    virtual Wasser * clone() { return new Wasser(win); };
};
class Wald :public Feld{
public:
    Wald(SDL_Window* win) : Feld(win){
        Typ = 2;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
    virtual Wald * clone() { return new Wald(win); };
};
class Grass :public Feld{
public:
    Grass(SDL_Window* win) : Feld(win){
        Typ = 3;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
    virtual Grass * clone() { return new Grass(win); };
};
class Festung :public Feld{
public:
    Festung(SDL_Window* win) : Feld(win){
        Typ = 4;
        source = {x:Typ*128,y:0,w:128,h:128};
    };
    virtual Festung * clone() { return new Festung(win); };
};

#endif
