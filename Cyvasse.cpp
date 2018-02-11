#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 100, 25, 8*128, 8*128, SDL_WINDOW_SHOWN);
    SDL_Surface *surf;
    surf = SDL_GetWindowSurface(win);
    SDL_Surface *Pieces = IMG_Load("Sources/Dragon-head-silhouette/Pieces.png");
    SDL_Surface *Board = IMG_Load("Sources/Board.png");
    SDL_Rect Piecerect = {x: 0, y: 0, w:4*128, h:128};
    SDL_Rect Boardrect = {x: 0, y: 0, w:8*128, h:8*128};
    SDL_Rect dest = {x: 0, y: 0, w:128, h:128};;
    SDL_BlitSurface(Board, &Boardrect, surf, NULL);
    SDL_BlitSurface(Pieces, &Piecerect, surf, &dest);
    SDL_UpdateWindowSurface(win);
    SDL_Delay(100000);
    return 1;
} test
