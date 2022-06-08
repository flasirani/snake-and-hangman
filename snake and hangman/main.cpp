#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
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

void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();

    if (printBottom)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}
bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}
string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}
void DrawHangman(int guessCount = 0)
{
    if (guessCount >= 1)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 2)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 3)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 4)
        PrintMessage("/  ", false, false);

    if (guessCount == 5)
        PrintMessage("/| ", false, false);

    if (guessCount >= 6)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount >= 7)
        PrintMessage("|", false, false);
    else
        PrintMessage("", false, false);

    if (guessCount == 8)
        PrintMessage("/", false, false);

    if (guessCount >= 9)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}
void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
    PrintMessage("Available letters");
    PrintLetters(taken, 'A', 'M');
    PrintLetters(taken, 'N', 'Z');
}
int drugimeni(){
    int p;
    cin>>p;
    return p;
}
int meni(){
    system("cls");
    cout << "     ____   _        ___  "<< endl;
cout << "    |__  ) (_)      /_ |   "<< endl;
cout << "       ) |  _ _ ___  | |   "<< endl;
cout << "      / /  | | '_  ) | |   "<< endl;
cout << "     / /_  | | | | |_| |_  "<< endl;
cout << "  __|____|_|_|_|_|_|_____| "<< endl;
cout << " |_   _/ ____|  __  ) ____|"<< endl;
cout << "   | || |  __| |__) | |__   "<< endl;
cout << "   | || | |_ |  __ {|  __|  "<< endl;
cout << "  _| || |__| | |  | | |___ "<< endl;
cout << " |_____)_____|_|  |_|_____|" << endl;

cout<< "" <<endl;
cout<< "       1. ZMIJICA" <<endl;
cout<< "       2. VESALICA" <<endl;
cout<< "       3. NAPUSTI IGRU" <<endl;
int q;
cin>>q;
return q;
}
void pocetak(){
    repN=0;
    kre=stop;
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
int main(){
int h;
while(1){
h=meni();
    if(h==1){
    pocetak();
    while(!izgubio){
        ispis();
        unos();
        logika();
    }
    system("cls");

    if(drugimeni()==2)
        break;
    }
    if(h==2){
        srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess = LoadRandomWord("rijeci.txt");
    int tries = 0;
    bool win = false;
    do
    {
        system("cls");
        PrintMessage("VESALICA");
        DrawHangman(tries);
        PrintAvailableLetters(guesses);
        PrintMessage("Pogadjaj rec");
        win = PrintWordAndCheckWin(wordToGuess, guesses);

        if (win)
            break;

        char x;
        cout << ">"; cin >> x;

        if (guesses.find(x) == string::npos)
            guesses += x;

        tries = TriesLeft(wordToGuess, guesses);

    } while (tries < 10);

    if (win)
        PrintMessage("POBEDA");
    else
        PrintMessage("LOS SI");
    if(drugimeni()==2)
        break;
    }
    if(h==3)
        break;
}
}
