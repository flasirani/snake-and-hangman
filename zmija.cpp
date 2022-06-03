#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const int sirina=20;
const int visina=20;
struct rep{
    int repX,repY;
}r[100];
int x,y,voceX,voceY,rezultat;
int repN;
bool izgubio;
enum kretanje{stop=0,gore,dole,levo,desno};
kretanje kre;
void pocetak(){
    izgubio=false;
    x=sirina/2;
    y=visina/2;
    voceX=rand()%sirina;
    voceY=rand()%visina;
    rezultat=0;
}

void ispis(){
    system("cls");
    for(int i=0;i<sirina+2;i++)
        cout<<"#";
    cout<<endl;
    for(int i=0;i<visina;i++){
        for(int j=0;j<sirina;j++){
            if(j==0)
                cout<<"#";
            if(x==j && y==i)
                cout<<"O";
            else if(voceX==j && voceY==i)
                cout<<"V";
            else{
                bool ispisi=false;
                for(int k=0;k<repN;k++){
                    if(r[k].repX==j && r[k].repY==i){
                        cout<<"o";
                        ispisi=true;
                    }
                }
                if(!ispisi)
                    cout<<" ";
            }

            if(j==sirina-1)
                cout<<"#";

        }
        cout<<endl;
    }
    for(int i=0;i<sirina+2;i++)
        cout<<"#";
    cout<<endl;
    cout<<"Rezutat: "<<rezultat;
}
void unos(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
            kre=levo;
            break;
            case 's':
            kre=dole;
            break;
            case 'd':
            kre=desno;
            break;
            case 'w':
            kre=gore;
            break;
        }
    }
}
void logika(){
    int prX=r[0].repX;
    int prY=r[0].repY;
    int p2X,p2Y;
    r[0].repX=x;
    r[0].repY=y;
    for(int i=1;i<repN;i++){
            p2X=r[i].repX;
            p2Y=r[i].repY;
            r[i].repX=prX;
            r[i].repY=prY;
            prX=p2X;
            prY=p2Y;
    }
    switch(kre){
        case levo:
        x--;
        break;
        case desno:
            x++;
            break;
        case gore:
            y--;
            break;
        case dole:
            y++;
            break;
        default:
            break;
}
        if(x<0 || x>sirina || y<0 || y>visina)
            izgubio=true;
        for(int i=0;i<repN;i++){
            if(x==r[i].repX && y==r[i].repY)
                izgubio=true;
        }
        if(x==voceX && y==voceY){
            rezultat++;
            voceX=rand()%sirina;
            voceY=rand()%visina;
            repN++;
        }

    }
int main()
{
    pocetak();
    while(!izgubio){
        ispis();
        unos();
        logika();
    }
    return 0;
}
