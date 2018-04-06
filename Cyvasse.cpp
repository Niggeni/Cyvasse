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
        void getinput(const Uint8*);
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
void Spielfeld::getinput(const Uint8 *keystate){
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
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    Rect = {x:x*128+448,y:y*128+28,w:128,h:128};
    SDL_BlitSurface(Pieces,&source,surf,&Rect);
}
void Figur::bewegen(int xpos, int ypos){
    x = xpos;
    y = ypos;
}
class Dragon :public Figur{
    public:
        Dragon(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 1;
        };
};
int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    Spielfeld Brett(win);
    // vector<Figur*> Figuren;
    //
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0;j<2;j++){
    //         Figur *currfig = new Figur(i,j + j*(7-j),j,i,win);
    //         Figuren.push_back(currfig);
    //     }
    // }
    Dragon Dragon_White(4,1,1,win);
    while (true){
        Dragon_White.aktualisieren();
        Brett.aktualisieren();
        // for (int i = 0; i < int(Figuren.size()); i++) {
        //     Figuren[i]->aktualisieren();
        // }
        // SDL_PumpEvents();
        // if (SDL_GetMouseState(NULL, NULL) || SDL_BUTTON(SDL_BUTTON_LEFT)) {
        //     std::cout << (SDL_BUTTON(SDL_BUTTON_LEFT));
        //     //SDL_Log("Mouse Button 1 (left) is pressed.");
        // }
        SDL_UpdateWindowSurface(win);
    }
    SDL_Delay(100000);
    return 1;

}
