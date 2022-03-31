#pragma once
#ifndef _CONTACT_
#include <iostream>
#include <string>

class Contact
{
	std::string name, surname, patronym, num, date;
public:

	Contact(std::string name,std::string surname, std::string patronym, std::string num, std::string date)
	{
		this->name = name;
		this->surname = surname;
		this->patronym = patronym;
		if (num != "-") { this->num = num; }
		else { this->num = ""; }
		if (date != "-") { this->date = date; }
		else { this->num = ""; }
	}

	Contact(std::string name, std::string surname, std::string patronym)
	{
		this->name = name;
		this->surname = surname;
		this->patronym = patronym;
		this->num = "";
		this->date = "";
	}

	Contact() {}
	~Contact() {}

	bool get_bool()
	{
		if (name == "") { return false; }
		return true;
	}

	void print()
	{
		std::cout << "Фамилия: " << surname << std::endl;
		std::cout << "Имя: " << name << std::endl;
		std::cout << "Отчество: " << patronym << std::endl;
		std::cout << "Телефон: " << num << std::endl;
		std::cout << "Дата рождения: " << date << std::endl << std::endl;
	}

	bool operator==(const Contact& c)
	{
		if (this->name == c.name &&
			this->surname == c.surname &&
			this->patronym == c.patronym)
		{
			return true;
		}
		return false;
	}

	void Set_Name(std::string _name) { this->name = _name; }
	void Set_Surname(std::string surname) { this->surname = surname; }
	void Set_Patronym(std::string patronym) { this->patronym = patronym; }
	void Set_Num(std::string num) { this->num = num; }
	void Set_Date(std::string date) { this->date = date; }
	std::string Get_Num() { return num; }
	std::string Get_Name() { return name; }
	std::string Get_Surname() { return surname; }
	std::string Get_Patronym() { return patronym; }
	std::string Get_Date() { return date; }
};

#endif