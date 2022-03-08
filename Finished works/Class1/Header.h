#ifndef HEADER.H
#define HEADER_H
class Distance
{
	double value;
public:
	Distance()
	{
		value = 0;
	}

	Distance(double _metr)
	{
		value = _metr;
	}

	~Distance()
	{
	}

	double to_km() {return this->value / 1000; }

	double to_mil() {return this->value / 1609;}

	Distance operator+ (const Distance& val) { return val.value + this->value; }
	Distance operator- (const Distance& val) { return this->value - val.value; }
	Distance operator* (const int val) { return this->value * val; }
	Distance operator= (const Distance& val) 
	{ 
		this->value = val.value;
		return val; 
	}
	bool operator==(const Distance& val) { return this->value == val.value; }
	bool operator!=(const Distance& val) { return this->value != val.value; }
	bool operator>(const Distance& val) { return this->value > val.value; }
	bool operator>=(const Distance& val) { return this->value >= val.value; }
	bool operator<(const Distance& val) { return this->value < val.value; }
	bool operator<=(const Distance& val) { return this->value <= val.value; }

	void print()
	{
		std::cout << this->value;
	}
};

#endif HEADER.H