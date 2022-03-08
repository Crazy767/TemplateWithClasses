#include "Hex.h"
#include <iostream>
#include <clocale>
#include <fstream>

int main()
{
	setlocale(LC_ALL, "");

	Hex hex1("AA", 2);
	Hex hex2("3AB", 3);
	Hex hex3("BA1", 3);

	hex1 = hex2 + hex3;
	hex1.print();

	hex2 = hex1 - hex3;
	hex2.print();

	hex3 = hex1 * hex2;
	hex3.print();

	std::cout << (hex1 < hex2) << "  " << (hex1 != hex3);

	std::fstream file;
	std::string s;

	file.open("file.txt", std::fstream::app); //Заполнение файла
	file << hex1;
	file.close();

	file.open("file.txt", std::fstream::in); //Вывод из файла в консоль
	file >> hex1;
	file.close();
}