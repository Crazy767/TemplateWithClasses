#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include "Console.h"
#include "Contact.h"
#include <fstream>
using namespace std;

void Console::menu_start()
{
	pos.X = 0; pos.Y = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("CLS");
	menu_print(menu.start, start_count_str);
	menu_cursor(menu.start[pos.Y]);
	do
	{
		SetConsoleCursorPosition(cons, pos);
		ch = _getch();

		switch (ch)
		{
		case up:
			if (pos.Y == 0) { pos.Y = 5; }
			pos.Y--;
			menu_cursor(menu.start[pos.Y]);
			break;
		case down:
			if (pos.Y == start_count_str - 1) { pos.Y = -1; }
			pos.Y++;
			menu_cursor(menu.start[pos.Y]);
			break;
		case enter:
			if (pos.Y == 0) { menu_create_contact(); }
			else if (pos.Y == 1) { menu_search_contact(); }
			else if (pos.Y == 2) { menu_get_count_contact(); }
			else if (pos.Y == 3) { menu_favorites(); }
			else if (pos.Y == 4) { menu_file(); }
			break;
		}
	} while (ch != 133);
}

void Console::menu_print_contact(Contact& c)
{
std::cout << "�������: " << c.Get_Surname() << std::endl;
std::cout << "���: " << c.Get_Name() << std::endl;
std::cout << "��������: " << c.Get_Patronym() << std::endl;
std::cout << "�������: " << c.Get_Num() << std::endl;
std::cout << "���� ��������: " << c.Get_Date() << std::endl << std::endl;
}

void Console::menu_search_contact()
{
	system("CLS");
	pos.X = 0; pos.Y = 0;
	menu_print(menu.search, search_count_str);
	menu_cursor(menu.search[pos.Y]);
	do
	{
		SetConsoleCursorPosition(cons, pos);
		ch = _getch();

		switch (ch)
		{
		case up:
			if (pos.Y == 0) { pos.Y = 3; }
			pos.Y--;
			menu_cursor(menu.search[pos.Y]);
			break;
		case down:
			if (pos.Y == search_count_str - 1) { pos.Y = -1; }
			pos.Y++;
			menu_cursor(menu.search[pos.Y]);
			break;
		case enter:
			if (pos.Y == 0) { menu_search_contact_fullname(); }
			else if (pos.Y == 1) { menu_search_contact_num(); }
			else if (pos.Y == 2) { menu_search_contact_firstchar(); }
			break;
		}
	} while (ch != 133);
}

void  Console::menu_create_contact()
{
	system("CLS");
	cout << "������� �������: ";
	cin >> surname;
	cout << "������� ���: ";
	cin >> name;
	cout << "������� ��������: ";
	cin >> patronym;
	cout << "������� ����� �������� (������� \"-\", ����� ����������): ";
	cin >> num;
	cout << "������� ���� �������� (������� \"-\", ����� ����������): ";
	cin >> date;
	Contact c(surname, name, patronym, num, date);
	c.add_contact_in_book();
	cout << "������� ������� ������!\n" << endl << "�������, ����� ����������...";
	_getch();
	system("CLS");
	menu_start();
}

void Console::menu_cursor(string str)
{
	pos.X = str.length() + 3;
	cout << "  \b";
	SetConsoleCursorPosition(cons, pos);
	cout << "<<";
}

void Console::menu_print(string menu[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << menu[i] << endl;
	}
}

void Console::menu_success_search(Contact& c)
{
	system("CLS");
	cout << "������� ������� ������!" << endl << endl;
	menu_search_contact(c);
}

void Console::menu_fail_search()
{
	cout << "\n������ �������� ��� � ������!" << endl;
	cout << "�������, ����� ����������...";
	_getch(); menu_start();
}

void Console::menu_search_contact_fullname()
{
	system("CLS");
	cout << "������� �������: ";
	cin >> surname;
	cout << "������� ���: ";
	cin >> name;
	cout << "������� ��������: ";
	cin >> patronym;
	Contact temp;

	if (search_contact_fullname(surname, name, patronym, temp))
	{
		menu_success_search(temp);
	}
	else { menu_fail_search(); }
}

void Console::menu_search_contact_num()
{
	system("CLS");
	int flag = 0;
	cout << "������� �������: ";
	cin >> num;
	Contact temp;

	if (search_contact_num(num, temp))
	{
		menu_success_search(temp);
	}
	else { menu_fail_search(); }
}

void Console::menu_get_count_contact()
{
	system("CLS");
	Contact temp;
	if(get_count_contact_in_book() > 0)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (search_contact_in_book(i, temp)) { menu_print_contact(temp); }
		}
	}
	cout << "����� ���������: " << get_count_contact_in_book() << endl << endl;
	cout << "�������, ����� ����������...";
	_getch(); menu_start();
}

void Console::menu_search_contact_firstchar()
{
	system("CLS");
	int count = 0, flag = 0;
	cout << "������� ������ ����� �������: ";
	cin >> surname;
	cout << "������� ������ ����� �����: ";
	cin >> name;
	cout << "������� ������ ����� ��������: ";
	cin >> patronym;
	system("CLS");
	Contact temp(surname, name, patronym);

	for (int i = 0; i < MAX; i++)
	{
		if (search_contact_firstchar(surname, name, patronym, temp, i))
		{
			menu_print_contact(temp);
			flag = 1; count++;
		}
	}

	if (flag == 0) { menu_fail_search(); }
	cout << "��������� �������: " << count << endl;
	cout << "�������, ����� ����������...";
	_getch(); menu_start();
}

void Console::menu_search_contact(Contact& c)
{
	menu_print_contact(c);
	menu_print(menu.edit_menu, edit_menu_count_str);
	pos.Y = SEARCH_Y;
	menu_cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
	do
	{
		SetConsoleCursorPosition(cons, pos);
		ch = _getch();

		switch (ch)
		{
		case up:
			if (pos.Y == SEARCH_Y) { continue; }
			pos.Y--;
			menu_cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
			break;
		case down:
			if (pos.Y == SEARCH_Y + edit_menu_count_str - 1) { continue; }
			pos.Y++;
			menu_cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
			break;
		case enter:
			if (pos.Y == SEARCH_Y) { menu_edit_contact(c); }
			else if (pos.Y == SEARCH_Y + 1){ c.delete_contact_in_book(); menu_start();}
			else if (pos.Y == SEARCH_Y + 2) { menu_start(); }
			break;
		}
	} while (ch != 133);
}

void Console::menu_edit_contact(Contact& c)
{
	system("CLS");
	menu_print(menu.menu_edit_contact, edit_contact_count_str);
	pos.Y = 0;
	menu_cursor(menu.menu_edit_contact[pos.Y]);
	do
	{
		SetConsoleCursorPosition(cons, pos);
		ch = _getch();

		switch (ch)
		{
		case up:
			if (pos.Y == 0) { continue; }
			pos.Y--;
			menu_cursor(menu.menu_edit_contact[pos.Y]);
			break;
		case down:
			if (pos.Y == 4) { continue; }
			pos.Y++;
			menu_cursor(menu.menu_edit_contact[pos.Y]);
			break;
		case enter:
			system("CLS");
			if (pos.Y == _surname)
			{
				cout << "������� �������: ";
				cin >> surname;
				c.Set_Surname(surname);
			}
			else if (pos.Y == _name)
			{
				cout << "������� ���: ";
				cin >> name;
				c.Set_Name(name);
			}
			else if (pos.Y == _patronym)
			{
				cout << "������� ��������: ";
				cin >> patronym;
				c.Set_Patronym(patronym);
			}
			else if (pos.Y == _num)
			{
				cout << "������� �����: ";
				cin >> num;
				c.Set_Num(num);
			}
			else if (pos.Y == _date)
			{
				cout << "������� ����: ";
				cin >> date;
				c.Set_Date(date);
			}
			system("CLS");
			cout << "������� ������� ��������!" << endl << endl;
			menu_search_contact(c);
			break;
		}
	} while (ch != 133);
}

void Console::menu_favorites()
{
	system("CLS");
	menu_print(menu.favorite_menu, favorites_count_str);
	pos.Y = 0;
	menu_cursor(menu.favorite_menu[pos.Y]);
	do
	{
		SetConsoleCursorPosition(cons, pos);
		ch = _getch();

		switch (ch)
		{
		case up:
			if (pos.Y == 0) { continue; }
			pos.Y--;
			menu_cursor(menu.favorite_menu[pos.Y]);
			break;
		case down:
			if (pos.Y == 2) { continue; }
			pos.Y++;
			menu_cursor(menu.favorite_menu[pos.Y]);
			break;
		case enter:
			if (pos.Y == 0) { menu_favorites_contact_print(); }
			else if (pos.Y == 1) { menu_favorites_contact_add(); }
			else if (pos.Y == 2) { menu_favorites_contact_delete(); }
		}
	} while (1);
}

void Console::menu_favorites_contact_print()
{
	system("CLS");
	Contact temp;
	int a = get_count_contact_in_favorites();
	if (get_count_contact_in_favorites() > 0)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (search_contact_in_favorites(i, temp))
			{
				menu_print_contact(temp);
			}
		}
	}
	else 
	{
		cout << "��������� �����..." << endl;
		cout << "�������, ����� ����������...";
		_getch(); menu_start();
	}
	cout << "\n�������, ����� ����������...";
	_getch(); menu_start();
}

void Console::menu_favorites_contact_add()
{
	system("CLS");
	cout << "������� �������: ";
	cin >> surname;
	cout << "������� ���: ";
	cin >> name;
	cout << "������� ��������: ";
	cin >> patronym;
	Contact temp(surname, name, patronym);
	
	if (temp.add_contact_in_favorites())
	{
		cout << "������� ������� �������� � ���������!" << endl;
		cout << "�������, ����� ����������...";
		_getch(); menu_start();
	}
	else
	{
		cout << "������ �������� �� ����������!" << endl;
		cout << "�������, ����� ����������...";
		_getch(); menu_start();
	}
}

void Console::menu_favorites_contact_delete()
{
	system("CLS");
	cout << "������� �������: ";
	cin >> surname;
	cout << "������� ���: ";
	cin >> name;
	cout << "������� ��������: ";
	cin >> patronym;
	Contact temp(surname, name, patronym, num, date);
	system("CLS");
	if (temp.delete_contact_in_favorites())
	{
		cout << "������� ������� ������!" << endl;
		cout << "�������, ����� ����������...";
		_getch(); menu_start();
	}

	cout << "������� �� ������!" << endl;
	cout << "�������, ����� ����������...";
	_getch(); menu_start();
}

void Console::menu_file()
{
	system("CLS");
	std::string filename;
	cout << "������� �������� �����: ";
	cin >> filename;
	fstream file((filename + ".txt"), ios::app | ios::in);
	std::string str;
	Contact temp;
	while (getline(file, str))
	{
		get_contact_file(str, temp);
		temp.add_contact_in_book();
	}
	cout << endl << "�������� ������� ���������!" << endl;
	cout << "�������, ����� ����������...";
	_getch(); menu_start();
}
