/* to samo co PLayer.h z wyj¥tkiem kilku funkcji odpowiedzialnych za 
samodzielne sterowanie pojazdem */
struct AI_01{
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
        if(d==(-1)) d=3;
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
            fill(pozX, pozY);
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
            if(dir==1 || dir==3) cout<<char(461)<<char(461); // ?
            if(dir==0 || dir==2) cout<<char(186);            // ?
        }
        
        SetConsoleTextAttribute(hConsole, defCol);   //zmiana na domyslny kolor
    }  
    /*===============================================*/ 
    //ANCHOR "m¢zgi" komputera:

    void displayBrain(){    //wyswwietlanie informacji (potrzebne tylko do testow co "widzi" komputer)
        
        setCursorPosition(sizeX*2+2,13);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,13);
        cout<<"top: "<<countDist(0);

        setCursorPosition(sizeX*2+2,14);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,14);
        cout<<"rig: "<<countDist(1);

        setCursorPosition(sizeX*2+2,15);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,15);
        cout<<"bot: "<<countDist(2);

        setCursorPosition(sizeX*2+2,16);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,16);
        cout<<"lef: "<<countDist(3);

        setCursorPosition(sizeX*2+2,17);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,17);
        cout<<"X: "<<pozX/2;

        setCursorPosition(sizeX*2+2,18);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,18);
        cout<<"Y: "<<pozY;
        
    }

    void displayBrain(int a, int b, int c){
        
        setCursorPosition(sizeX*2+2,13);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,13);
        cout<<"z1: "<<a;

        setCursorPosition(sizeX*2+2,14);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,14);
        cout<<"z2: "<<b;

        setCursorPosition(sizeX*2+2,15);
        cout<<"             ";
        setCursorPosition(sizeX*2+2,15);
        cout<<"z3: "<<c;

        
    }
    

    int countDist(int d){       // liczenie dystansu od miejsca gracza do pierwszej 1 w kierunku 'd' 
        int ile{};
        int i=1;
        
        if(d==0){
            while(grid[pozX/2][pozY-i]==0){
                ile++;
                i++;
            }
            return ile;

        }else if(d==1){
            while(grid[(pozX+i)/2][pozY]==0){
                ile++;
                i++;
            }
            return ile/2;

        }else if(d==2){
            while(grid[pozX/2][pozY+i]==0){
                ile++;
                i++;
            }
            return ile;
            
        }else if(d==3){
            while(grid[(pozX-i)/2][pozY]==0){
                ile++;
                i++;
            }
            return ile/2;
        }
        
        return ile;
    }
    
    void changeDir_random(){  //losowy (najbardziej bez sensu) 
        setDir(dist(gen));
    }

    void changeDir_linear(){    //ANCHOR "liniowy" por¢wnuje prawo lewo i ocenia kt¢ry skr©t jest bardziej opˆacalny (˜redni)

        int rn{};
        int top = countDist(0);
        int right = countDist(1);
        int bot = countDist(2);
        int left = countDist(3);
        int front = countDist(dir);
        int acc=dist_2(gen);    //losowanie momentu gdy ma skr©ci†

        if(front<=acc || front <= 1){        
            if(dir%2==1){   //aktualny kurs: prawo/lewo
                
                
                if(top>bot && top > 0){
                    setDir(0);
                }else if(bot>top && bot > 0){
                    setDir(2);

                }else if(top!=0 && bot!=0){
                    rn=dist(gen);
                    if(rn%2==1) rn = 1 ? 0 : 2;
                    setDir(rn);
                }
                

            }else{          //aktualny kurs: gora/dol
                if(right>left && right > 0){
                    setDir(1);
                }else if(left>right && left > 0){
                    setDir(3);

                }else if(right!=0 && left!=0){
                    rn=dist(gen);
                    if(rn%2==0) rn = 0 ? 1 : 3;
                    setDir(rn);
                }
            }
        }



    }
   /* 
    void changeDir_zoner(){     //ANCHOR "strefowy" 

        float z1_free{}, z1_ile{}, z1_percent;  //gora
        float z2_free{}, z2_ile{}, z2_percent;  //dol
        float z3_free{}, z3_ile{}, z3_percent;  //lewo
        float z4_free{}, z4_ile{}, z4_percent;  //prawo

        for(int i=0;i<pozY-1;i++){    //gora
            for(int j=0;j<sizeX/2;j++){    
                z1_ile++;
                if(!grid[j][i]){
                    z1_free++;

                }
            }
        }
        z1_percent=(100.0/z1_ile)*z1_free;

        for(int i=0;i<pozY;i++){    //dol
            for(int j=0;j<sizeX/2;j++){    
                z2_ile++;
                if(!grid[j][i]){
                    z2_free++;

                }
            }
        }
        z2_percent=(100.0/z2_ile)*z2_free;

        for(int i=pozY+1;i<sizeY;i++){    //lewo
            for(int j=0;j<sizeX/2;j++){    
                z2_ile++;
                if(!grid[j][i]){
                    z2_free++;

                }
            }
        }
        z2_percent=(100.0/z2_ile)*z2_free;
       
        displayBrain(z1_percent, z2_percent, 0);

    }
*/
    //funckje do "spacera"
    void drawBorder(){  //rysuje linie prost¥ przed siebie by odzieli† prawa i lewo strone
        int i=0;
        int pozXx=pozX/2;
        if(dir==3){
            while(grid[pozXx -i][pozY]!=1){
                grid[pozXx -i][pozY]=9;
                i++;
            }
        }
        if(dir==2){
            while(grid[pozXx][pozY +i]!=1){
                grid[pozXx][pozY +i]=9;
                i++;
            }
        }
        if(dir==1){
            while(grid[pozXx +i][pozY]!=1){
                grid[pozXx +i][pozY]=9;
                i++;
            }
        }
        if(dir==0){
            while(grid[pozXx][pozY -i]!=1){
                grid[pozXx][pozY -i]=9;
                i++;
            }
        }
        
    }
    void clearBorder(){     //usuwa znaki pomocnicze z planszy
        for(int i=0;i<sizeY;i++){
            for(int j=0;j<sizeX;j++){
                if(grid[j][i]==9) grid[j][i]=0;
            }
        }
    }
    void flow(int x, int y, int* licz){     //sprawdza ilo˜† dost©pnych p¢l (nazwa od wody kt¢ra "pˆynie" po labiryncie)
        if(grid[x][y] != 0) return;
        *licz+=1;
        grid[x][y]=9;
        if(x>1)       flow(x-1, y, licz);
        if(x<sizeX-1) flow(x+1, y, licz);
        if(y>1)       flow(x, y-1, licz);
        if(y<sizeY-1) flow(x, y+1, licz);
        /*Czy wiesz ¾e...limit stosu wywoˆaä funkcji w VisualStudio to 5000? :P */
    }
    
    
    void changeDir_spacer(){    //ANCHOR "Spacer" por¢wnuje dost©pne miejsce do poruszania si© po obu stronach (nie bierze pod uwag© zamkni©tych miejsc do kt¢rych nie da si© dosta†) [trudny]
        //TODO: nie widzi przeciwnika gdy jada "ˆeb w ˆeb"
        //TODO EXTRA: sprawi† by wykrywaˆ ˜lepe uliczki i nie wje¾dzaˆ w nie
        int left{}, right{};
        int m{}, n{};
        int acc = dist_2(gen);
        int front = countDist(dir);

        ////

        if(dir==0){
            m=0;
            n=1;
        }
        if(dir==1){
            m=1;
            n=0;
        }
        if(dir==2){
            m=0;
            n=(-1);
        }
        if(dir==3){
            m=(-1);
            n=0;
        }

        ////

        drawBorder();   
        flow(pozX/2 -n,pozY -m, &left);
        clearBorder();

        drawBorder();
        flow(pozX/2 +n,pozY +m, &right);
        clearBorder();
        
        //skracanie momentu skr©tu wraz ze zmniejszaj¥cym si© dost©pnym miejscem na planszy
        if(left > 100 || right > 100){
            if(left>right){
                acc = acc % (left/100);
            }else{
                acc = acc % (right/100);
            }
        }else if(left < 100 && right < 100){
            acc = 0;
        }

        if(front <= acc || front < 1){
           

            //displayBrain(left,right,dist_1(gen));

            if(left>right && left!=0){
                setDir( ((dir-1) % 4) );
            }else if(right>left & right!=0){
                setDir( ((dir+1) % 4) );
            }else if(right!=0 && left!=0){
                if(dist_1(gen)==1){     //losowo
                    setDir( ((dir+1) % 4) );
                }else{
                    setDir( ((dir-1) %4) );
                }  
            }      

            left=0;
            right=0;
            
        }

    }
    
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
void setScoreBoard(Player a, AI_01 b){
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
void updateScoreBoard(Player a, AI_01 b){
    setCursorPosition(sizeX*2+12,4);
    a.print(a.lifes);
    setCursorPosition(sizeX*2+12,6);
    a.print(a.wins);
   
    setCursorPosition(sizeX*2+23,4);
    b.print(b.lifes);
    setCursorPosition(sizeX*2+23,6);
    b.print(b.wins);

}
void setScoreBoard(AI_01 a, AI_01 b){
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
void updateScoreBoard(AI_01 a, AI_01 b){
    setCursorPosition(sizeX*2+12,4);
    a.print(a.lifes);
    setCursorPosition(sizeX*2+12,6);
    a.print(a.wins);
   
    setCursorPosition(sizeX*2+23,4);
    b.print(b.lifes);
    setCursorPosition(sizeX*2+23,6);
    b.print(b.wins);

}
