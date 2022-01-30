#include <iostream>

#include "Book.h"



Book::Book(size_t book_code, std::string& book_title, std::string& book_author) :
	code{book_code},
	title{book_title},
	author{book_author},
	book_free{true}
{
	registration_date = time(0);
	std::cout << "NEW BOOK: code - " << code << ", title - " << book_title << ", author - " << book_author << std::endl;
}

bool Book::book_in_use_status()
{
	return book_free;
}

void Book::set_book_in_use()
{
	book_free = false;
}

void Book::set_book_free()
{
	book_free = true;
}