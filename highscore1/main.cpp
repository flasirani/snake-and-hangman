#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    int w[100];
    ofstream fout;
    fout.open("highscore1.dat", ios::binary);
    if(!fout)
        cout<<"nista";
    else{
        for(int i=0;i<100;i++){
            w[i]=i+1;
        }
        fout.write((char*)w,sizeof w);
    }
    fout.close();
    int x;
    vector <int> highscore2;
    ifstream fin;
    fin.open("highscore1.dat", ios::binary);
    while(1){
    fin.read((char*) &x, sizeof(x));
        if(fin.eof())
            break;
        highscore2.push_back(x);
        }
    for(int i=0;i<sizeof highscore2;i++){
        for(int j=0;j<sizeof highscore2-1-i;j++){
            int pom=highscore2[j];
            highscore2[j]=highscore2[j+1];
            highscore2[j+1]=pom;
        }
    }
    for(int i=0;i<15;i++)
        cout<<highscore2[i]<<endl;
    fin.close();
    return 0;
}
