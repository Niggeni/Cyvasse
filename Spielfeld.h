// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef SPIELFELD_H
#define SPIELFELD_H
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
        vector<Figur*> Figuren;
        Spielfeld(SDL_Window*);
        void aktualisieren();
        void getinput(SDL_Event);
        void schlagen(int,int,int);
};
Spielfeld::Spielfeld(SDL_Window *win){
    surf = SDL_GetWindowSurface(win);
    dest =  {x:448,y:28,w:1920,h:1080};
    Feld = IMG_Load("Sources/Board.png");
    Back = IMG_Load("Sources/Back.png");
    source  = {x:0, y: 0, w:8*128, h:8*128};
    for (int j = 0;j<2;j++){
        Figuren.push_back(new King(0,j + j*(7-j),j,win));
        Figuren.push_back(new Dragon(1,j + j*(7-j),j,win));
        Figuren.push_back(new Heavy_Cav(2,j + j*(7-j),j,win));
        Figuren.push_back(new Light_Cav(3,j + j*(7-j),j,win));
        Figuren.push_back(new Elephant(4,j + j*(7-j),j,win));
    }
}
void Spielfeld::aktualisieren() {
    //SDL_BlitSurface(Back,NULL,surf,NULL);
    SDL_BlitSurface(Feld,NULL,surf,NULL);
    for (int i = 0; i < int(Figuren.size()); i++) {
        Figuren[i]->aktualisieren();
    }
}
void Spielfeld::getinput(SDL_Event e){
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Maus_x = e.button.x;
        int Maus_y = e.button.y;
        int Feld_x = (Maus_x-448)/128;
        int Feld_y = (Maus_y-28)/128;
        //std::cout << "("<< Maus_x << " , "<< Maus_y << ")"<< '\n';
        for (int i = 0; i < int(Figuren.size()); i++) {
            if(Figuren[i]->Auswahl){
                if (Figuren[i]->zugErlaubt(Feld_x,Feld_y)){
                    Figuren[i]->bewegen(Feld_x,Feld_y);
                    schlagen(Feld_x,Feld_y,i);
                }else if (Figuren[i]->numMoves == 0){
                    Figuren[i]->Auswahl = false;
                }
            }else if (Figuren[i]->aufFeld(Feld_x,Feld_y)){
                Figuren[i]->Auswahl = true;
                //std::cout << "test" << '\n';
            }

        }
    }
}
void Spielfeld::schlagen(int x,int y,int currfig){
    for (int i = 0; i < int(Figuren.size()); i++) {
        if (i==currfig){
            continue;
        }else if (Figuren[i]->aufFeld(x,y)){
            delete Figuren[i];
            Figuren.erase(Figuren.begin()+i);
            break;
            //std::cout << Figuren.size() << '\n';
        }
    }
}
#endif
