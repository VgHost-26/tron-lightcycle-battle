void setCursorPosition(int x, int y){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void setColors(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

    info.ColorTable[1] = RGB(200, 255, 255);    //white (flynn)
    info.ColorTable[2] = RGB(50, 150, 255);     //blue
    info.ColorTable[3] = RGB(21, 189, 32);      //green
    info.ColorTable[4] = RGB(97, 215, 215);     //cyan (tron)
    info.ColorTable[5] = RGB(255, 23, 220);     //pink
    info.ColorTable[6] = RGB(204, 0, 112);      //magenta
    info.ColorTable[8] = RGB(248, 255, 0);      //yellow (abraxas)
    info.ColorTable[9] = RGB(230, 142, 0);      //orange (clue)
    info.ColorTable[10] = RGB(255, 1, 1);       //red   (guard)
    info.ColorTable[12] = RGB(123, 0, 212);     //vilet
    info.ColorTable[13] = RGB(35, 35, 35);      //grid
    info.ColorTable[14] = RGB(95, 95, 95);      //border

    SetConsoleScreenBufferInfoEx(hConsole, &info);

}

void setConsolSize(){
    fstream p;
    p.open("resolution.txt");
    int res{};
    p>>res;
    p.close();


    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0); //pelny ekran

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    //cfi.dwFontSize.Y = 27;                  // Height
    cfi.dwFontSize.Y = res/56.8;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void hideCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void showCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void setGrid(){
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
                    cout<<char(219)<<char(219);
                }else if(j>=sizeX){
                    cout<<"  ";
                }else{
                    //cout<<"  ";
                    SetConsoleTextAttribute(hConsole, 13);
                    cout<<char(197)<<char(196);
                }
        }
        cout<<endl;
        
    }
    SetConsoleTextAttribute(hConsole, 7);

    Sleep(100);
}

int getKey(){
    if(kbhit()){
         return getch();
    }
    return 0;
}
void fill(int x, int y){
    grid[x/2][y]=1;
}
void clearGrid(){   //czyszczenie tablicy
    for(int i=0;i<sizeX;i++){
        for(int j=0;j<sizeY;j++){
            grid[i][j]=0;
        }
    }
}
