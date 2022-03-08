#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>


class EmployeeControl
{
	std::string m_file;
	static constexpr unsigned int _FieldQuantity = 7;
	static constexpr unsigned int _ArrayLEngth = 15;
	std::array<const char[_ArrayLEngth], _FieldQuantity> _RequiredParams {
		"Имя",
		"Фамилия",
		"Отчество",
		"Пол(м/ж)",
		"Год рождения",
		"Месяц рождения",
		"День рождения"};

	std::vector<std::string> ParseRecord(const char* Data);
	std::vector<std::vector<std::string>> FileGetAllContent();

public:
	EmployeeControl(const char *FileName);
	void FilePrintAllContent();
	void FileAddData();
	void FileSortData();
	void FilePrintListReqMonth(unsigned int Month);
	void FilePrintOldMan();
	void FilePrintSurname(char Letter);
};

