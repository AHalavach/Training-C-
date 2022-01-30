#pragma once
#include <string>

struct FIO
{
	std::string Name;
	std::string FamilyName;
	std::string Patronymic;
};

class Reader
{
	size_t code;
	size_t registration_card_number;
	FIO fio;

public:
	Reader() = delete;
	Reader(size_t reader_code, size_t card_number, FIO& fio_data);
	FIO& get_reader_fio(size_t card_number);
};