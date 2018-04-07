#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
#include "Pieces.h"
using namespace std;
class Spielfeld{
    private:
        SDL_Surface *surf;
        SDL_Surface *Feld;
        SDL_Surface *Back;
        SDL_Rect source;
        SDL_Rect dest;
    public:
        Spielfeld(SDL_Window*);
        void aktualisieren();
        void getinput(SDL_Event);
};
Spielfeld::Spielfeld(SDL_Window *win){
    surf = SDL_GetWindowSurface(win);
    dest =  {x:448,y:28,w:1920,h:1080};
    Feld = IMG_Load("Sources/Board.png");
    Back = IMG_Load("Sources/Back.png");
    source  = {x:0, y: 0, w:8*128, h:8*128};
}
void Spielfeld::aktualisieren(/* arguments */) {
    //SDL_BlitSurface(Back,NULL,surf,NULL);
    SDL_BlitSurface(Feld,NULL,surf,NULL);
}
void Spielfeld::getinput(SDL_Event e){
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Feld_x = (e.button.x-448)/128;
        int Feld_y = (e.button.y-28)/128;
        std::cout << Feld_y << '\n';
        std::cout << Feld_x << '\n';
    }
}
class Figur{
    protected:
        SDL_Surface *surf;
        SDL_Surface *Pieces;
        SDL_Rect Rect;
        SDL_Rect source;
        SDL_Rect dest;
        int x;
        int y;
        int Team;
        int Typ;
    public:
        Figur(int,int,int,SDL_Window*);
        void aktualisieren();
        void bewegen(int,int);
        //void bewegen(int,int);
};
Figur::Figur(int xpos,int ypos,int Teamvar,SDL_Window *win){
    x = xpos;
    y = ypos;
    Team = Teamvar;
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    Pieces = IMG_Load("Sources/Pieces/Pieces.png");
    surf = SDL_GetWindowSurface(win);
}
void Figur::aktualisieren(){
    Rect = {x:x*128+448,y:y*128+28,w:128,h:128};
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    SDL_BlitSurface(Pieces,&source,surf,&Rect);
}
void Figur::bewegen(int xpos, int ypos){
    x = xpos;
    y = ypos;
}
class King :public Figur{
public:
    King(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
        Typ = 0;
    };
};
class Dragon :public Figur{
    public:
        Dragon(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 1;
        };
};
class Heavy_Cav :public Figur{
    public:
        Heavy_Cav(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 2;
        };
};
class Light_Cav :public Figur{
    public:
        Light_Cav(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 3;
        };
};
class Elephant :public Figur{
    public:
        Elephant(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 4;
        };
};
int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    Spielfeld Brett(win);
    vector<Figur*> Figuren;
    SDL_Event Event;
    for (int j = 0;j<2;j++){
        Figuren.push_back(new King(0,j + j*(7-j),j,win));
        Figuren.push_back(new Dragon(1,j + j*(7-j),j,win));
        Figuren.push_back(new Heavy_Cav(2,j + j*(7-j),j,win));
        Figuren.push_back(new Light_Cav(3,j + j*(7-j),j,win));
        Figuren.push_back(new Elephant(4,j + j*(7-j),j,win));
    }
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            Brett.getinput(Event);
            Brett.aktualisieren();
            for (int i = 0; i < int(Figuren.size()); i++) {
             Figuren[i]->aktualisieren();
            }
            SDL_UpdateWindowSurface(win);
        }
    }
    SDL_Delay(100000);
    return 1;

}
