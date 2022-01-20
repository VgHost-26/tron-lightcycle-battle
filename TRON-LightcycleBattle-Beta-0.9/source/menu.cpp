#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <mmsystem.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

#include "systemFunctions.h"
#include "menuFunctions.h"





int main(){

    
    
    
    playSound("",0);
    //mciSendString(TEXT("play sounds/menuTheme.wav"), NULL, 0, NULL);

    setConsolSize();    //ustawienie czcionki konsoli i wˆ¥czenie peˆnego okna    
    hideCursor();       //ukrycie kursora konsoli (tego migaj¥cego paska)
    setColors();        //ustawienie kolor¢w konsoli

    //pobieranie wielko˜ci konsoli (do p¢«niejszego centrowania)
    CONSOLE_SCREEN_BUFFER_INFO csbi;    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int winWidth = csbi.dwMaximumWindowSize.X;
    int winHeight = csbi.dwMaximumWindowSize.Y;


    string table[4]={
        "ÉÍÍÍÍÍÍÍÍÍÍÍ»",    //top
        "º           º",    //sides
        "ÌÍÍÍÍÍÍÍÍÍÍÍ¹",    //separator
        "ÈÍÍÍÍÍÍÍÍÍÍÍ¼",    //bottom
    };

    string menuList[4]={
        "    Graj",
        " Jak gra†?",
        "   Opcje",
        "   Wyjd«"
    };
    string menuList2[2]={
        "    PvP   ",
        "    PvE   "
    };
    string playerSetList[2]={
        "   Nazwa   ",
        " <  ÍÍÍ  > "
    };
    string difficulty[3][1]={
        "<  ˆatwy  >",
        "<  ˜redni >",
        "<  trudny >"
    };

    int arrows[3]={1,3,5};
    int arrows2[1]={5};
    int arrows3[6]={2,4,5,6};
    int arrows4[6]={1,3,5,6};

    int k{};
    int selected{};
    int defCol=3;      //domyslny kolor menu
    int alertCol=10;      //informacje (czerwony)

    bool valid=false;   //zmienna do walidacji danych

    string playerName{};
    string playerNameTmp{};
    int playerColor;
    int diffLvl{};

    ofstream plik;
    plik.open("playersConfig.txt"); //plik w kt¢rym zapisane b©d¥ nazwy i kolor graczy
    

    //wyswietlanie logo    
    printLogo(defCol, middleCalc(winWidth, 113));    
    //SetConsoleTextAttribute(hConsole, 7);

    /*--------MENU------------*/


    
    generateTable(table, 4, middleCalc(winWidth, 14));
    buttonHelp(arrows, 3);


    
   
    select(menuList, 4, selected, defCol, 9, middleCalc(winWidth, 10));

    /*--------MENU 1------------*/
    while(1){
        
        
        k=getKey();
        if(k==72){              //Strzaˆka w g¢re
            if(selected>0){
                selected--;
                select(menuList, 4, selected, defCol, 9, middleCalc(winWidth, 10));
            }
        }else if(k==80){        //Strzaˆka w d¢ˆ
            if(selected<3){
                selected++;
                select(menuList, 4, selected, defCol, 9, middleCalc(winWidth, 10));
            }
            
        }else if(k==13){        //ENTER
            if(selected==0){    //graj
                /*-------------MENU 2 (pvp / pve)--------------------*/
                //system("cls");
                //printLogo(defCol, middleCalc(winWidth, 113));
                for(int ii=14;ii<25;ii++){ clearLine(0,ii,120);}
                setCursorPosition(0,14);
                
                generateTable(table, 2, middleCalc(winWidth, 14));
                buttonHelp(arrows4, 4);
                select(menuList2, 2, selected, defCol, 9, middleCalc(winWidth, 10));
                selected=0;
                while(1){
                    k=getKey();
                    if(k==72){              //Strzaˆka w g¢re
                        if(selected>0){
                            selected--;
                            select(menuList2, 2, selected, defCol, 9, middleCalc(winWidth, 10));
                        }
                    }else if(k==80){        //Strzaˆka w d¢ˆ
                        if(selected<1){
                            selected++;
                            select(menuList2, 2, selected, defCol, 9, middleCalc(winWidth, 10));
                        }
                        
                    }else if(k==13){        //ENTER
            
                        if(selected==0){     //PvP
                        
                            /*-------------MENU 3 (pobranie danych o graczu)--------------------*/
                            //system("cls");
                            //printLogo(defCol, middleCalc(winWidth, 113));
                            for(int ii=14;ii<25;ii++){ clearLine(0,ii,120);}
                
                            setCursorPosition(0,14);
                            
                            generateTable(table, 2, middleCalc(winWidth, 14));
                            
                            
                            for(int i=0;i<2;i++){       
                                if(i==0)playerSetList[0]="  Gracz 1  ";
                                if(i==1)playerSetList[0]="  Gracz 2  ";
                                
                                buttonHelp(arrows2, 1);
                                
                                selected=1;
                                select(playerSetList, 2, 1, 13, selected, middleCalc(winWidth, 10));
                                setCursorPosition(middleCalc(winWidth, -10),15+2);
                                cout<<"  ";
                                setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                cout<<"  ";
                                                        //ANCHOR wybranie nazwy
                                while(!valid){          // walidacja nazwy
                                    setCursorPosition(middleCalc(winWidth, -10),15);
                                    showCursor();
                                    // if(getKey()==27){
                                    //     system("start menu.exe");
                                    //     return 0;
                                    // }
                                    getline(cin,playerName);
                                    
                                    if(playerName.length()>8 || includeChar(playerName,';')){
                                        clearLine(middleCalc(winWidth, -46), 12, 46);
                                        clearLine(middleCalc(winWidth, -46), 13, 46);
                                        setCursorPosition(middleCalc(winWidth, -46), 13);
                                        SetConsoleTextAttribute(hConsole,alertCol);
                                        if(playerName.length()>8) cout<<"! Nazwa powinna by† nie dˆu¾sza ni¾ 8 znak¢w !";
                                        if(playerName.length()>8 && includeChar(playerName,';')) setCursorPosition(middleCalc(winWidth, -46), 12); 
                                        if(includeChar(playerName,';')) cout<<"! Nazwa nie mo¾e zawiera† znaku ˜rednika ';' !";
                                        SetConsoleTextAttribute(hConsole, defCol);
                                        
                                        clearLine(middleCalc(winWidth, -10), 15, playerName.length()+4);     //czyszczenie smieci po wpisaniu
                                        
                                        setCursorPosition(0,14);
                                        generateTable(table, 2, middleCalc(winWidth, 14));
                                        setCursorPosition(middleCalc(winWidth, -10),15);

                                        select(playerSetList, 2, 1, 13, selected, middleCalc(winWidth, 10));
                                        setCursorPosition(middleCalc(winWidth, -10),15+2);
                                        cout<<"  ";
                                        setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                        cout<<"  ";
                                        

                                    }else if(i==1 && playerName==playerNameTmp && playerName!=""){
                                            
                                        clearLine(middleCalc(winWidth, -46),12,46);
                                        clearLine(middleCalc(winWidth, -46),13,46);
                                        setCursorPosition(middleCalc(winWidth, -28),13);
                                        SetConsoleTextAttribute(hConsole,alertCol);
                                        cout<<"! Ta nazwa jest ju¾ zaj©ta !";
                                        SetConsoleTextAttribute(hConsole, defCol);

                                        setCursorPosition(0,14);
                                        generateTable(table, 2, middleCalc(winWidth, 14));
                                        setCursorPosition(middleCalc(winWidth, -10), 15);

                                        select(playerSetList, 2, 1, 13, selected, middleCalc(winWidth, 10));
                                        setCursorPosition(middleCalc(winWidth, -10), 15+2);
                                        cout<<"  ";
                                        setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                        cout<<"  ";

                                    }else{      //wszytskie dane podane prwidlowo
                                        valid=true;
                                        clearLine(middleCalc(winWidth, -46),12,46);
                                        clearLine(middleCalc(winWidth, -46),13,46);
                                    }
                                    
                                }
                                
                                //playerName=nameValidation(playerSetList,selected, alertCol, defCol)
                                valid=false;
                                
                                select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));
                                setCursorPosition(middleCalc(winWidth, -10),15+2);
                                cout<<"  ";
                                

                                hideCursor();
                                buttonHelp(arrows3,4);
                                playerSetList[0]=playerName;
                                playerNameTmp=playerName;
                                setCursorPosition(middleCalc(winWidth, -10),15);
                                cout<<"           ";
                                setCursorPosition(middleCalc(winWidth, -10),15);
                                int middle=(11/2)+(playerName.length()/2)+1;
                                cout.width(middle);
                                cout<<playerName;
                                

                                while(1){         //ANCHOR wybieranie koloru
                                    k=getKey();
                                
                                    if(k==75){              //Strzaˆka w lewo
                                        if(selected>1){
                                            selected--;
                                            cout.width(middle);
                                            select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));

                                            if(selected==1){
                                                setCursorPosition(middleCalc(winWidth, -10),15+2);
                                                cout<<"  "; 
                                            }
                                        }
                                    }else if(k==77){        //Strzaˆka w prawo
                                        if(selected<12){
                                            selected++;
                                            cout.width(middle);
                                            select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));

                                            if(selected==12){
                                                setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                                cout<<"  "; 
                                            }
                                        }
                                    }else if(k==13){    //ENTER
                                        if(i==1 && selected==playerColor){
                                            clearLine(middleCalc(winWidth, -46),13,46);
                                            setCursorPosition(middleCalc(winWidth, -28),13);
                                            SetConsoleTextAttribute(hConsole,alertCol);
                                            cout<<"! Ten kolor jest ju¾ zaj©ty !";
                                        }else{
                                            clearLine(middleCalc(winWidth, -46),13,46);
                                            playerColor=selected;
                                            break;
                                        }
                                        
                                    }else if(k==27){    //ESC

                                        system("start menu.exe");
                                        return 0;
                                    }
                                }
                                
                                plik<<playerName<<";"<<playerColor<<endl;   //zapisanie danych graczy

                            }

                            SetConsoleTextAttribute(hConsole,defCol);
                            plik.close();
                            system("start main.exe");
                            return 0;
                        }else if(selected==1){  //PvE

                            /*-------------MENU 3 (pobranie danych o graczu) PVE--------------------*/
                            // system("cls");
                            // printLogo(defCol, middleCalc(winWidth, 113));
                            for(int ii=14;ii<25;ii++){ clearLine(0,ii,120);}
                            setCursorPosition(0,14);
                            SetConsoleTextAttribute(hConsole,defCol);

                            generateTable(table, 3,  middleCalc(winWidth, 14));
                            buttonHelp(arrows2, 1);

                           // playerSetList[0]="   Nazwa   ";
                            selected=1;
                            select(playerSetList, 2, 1, 13, selected, middleCalc(winWidth, 10));
                            setCursorPosition(middleCalc(winWidth, -10),15+2);
                            cout<<"  ";
                            setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                            cout<<"  ";
                                                    //ANCHOR wybranie nazwy PVE
                            while(!valid){          // walidacja danych
                                setCursorPosition(middleCalc(winWidth, -10),15);
                                showCursor();
                                getline(cin,playerName);
                                
                                if(playerName.length()>8 || includeChar(playerName,';')){
                                    clearLine(middleCalc(winWidth, -46), 12, 46);
                                    clearLine(middleCalc(winWidth, -46), 13, 46);
                                    setCursorPosition(middleCalc(winWidth, -46),13);
                                    SetConsoleTextAttribute(hConsole,alertCol);
                                    if(playerName.length()>8) cout<<"! Nazwa powinna by† nie dˆu¾sza ni¾ 8 znak¢w !";
                                    if(playerName.length()>8 && includeChar(playerName,';')) setCursorPosition(middleCalc(winWidth, -46),12); 
                                    if(includeChar(playerName,';')) cout<<"! Nazwa nie mo¾e zawiera† znaku ˜rednika ';' !";
                                    SetConsoleTextAttribute(hConsole, defCol);
                                    
                                    clearLine(middleCalc(winWidth, -10),15,playerName.length()+4);     //czyszczenie smieci po wpisaniu
                                    
                                    setCursorPosition(0,14);
                                    generateTable(table, 3, middleCalc(winWidth, 14));
                                    setCursorPosition(middleCalc(winWidth, -10),15);

                                    select(playerSetList, 2, 1, 13, selected, middleCalc(winWidth, 10));
                                    setCursorPosition(middleCalc(winWidth, -10),15+2);
                                    cout<<"  ";
                                    setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                    cout<<"  ";
                                }else{
                                    valid=true;
                                    clearLine(middleCalc(winWidth, -46),12,46);
                                    clearLine(middleCalc(winWidth, -46),13,46);
                                }
                            }
                                
                            select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));
                            setCursorPosition(middleCalc(winWidth, -10),15+2);
                            cout<<"  ";
                            
                            hideCursor();
                            buttonHelp(arrows3,4);
                            playerSetList[0]=playerName;
                            playerNameTmp=playerName;
                            setCursorPosition(middleCalc(winWidth, -10),15);
                            cout<<"        ";
                            setCursorPosition(middleCalc(winWidth, -10),15);
                            int middle=(11/2)+(playerName.length()/2)+1;
                            cout.width(middle);
                            SetConsoleTextAttribute(hConsole, selected);
                            cout<<playerName;

                            while(1){         //ANCHOR wybieranie koloru PVE
                                k=getKey();
                                
                                if(k==75){              //Strzaˆka w lewo
                                    if(selected>1){
                                        selected--;
                                        cout.width(middle);
                                        select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));

                                        if(selected==1){
                                        setCursorPosition(middleCalc(winWidth, -10),15+2);
                                        cout<<"  "; 
                                        }
                                    }
                                }else if(k==77){        //Strzaˆka w prawo
                                    if(selected<12){
                                        selected++;
                                        cout.width(middle);
                                        select(playerSetList, 2, 1, selected, selected, middleCalc(winWidth, 10));

                                        if(selected==12){
                                            setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                            cout<<"  "; 
                                        }
                                    }
                                }else if(k==13){    //ENTER
                                    playerColor=selected;

                                    setCursorPosition(middleCalc(winWidth, -10)+8,15+2);
                                    cout<<"  ";
                                    setCursorPosition(middleCalc(winWidth, -10),15+2);
                                    cout<<"  "; 

                                    break;
                                }else if(k==27){    //ESC

                                    system("start menu.exe");
                                    return 0;
                                }
                            }


                            selected=0;
                            select(difficulty[selected], 1, 2, playerColor, 9, middleCalc(winWidth, 10), 2);
                            setCursorPosition(middleCalc(winWidth, -10),15+4);
                            cout<<"  ";
                            while(1){         //ANCHOR wybieranie trudno˜ci PVE
                                k=getKey();
                                
                                if(k==75){              //Strzaˆka w lewo
                                    if(selected>0){
                                        selected--;
                                        cout.width(middle);
                                        select(difficulty[selected], 1, 2, playerColor, 9, middleCalc(winWidth, 10), 2);

                                        if(selected==0){
                                            setCursorPosition(middleCalc(winWidth, -10),15+4);
                                            cout<<"  "; 
                                        }
                                    }
                                }else if(k==77){        //Strzaˆka w prawo
                                    if(selected<2){
                                        selected++;
                                        cout.width(middle);
                                        select(difficulty[selected], 1, 2, playerColor, 9, middleCalc(winWidth, 10), 2);

                                        if(selected==2){
                                            setCursorPosition(middleCalc(winWidth, -10)+9,15+4);
                                            cout<<"  "; 
                                        }
                                    }
                                }else if(k==13){    //ENTER
                                    diffLvl=selected;
                                    break;
                                }else if(k==27){    //ESC

                                    system("start menu.exe");
                                    return 0;
                                }
                            }
                                
                            plik<<playerName<<";"<<playerColor<<endl;   //zapisanie danych gracza
                            plik<<diffLvl;


                            system("start PVE.exe");
                            return 0;
                        }
                    }else if(k==27){
                        system("start menu.exe");
                        return 0;
                    }
                }
            }else if(selected==1){  //jak grac
                system("start how2play.exe");
                return 0;

            }else if(selected==2){  //opcje


            }else if(selected==3){  //exit
                select(menuList, 4, selected, defCol, defCol, middleCalc(winWidth, 10));

                if(confirm(middleCalc(winWidth, -8), 25, defCol, 9, true, "Na pewno?")) return 0;  //wyswietlenie ramki z zapytaniem "czy na pewno"

                select(menuList, 4, selected, defCol, 9, middleCalc(winWidth, 10));
                

            }

        }

        //72 /\
        //75 <
        //77 >
        //80 \/
        //13 ENTER
    }

    /**/
      
        
    


   
   
    
    return 0;
}