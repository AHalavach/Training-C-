#include <iostream>

#include "Reader.h"


Reader::Reader(size_t reader_code, size_t card_number, FIO& fio_data) :
	code{ reader_code },
	registration_card_number{ card_number },
	fio{ fio_data.Name , fio_data.FamilyName, fio_data.Patronymic }
{
	std::cout << "NEW RAEDER: code - " << code << ", card number - " << registration_card_number \
		<< ", name - " << fio.Name << ", family name - " << fio.FamilyName \
		<< ", patronymic - " << fio.Patronymic << std::endl;
}

FIO& Reader::get_reader_fio(size_t card_number)
{
	return fio;
}
