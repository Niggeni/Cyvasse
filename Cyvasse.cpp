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
class Figur{
    private:
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
        Figur(int,int,SDL_Window*);
        void aktualisieren();
        void bewegen(int,int);
};
Figur::Figur(int xpos,int ypos,,int Teamvar,int Typvar,SDL_Window *win){
    x = xpos;
    y = ypos;
    Team = Teamvar;
    Typ = Typvar;
    source = {x: 32*numx, y: 32*numy, w:32, h:32};
    Pieces = IMG_Load("Sources/Pieces/Pieces.png");
    surf = SDL_GetWindowSurface(win);
}
int main(int, char**) {
    std::cout << add(2,2) << '\n';
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    SDL_Surface *surf;
    surf = SDL_GetWindowSurface(win);
    SDL_Surface *Pieces = IMG_Load("Sources/Pieces/Pieces.png");
    SDL_Surface *Board = IMG_Load("Sources/Board.png");
    SDL_Rect Piecerect = {x: 0, y: 0, w:5*128, h:2*128};
    SDL_Rect Boardrect = {x:0, y: 0, w:8*128, h:8*128};
    SDL_Rect dest = {x: 300, y: 0, w:128, h:128};
    SDL_Rect Boarddest =  {x:300,y:0,w:1920,h:1080};
    SDL_BlitSurface(Board, &Boardrect, surf,&Boarddest);
    SDL_BlitSurface(Pieces, &Piecerect, surf, &dest);
    SDL_UpdateWindowSurface(win);
    SDL_Delay(100000);
    return 1;
}
