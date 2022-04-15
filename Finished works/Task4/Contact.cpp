#include <iostream>
#include <string>
#include "Contact.h"
Contact book[100];
Contact favorites[100];
Contact::Contact(std::string surname, std::string name, std::string patronym, std::string num, std::string date)
{
	this->name = name;
	this->surname = surname;
	this->patronym = patronym;
	if (num != "-") { this->num = num; }
	else { this->num = ""; }
	if (date != "-") { this->date = date; }
	else { this->num = ""; }
}

Contact::Contact(std::string surname, std::string name, std::string patronym)
{
	this->name = name;
	this->surname = surname;
	this->patronym = patronym;
	this->num = "";
	this->date = "";
}

Contact::Contact(const Contact& c)
{
	this->name = c.name;
	this->surname = c.surname;
	this->patronym = c.patronym;
	this->num = c.num;
	this->date = c.date;
}

Contact::Contact() {}
Contact::~Contact() {}

bool Contact::get_bool()
{
	if (name == "") { return false; }
	return true;
}

bool Contact::operator==(const Contact& c)
{
	if (this->name == c.name &&
		this->surname == c.surname &&
		this->patronym == c.patronym)
	{
		return true;
	}
	return false;
}

Contact& Contact::add_contact_in_book()
{
	for (int i = 0; i < MAX; i++)
	{
		if (book[i].get_bool() == false) { book[i] = *this; break; }
	}
	return *this;
}

Contact Contact::delete_contact_in_book()
{
	for (int i = 0; i < MAX; i++)
	{
		if (book[i] == *this)
		{
			int del = i;
			while (book[del].Get_Name() != "")
			{
				book[del] = book[del + 1];
				del++;
			}
		}
	}
	return *this;
}

Contact& Contact::Set_Name(std::string _name) { this->name = _name; return *this; }
Contact& Contact::Set_Surname(std::string surname) { this->surname = surname; return *this; }
Contact& Contact::Set_Patronym(std::string patronym) { this->patronym = patronym; return *this; }
Contact& Contact::Set_Num(std::string num) { this->num = num; return *this; }
Contact& Contact::Set_Date(std::string date) { this->date = date; return *this; }
std::string Contact::Get_Num() { return num; }
std::string Contact::Get_Name() { return name; }
std::string Contact::Get_Surname() { return surname; }
std::string Contact::Get_Patronym() { return patronym; }
std::string Contact::Get_Date() { return date; }

bool search_contact_fullname(std::string surname, std::string name, std::string patronym, Contact& temp)
{
	for (int i = 0; i < MAX; i++)
	{
		if (book[i].Get_Name() == name && 
			book[i].Get_Surname() == surname && 
			book[i].Get_Patronym() == patronym)
		{
			temp = book[i];
			return true;
		}
	}
	return false;
}

bool search_contact_num(std::string num, Contact& temp)
{
	for (int i = 0; i < MAX; i++)
	{
		if (book[i].Get_Num() == num)
		{
			temp = book[i];
			return true;
		}
	}
	return false;
}

bool search_contact_firstchar(std::string surname, std::string name, std::string patronym, Contact& temp, int index)
{
	if (name[0] == book[index].Get_Name()[0] &&
		surname[0] == book[index].Get_Surname()[0] &&
		patronym[0] == book[index].Get_Patronym()[0])
	{
		temp = book[index];
		return true;
	}
	else { return false; }
}

bool search_contact_in_book(int index, Contact& temp)
{
	if (book[index].Get_Name()[0] != '\0') 
	{ 
		temp = book[index];
		return true; 
	}
	return false;
}

int get_count_contact_in_book()
{
	int count = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (book[i].Get_Name() != "") { count++; }
	}
	return count;
}

int get_count_contact_in_favorites()
{
	int count = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (favorites[i].Get_Name() != "") { count++; }
	}
	return count;
}

bool search_contact_in_favorites(int index, Contact& temp)
{
	if (favorites[index].Get_Name()[0] != '\0')
	{
		temp = favorites[index];
		return true;
	}
}

bool Contact::add_contact_in_favorites()
{
	int flag = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (book[i].Get_Surname() == this->Get_Surname() &&
			book[i].Get_Name() == this->Get_Name()&&
			book[i].Get_Patronym() == this->Get_Patronym()) 
		{ 
			*this = book[i];
			flag = 1; 
			break; 
		}
	}
	if (flag == 1)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (favorites[i].Get_Name()[0] == '\0')
			{
				favorites[i] = *this;
				return true;
			}
		}
	}
	return false;
}

bool Contact::delete_contact_in_favorites()
{
	for (int i = 0; i < MAX; i++)
	{
		if (favorites[i] == *this)
		{
			while (favorites[i].Get_Name() != "")
			{
				favorites[i] = favorites[i + 1];
			}
			return true;
		}
	}
	return false;
}

Contact get_contact_file(std::string str, Contact& temp)
{
	std::string s = ""; 
	int pars = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ';')
		{
			s += str[i];
		}
		else if (pars == 0) { temp.Set_Surname(s); s = ""; pars++; }
		else if (pars == 1) { temp.Set_Name(s); s = ""; pars++; }
		else if (pars == 2) { temp.Set_Patronym(s); s = ""; pars++; }
		else if (pars == 3) { temp.Set_Num(s); s = ""; pars++; }
		else if (pars == 4) { temp.Set_Date(s); s = ""; pars++; }
	}
	return temp;
}
