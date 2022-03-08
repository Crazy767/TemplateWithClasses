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

	Hex(const Hex& h)
	{
		this->size = h.size;
		this->hex = new unsigned char[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->hex[i] = h.hex[i];
		}
		this->flag_memory = h.flag_memory;
	}

	~Hex()
	{
		delete[] this->hex;
	}

	Hex & operator=(const Hex &_num)
	{
		if (this->size != _num.size)
		{
			this->size = _num.size;
			delete[] this->hex;
			this->hex = new unsigned char[this->size];
		}
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
		sum = this->htoi() + _num.htoi();
		h = itoh(sum);
		return h;
	}

	Hex operator-(const Hex& _num)
	{
		Hex h;
		int sum;
		sum = this->htoi() - _num.htoi();
		h = itoh(sum);
		return h;
	}
	Hex operator*(const Hex& _num)
	{
		Hex h;
		int sum;
		sum = this->htoi() * _num.htoi();
		h = itoh(sum);
		return h;
	}

	bool operator>(const Hex& _num) { return this->htoi() >  _num.htoi(); }
	bool operator>=(const Hex& _num){ return this->htoi() >= _num.htoi(); }
	bool operator<(const Hex& _num) { return this->htoi() < _num.htoi(); }
	bool operator<=(const Hex& _num){ return this->htoi() <= _num.htoi(); }
	bool operator==(const Hex& _num){ return this->htoi() == _num.htoi(); }
	bool operator!=(const Hex& _num){ return this->htoi() != _num.htoi(); }


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

	int htoi()const
	{
		int n = 0;
		for (int i = 0; i < this->size; i++)
		{
			switch(this->hex[i])
			{
			case 65: n += 10 * pow(16, this->size - 1 - i); break;
			case 66: n += 11 * pow(16, this->size - 1 - i); break;
			case 67: n += 12 * pow(16, this->size - 1 - i); break;
			case 68: n += 13 * pow(16, this->size - 1 - i); break;
			case 69: n += 14 * pow(16, this->size - 1 - i); break;
			case 70: n += 15 * pow(16, this->size - 1 - i); break;
			default: n += (this->hex[i] - 48) * pow(16, this->size - 1 - i);
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
		os << std::endl;
		return os;
	}

	friend std::istream& operator>>(std::istream& in, const Hex& hex)
	{
		std::string s;
		std::cout << std::endl;
		while (getline(in, s))
		{
			std::cout << s << std::endl;
		}
		return in;
	}
};
#endif HEX.H