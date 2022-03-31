#pragma once
#ifndef _CONSOLE_
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#define MAX 100
#define SEARCH_Y 8

Contact total[MAX];
Contact favorites[MAX];
using namespace std;

const int start_count_str = 4, search_count_str = 3, edit_menu_count_str = 3, edit_contact_count_str = 5, favorites_count_str = 3;

struct Menu
{
	string start[start_count_str] = { "Создать новый контакт", "Найти контакты" ,"Узнать число всех контактов", "Избранное"};
	string search[search_count_str] = {"Найти контакт по ФИО", "Найти контакт по Телефону", "Найти все контакты по начальной букве ФИО"};
	string edit_menu[edit_menu_count_str] = { "Изменить контакт", "Удалить контакт", "Сохранить контакт"};
	string edit_contact[edit_contact_count_str] = { "Изменить фамилию", "Изменить имя", "Изменить отчество", "Изменить телефон" ,"Изменить дату" };
	string favorite_menu[favorites_count_str] = { "Просмотреть избранное", "Добавить в избранное", "Удалить из избранного"};
};

class Console
{
	int size_fav = 0;
	Menu menu;
	enum input {up = 72, down = 80, enter = 13};
	enum data_contact { _surname, _name, _patronym, _num, _date };
	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	unsigned int ch;
	string name, surname, patronym, num, date;
public:
	void menu_start()
	{
		pos.X = 0; pos.Y = 0;
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		system("CLS");
		print_menu(menu.start, start_count_str);
		cursor(menu.start[pos.Y]);
		do
		{
			SetConsoleCursorPosition(cons, pos);
			ch = _getch();

			switch (ch)
			{
			case up:
				if (pos.Y == 0) { continue; }
				pos.Y--;
				cursor(menu.start[pos.Y]);
				break;
			case down:
				if (pos.Y == start_count_str-1) { continue; }
				pos.Y++;
				cursor(menu.start[pos.Y]);
				break;
			case enter:
				if (pos.Y == 0) { create_contact(); }
				else if (pos.Y == 1) { menu_search_contact(); }
				else if (pos.Y == 2) { get_count_contact(); }
				else if (pos.Y == 3) { favorites_menu(); }
				break;
			}
		} while (ch != 133);
		////Перемещение курсора
		////Вывод пункта
		//void print(int x, int y)
		//{
		//	COORD temp;
		//	temp.X = x; temp.Y = y + count_item + 3;
		//	SetConsoleCursorPosition(cons, temp);
		//	cout << "Был выбран пункт: " << (pos.Y) << endl;
		//}
	}

	void menu_search_contact()
	{
		system("CLS");
		pos.X = 0; pos.Y = 0;
		print_menu(menu.search, search_count_str);
		cursor(menu.search[pos.Y]);
		do
		{
			SetConsoleCursorPosition(cons, pos);
			ch = _getch();

			switch (ch)
			{
			case up:
				if (pos.Y == 0) { continue; }
				pos.Y--;
				cursor(menu.search[pos.Y]);
				break;
			case down:
				if (pos.Y == search_count_str - 1) { continue; }
				pos.Y++;
				cursor(menu.search[pos.Y]);
				break;
			case enter:
				if (pos.Y == 0) { search_contact_fullname(); }
				else if (pos.Y == 1) { search_contact_num(); }
				else if (pos.Y == 2) { search_contact_firstchar(); }
				break;
			}
		} while (ch != 133);
	}

	void create_contact()
	{
		system("CLS");
		cout << "Введите фамилию: ";
		cin >> surname;
		cout << "Введите имя: ";
		cin >> name;
		cout << "Введите отчество: ";
		cin >> patronym;
		cout << "Введите номер телефона (введите \"-\", чтобы пропустить): ";
		cin >> num;
		cout << "Введите дату рождения (введите \"-\", чтобы пропустить): ";
		cin >> date;
		Contact c(surname, name, patronym, num, date);
		add_contact(c);
		cout << "Контакт успешно создан!\n" << endl << "Нажмите, чтобы продолжить...";
		_getch();
		system("CLS");
		menu_start();
	}
private:
	void cursor(string str)
	{
		pos.X = str.length() + 3;
		cout << "  \b";
		SetConsoleCursorPosition(cons, pos);
		cout << "<<";
	}

	void print_menu(string menu[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << menu[i] << endl;
		}
	}

	void add_contact(Contact c)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (total[i].get_bool() == false) { total[i] = c; break; }
		}
	}
	
	void delete_contact(Contact& c)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (total[i] == c) { delete[] total; }
		}
	}

	int success_search(int& flag, Contact& c)
	{
		system("CLS");
		cout << "Контакт успешно найден!" << endl << endl;
		search_contact_menu(c);
		return flag=1;
	}

	void fail_search()
	{
		cout << "\nТакого контакта нет в списке!" << endl;
		cout << "Нажмите, чтобы продолжить...";
		_getch(); menu_start();
	}

	void search_contact_fullname()
	{
		system("CLS");
		int flag = 0;
		cout << "Введите фамилию: ";
		cin >> surname;
		cout << "Введите имя: ";
		cin >> name;
		cout << "Введите отчество: ";
		cin >> patronym;
		Contact temp(surname, name, patronym);
		for (int i = 0; i < MAX; i++)
		{
			if (total[i] == temp) { success_search(flag, total[i]); break; }
		}
		if (flag == 0) { fail_search(); }
	}

	void search_contact_num()
	{
		system("CLS");
		int flag = 0;
		cout << "Введите телефон: ";
		cin >> num;
		for (int i = 0; i < MAX; i++)
		{
			if (total[i].Get_Num() == num) { success_search(flag, total[i]); break; }
		}
		if (flag == 0) { fail_search(); }
	}

	void get_count_contact()
	{
		system("CLS");
		int count;
		for (count = 0; count < MAX; count++)
		{
			if (total[count].Get_Name()[0] == '\0') { break; }
			total[count].print();
		}
		cout << "Всего контактов: " << count << endl << endl;
		cout << "Нажмите, чтобы продолжить...";
		_getch(); menu_start();
	}

	void search_contact_firstchar()
	{
		system("CLS");
		int flag = 0, count = 0; 
		cout << "Введите первую букву Фамилии: ";
		cin >> surname;
		cout << "Введите первую букву Имени: ";
		cin >> name;
		cout << "Введите первую букву Отчества: ";
		cin >> patronym;
		system("CLS");
		for (int i = 0; i < MAX; i++)
		{
			if (   name[0] == total[i].Get_Name()[0] &&
				   surname[0] == total[i].Get_Surname()[0] &&
				   patronym[0] == total[i].Get_Patronym()[0]   )
			{ 
				flag = 1;
				total[i].print();
				count++;
			}
		}
		if (flag == 0) { fail_search(); }
		cout << "Контактов найдено: " << count << endl;
		cout << "Нажмите, чтобы продолжить...";
		_getch(); menu_start();
	}

	void search_contact_menu(Contact& c)
	{
		c.print();
		print_menu(menu.edit_menu, edit_menu_count_str);
		pos.Y = SEARCH_Y;
		cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
		do
		{
			SetConsoleCursorPosition(cons, pos);
			ch = _getch();

			switch (ch)
			{
			case up:
				if (pos.Y == SEARCH_Y) { continue; }
				pos.Y--;
				cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
				break;
			case down:
				if (pos.Y == SEARCH_Y + edit_menu_count_str - 1) { continue; }
				pos.Y++;
				cursor(menu.edit_menu[pos.Y - SEARCH_Y]);
				break;
			case enter:
				if (pos.Y == SEARCH_Y) { edit_contact(c); }
				else if (pos.Y == SEARCH_Y + 1)
				{
					delete_contact(c);
				}
				else if (pos.Y == SEARCH_Y + 2) { menu_start(); }
				break;
			}
		} while (ch != 133);
	}

	void edit_contact(Contact& c)
	{
		system("CLS");
		print_menu(menu.edit_contact, edit_contact_count_str);
		pos.Y = 0;
		cursor(menu.edit_contact[pos.Y]);
		do
		{
			SetConsoleCursorPosition(cons, pos);
			ch = _getch();

			switch (ch)
			{
			case up:
				if (pos.Y == 0) { continue; }
				pos.Y--;
				cursor(menu.edit_contact[pos.Y]);
				break;
			case down:
				if (pos.Y == 4) { continue; }
				pos.Y++;
				cursor(menu.edit_contact[pos.Y]);
				break;
			case enter:
				system("CLS");
				if (pos.Y == _surname)
				{
					cout << "Введите фамилию: ";
					cin >> surname;
					c.Set_Surname(surname);
				}
				else if (pos.Y == _name)
				{
					cout << "Введите имя: ";
					cin >> name;
					c.Set_Name(name);
				}
				else if (pos.Y == _patronym)
				{
					cout << "Введите отчество: ";
					cin >> patronym;
					c.Set_Patronym(patronym);
				}
				else if (pos.Y == _num)
				{
					cout << "Введите номер: ";
					cin >> num;
					c.Set_Num(num);
				}
				else if (pos.Y == _date)
				{
					cout << "Введите дату: ";
					cin >> date;
					c.Set_Date(date);
				}
				system("CLS");
				cout << "Контакт успешно обновлен!" << endl << endl;
				search_contact_menu(c);
				break;
			}
		} while (ch != 133);
	}

	void favorites_menu()
	{
		system("CLS");
		print_menu(menu.favorite_menu, favorites_count_str);
		pos.Y = 0;
		cursor(menu.favorite_menu[pos.Y]);
		do
		{
			SetConsoleCursorPosition(cons, pos);
			ch = _getch();

			switch (ch)
			{
			case up:
				if (pos.Y == 0) { continue; }
				pos.Y--;
				cursor(menu.favorite_menu[pos.Y]);
				break;
			case down:
				if (pos.Y == 2) { continue; }
				pos.Y++;
				cursor(menu.favorite_menu[pos.Y]);
				break;
			case enter:
				if (pos.Y == 0) { favorites_print(); }
				else if (pos.Y == 1) { favorites_add(); }
				else if (pos.Y == 2) { favorites_delete(); }
			}
		}while (1);
	}

	void favorites_print()
	{
		system("CLS");
		for (int i = 0; i < MAX; i++)
		{
			if (favorites[0].Get_Name()[0] == '\0')
			{
				cout << "Избранное пусто..." << endl;
				cout << "Нажмите, чтобы продолжить...";
				_getch(); menu_start();
				break; 
			}
			else 
			{ 
				if (favorites[i].Get_Name()[0] != '\0') 
				{ 
					favorites[i].print(); 
				}
			}
		}
		cout << "\nНажмите, чтобы продолжить...";
		_getch(); menu_start();
	}

	void favorites_add()
	{
		system("CLS");
		cout << "Введите фамилию: ";
		cin >> surname;
		cout << "Введите имя: ";
		cin >> name;
		cout << "Введите отчество: ";
		cin >> patronym;
		Contact temp(surname, name, patronym, num, date);
		int flag = 0;
		for (int i = 0; i < MAX; i++)
		{
			if (total[i] == temp) { flag = 1; break; }
		}
		if (flag == 1)
		{
			for (int i = 0; i < MAX; i++)
			{
				if (favorites[i].Get_Name()[0] == '\0') 
				{ 
					favorites[i] = temp; 
					cout << "Контакт успешно добавлен в избранное!" << endl;
					cout << "Нажмите, чтобы продолжить...";
					_getch(); menu_start();
					break;
				}
			}
		}
		else
		{
			cout << "Такого контакта не существует!" << endl;
			cout << "Нажмите, чтобы продолжить...";
			_getch(); menu_start();
		}
	}

	void favorites_delete()
	{
		system("CLS");
		cout << "Введите фамилию: ";
		cin >> surname;
		cout << "Введите имя: ";
		cin >> name;
		cout << "Введите отчество: ";
		cin >> patronym;
		Contact temp(surname, name, patronym, num, date);

		for (int i = 0; i < MAX; i++)
		{
			if (favorites[i] == temp)
			{
				Contact clear;
				favorites[i] = clear;
				cout << "Контакт успешно удален!" << endl;
				cout << "Нажмите, чтобы продолжить...";
				_getch(); menu_start();
			}
		}
		cout << "Контакт не найден!" << endl;
		cout << "Нажмите, чтобы продолжить...";
		_getch(); menu_start();
	}
};
#endif // _CONSOLE_