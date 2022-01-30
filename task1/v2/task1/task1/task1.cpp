// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "Library.h"

const char* const COMMAND_READER = "reader";
const char* const COMMAND_BOOK = "book";
const char* const COMMAND_EXIT = "exit";

const char* const ENTER_READER_CODE = "Enter reader code:";
const char* const ENTER_RAEDER_NAME = "Enter reader name:";
const char* const ENTER_RAEDER__FAMILY_NAME = "Enter reader family name:";
const char* const ENTER_RAEDER_PATRONYMIC = "Enter reader patronymic:";

const char* const ENTER_BOOK_TITLE = "Enter book title:";
const char* const ENTER_BOOK_AUTHOR = "Enter book author:";

std::string get_cli_info(const char* data)
{
    std::string buffer{ "" };

    std::cout << data << std::endl;
    std::getline(std::cin, buffer);

    return buffer;
}


int main()
{
    Library lib{"One"};
    std::cout << "Welcome to the library " << lib.get_library_name() << std::endl;

    do
    {
        std::cout << "Enter new command : " << COMMAND_READER << "/" << COMMAND_BOOK << "/" << COMMAND_EXIT << std::endl;
        std::cout << std::endl;
        std::string buffer{""};
        std::getline(std::cin, buffer);

        if (!buffer.compare(COMMAND_READER))
        {
            size_t code = stoi(get_cli_info(ENTER_READER_CODE));
            std::string name{ get_cli_info(ENTER_RAEDER_NAME) };
            std::string family_name{ get_cli_info(ENTER_RAEDER__FAMILY_NAME) };
            std::string patronymic{ get_cli_info(ENTER_RAEDER_PATRONYMIC) };
                           
            FIO reader_fio{name, family_name, patronymic};

            lib.add_reader(code, reader_fio);
        }
        else if (!buffer.compare(COMMAND_BOOK))
        {
            std::string title{ get_cli_info(ENTER_BOOK_TITLE) };
            std::string author{ get_cli_info(ENTER_BOOK_AUTHOR) };
            lib.add_book(title, author);
        }
        else if (!buffer.compare(COMMAND_EXIT))
        {
            break;
        }
        else
        {
            std::cout << "Unrecognized command " << std::endl;
        }
    } while (1);



    return 0;
}