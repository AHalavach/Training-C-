#include "Library.h"

Library::Library(std::string name) :
	library_name{ name },
	last_book_code{ 0 },
	reader_card_number{ 0 }
{}

std::string& Library::get_library_name()
{
	return library_name;
}

void Library::add_book(std::string& title, std::string& author)
{
	Book temp{ ++last_book_code, title, author };
	books_pool.push_back(temp);
}

void Library::add_reader(size_t reader_code, FIO& fio_data)
{
	Reader temp{ reader_code, ++reader_card_number, fio_data };
	readers_pool.push_back(temp);
}
