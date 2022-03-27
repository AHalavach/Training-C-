#pragma once

const size_t CHAR_FIELD_LENGTH = 64;

struct StudentInfo
{
	bool hasDriverLicense;
	unsigned short Age;
	unsigned int FacultyCode;
	char Name[CHAR_FIELD_LENGTH];
	char Email[CHAR_FIELD_LENGTH];
};

struct StudentInfoM
{
	unsigned short Age;
	char Name[CHAR_FIELD_LENGTH];
	unsigned int FacultyCode;
	bool hasDriverLicense;
	char Email[CHAR_FIELD_LENGTH];
};