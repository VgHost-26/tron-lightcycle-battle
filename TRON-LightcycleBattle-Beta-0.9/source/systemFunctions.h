/*funkcje odpowiedzialne za zmiany systemowe takie jak: kolory i wielko˜† czcionki
konsoli, ustawianie pozycji kursora itp*/
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")

void setCursorPosition(int x, int y){    //ustawinei pozycji kursora w konsoli
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void setColors(){       //ustawienie tablicy kolorow konsoli
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX info;
    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &info);
            //dla graczy:
    info.ColorTable[1] = RGB(200, 255, 255);    //white (Flynn)
    info.ColorTable[2] = RGB(50, 150, 255);     //blue
    info.ColorTable[3] = RGB(97, 215, 215);     //cyan (Tron)
    info.ColorTable[4] = RGB(0, 128, 128);      //teal (ciemno-niebieski)
    info.ColorTable[5] = RGB(255, 23, 220);     //pink
    info.ColorTable[6] = RGB(204, 0, 112);      //magenta
    info.ColorTable[7] = RGB(123, 0, 212);      //vilet
    info.ColorTable[8] = RGB(248, 255, 0);      //yellow (Abraxas)
    info.ColorTable[9] = RGB(230, 142, 0);      //orange (Clu)
    info.ColorTable[10] = RGB(255, 1, 1);       //red   (Guard)
    info.ColorTable[11] = RGB(0, 201, 10);      //green
    info.ColorTable[12] = RGB(0, 255, 183);     //mint
            //systemowe:
    info.ColorTable[13] = RGB(35, 35, 35);      //grid
    info.ColorTable[14] = RGB(95, 95, 95);      //border
    //info.ColorTable[15] = RGB(200, 200, 200);      //default

    SetConsoleScreenBufferInfoEx(hConsole, &info);  //zatwierdzenie zmian

}

void setConsolSize(){      //ustawienie konsoli na peˆny ekran oraz dopasowanie czcionki do ro«dzielczo˜ci monitora
    // fstream p;
    // p.open("resolution.txt");
    // int res{};
    // p>>res;
    // p.close();
    int W = GetSystemMetrics(SM_CXSCREEN); //pobranie szerokosci ekranu
    int H = GetSystemMetrics(SM_CYSCREEN); //pobranie wysokosci ekranu
    int res{};
    
    if(W/H > 16/9){     //oprymalizacja dla szerszych ekran¢w ni¾ 16:9
        res = W - (((W*9)-(H*16))/9);
    }else{
        res = W;
    }

    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0); //pelny ekran
    ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);  //schowania scrollbara

    //ustawienia czcionki
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   
    //cfi.dwFontSize.Y = 27;                  
    cfi.dwFontSize.Y = res/56.8;                  // wysokosc znaku
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // domyslna czcionka
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);  //zatwierdzenie zmian
}
void hideCursor(){  //ukrycie kursora konsoli
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void showCursor(){  //pokazanie kursora
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
int getKey(){   //pobranie klawisza w momencie nacisni©cia
    if(kbhit()){
         return getch();
    }
    return 0;
}
void playSound(string name, bool IO){   //muzyczka
    if(IO){
        // string str="play sounds/";
        // str+=name;
        // str+=".wav";
       // mciSendString(TEXT("play sounds/menuTheme.wav"), NULL, 0, NULL);
    }
}