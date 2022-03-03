#ifndef HEX.H
#define HEX_H
#include <iostream>
#include <string>
#include <fstream>

class Hex
{
	int size;
	unsigned char* hex;
	bool flag_memory = false;

public:
	Hex()
	{
		size = 1;
		hex = new unsigned char[size];
	}

	Hex(std::string str_hex, int _size)
	{
		size = _size;
		hex = new unsigned char[size];
		if (str_hex.length() <= size)
		{
			for (int i = 0; i < str_hex.length(); i++)
			{
				hex[i] = str_hex[i];
			}
		}
		else
		{
			std::cout << "Ошибка выделения памяти!" << std::endl;
			hex[0] = 0;
			flag_memory = true;
		}
	}

	Hex(const int& _size)
	{

	}

	~Hex()
	{
		delete[] this->hex;
	}

	Hex & operator=(const Hex &_num)
	{
		this->size = _num.size;
		delete[] this->hex;
		this->hex = new unsigned char[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->hex[i] = _num.hex[i];
		}
		return *this;
	}

	Hex operator+(const Hex &_num)
	{
		Hex h;
		int sum;
		sum = htoi(*this) + htoi(_num);
		h = itoh(sum);
		return *this;
	}

	Hex operator-(const Hex& _num)
	{
		Hex h;
		int sum;
		sum = htoi(*this) - htoi(_num);
		h = itoh(sum);
		return *this;
	}
	Hex operator*(const Hex& _num)
	{
		Hex h;
		int sum;
		sum = htoi(*this) * htoi(_num);
		h = itoh(sum);
		return *this;
	}

	bool operator>(const Hex& _num) { return htoi(*this) >  htoi(_num); }
	bool operator>=(const Hex& _num){ return htoi(*this) >= htoi(_num); }
	bool operator<(const Hex& _num) { return htoi(*this) <  htoi(_num); }
	bool operator<=(const Hex& _num){ return htoi(*this) <= htoi(_num); }
	bool operator==(const Hex& _num){ return htoi(*this) == htoi(_num); }
	bool operator!=(const Hex& _num){ return htoi(*this) != htoi(_num); }


	void print()
	{
		if (flag_memory == false)
		{
			for (int i = 0; i < size; i++)
			{
				std::cout << hex[i];
			}
			std::cout << std::endl;
		}
		else { std::cout << "Невозможно вывести данный массив" << std::endl; }
	}

	int htoi(const Hex &hex)
	{
		int n = 0;
		for (int i = 0; i < size; i++)
		{
			switch(hex.hex[i])
			{
			case 65: n += 10 * pow(16, hex.size - 1 - i); break;
			case 66: n += 11 * pow(16, hex.size - 1 - i); break;
			case 67: n += 12 * pow(16, hex.size - 1 - i); break;
			case 68: n += 13 * pow(16, hex.size - 1 - i); break;
			case 69: n += 14 * pow(16, hex.size - 1 - i); break;
			case 70: n += 15 * pow(16, hex.size - 1 - i); break;
			default: n += (hex.hex[i] - 48) * pow(16, hex.size - 1 - i);
			}
		}
		return n;
	}

	Hex & itoh(int num)
	{
		int ost, size = 0, t_num = num;
		while (t_num > 0)
		{
			size += 1;
			t_num = t_num / 16;
		}
		unsigned char* mass;
		mass = new unsigned char[size];
		for (int i = size-1; num > 0; i--)
		{
			ost = num % 16;
			num /= 16;
			if (ost > 9) { mass[i] = ost + 55; }
			else { mass[i] = ost + 48; }
		}
		this->size = size;
		this->hex = mass;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Hex& hex)
	{
		for (int i = 0; i < hex.size; i++)
		{
			os << hex.hex[i];
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, const Hex& hex)
	{
		is >> hex.hex;
		return is;
	}
};
#endif HEX.H