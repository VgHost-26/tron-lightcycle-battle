/*funkcje do obsˆugi menu i elementow wizualnych*/
void select(string tab[], int dl, int kt, int baseColor, int selectedColor, int place, int offset=0){    //podswitlanie wybranego elementu menu

    for(int i=0;i<dl;i++){
        
        if(i==kt){
            SetConsoleTextAttribute(hConsole, selectedColor);
        }else{
            SetConsoleTextAttribute(hConsole, baseColor);
        }
        setCursorPosition(place-10,15+((i+offset)*2));
        cout<<tab[i];
    }
}
void generateTable(string style[], int size, int place){    //tworzy tabelke na bazie przekazanego stylu
    cout.width(place);
    cout<<style[0]<<endl;
    for(int i=0;i<size;i++){
        cout.width(place);
        cout<<style[1]<<endl;
        if(i!=size-1){
            cout.width(place);
            cout<<style[2]<<endl;
        }
    }
    cout.width(place);
    cout<<style[3]<<endl;
}
void printLogo(int color, int place){   //wyswietlanie logo TRON na ˜rodku ekranu   
    
   //cout<<columns<<" "<<middle<<endl;
    fstream plik;
    string line{};
    plik.open("logo.txt");
    SetConsoleTextAttribute(hConsole, color);
    cout<<endl<<endl;
    for(int i=0;i<10;i++){
        cout.width(place);
        
        getline(plik,line);
        cout<<line<<endl;
    }
    cout<<endl<<endl;
    plik.close();  
}

int middleCalc(int winWidth, int objWidth){     //obliczanie miejsca na ˜rodku ekranu dla konkretnego elementu wzgledem szeroko˜ci ekranu
    return winWidth-((winWidth-objWidth)/2);
}
void clearLine(int x, int y, int width){    //czy˜ci wybran¥ linie
    setCursorPosition(x,y);
    for(int i=0;i<width;i++) cout<<" ";

}
bool includeChar(string st, char z){    //sprawdza czy "string st" zawiera znak "char z"

    for(int i=0;i<st.length();i++){
        if(st[i]==z){
            return true;
        }
    }
    return false;

}
void buttonHelp(int tab[], int size){   //wyswietla informacje pomocnicze w prawym dolnym rogu ekranu
    SetConsoleTextAttribute(hConsole,15);
    int poz{};
    for(int i=0;i<size;i++){
        if(tab[i]==1 || tab[i]==3){
            poz+=7;
        }else{
            poz+=14;
        }
    }

    //setCursorPosition(117 - 13*5,29);
    clearLine(0,29,118);
    setCursorPosition(117 - poz,29);
    for(int i=0;i<size;i++){

        if(tab[i]==1){
            cout<<char(30)<<" g¢ra";    //?
        }
        if(tab[i]==2){
            cout<<char(17)<<" poprzedni";//?
        }
        if(tab[i]==3){
            cout<<char(31)<<" d¢ˆ";     //?
        }
        if(tab[i]==4){
            cout<<char(16)<<" nast©pny";//?
        }
        if(tab[i]==5){
            cout<<"<"<<char(217)<<" zatwierd«"; //<Ù
        }
        if(tab[i]==6){
            cout<<"Esc"<<" menu"; //Esc
        }
        if(i<size-1){
            cout<<" | ";
        }

    }
    SetConsoleTextAttribute(hConsole,3);


}
bool confirm(int x, int y, int dCol, int sCol, bool border=0, string msg=""){ //wypisanei na ekranie funkcjonalnego tak/nie z mo¾liwoscia wyboru
            // pozycja,     kolor,   kolor wybranego el, czy ramka, wiadomosc
    if(border){
        //rysowanie ramki jesli tak wybrano
        int tmp=1;
        if(msg!=""){
            setCursorPosition(x - 2, y - 1);
            cout<<char(186);
            cout.width( 11 - (11 - msg.length())/2 );
            cout<<msg;
            cout.width( (11 - msg.length())/2 +1 );
            cout<<char(186);
            tmp=2;
        }
        setCursorPosition(x - 2, y);
        cout<<char(186)<<"           "<<char(186);
        
        setCursorPosition(x - 2, y + 1);
        cout<<char(200);
        for(int i=0;i<11;i++) cout<<char(461);
        cout<<char(188);

        setCursorPosition(x - 2, y - tmp);
        cout<<char(201);
        for(int i=0;i<11;i++) cout<<char(461);
        cout<<char(187);
    }

    setCursorPosition(x,y);
    SetConsoleTextAttribute(hConsole, dCol);
    cout<<"Tak"<<"   ";
    SetConsoleTextAttribute(hConsole, sCol);
    cout<<"Nie";
    int tn=0;
    int k{};
    while(1){
        k=getKey();
        if(k==77){   // w prawo
            setCursorPosition(x,y);
            SetConsoleTextAttribute(hConsole, dCol);
            cout<<"Tak   ";
            SetConsoleTextAttribute(hConsole, sCol);
            cout<<"Nie";
            tn=0;
        }
        if(k==75){   // w lewo
            setCursorPosition(x,y);
            SetConsoleTextAttribute(hConsole, sCol);
            cout<<"Tak   ";
            SetConsoleTextAttribute(hConsole, dCol);
            cout<<"Nie";
            tn=1;
        }
        if(k==13){   //enter
            clearLine(x-2,y,  13);
            clearLine(x-2,y-2,13);
            clearLine(x-2,y-1,13);
            clearLine(x-2,y+1,13);
            return tn;
        }
    }
    return 0;
}
