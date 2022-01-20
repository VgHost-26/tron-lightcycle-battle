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


#include "systemFunctions.h"
#include "gameFunctions.h"
#include "menuFunctions.h"
#include "player.h"

    


int main(){
    SetConsoleTextAttribute(hConsole, defCol);
    setColors();
    setConsolSize();


    
    fstream plik;
    plik.open("playersConfig.txt"); 
    //odczytywanie danych o graczach
    
    string line{};
    string name{};
    int color=1;
    int tmp{},tmpp{};
    Player p1;
    Player p2;
    if(!plik.is_open()){
        plik.close();
        //cout<<"error"<<endl;

    }else{
        for(int j=0;j<2;j++){  
            name="";  
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
                //wpisanie danych do Player
            if(j==0){ 
                p1.setName(name);
                p1.setColor(color);
            
                
            }else{
                p2.setName(name);
                p2.setColor(color);
                
            }
        }
    }
    //maˆy sekret gdyby kt¢ry˜ z graczy nie wisaˆ swojeej nazwy lub plik si© nie otworzyˆ
    if(p1.name=="" && ((p2.name!= "Tron" && p2.name!= "tron") && p2.color!=3)){
        p1.setName("Tron");
        p1.setColor(3);
    }else if(p1.name=="" && ((p2.name!= "Clu" && p2.name!= "clu") && p2.color!=9)){
        p1.setName("Clu");
        p1.setColor(9);
    }else if(p1.name==""){
        p1.setName("Flinn");
        p1.setColor(1);
    }

    if(p2.name=="" && ((p1.name!= "Tron" && p1.name!= "tron") && p1.color!=3)){
        p2.setName("Tron");
        p2.setColor(3);
    }else if(p2.name=="" && ((p1.name!= "Clu" && p1.name!= "clu") && p1.color!=9)){
        p2.setName("Clu");
        p2.setColor(9);
    }else if(p2.name==""){
        p2.setName("Flinn");
        p2.setColor(1);
    }

    plik.close();

    
    ///=================GRA=============///
    
    
    bool valid=false;
    bool tnb=true;
    char tn='t';

    int key{};
    int speed=100;
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

            Sleep(400);
            
            
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

                if(key==105) p2.setDir(0);  //I
                if(key==108) p2.setDir(1);  //L
                if(key==107) p2.setDir(2);  //K
                if(key==106) p2.setDir(3);  //J


                

                Sleep(speed);     //predkosc
            }
            Sleep(500);
            clearGrid();    //czyszczenie tablicy
            updateScoreBoard(p1,p2);

            setCursorPosition(sizeX*2+4,10);
            cout<<"Naci˜nij by kontynuowa†";
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
        
       /* while(!valid){
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
        }*/
        
        clearLine(sizeX*2+4,10,24);
        if(confirm(sizeX*2 + 12, 10, 14, 15, 0, "Jeszcze raz")){
            tnb=1;
        }else{
            tnb=0;
        }
    }
   
    system("start menu.exe");
    return 0;
}