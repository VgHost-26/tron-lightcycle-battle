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

#pragma comment(lib, "user32.lib")


const int sizeX = 42;
const int sizeY = 32;

const int defCol = 15;

int grid[sizeX][sizeY]{};


using namespace std;
//#include "funkcje.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
mt19937 gen(time(0));
uniform_int_distribution<int> dist(0,3);
uniform_int_distribution<int> dist_1(0,2);
uniform_int_distribution<int> dist_2(1,10);
uniform_int_distribution<int> randColor(1,12);


#include "systemFunctions.h"
#include "gameFunctions.h"
#include "player.h"
#include "AI.h"



    


int main(){
    SetConsoleTextAttribute(hConsole, defCol);
    setColors();
    setConsolSize();


    fstream plik;
    plik.open("playersConfig.txt"); 
    //zczytywanie danych o graczach
    if(!plik.is_open()){
        plik.close();
        cout<<"error"<<endl;

    }
    string line{};
    string name{};
    int color=1;
    int tmp{},tmpp{};
    int diffLvl{};
    getline(plik,line);
    for(int i=0;i<line.length();i++){   //odczyt danych
        if(line[i]!=';'){
            name+=line[i];
        }else{
            if(line.length()-i>2){
                tmp = (line[i+1]-48);
                tmpp =(line[i+2]-48);
                tmp*=10;
                color=tmp+tmpp;
            }else{
                color=line[i+1]-48;
            }
            break;
        }
        
    }
    plik>>diffLvl;
    if(name==""){
        name="Tron";
        color=3;
    }
   //Player p1{"Tron"};
    Player p1{name};
    AI_01 p2{"Program"};
    
    p1.setColor(color);
    int color2=1;
    do{
        color2=randColor(gen);
    }while(color2==color);
    
    p2.setColor(color2);
    
    
    bool valid=false;
    bool tnb=true;
    char tn='t';

    int key{};
    int speed=100;   //presdkosc mniej-szybciej
    bool end=false;

    hideCursor();
    

    while(tnb){
        while(!p1.isDead() && !p2.isDead()){
            setCursorPosition(0,0);
            setGrid();
            setScoreBoard(p1, p2);
            

            p1.resetPoz(0);
            p2.resetPoz(1);

            p1.update(0);
            p2.update(0);

            end=false;
            valid=false;

            Sleep(100);
            
            
            while(1){

                

                if(!p2.ruch()){
                    end=true;
                    p2.lifes--;
                    //break;
                }
                if(!p1.ruch()){
                    end=true;
                    p1.lifes--;
                // break;
                }
                if(end) break;



                p1.update(0);
                p2.update(0);

                key=getKey();

                if(key==119) p1.setDir(0);  //W
                if(key==100) p1.setDir(1);  //D
                if(key==115) p1.setDir(2);  //S
                if(key==97)  p1.setDir(3);  //A   
                /*
                if(key==105) p2.setDir(0);  //I
                if(key==108) p2.setDir(1);  //L
                if(key==107) p2.setDir(2);  //K
                if(key==106) p2.setDir(3);  //J
                */

                if(diffLvl==0) p2.changeDir_random();    //easy
                if(diffLvl==1) p2.changeDir_linear();    //normal
                if(diffLvl==2) p2.changeDir_spacer();    //hard
               
                                            //super hard

                //p2.displayBrain();

                Sleep(speed);     //predkosc
               
            }
            Sleep(500);
            clearGrid();    //czyszczenie tablicy
            updateScoreBoard(p1, p2);

            setCursorPosition(sizeX*2+4,10);
            cout<<"Naci˜nij by kontynuaowa†";
            _getch();
        }
        
        if(p1.isDead() && p2.isDead()){
            //remis
        }else if(p1.isDead()){
            p2.wins++;
        }else if(p2.isDead()){
            p1.wins++;
        }

        p1.resetLifes();
        p2.resetLifes();
        
        while(!valid){
            setCursorPosition(sizeX*2+4,10);
            cout<<"                        ";
            setCursorPosition(sizeX*2+4,10);
            cout<<"Jeszcze raz? [t/n]"<<endl;
            setCursorPosition(sizeX*2+4,11);
            cin>>tn;
            if(tn=='t' || tn=='T'){
                tnb=1;
                valid=true;
            }else if(tn=='n' || tn=='N'){
                tnb=0;
                valid=true;
            }else{
                valid=false;
            }
        }
    }
   
    system("start menu.exe");
    return 0;
}