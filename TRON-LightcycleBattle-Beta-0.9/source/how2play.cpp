#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <random> 
#include <ctime> 
#include <chrono> 
#include <cstdlib>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



const int defCol = 3;



#include "systemFunctions.h"


void typingPrint(string str){

    mt19937 gen(time(0));
    uniform_int_distribution<int> dist(10,20);


    int r=10;
    r=dist(gen);
    for(int i = 0; i < str.length(); i++){
        cout<<str[i];

        Sleep(10*r);
    }

}

int main(){
   
    setColors();
    setConsolSize();


    //setGridButCooler();
    //system("pause");

    //typingPrint("Witaj urzytkowniku...\n");

    SetConsoleTextAttribute(hConsole, defCol);
    char spChars[4]={
        char(197), // Å
        char(219), // Û 
        char(461), // Í 
        char(461)  // Í 
    };
    int colTb[4]={13,14,1,1};
    string line{};
    ifstream plik;
    plik.open("instrukcja.txt");

    if(plik.is_open()){
        int i=0;
        while(!plik.eof()){
            getline(plik,line);
            
            for(int j=0; j<line.length(); j++){
                if(line[j]=='#'){
                    SetConsoleTextAttribute(hConsole, colTb[i]);
                    cout<<spChars[i];
                    i++;
                    SetConsoleTextAttribute(hConsole, defCol);
                }else{
                    cout<<line[j];
                }
            }

            cout<<endl;

        }
        
       

    }else{
        cout<<"error"<<endl;
        //plik sie nie wczytal;
    }
    system("pause"); 
    plik.close();
    system("start menu.exe");

    return 0;
}