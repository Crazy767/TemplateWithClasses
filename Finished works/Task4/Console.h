#pragma once
#ifndef _CONSOLE_
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include "Contact.h"
#define SEARCH_Y 8

using namespace std;

const int start_count_str = 5, search_count_str = 3, edit_menu_count_str = 3, edit_contact_count_str = 5, favorites_count_str = 3;

struct Menu
{
	string start[start_count_str] = { "Создать новый контакт", "Найти контакты" ,"Узнать число всех контактов", "Избранное", "Импортировать из файла"};
	string search[search_count_str] = {"Найти контакт по ФИО", "Найти контакт по Телефону", "Найти все контакты по начальной букве ФИО"};
	string edit_menu[edit_menu_count_str] = { "Изменить контакт", "Удалить контакт", "Сохранить контакт"};
	string menu_edit_contact[edit_contact_count_str] = { "Изменить фамилию", "Изменить имя", "Изменить отчество", "Изменить телефон" ,"Изменить дату" };
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
	void menu_start();

private:
	void menu_print_contact(Contact& c);

	void menu_search_contact();

	void menu_create_contact();

	void menu_cursor(string str);

	void menu_print(string menu[], int size);

	void menu_success_search(Contact& c);

	void menu_fail_search();

	void menu_search_contact_fullname();

	void menu_search_contact_num();

	void menu_get_count_contact();

	void menu_search_contact_firstchar();

	void menu_search_contact(Contact& c);

	void menu_edit_contact(Contact& c);

	void menu_favorites();

	void menu_favorites_contact_print();

	void menu_favorites_contact_add();

	void menu_favorites_contact_delete();

	void menu_file();
};
#endif // _CONSOLE_