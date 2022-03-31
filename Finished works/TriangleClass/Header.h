#pragma once
#ifndef HEADER.H
#include <iostream>
#include <cmath>

class Point
{
	int x, y;
public:
	Point()
	{
		x = 0; y = 0;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point(const int& x, const int& y)
	{
		this->x = x;
		this->y = y;
	}
	~Point()
	{
	}


};

class Triangle
{
	Point pointt;
	int AB, AC, BC;
	int h;
	float p, S;
	// По трем сторонам
public:
	Triangle()
	{
		AB = 0; AC = 0; BC = 0; h = 0; p = 0; S = 0;
	}

	Triangle(int AB, int AC, int BC)
	{
		this->AB = AB;
		this->AC = AC;
		this->BC = BC;
	}
	//По основанию и высоте
	Triangle(int AB, int h)
	{
		this->AB = AB;
		this->h = h;
	}

	void inputTriangle(enum Type _type)
	{
		switch (_type)
		{
		case bySides:
			break;
		}
	}

	void SetAB(int AB) { this->AB = AB; }
	void SetAC(int AC) { this->AC = AC; }
	void SetBC(int BC) { this->BC = BC; }
};

class Menu
{
	int AB, AC, BC;
public:
	Menu()
	{
		AB = 0; AC = 0; BC = 0;
	}

	Triangle inputSide()
	{
		while (1)
		{
			std::cout << "Input 3 side of triangle (between space): ";
			std::cin >> AB >> BC >> AC;
			if (!(AB + BC > AC && AB + AC > BC && AC + BC > AB))
			{
				std::cout << "Input error: triangle dont exist" << std::endl;
				std::cout << "Try again" << std::endl;
				continue;
			}
			Triangle temp;
			temp.SetAB(AB);
			temp.SetAC(AC);
			temp.SetBC(BC);
			return temp;
		}
	}

};

#endif // !HEADER.H
