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
    protected:
        SDL_Surface *surf;
        SDL_Surface *Pieces;
        SDL_Surface *Auswahlpic;
        SDL_Rect Rect;
        SDL_Rect source;
        SDL_Rect dest;
    public:
        int x;
        bool Auswahl;
        int y;
        int Feld_x;
        int Feld_y;
        int Team;
        int Typ;
        Figur(int,int,int,SDL_Window*);
        ~Figur(){};
        void aktualisieren();
        void bewegen(int,int);
        bool aufFeld(int,int);
        //void bewegen(int,int);
};

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
        void setupmove(int,int,int);
};
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
}
void Spielfeld::getinput(SDL_Event e){
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Maus_x = e.button.x;
        int Maus_y = e.button.y;
        int Feld_x = (Maus_x-448)/128;
        int Feld_y = (Maus_y-28)/128;
        //std::cout << "("<< Feld_x << " , "<< Feld_y << ")"<< '\n';
        for (int i = 0; i < int(Figuren.size()); i++) {
            if(Figuren[i]->Auswahl){
                if (!(Figuren[i]->aufFeld(Feld_x,Feld_y))){
                    Figuren[i]->bewegen(Feld_x,Feld_y);
                    setupmove(Feld_x,Feld_y,i);
                }
                Figuren[i]->Auswahl = false;
                break;
            }else if (Figuren[i]->aufFeld(Feld_x,Feld_y)){
                Figuren[i]->Auswahl = true;
                //std::cout << "test" << '\n';
            }

        }
    }
}
void Spielfeld::setupmove(int x,int y,int currfig){
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
Figur::Figur(int xpos,int ypos,int Teamvar,SDL_Window *win){
    Auswahl = false;
    Feld_x = xpos;
    Feld_y = ypos;
    x = Feld_x*128;
    y = Feld_y*128;
    Team = Teamvar;
    source = {x: Typ, y: Team, w:128, h:128};
    Pieces = IMG_Load("Sources/Pieces/Pieces.png");
    Auswahlpic = IMG_Load("Sources/Auswahl.png");
    surf = SDL_GetWindowSurface(win);
}
void Figur::aktualisieren(){
    Rect = {x:x+448,y:y+28,w:128,h:128};
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    SDL_BlitSurface(Pieces,&source,surf,&Rect);
    if (Auswahl){
        SDL_BlitSurface(Auswahlpic,NULL,surf,&Rect);
    }
}
void Figur::bewegen(int xpos, int ypos){
    Feld_x = xpos;
    Feld_y = ypos;
    x = xpos*128;
    y = ypos*128;
    Auswahl = false;

}
bool Figur::aufFeld(int xpos, int ypos){
    if (xpos == Feld_x && ypos == Feld_y){
        return true;
    }else{
        return false;
    }
}
int main(int, char**) {
    SDL_Window *win = SDL_CreateWindow("Cyvasse", 0, 0, 1920 , 1080, SDL_WINDOW_SHOWN);
    Spielfeld Brett(win);
    SDL_Event Event;
    //vector<Figur*> *Figuren = &(Brett.Figuren.begin());
    while (true){
        while( SDL_PollEvent( &Event ) != 0 ) {
            Brett.getinput(Event);
            Brett.aktualisieren();
            for (int i = 0; i < int(Brett.Figuren.size()); i++) {
             Brett.Figuren[i]->aktualisieren();
            }
            SDL_UpdateWindowSurface(win);
            //std::cout << Brett.Figuren.size() << '\n';
        }
    }
    SDL_Delay(100000);
    return 1;

}
