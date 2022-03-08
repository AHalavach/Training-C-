#include "EmployeeControl.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <iostream>
#include <cctype>


static const size_t READ_BUFFER_LENGTH = 100;
static const char DATA_DELIMITER = ';';

EmployeeControl::EmployeeControl(const char* FileName) :
	m_file(FileName)
{}

std::vector<std::string> EmployeeControl::ParseRecord(const char* Data)
{
	std::string s(Data);
	std::vector<std::string> Person;
	Person.reserve(_FieldQuantity);

	auto start = 0U;
	auto end = s.find(DATA_DELIMITER);
  	size_t VecPos = 0;

	while (end != std::string::npos)
	{   
		if (VecPos > _FieldQuantity)
		{
			Person.clear();
			break;
		}

		Person.push_back(s.substr(start, end - start));
		VecPos++;
		start = end + sizeof(DATA_DELIMITER);
		end = s.find(DATA_DELIMITER, start);
	}
	
	return Person;
}

std::vector<std::vector<std::string>> EmployeeControl::FileGetAllContent()
{
	std::ifstream infile(m_file.c_str());
	std::vector<std::vector<std::string>> Result;

	if (!infile)
	{
		std::cout << "Невозможно открыть файл " << m_file.c_str() << std::endl;
		std::cout << "Код ошибки = " << infile.rdstate() << std::endl;
	}
	else
	{
		char buffer[READ_BUFFER_LENGTH];

		while (infile)
		{
			infile.getline(buffer, 100);
			std::vector<std::string> Record = ParseRecord(buffer);

			if (!Record.empty())
			{
				Result.push_back(Record);
			}
		}
	}

	return Result;
}

void EmployeeControl::FilePrintAllContent()
{
	std::vector<std::vector<std::string>> Content = FileGetAllContent();

	if (!Content.empty())
	{
		for (auto& item : Content)
		{
			if (!item.empty())
			{
				std::cout << std::endl;

				for (size_t i = 0; i < _FieldQuantity; i++)
				{
					std::cout << _RequiredParams[i] << " : " << item[i] << std::endl;
				}
			}
		}
	}
}

void EmployeeControl::FileAddData()
{
	std::ofstream outfile;
	outfile.open(m_file.c_str(), std::ios::app);

	if (!outfile)
	{
		std::cout << "Невозможно открыть файл " << m_file.c_str() << std::endl;
		std::cout << "\nКод ошибки = " << outfile.rdstate();
	}
	else
	{
		std::cout << "Файл " << m_file.c_str() << " открыт" << std::endl;
		std::string content;
		std::string buffer;
		std::cin.ignore(32678, '\n');

		for (auto &item : _RequiredParams)
		{
			std::cout << item << std::endl;
			std::getline(std::cin, buffer);
			content.append(buffer);
			content.push_back(DATA_DELIMITER);
		}
		content.push_back('\n');

		// write data to the file
		outfile << content;
	}


}

void EmployeeControl::FileSortData()
{
	const char *ParamName = "Фамилия";
	std::vector<std::vector<std::string>> Content = FileGetAllContent();

	size_t Number = 0;
	for (size_t i = 0; i < _FieldQuantity; i++)
	{
		if (strcmp(_RequiredParams[i], ParamName) == 0)
		{
			Number = i;
			break;
		}
	}

	if (!Content.empty())
	{
		std::sort(Content.begin(), Content.end(), [Number](std::vector<std::string>& A, std::vector<std::string>& B) {
			int RetValue = A[Number].compare(B[Number]);
			bool Result = false;

			if (RetValue < 0)
			{
				Result = true;
			}

			return Result;
			});

		for (auto& item : Content)
		{
			if (!item.empty())
			{
				std::cout << std::endl;

				for (size_t i = 0; i < _FieldQuantity; i++)
				{
					std::cout << _RequiredParams[i] << " : " << item[i] << std::endl;
				}
			}
		}

	}
}

void EmployeeControl::FilePrintListReqMonth(unsigned int Month)
{
	const char* ParamName = "Месяц рождения";
	std::vector<std::vector<std::string>> Content = FileGetAllContent();

	size_t Number = 0;
	for (size_t i = 0; i < _FieldQuantity; i++)
	{
		if (strcmp(_RequiredParams[i], ParamName) == 0)
		{
			Number = i;
			break;
		}
	}

	if (!Content.empty())
	{
		std::for_each(Content.begin(), Content.end(), [Month, Number](std::vector<std::string>& Data) {
			
			try
			{
				unsigned int BirthMonth = stoi(Data[Number]);
				if (Month == BirthMonth)
				{
					std::cout << std::endl;

				   for (size_t i = 0; i < _FieldQuantity; i++)
				   {
					   std::cout << Data[i] << std::endl;
				   }
				}
			}
			catch (std::invalid_argument const& ex)
			{
				std::cout << "#1: " << ex.what() << std::endl;
			}
			catch (const std::out_of_range const& oor)
			{
				std::cerr << "#2: " << oor.what() << '\n';
			}
			});
	}
}

void EmployeeControl::FilePrintOldMan()
{
    std::vector<std::vector<std::string>> Content = FileGetAllContent();

	unsigned int OldestBirthYear = 2022;
	unsigned int OldestBirthMonth = 1;
	unsigned int OldestBirthDay = 1;

	if (!Content.empty())
	{
		std::array<unsigned int, 3> Params{2022, 12, 12};
		std::string Oldest{""};
		std::for_each(Content.begin(), Content.end(), [&Params, &Oldest](std::vector<std::string>& Data) {
			try
			{
				unsigned int BirthYear = stoi(Data[4]);
				unsigned int BirthMonth = stoi(Data[5]);
				unsigned int BirthDay = stoi(Data[5]);

				if (BirthYear < Params[0])
				{
					Params[0] = BirthYear;
					Params[1] = BirthMonth;
					Params[2] = BirthDay;
					Oldest = Data[1];
				}
				else if (BirthYear == Params[0])
				{
					if (BirthMonth < Params[1])
					{
						Params[1] = BirthMonth;
						Params[2] = BirthDay;
						Oldest = Data[1];
					}
					else if (BirthYear == Params[0])
					{
						if (BirthDay < Params[2])
						{
							Params[2] = BirthDay;
							Oldest = Data[1];
						}
					}
				}
			}
			catch (std::invalid_argument const& ex)
			{
				std::cout << "#1: " << ex.what() << std::endl;
				return;
			}
			catch (const std::out_of_range const& oor)
			{
				std::cerr << "#2: " << oor.what() << '\n';
				return;
			}
			});

		std::cout << "Самый старший человек: " << Oldest << std::endl;
	}
}

void EmployeeControl::FilePrintSurname(char Letter)
{
	std::vector<std::vector<std::string>> Content = FileGetAllContent();
	
	// Преобразование в символ верхнего регистра
	if (Letter > -64)
	{
		Letter -= 32;
	}
	std::cout << "Список фамилий на букву " << Letter << " : \r\n";

	std::for_each(Content.begin(), Content.end(), [Letter](std::vector<std::string>& Data) {

		if (Data[1].data()[0] == Letter)
		{
			std::cout << Data[1] << std::endl;
		}
	});
}
