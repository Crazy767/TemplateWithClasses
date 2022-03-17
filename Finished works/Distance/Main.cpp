#include<iostream>
#include "Header.h"

int main()
{
	Distance dist(1234);
	Distance dist2(500);
	dist.print();
	std::cout << " m = " << dist.to_km() << " km" << std::endl;
	dist2.print();
	std::cout << " m = " << dist2.to_mil() << " mil" << std::endl;

	dist = dist + dist2;
	dist.print();

}