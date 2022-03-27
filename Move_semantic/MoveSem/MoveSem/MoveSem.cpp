// MoveSem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "VectorClass.hpp"

int main()
{
	Vector<int> v = { 7, 5, 16, 8 };

	v.push_back(1);

	std::cout << "Print with the operator <<\r\n";

	std::cout << v;

	std::cout << "Print with the iterator\r\n";

	std::for_each(v.cbegin(), v.cend(), [](const int& a)
		{
			std::cout << ": " << a << std::endl;
	    });
}
