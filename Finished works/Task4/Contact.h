#pragma once
#ifndef _CONTACT_
#include <iostream>
#include <string>
#define MAX 100

class Contact
{
	std::string name, surname, patronym, num, date;
public:

	Contact(std::string surname, std::string name, std::string patronym, std::string num, std::string date);

	Contact(std::string surname, std::string name, std::string patronym);

	Contact(const Contact& c);
	Contact();
	~Contact();

	bool get_bool();

	bool operator==(const Contact& c);

	Contact& Set_Name(std::string _name);
	Contact& Set_Surname(std::string surname);
	Contact& Set_Patronym(std::string patronym);
	Contact& Set_Num(std::string num);
	Contact& Set_Date(std::string date);
	Contact& add_contact_in_book();
	Contact delete_contact_in_book();
	bool add_contact_in_favorites();
	bool delete_contact_in_favorites();
	std::string Get_Num();
	std::string Get_Name();
	std::string Get_Surname();
	std::string Get_Patronym();
	std::string Get_Date();
};

bool search_contact_fullname(std::string surname, std::string name, std::string patronym, Contact& temp);
bool search_contact_num(std::string num, Contact& temp);
bool search_contact_firstchar(std::string surname, std::string name, std::string patronym, Contact& temp, int index);
bool search_contact_in_book(int index, Contact& temp);
bool search_contact_in_favorites(int index, Contact& temp);
int get_count_contact_in_book();
int get_count_contact_in_favorites();
Contact get_contact_file(std::string str, Contact& temp);
#endif