#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include "Console.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Menu menu(1, 1, 80, 3, "File New View");
    menu.Start();

    Menu menu2("file.txt");
    menu2.Start();
}