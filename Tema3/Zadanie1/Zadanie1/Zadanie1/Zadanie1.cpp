// Zadanie1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Test_class.hpp"
#include <stdexcept>



int main()
{
	try 
	{
		Integer<int8_t, SaturationPolicy> a1{ 64 };
		Integer<int8_t, SaturationPolicy> b1{ 2 };
		Integer<int8_t, SaturationPolicy> result1 = a1 * b1;

		Integer<int8_t, ThrowingPolicy> a2{ 64 };
		Integer<int8_t, ThrowingPolicy> b2{ 2 };
		Integer<int8_t, ThrowingPolicy> result2 = a2 * b2;

	}
	catch (const ArithmeticOverflowException* e)
	{
		std::cout << e->what() << std::endl;
	}
	catch (const ArithmeticUnderflowException* e)
	{
	    std::cout << e->what() << std::endl;
	}

}

