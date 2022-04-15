#ifndef TIME_H // include guard
#define TIME_H

#include <iostream>
#include <string>
#include <cstdlib>

class Time
{
	int hour, min, sec, time_sec, flag = 0;
public:
	Time() 
	{
		hour = 0; min = 0; sec = 0; time_sec = 0;
	}

	Time(int _hour, int _min, int _sec) 
	{
		hour = _hour; min = _min; sec = _sec;
		time_sec = (hour * 3600) + (min * 60) + sec;
		if (hour >= 0 && hour < 24) { hour = _hour; }
		if (min >= 0 && min < 60) { min = _min; }
		if (sec >= 0 && sec < 60) { min = _min; }
		else { flag = 1; }
	}

	Time(int &_hour, int &_min, int &_sec) {}

	~Time() {}

	Time operator+(int t) // Сложение
	{
		Time temp;
		this->time_sec = this->time_sec + t;
		temp.hour = this->time_sec / 3600 % 24;
		temp.min = this->time_sec / 60 % 60;
		temp.sec = this->time_sec % 60;
		temp.time_sec = this->time_sec;
		return temp;
	}

	Time operator-(int t) // Вычитание
	{
		Time temp;
		if ((this->time_sec - t) < 0) { this->time_sec += 86400; }
		this->time_sec = abs(this->time_sec - t);
		temp.hour = this->time_sec / 3600 % 24;
		temp.min = this->time_sec / 60 % 60;
		temp.sec = this->time_sec % 60;
		temp.time_sec = this->time_sec;
		return temp;
	}

	Time operator=(Time* t)//Присваивание
	{
		Time temp;
		temp = t;
		return temp;
	}

	bool operator<(Time t) { return this->time_sec < t.time_sec; }

	bool operator<=(Time t) { return this->time_sec <= t.time_sec; }

	bool operator>(Time t) { return this->time_sec > t.time_sec; }

	bool operator>=(Time t) { return this->time_sec >= t.time_sec; }

	bool operator==(Time t) { return this->time_sec == t.time_sec; }

	bool operator!=(Time t) { return this->time_sec != t.time_sec; }


	void print() 
	{
		std::string h = std::to_string(hour);
		std::string m = std::to_string(min); 
		std::string s = std::to_string(sec);
		if (flag == 0)
		{ 
			if (hour < 10) { h = "0" + h; }
			if (min < 10) { m = "0" + m; }
			if (sec < 10) { s = "0" + s; }
			std::cout << h << ":" << m << ":" << s << std::endl;
		}
		else { std::cout  << "Error time!" << std::endl; }
	}

	void input(int _hour, int _min, int _sec)
	{
		hour = _hour; min = _min; sec = _sec;
		time_sec = (hour * 3600) + (min * 60) + sec;
		if (hour >= 0 && hour < 24) { hour = _hour; }
		if (min >= 0 && min < 60) { min = _min; }
		if (sec >= 0 && sec < 60) { min = _min; }
		else { flag = 1; }
	}
};

#endif /* TIME_H */