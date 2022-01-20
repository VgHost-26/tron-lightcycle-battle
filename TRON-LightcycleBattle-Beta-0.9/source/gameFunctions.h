/*funkcje potrzebne do samej gry*/
void setGrid(){     //wyswietlenie pola gry oraz nadanie podstawowych wartosci tablicy
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    for(int i=0;i<sizeY;i++){
        for(int j=0;j<sizeX+17;j++){
            
            if( i==0  ||
                i==sizeY-1 ||
                j==0  ||
                j==sizeX-1 ||
                j==sizeX+16
                ){
                    SetConsoleTextAttribute(hConsole, 14);
                    //cout<<"* ";   
                    cout<<char(219)<<char(219); // ш 
                    grid[j][i]=1;
                }else if(j>=sizeX){
                    cout<<"  ";
                }else{
                    //cout<<"  ";
                    SetConsoleTextAttribute(hConsole, 13);
                    cout<<char(197)<<char(196); // ед
                }
        }
        cout<<endl;
        
    }
    SetConsoleTextAttribute(hConsole, defCol);

    Sleep(100);
}
void fill(int x, int y){   //wpisanie wartosci 1 do pola w tablicy
    grid[x/2][y]=1;
}
void clearGrid(){   //czyszczenie tablicy
    for(int i=0;i<sizeX;i++){
        for(int j=0;j<sizeY;j++){
            grid[i][j]=0;
        }
    }
}

