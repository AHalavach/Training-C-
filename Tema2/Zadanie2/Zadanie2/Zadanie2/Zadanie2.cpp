// Zadanie2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#pragma execution_character_set("utf-8")

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "EmployeeControl.hpp"

const char PROMPT_STRING[] = "�������� ��������(�����):\r\n\
 1 ����������� ������ �����\r\n\
 2 �������� ������ � ����\r\n\
 3 ���������� ���� ������ �� ��������(�� �������)\r\n\
 4 �����: ������ �����, ���������� � �������� ������\r\n\
 5 ����� : ������� ������ �������� �������\r\n\
 6 ����� : ��� �������, ������������ � �������� �����\r\n\
 0 ����� �� ���������\r\n";

int main()
{
    /* ��������� �������� ����� � ���������� / ������� ��������� ��������� (Windows), ������� �������� 1251 */
    system("chcp 1251"); // ����������� ��������� �������
    system("cls");       // ������ ������ ��������� � ���������� � �������


    // ��� ������ ����������� ���� Employee.dat

    char buffer[256] = {0};
    std::cout << "������� ��� ����� \r\n";
    std::cin.getline(buffer, sizeof(buffer), '\n');
    if (std::cin.good())
    {
        std::cout << "��� ������ ����� \r\n";
    }

    EmployeeControl Info(buffer);

    while (true)
    {
        std::cout << std::endl << PROMPT_STRING;
 
        int option = -1;
        std::cin >> option;

        if (std::cin.good())
        {
            switch (option)
            {
            case 0:
                exit(EXIT_SUCCESS);
            case 1:
                Info.FilePrintAllContent();
                break;
            case 2:
                Info.FileAddData();
                break;
            case 3:
                Info.FileSortData();
                break;
            case 4:
            {
                std::cout << "\r\n������� ����� ������\r\n";
                unsigned int Month = 0;
                std::cin >> Month;
                if (std::cin.good())
                {
                    if ((Month > 0) && (Month < 13))
                    {
                        Info.FilePrintListReqMonth(Month);
                    }
                    else
                    {
                        std::cout << "������ ����� ������ ������\r\n";
                    }
                }
                break;
            }
            case 5:
                Info.FilePrintOldMan();
                break;
            case 6:
            {
                std::cout << "\r\n������� ��������� ����� �������\r\n";
                char Letter;
                std::cin >> Letter;
                if (std::cin.good())
                {
                    Info.FilePrintSurname(Letter);
                }
                std::cin.ignore(32768, '\n');
                break;
            }
            default:
                break;
            }
        }
        else
        {
            std::cin.clear();
            std::cout << "������ ����� ������\r\n";
        }
    }
}


