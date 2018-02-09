#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <math.h>
using namespace std;
struct Texturen{
    SDL_Surface *Bild;
    SDL_Rect Rect;
};
class Spielfeld{
    private:
        SDL_Surface *surf;
        SDL_Surface *fruits;
        SDL_Surface *tiles;
        SDL_Rect Rect;
        SDL_Rect source;
        SDL_Rect dest;
;
    public:
        int Y;
        int X;
        vector< vector<char> > Karte;
        Spielfeld(int,int,vector<vector<char> >,SDL_Window*);
        void aktualisieren();
        //void aendern(int,int,char);
};
Spielfeld::Spielfeld(int Xlen,int Ylen,vector<vector<char> > Kartenvec,SDL_Window *win){
    X = Xlen;
    Y = Ylen;
    Karte = Kartenvec;
    fruits = IMG_Load("Tag10/bilder/fruit.png");
    tiles = IMG_Load("Tag10/bilder/tiles.png");
    surf = SDL_GetWindowSurface(win);
}

void Spielfeld::aktualisieren(){
    SDL_Surface *currentfig;
    int numx;
    int numy;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            dest = {x: i*32, y: j*32, w:32, h:32};
            switch (Karte[i][j]) {
                case '#':
                    numx = 1;
                    numy = 1;
                    currentfig = tiles;
                break;
                case '_':
                    numx = 0;
                    numy = 1;
                    currentfig = tiles;
                break;
                case 'b':
                    numx = 0;
                    numy = 0;
                    currentfig = fruits;
                break;
                case '*':
                    numx = 0;
                    numy = 0;
                    currentfig = tiles;
                break;
                case '.':
                    numx = 1;
                    numy = 2;
                    currentfig = tiles;
                break;
            };
            source = {x: 32*numx, y: 32*numy, w:32, h:32};
            SDL_BlitSurface(currentfig, &source, surf, &dest);
        }
    }
}
class Viech{
    protected:
        bool god;
        int x;
        int y;
        int Punkte;
        SDL_Surface *surf;
        SDL_Surface *Bild;
        SDL_Rect source;
        Spielfeld *Map;
        virtual void bewegen(int, int);
        virtual bool checkmove(int,int);
    public:
        Viech(SDL_Window*,Spielfeld*);
        void aktualisieren();
};

Viech::Viech(SDL_Window* win,Spielfeld* Kartvar){
    Map = Kartvar;
    x = rand()%(25*Map->X)+32;
    y = rand()%(25*Map->Y)+32;

    surf = SDL_GetWindowSurface(win);
    Bild = IMG_Load("Tag10/bilder/tiles.png");

    Punkte = 0;
    god = false;
    source = {x: 32*1, y: 32*3, w:32, h:32};
}
bool Viech::checkmove(int vx,int vy) {
    int newposx = (x+vx*16);
    int newposy = (y+vy*16);
    if(Map->Karte[newposx/32][newposy/32] != '#'||god ==true){
        return true;
    }else{
        return false;
    }
}

void Viech::bewegen(int vx, int vy){
    if(checkmove(vx,vy)){
        x += vx;
        y += vy;
    }
}
void Viech::aktualisieren(){
    SDL_Rect Rect = {x:x-16,y:y-16,w:32,h:32};
    SDL_BlitSurface(Bild,&source,surf,&Rect);
}
class PacMan :public Viech{
    private:
        int counter = 0;
    public:
        PacMan(SDL_Window* win,Spielfeld* Kartvar): Viech(win,Kartvar){x = 7*32+16;y=4*32+16;god = true;};
        void getinput(const Uint8 *);
        void bewegen(int,int);
};
void PacMan::getinput(const Uint8 *keystate){
    int vx=0;
    int vy=0;
    counter++;
    source.x=32*((counter/16)%3);
    if (keystate[SDL_SCANCODE_D]) {
        vx = 1;
        source.y= 32*3;
    }
    if (keystate[SDL_SCANCODE_A]) {
        vx = -1;
        source.y= 32*4;
    }
    if (keystate[SDL_SCANCODE_W]) {
        vy = -1;
        source.y= 32*6;
    }
    if (keystate[SDL_SCANCODE_S]) {
        vy = 1;
        source.y= 32*5;
    }
    if (vx == vy){
        source.x=1*32;
    }
    bewegen(vx,vy);
}
void PacMan::bewegen(int vx,int vy){
    Viech::bewegen(vx,vy);
    if(Map->Karte[(x)/31][(y)/31] == '.'){
        Map->Karte[(x)/31][(y)/31] = '_';
        Punkte +=1;
        cout << "Punkte:" << Punkte<<'\n';
    }
    if(Map->Karte[(x)/31][(y)/31] == 'b'){
        Map->Karte[(x)/31][(y)/31] = '_';
        Punkte +=25;
        cout << "Punkte:" << Punkte<<'\n';
    }
}
class Geist :public Viech{
    private:
        int currvx;
        int currvy;
        int langsamkeit;
    public:
        void bewegen();
        Geist(SDL_Window* win,Spielfeld* Kartvar): Viech(win,Kartvar){
            source = {x: 32*2, y: 32*8, w:32, h:32};
            currvx = 1;
            currvy = 0;
            langsamkeit = 10;
            //god = true;
        };
};
void Geist::bewegen(){


    int hilfsvx = currvx;
    int hilfsvy = currvy;
    do{
        int ereignis = rand()%1000;
        if (ereignis >1000-langsamkeit){
            currvx = rand() %3 -1;
            currvy = 0;
        }
        if( ereignis < langsamkeit){
            currvy = rand() %3 -1;
            currvx = 0;
        }
        if (currvx ==0 && currvy == 0){
            currvx = hilfsvx;
            currvy = hilfsvy;
        }
    }while(!checkmove(currvx,currvy));
    Viech::bewegen(currvx,currvy);
}
int main(int, char**) {
    srand(time(NULL));
    int X = 16;
    int Y = 16;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    vector<vector<char> > spielfeld(X, vector<char>(Y));
    spielfeld = {
  {'#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#'},
  {'#', 'b', '.', '.', '.', '.', 'b', '.','#', 'b', '.', '.', '.', '.', 'b', '#'},
  {'#', '.', '.', '.', '.', '#', '.', '.','#', '.', '#', '#', '.', '#', '.', '#'},
  {'#', '.', '.', '.', '.', '#', '.', '.','.', '.', '.', '.', '.', '#', '.', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.','#', '.', '#', '.', '.', '.', '.', '#'},
  {'#', '.', '#', '.', '#', '#', '.', '.','#', '.', '#', '.', '#', '#', '.', '#'},
  {'#', 'b', '.', '.', '.', '.', 'b', '.','#', 'b', '.', '.', '.', '.', 'b', '#'},
  {'#', '#', '#', '#', '*', '#', '#', '.','#', '#', '#', '#', '*', '#', '#', '#'},
  {'#', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '#'},
  {'#', 'b', '.', '.', '.', '.', 'b', '.','#', 'b', '.', '.', '.', '.', 'b', '#'},
  {'#', '.', '#', '#', '.', '#', '.', '.','#', '.', '#', '#', '.', '#', '.', '#'},
  {'#', '.', '.', '.', '.', '#', '.', '.','#', '.', '.', '.', '.', '#', '.', '#'},
  {'#', '.', '#', '.', '.', '.', '.', '.','#', '.', '#', '.', '.', '.', '.', '#'},
  {'#', '.', '#', '.', '#', '#', '.', '.','.', '.', '#', '.', '#', '#', '.', '#'},
  {'#', 'b', '.', '.', '.', '.', 'b', '.','#', 'b', '.', '.', '.', '.', 'b', '#'},
  {'#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#'}
};
    vector< vector<char> > Karte;
    for (int i = 0; i < Y; i++) {
        Karte.push_back(vector<char>(X, '#'));
    }
    SDL_Window *win = SDL_CreateWindow("ManPac", 0, 25, X*32, Y*32, SDL_WINDOW_SHOWN);
    Spielfeld Map(X,Y,spielfeld,win);
    PacMan Spieler(win,&Map);
    vector<Geist*> Geister;
    for (int i = 0; i < 5; i++) {
        Geist *Spookygeist = new Geist(win,&Map);
        Geister.push_back(Spookygeist);
    }
    while (true) {
        SDL_PumpEvents();
        Map.aktualisieren();
        Spieler.getinput(keystate);
        Spieler.aktualisieren();
        for (int i = 0; i < 5; i++) {
            Geister[i]->bewegen();
            Geister[i]->aktualisieren();
        }
        SDL_UpdateWindowSurface(win);
        SDL_Delay(.1);
    }

    return 1;
}
