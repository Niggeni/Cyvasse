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
        vector<Feld*> Anzeigetiles;
        Spielfeld(SDL_Window*);
        void aktualisieren();
        int * getinput(SDL_Event);
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

    Anzeigetiles.push_back(new Berg(win));
    Anzeigetiles.push_back(new Wasser(win));
    Anzeigetiles.push_back(new Wald(win));
    Anzeigetiles.push_back(new Festung(win));
    //Anzeigetiles.push_back(Anzeigetiles[1]->clone());

    SDL_Event Event;
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            aktualisieren();
            getinput(Event);
            for (int i = 0; i < int(Anzeigetiles.size()); i++) {
                Anzeigetiles[i]->aktualisieren(-2,i);
            }
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
    int Select = -1;
    if(Feld_x == -2){
        Select = Feld_y;
    }
    if (Select >=0 && Select <4){
        for (int i = 0; i < int(Anzeigetiles.size()); i++) {
            if(i==Select){
                continue;
            }
            Anzeigetiles[i]->Auswahl = false;
        }
        Anzeigetiles[Select]->Auswahl = ! Anzeigetiles[Select]->Auswahl;
    }
    else if (Feld_x>=0&& Feld_x < 8 && Feld_y>=0&& Feld_y < 8){
        for (int i = 0; i < int(Anzeigetiles.size()); i++) {
            if(Anzeigetiles[i]->Auswahl){
                Felder[Feld_x][Feld_y] = Anzeigetiles[i]->clone();
            }
        }
    }
}
int * Spielfeld::getinput(SDL_Event e){
    static int Input[3] = {0};

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Maus_x = e.button.x;
        int Maus_y = e.button.y;
        int Feld_x = (Maus_x-64)/128 -3; //offset
        int Feld_y = (Maus_y-28)/128;
        figurinteract(Feld_x,Feld_y);
        feldinteract(Feld_x,Feld_y);
        Input[0] = 1;
        Input[1] = Feld_x;
        Input[2] = Feld_y;
    }
    return Input; //noch nicht benutzt
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
