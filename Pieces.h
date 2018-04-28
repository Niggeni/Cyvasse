
#ifndef PIECES_H
#define PIECES_H
#include "IMG.h"
#include "Tiles.h"

using namespace std;


class Figur{
    protected:
        SDL_Surface *surf;
        SDL_Rect Rect;
        SDL_Rect source;
        int Feld_x;
        int Feld_y;
        int Typ;
        int Mobility;
        vector<vector<Feld*>>* Felder;
    public:
        int Team;
        int numMoves;
        bool Auswahl;
        bool Fernkampf;
        bool platziert;
        Figur(int,int,int,vector<vector<Feld*>>*,SDL_Window*);
        virtual ~Figur(){};
        void aktualisieren();
        void legalanzeigen();
        bool bewegen(int,int);
        void platzieren(int,int);
        bool aufFeld(int,int);
        virtual bool zugErlaubt(int,int);
        virtual bool attack(int,int);
        bool platzierungErlaubt(int,int,int);
        //void bewegen(int,int);
};

Figur::Figur(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win){
    Auswahl = false;
    Feld_x = xpos;
    Feld_y = ypos;
    Team = Teamvar;
    Fernkampf = false;
    Mobility = 1;
    numMoves = 0;
    Felder = Feldervar;
    source = {x: Typ, y: Team, w:128, h:128};
    surf = SDL_GetWindowSurface(win);
    platziert = false;
}

class Rabble :public Figur{
    public:
        Rabble(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 0;
        };
        virtual bool zugErlaubt(int,int);
};
class Spearmen :public Figur{
    public:
        Spearmen(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 1;
        };
        virtual bool zugErlaubt(int,int);
};
class Crossbowmen :public Figur{
    public:
        Crossbowmen(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 2;
            Fernkampf = true;
        };
        virtual bool zugErlaubt(int,int);
        virtual bool attack(int,int);
};
class Light_Cav :public Figur{
public:
    Light_Cav(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
        Typ = 3;
        Mobility = 3;
    };
    virtual bool zugErlaubt(int,int);
};
class Heavy_Cav :public Figur{
    public:
        Heavy_Cav(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 4;
            Mobility = 2;
        };
        virtual bool zugErlaubt(int,int);
};

class Elephant :public Figur{
    public:
        Elephant(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 5;
        };
        virtual bool zugErlaubt(int,int);
};
class Catapult :public Figur{
    public:
        Catapult(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 6;
            Fernkampf = true;
        };
        virtual bool zugErlaubt(int,int);
        virtual bool attack(int,int);
};
class Trebuchet :public Figur{
    public:
        Trebuchet(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 7;
            Fernkampf = true;
        };
        virtual bool zugErlaubt(int,int);
        virtual bool attack(int,int);
};

class Dragon :public Figur{
    public:
        Dragon(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
            Typ = 8 ;
        };
        virtual bool zugErlaubt(int,int);
};

class King :public Figur{
public:
    King(int xpos,int ypos,int Teamvar,vector<vector<Feld*>>* Feldervar, SDL_Window *win): Figur(xpos,ypos,Teamvar,Feldervar,win){
        Typ = 9;
    };
    virtual bool zugErlaubt(int,int);
};

void Figur::aktualisieren(){
    Rect = {x:Feld_x*128+448,y:Feld_y*128+28,w:128,h:128};
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    SDL_BlitSurface(Pieces,&source,surf,&Rect);
    if (Auswahl){
        SDL_BlitSurface(Auswahlpic,NULL,surf,&Rect);
    }
}
void Figur::legalanzeigen(){
    SDL_Rect erlaubteFelder;
    if (Auswahl){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if(zugErlaubt(i,j)){
                    erlaubteFelder = {x:i*128+448,y:j*128+28,w:128,h:128};
                    SDL_BlitSurface(Erlaubtpic,NULL,surf,&erlaubteFelder);
                }
            }
        }
    }
}
bool Figur::bewegen(int xpos, int ypos){
    Feld_x = xpos;
    Feld_y = ypos;
    numMoves++;
    bool Zugbeendet = false;
    if (numMoves >= Mobility){
        Auswahl = false;
        numMoves = 0;
        Zugbeendet = true;
    }
    return(Zugbeendet);
}
void Figur::platzieren(int xpos, int ypos){
    Feld_x = xpos;
    Feld_y = ypos;
    platziert = true;
    //std::cout << Felder[xpos][ypos]->Typ << '\n';
}
bool Figur::aufFeld(int xpos, int ypos){
    if (xpos == Feld_x && ypos == Feld_y){
        return true;
    }else{
        return false;
    }
}
bool Figur::zugErlaubt(int xpos,int ypos){
    if (xpos >=0 && xpos < 8&&ypos >=0 && ypos < 8&& !(aufFeld(xpos,ypos)) && Felder[xpos][ypos]->Typ != 0){
        return true;
    }
    else{
        return false;
    }
}
bool Figur::platzierungErlaubt(int xpos,int ypos,int Player){
    if (xpos >=0 && xpos < 8&&ypos >=4- 4*Player && ypos < 8-4*Player&& !(aufFeld(xpos,ypos)) && Felder[ypos][xpos]->Typ != 0 ){
        std::cout << Felder[xpos][ypos]->Typ << '\n';
        return true;
    }
    else{
        return false;

    }
}
bool Figur::attack(int xpos,int ypos){
    return zugErlaubt(xpos,ypos);
}
bool Dragon::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (xpos == Feld_x || ypos == Feld_y || abs(xpos-Feld_x) == abs(ypos - Feld_y)){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool King::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Heavy_Cav::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Light_Cav::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Elephant::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Rabble::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Spearmen::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Crossbowmen::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Catapult::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Trebuchet::zugErlaubt(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return(Figur::zugErlaubt(xpos,ypos)&&erlaubt);
}
bool Crossbowmen::attack(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=1 && abs(ypos - Feld_y)<=1){
        erlaubt = true;
    }
    return erlaubt;
}
bool Catapult::attack(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=2 && abs(ypos - Feld_y)<=2){
        erlaubt = true;
    }
    return erlaubt;
}
bool Trebuchet::attack(int xpos, int ypos){
    bool erlaubt=false;
    if (abs(xpos-Feld_x) <=3 && abs(ypos - Feld_y)<=3){
        erlaubt = true;
    }
    return erlaubt;
}
#endif
