
#ifndef PIECES_H
#define PIECES_H

// This is the content of the .h file, which is where the declarations go
class Figur{
    protected:
        SDL_Surface *surf;
        SDL_Surface *Pieces;
        SDL_Surface *Auswahlpic;
        SDL_Surface *Erlaubtpic;
        SDL_Rect Rect;
        SDL_Rect source;
        int Feld_x;
        int Feld_y;
        int Team;
        int Typ;
        int Mobility;
    public:
        int numMoves;
        bool Auswahl;
        Figur(int,int,int,SDL_Window*);
        virtual ~Figur(){};
        void aktualisieren();
        void bewegen(int,int);
        bool aufFeld(int,int);
        virtual bool zugErlaubt(int,int);
        //void bewegen(int,int);
};

Figur::Figur(int xpos,int ypos,int Teamvar,SDL_Window *win){
    Auswahl = false;
    Feld_x = xpos;
    Feld_y = ypos;
    Team = Teamvar;
    Mobility = 1;
    numMoves = 0;
    source = {x: Typ, y: Team, w:128, h:128};
    Pieces = IMG_Load("Sources/Pieces/Pieces.png");
    Auswahlpic = IMG_Load("Sources/Auswahl.png");
    Erlaubtpic = IMG_Load("Sources/erlaubt.png");
    surf = SDL_GetWindowSurface(win);
}
void Figur::aktualisieren(){
    Rect = {x:Feld_x*128+448,y:Feld_y*128+28,w:128,h:128};
    SDL_Rect erlaubteFelder;
    source = {x: 128*Typ, y: 128*Team, w:128, h:128};
    SDL_BlitSurface(Pieces,&source,surf,&Rect);
    if (Auswahl){
        SDL_BlitSurface(Auswahlpic,NULL,surf,&Rect);
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
class King :public Figur{
public:
    King(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
        Typ = 0;
    };
    virtual bool zugErlaubt(int,int);
};
class Dragon :public Figur{
    public:
        Dragon(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 1;
        };
        virtual bool zugErlaubt(int,int);
};
class Heavy_Cav :public Figur{
    public:
        Heavy_Cav(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 2;
            Mobility = 2;
        };
        virtual bool zugErlaubt(int,int);
};
class Light_Cav :public Figur{
    public:
        Light_Cav(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 3;
            Mobility = 3;
        };
        virtual bool zugErlaubt(int,int);
};
class Elephant :public Figur{
    public:
        Elephant(int xpos,int ypos,int Teamvar,SDL_Window *win): Figur(xpos,ypos,Teamvar,win){
            Typ = 4;
        };
        virtual bool zugErlaubt(int,int);
};

void Figur::bewegen(int xpos, int ypos){
    Feld_x = xpos;
    Feld_y = ypos;
    numMoves++;
    if (numMoves >= Mobility){
        Auswahl = false;
        numMoves = 0;
    }
}
bool Figur::aufFeld(int xpos, int ypos){
    if (xpos == Feld_x && ypos == Feld_y){
        return true;
    }else{
        return false;
    }
}
bool Figur::zugErlaubt(int xpos,int ypos){
    if (xpos >=0 && xpos < 8&&ypos >=0 && ypos < 8&& !(aufFeld(xpos,ypos))){
        return true;
    }
    else{
        return false;
    }
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
// This is the end of the header guard
#endif
