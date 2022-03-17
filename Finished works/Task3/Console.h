#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

class Menu
{
	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int x, y, len, count_item;
	char** item;

public:
	Menu()
	{
		x = 0; y = 0; len = 0; count_item = 0;
	}

	Menu(int _x, int _y, int _len, int _count_item, string s)
	{
		x = _x;
		y = _y;
		len = _len;
		count_item = _count_item;
		item = new char*[count_item];

		for (int i = 0; i < count_item; i++)
		{
			item[i] = new char[len];
		}
		int t = 0, j = 0;
		for (int i = 0; i < s.length()+1; i++)
		{
			if (s[i] != ' ')
			{
				item[j][t++] = s[i];
			}
			else
			{
				item[j][t++] = '\0';
				t = 0; j++;
			}
		}
	}

	Menu(string file_name)
	{
		ifstream file(file_name);
		file >> x;
		file >> y;
		file >> len;
		file >> count_item;

		item = new char* [count_item];

		for (int i = 0; i < count_item; i++)
		{
			item[i] = new char[len];
		}

		for (int i = 0; i < count_item; i++)
		{
			file >> item[i];
		}
	}

	Menu(const int& _x, const int& _y, const int& _len, const int& _count_item)
	{
		x = _x;
		y = _y;
		len = _len;
		count_item = _count_item;
		item = new char*[count_item];
	}

	~Menu()
	{
		for (int i = 0; i < count_item; i++)
		{
			delete[] item[i];
		}
		delete[] item;
	}

	void Start()
	{
		pos.X = x; pos.Y = y;
		for (int i = 0; i < count_item; i++) //Вывод меню
		{
			SetConsoleCursorPosition(cons, pos);
			cout << item[i] << endl; 
			pos.Y++;
		}
		pos.Y--;
		int input;
		do
		{
			cursor();
			SetConsoleCursorPosition(cons, pos);
			cout << "<<";
			input = _getch();
			switch (input) //Перемещение по меню (стрелки, ENTER, ESC)
			{
			case 80:
				if (pos.Y == y + count_item -1) { continue; }
				pos.Y++;
				break;
			case 72:
				if (pos.Y == y) { continue; }
				pos.Y--;
				break;
			case 27:
				system("CLS");
				break;
			case 13:
				print(x, y);
				break;
			default:
				break;
			}
		} while (input != 27);
	}
private:
	//Перемещение курсора
	void cursor()
	{
		if (pos.Y - y <= count_item)
		{ 
			pos.X = strlen(item[pos.Y - y]) + 4;
		}
		cout << "\b\b  \b";
	}
	//Вывод пункта
	void print(int x, int y)
	{
		COORD temp;
		temp.X = x; temp.Y = y + count_item + 3;
		SetConsoleCursorPosition(cons, temp);
		cout << "Был выбран пункт: " << (pos.Y) << endl;
	}
};
#endif