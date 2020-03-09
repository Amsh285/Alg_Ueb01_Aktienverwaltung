#include "CsvLineException.h"

CsvLineException::CsvLineException()
{
    this->message = "";
}

CsvLineException::CsvLineException(std::string message)
{
    this->message = message;
}

CsvLineException::~CsvLineException()
{
    //dtor
}
