#include "ShareEntry.h"

ShareEntry::ShareEntry(std::string date, double open, double high, double low, double close, double volume, double adjustedClose)
{
    this->date = date;
    this->open = open;
    this->high = high;
    this->low = low;
    this->close = close;
    this->volume = volume;
    this->adjustedClose = adjustedClose;
}

ShareEntry::~ShareEntry()
{
    //dtor
}
