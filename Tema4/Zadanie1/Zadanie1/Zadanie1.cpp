// Zadanie1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Student.hpp"

const unsigned int GROUP_SIZE_LIMIT = 50;
static StudentInfo group1[30] = {};

int main()
{
	int ArrayLength;

	system("chcp 1251");
	system("cls");
	std::cout << "¬ведите размер группы студентов\r\n";
	std::cin >> ArrayLength;

	if (std::cin.good())
	{
		StudentInfo* group2 = nullptr;

		if (ArrayLength > GROUP_SIZE_LIMIT)
			ArrayLength = GROUP_SIZE_LIMIT;
		try
		{
			std::cout << "\r\n3. ¬ыделить динамический массив пам€ти  \r\n";
			group2 = new StudentInfo[ArrayLength];
				
			std::cout << "\r\n4. ѕолучить доступ к первому студенту из массива \r\n";
			group2[0].hasDriverLicense = false;
			group2[0].Age = 20;
			
			const char* email = "123@ab";
			const size_t  email_size = strlen(email);
			memcpy(group2[0].Email, email, email_size);
			group2[0].Email[email_size] = 0;
						
			std::cout << "\r\n5. ¬ычислить размер пам€ти, занимаемый массивом \r\n";
			std::cout << "–азмер пам€ти, занимаемый массивом:" << sizeof(StudentInfo) * ArrayLength << std::endl;

			std::cout << "\r\n6. ѕроитерироватьс€ по массиву студентов \r\n";
			StudentInfo *info = group2;
			StudentInfo* previous = group2;
			for (size_t i = 0; i < ArrayLength; i++)
			{
				int diff = reinterpret_cast<char*>(info) - reinterpret_cast<char*>(previous);
				std::cout << i << " : " << info << ", разница значений указателей: "<< diff << std::endl;
				previous = info;
				info++;
			}

			
			std::cout << "\r\n7. ¬ывести на консоль адреса соседних полей структуры \r\n";
			std::cout << &group2[0].hasDriverLicense << std::endl;
			std::cout << &group2[0].Age << std::endl;
			std::cout << &group2[0].FacultyCode << std::endl;
			std::cout << &group2[0].Name << std::endl;
			std::cout << &group2[0].Email << std::endl;

			std::cout << "\r\n8. —оздать структуру с таким же набором полей, но другой последовательностью полей\r\n";
			StudentInfoM student;
			std::cout << "–азмер структур: " << sizeof(StudentInfoM) << ", " << sizeof(StudentInfo) << std::endl;
	        
			std::cout << &student.Age << std::endl;
			std::cout << &student.Name << std::endl;
			std::cout << &student.FacultyCode << std::endl;
			std::cout << &student.hasDriverLicense << std::endl;
			std::cout << &student.Email << std::endl;

			delete[] group2;
		}
		catch (...)
		{
			delete[] group2;
			std::cout << "Exception \r\n";
		}
		
	}

}

