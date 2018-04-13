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
#include "Tiles.h"
//#include "Felder.h"
using namespace std;
class Spielfeld{
    private:
        SDL_Surface *surf;
        SDL_Surface *Feldimage;
        SDL_Surface *Back;
        SDL_Surface *Vorhang;
        SDL_Window *win;
        SDL_Rect source;
        SDL_Rect dest;
        int Phase;
        int Player;
    public:
        vector<Figur*> Figuren;
        vector<vector<Feld*>> Felder;
        Spielfeld(SDL_Window*);
        void aktualisieren();
        void getinput(SDL_Event);
        void schlagen(int,int,int);
        void figurinteract(int,int);
        void feldinteract(int,int);
        void aufbauen(int);
        void aufbauanzeige();
};
Spielfeld::Spielfeld(SDL_Window *winvar){
    win = winvar;
    surf = SDL_GetWindowSurface(win);
    dest =  {x:448,y:28,w:1920,h:1080};
    Feldimage = IMG_Load("Sources/Board.png");
    Back = IMG_Load("Sources/Back.png");
    Vorhang = IMG_Load("Sources/Landschaft/Vorhang.png");
    source  = {x:0, y: 0, w:8*128, h:8*128};
    Phase = 0;
    vector <Feld*> Tilessetup;
    Grass *Grasstile = new Grass(win);
    for (int i = 0; i < 8; i++) {
        Tilessetup.push_back(Grasstile);
    }
    for (int i = 0; i < 8; i++) {
        Felder.push_back(Tilessetup);
    }
}
void Spielfeld::aktualisieren() {
    //SDL_BlitSurface(Back,NULL,surf,NULL);
    SDL_BlitSurface(Feldimage,NULL,surf,NULL);
    for (int i = 0; i < int(Figuren.size()); i++) {
        Figuren[i]->aktualisieren();
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Felder[i][j]->aktualisieren(i,j);
        }
    }
    if(Phase<2){
        SDL_Rect dest = {x:448,y:Player*(512+50)-50,w:620,h:1024};
        SDL_BlitSurface(Vorhang,NULL,surf,&dest);
    }
}
void Spielfeld::aufbauen(int Playervar){
    // int nBerg = 6;
    // int nWasser = 5;
    // int nWald = 6;
    // int nFestung = 1;

    Berg Preview_Berg(win);
    Wasser Preview_Wasser(win);
    Wald Preview_Wald(win);
    Festung Preview_Festung(win);
    SDL_Event Event;
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            aktualisieren();
            Preview_Berg.aktualisieren(-2,0);
            Preview_Wasser.aktualisieren(-2,1);
            Preview_Wald.aktualisieren(-2,2);
            Preview_Festung.aktualisieren(-2,3);
            SDL_UpdateWindowSurface(win);
        }

    }

    Player = Playervar;
    // Figuren.push_back(new King(0,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Dragon(1,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Heavy_Cav(2,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Light_Cav(3,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Elephant(4,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Rabble(5,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Spearmen(6,Player + Player*(7-Player),Player,win));
    // Figuren.push_back(new Crossbowmen(7,Player + Player*(7-Player),Player,win));
}
void Spielfeld::figurinteract(int Feld_x, int Feld_y) {
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
void Spielfeld::feldinteract(int Feld_x, int Feld_y) {

    if(Feld_x == -2){
        Select = Feld_y;
    }
    // if (!(Select==-1)){
    //
    // }
}
void Spielfeld::getinput(SDL_Event e){
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Maus_x = e.button.x;
        int Maus_y = e.button.y;
        int Feld_x = (Maus_x-448)/128;
        int Feld_y = (Maus_y-28)/128;
        figurinteract(Feld_x,Feld_y);

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
void Spielfeld::aufbauanzeige(){

}
#endif
