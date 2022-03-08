// Zadanie2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#pragma execution_character_set("utf-8")

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "EmployeeControl.hpp"

const char PROMPT_STRING[] = "¬ыберите действие(номер):\r\n\
 1 просмотреть данные файла\r\n\
 2 добавить данные в файл\r\n\
 3 сортировка базы данных по алфавиту(по фамилии)\r\n\
 4 вывод: список людей, родившихс€ в заданном мес€це\r\n\
 5 вывод : фамилию самого старшего мужчины\r\n\
 6 вывод : все фамилии, начинающиес€ с заданной буквы\r\n\
 0 выход из программы\r\n";

int main()
{
    /* —охранить исходный текст с кодировкой / выбрать кодировку  ириллица (Windows), кодова€ страница 1251 */
    system("chcp 1251"); // настраиваем кодировку консоли
    system("cls");       // отмена вывода сообщени€ с кодировкой в консоли


    // ƒл€ работы использовал файл Employee.dat

    char buffer[256] = {0};
    std::cout << "¬ведите им€ файла \r\n";
    std::cin.getline(buffer, sizeof(buffer), '\n');
    if (std::cin.good())
    {
        std::cout << "Ќет ошибок ввода \r\n";
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
                std::cout << "\r\n¬ведите номер мес€ца\r\n";
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
                        std::cout << "ќшибка ввода номера мес€ца\r\n";
                    }
                }
                break;
            }
            case 5:
                Info.FilePrintOldMan();
                break;
            case 6:
            {
                std::cout << "\r\n¬ведите начальную букву фамилии\r\n";
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
            std::cout << "ќшибка ввода данных\r\n";
        }
    }
}


