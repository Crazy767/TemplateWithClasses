//Time
#include <iostream>
#include "time.h"

int main()
{
	Time time1;
	time1.print(); 

	Time time2(12, 34, 56);
	time2.print();

	time2 = time2 + 300;
	time2.print();

	time1 = time1 - 60;
	time1.print();

	bool b = time1 < time2;
	std::cout << b << std::endl;

	time1.input(1, 2, 3);
	time1.print();
}