/*plik ze Struktur¥ gracza*/
struct Player{
    string name;    //nazwa gracz
    int wins=0;       //wygrane
    int lifes=3;      //zycia
    int pozX=10;       //pozycja x
    int pozY=(sizeY-2)/2;       //pozycja y
    int dir=1;        //kierunek ruchu (0-gora; 1-prawo; 2-dol; 3-lewo)
    int dirPrev=1;   //poprzedni kierunek 
    int color;      //kolor 

    void setName(string n){
        name=n;
    }
    bool setDir(int d){    // ustawienie kierunku
        if(d==dir-2 || d==dir+2) return false;
        dirPrev=dir;
        dir=d;
        update(1);
        return true;
    }
    void setPoz(int x, int y){  //ustawienie pozycji
        pozX=x;
        pozY=y;
    }
    void setColor(int c){
        //1 white (flynn)   //7 default grey
        //2 blue            //8 yellow (abraxas)
        //3 green           //9 orange (clue)
        //4 cyan (tron)     //10 red   (guard)
        //5 pink            //12 vilet
        //6 magenta
        color=c;
    }   
    void resetPoz(int d){
        pozY=(sizeY-2)/2;
        if(d==0){
            pozX=10;
            dir=1; 
        }else{
            pozX=sizeX*2-20;
            dir=3;
        }
        
    }
    void resetLifes(){
        lifes=3;
    }
    bool isFree(int x,int y){      // spr czy pole jest puste
        if(grid[x/2][y]==1) return false;
        return true;
    }
    bool isDead(){   //czy ma jeszcze zycia
        if(lifes<=0){
            return true;
        }else{
            return false;
        }
    }
    bool ruch(){        //ruch o jedno pole jesli mozliwe
        if(outOfGrid()){
            return false;
        }else if(isFree(pozX, pozY)){
            fill(pozX,pozY);
            if(dir==0) pozY--;
            if(dir==1) pozX+=2;
            if(dir==2) pozY++;
            if(dir==3) pozX-=2;
            return true;
        }else{
            return false;
        }
    }
    bool outOfGrid(){       // czy poza polem
        if( pozX <= 1 || pozX >= (sizeX*2)-2 ||
            pozY <= 0 || pozY >= sizeY-1){
                return true;
        }else{
           return false;
        }
    }
    void update(int zm){       //wyswietlenie zmian
        
        setCursorPosition(pozX,pozY);
        SetConsoleTextAttribute(hConsole, color);    
        if(zm){
            if(dirPrev==1 && dir==0) cout<<char(188)<<" ";       // ¼
            if(dirPrev==1 && dir==2) cout<<char(187)<<" ";       // »
            if(dirPrev==0 && dir==3) cout<<char(187);            // »
            if(dirPrev==0 && dir==1) cout<<char(201)<<char(461); // É
            if(dirPrev==3 && dir==0) cout<<char(200);            // È
            if(dirPrev==3 && dir==2) cout<<char(201);            // É
            if(dirPrev==2 && dir==1) cout<<char(200)<<char(461); // È
            if(dirPrev==2 && dir==3) cout<<char(188);            // ¼
            
        }else{  
            if(dir==1 || dir==3) cout<<char(461)<<char(461); // ÍÍ
            if(dir==0 || dir==2) cout<<char(186);            // º
        }
        
        SetConsoleTextAttribute(hConsole, defCol);   //zmiana na domyslny kolor
    }
    //wyswietlanie informacji w kolorze gracza:
    void print(string words, int num){
        SetConsoleTextAttribute(hConsole, color);
        cout<<words<<num<<endl;
        SetConsoleTextAttribute(hConsole, defCol);
    }
    void print(string words){
        SetConsoleTextAttribute(hConsole, color);
        cout<<words<<endl;
        SetConsoleTextAttribute(hConsole, defCol);
    }
    void print(int number){
        SetConsoleTextAttribute(hConsole, color);
        cout<<number<<endl;
        SetConsoleTextAttribute(hConsole, defCol);
    }

};
//wyswietlanie informacji o graczach
void setScoreBoard(Player a, Player b){
    setCursorPosition(sizeX*2+12,2);
    a.print(a.name);
    setCursorPosition(sizeX*2+3,4);
    cout<<"¾ycia:   ";
    a.print(a.lifes);
    setCursorPosition(sizeX*2+3,6);
    cout<<"wygrane: ";
    a.print(a.wins);
   
   
    //cout.width(12);
    setCursorPosition(sizeX*2+23,2);
    b.print(b.name);
    setCursorPosition(sizeX*2+23,4);
    b.print(b.lifes);
    setCursorPosition(sizeX*2+23,6);
    b.print(b.wins);
   
}
void updateScoreBoard(Player a, Player b){
    setCursorPosition(sizeX*2+12,4);
    a.print(a.lifes);
    setCursorPosition(sizeX*2+12,6);
    a.print(a.wins);
   
    setCursorPosition(sizeX*2+23,4);
    b.print(b.lifes);
    setCursorPosition(sizeX*2+23,6);
    b.print(b.wins);

}
