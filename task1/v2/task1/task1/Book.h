#pragma once
#include <string>
#include <ctime>

class Book
{
	size_t code;
	time_t registration_date;
	std::string title;
	std::string author;
	bool book_free;

public:
	Book() = delete;
	Book(size_t book_code, std::string& book_title, std::string& book_author);
	bool book_in_use_status();
	void set_book_in_use();
	void set_book_free();
};