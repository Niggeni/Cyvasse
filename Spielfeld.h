#ifndef SPIELFELD_H
#define SPIELFELD_H
#include "Pieces.h"
#include "Tiles.h"
//using namespace std;
class Spielfeld{
    private:
        SDL_Surface *surf;
        SDL_Surface *Feldimage;
        SDL_Surface *Back;
        SDL_Surface *Vorhang;
        SDL_Surface *Ende;
        SDL_Surface *Endepressed;
        SDL_Surface *Attackpic;
        SDL_Surface *Attackpressed;
        SDL_Window *win;
        SDL_Rect source;
        SDL_Rect dest;
        int Player;
        bool Zugbeendet;
        bool Attack;
    public:
        int Phase;
        vector<Figur*> Figuren;
        vector<Figur*> Anzeigefiguren;
        vector<vector<Feld*>> Felder;
        vector<Feld*> Anzeigetiles;
        Spielfeld(SDL_Window*);
        void aktualisieren();
        int * getinput(SDL_Event);
        void schlagen(int,int,int);
        void figurinteract(int,int);
        void feldinteract(int,int);
        void aufbauen(int);
        void aufbauanzeige(int);
        int figurAufPos(int,int);
};
Spielfeld::Spielfeld(SDL_Window *winvar){
    win = winvar;
    Zugbeendet = false;
    Attack = false;
    surf = SDL_GetWindowSurface(win);
    dest =  {x:448,y:28,w:1920,h:1080};
    Feldimage = IMG_Load("Sources/Board.png");
    Back = IMG_Load("Sources/Back.png");
    Vorhang = IMG_Load("Sources/Landschaft/Vorhang.png");
    Ende = IMG_Load("Sources/END.png");
    Endepressed = IMG_Load("Sources/END_pressed.png");
    Attackpic = IMG_Load("Sources/Attack.png");
    Attackpressed = IMG_Load("Sources/Attack_pressed.png");
    source  = {x:0, y: 0, w:8*128, h:8*128};
    vector <Feld*> Tilessetup;
    Grass *Grasstile = new Grass(win);
    for (int i = 0; i < 8; i++) {
        Tilessetup.push_back(Grasstile);
    }
    for (int i = 0; i < 8; i++) {
        Felder.push_back(Tilessetup);
    }
    Anzeigetiles.push_back(new Grass(win));
    Anzeigetiles.push_back(new Berg(win));
    Anzeigetiles.push_back(new Wasser(win));
    Anzeigetiles.push_back(new Wald(win));
    Anzeigetiles.push_back(new Festung(win));
}
void Spielfeld::aktualisieren() {
    //SDL_BlitSurface(Back,NULL,surf,NULL);
    SDL_BlitSurface(Feldimage,NULL,surf,NULL);
    if(Zugbeendet){
        SDL_Rect Enddest = {x:1152+448,y:924+15,w:252,h:113};
        SDL_BlitSurface(Endepressed,NULL,surf,&Enddest);
    }
    else{
        SDL_Rect Enddest = {x:1152+448,y:924,w:256,h:128};
        SDL_BlitSurface(Ende,NULL,surf,&Enddest);
    }
    if(Attack){
        SDL_Rect Attackdest = {x:1152+448,y:796+15,w:252,h:113};
        SDL_BlitSurface(Attackpressed,NULL,surf,&Attackdest);
    }else{
        SDL_Rect Attackdest = {x:1152+448,y:796,w:256,h:128};
        SDL_BlitSurface(Attackpic,NULL,surf,&Attackdest);
    }
    for (int i = 0; i < int(Figuren.size()); i++) {
        Figuren[i]->aktualisieren();
        if(Phase != 0){
            Figuren[i]->legalanzeigen();
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Felder[i][j]->aktualisieren(i,j);
        }
    }

}
void Spielfeld::aufbauen(int Playervar){
    Player = Playervar;
    Phase = 0;
    Zugbeendet = false;
    // int nBerg = 6;
    // int nWasser = 5;
    // int nWald = 6;
    // int nFestung = 1;
    Anzeigefiguren.clear();
     Figuren.push_back(new King(-3,0,Player,win));
     Figuren.push_back(new Dragon(-3,1,Player,win));
     Figuren.push_back(new Heavy_Cav(-3,2,Player,win));
     Figuren.push_back(new Light_Cav(-3,3,Player,win));
     Figuren.push_back(new Elephant(-3,4,Player,win));
     Figuren.push_back(new Rabble(-3,5,Player,win));
     Figuren.push_back(new Spearmen(-3,6,Player,win));
     Figuren.push_back(new Crossbowmen(-3,7,Player,win));
     Figuren.push_back(new Catapult(-2,0,Player,win));
     Figuren.push_back(new Trebuchet(-2,1,Player,win));


    SDL_Event Event;
    while (!Zugbeendet){
        // std::cout << Zugbeendet << '\n';
        while( SDL_PollEvent( &Event ) != 0 ) {
            //cout<<Event.type<< " "<<SDLK_RETURN2<<endl;
            //aktualisieren();
            getinput(Event);
            aufbauanzeige(Player);
            SDL_UpdateWindowSurface(win);
        }


    }
}
void Spielfeld::figurinteract(int Feld_x, int Feld_y) {
    if(Phase == 0){
        for (int i = 0; i < int(Figuren.size()); i++) {
            if (Figuren[i]->aufFeld(Feld_x,Feld_y)){
                Figuren[i]->Auswahl = !Figuren[i]->Auswahl;
            }
            if(Figuren[i]->Auswahl){
                if (Figuren[i]->platzierungErlaubt(Feld_x,Feld_y,Player)){
                    Figuren[i]->platzieren(Feld_x,Feld_y);
                    Figuren[i]->Auswahl = false;
                }
            }

        }
    }
    else{
        for (int i = 0; i < int(Figuren.size()); i++) {
            if(Figuren[i]->Auswahl){
                if(figurAufPos(Feld_x,Feld_y) != -1){
                    if(Attack&&Figuren[i]->attack(Feld_x,Feld_y)){
                        if (!Figuren[i]->Fernkampf){
                            Figuren[i]->bewegen(Feld_x,Feld_y);
                        }
                        schlagen(Feld_x,Feld_y,i);
                    }
                }else if (Figuren[i]->zugErlaubt(Feld_x,Feld_y)){
                    Zugbeendet = Figuren[i]->bewegen(Feld_x,Feld_y);

                }
                if (Figuren[i]->numMoves == 0){
                    Figuren[i]->Auswahl = false;
                }
                Attack = false;

            }else if (Figuren[i]->aufFeld(Feld_x,Feld_y) && Figuren[i]->Team == Player){
                Figuren[i]->Auswahl = true;
            }

        }
        if(Zugbeendet){
            Player = 1- Player;
            Zugbeendet = false;
        }
    }
}
void Spielfeld::feldinteract(int Feld_x, int Feld_y) {
    int Select = -1;
    if(Feld_x == -1){
        Select = Feld_y;
    }
    if (Select >=0 && Select <int(Anzeigetiles.size())){
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
                //delete (Felder[Feld_x][Feld_y]);
                //Felder.erase();
                //std::cout << Felder.size() << '\n';
                Felder[Feld_x][Feld_y] = Anzeigetiles[i]->clone();
            }
        }
    }
}

int * Spielfeld::getinput(SDL_Event e){
    static int Input[3] = {0};
    if (Phase == 1){
        Zugbeendet = false;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int Maus_x = e.button.x;
        int Maus_y = e.button.y;
        int Feld_x = (Maus_x-64)/128 -3; //offset
        int Feld_y = (Maus_y-28)/128;
        if(Feld_y == 7 && (Feld_x == 9 || Feld_x ==10)){
            bool beendenerlaubt = true;
            for (int i = 0; i < int(Figuren.size()); i++) {
                if(!Figuren[i]->platziert){
                    beendenerlaubt = false;
                }
            }
            if(beendenerlaubt){
                Zugbeendet = true;
                Player = 1- Player;
                aktualisieren();
            }
        }
        else if(Feld_y == 6 && (Feld_x == 9 || Feld_x ==10)){
            Attack = !Attack;
        }
        else{
            figurinteract(Feld_x,Feld_y);
            feldinteract(Feld_x,Feld_y);
        }
        Input[0] = 1;
        Input[1] = Feld_x;
        Input[2] = Feld_y;
        //std::cout << Feld_x << " " << Feld_y<< '\n';
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
    Zugbeendet = true;
}
void Spielfeld::aufbauanzeige(int Player){
    aktualisieren();
    SDL_Rect dest = {x:448,y:Player*(512+50)-50,w:620,h:1024};
    SDL_BlitSurface(Vorhang,NULL,surf,&dest);
    for (int i = 0; i < int(Anzeigetiles.size()); i++) {
        Anzeigetiles[i]->aktualisieren(-1,i);
    }
}
int Spielfeld::figurAufPos(int x,int y){
    int Auswahl = -1;
    for (int i = 0; i < int(Figuren.size()); i++) {
        if(Figuren[i]->aufFeld(x,y)){
            Auswahl = i;
            break;
        }
    }
    return Auswahl;
}
#endif
