#pragma once
#include <vector>

#include "Book.h"
#include "Reader.h"

class Library
{
	std::string library_name;
	size_t last_book_code;
	size_t reader_card_number;
	std::vector<Book> books_pool;
	std::vector<Reader> readers_pool;
public:
	Library() = delete;
	Library(std::string name);
	std::string& get_library_name();
	void add_book(std::string& title, std::string& author);
	void add_reader(size_t reader_code, FIO& fio_data);
};
