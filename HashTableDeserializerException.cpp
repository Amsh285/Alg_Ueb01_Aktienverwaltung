#include "HashTableDeserializerException.h"

HashTableDeserializerException::HashTableDeserializerException(std::string errorMessage)
    : errorMessage(errorMessage)
{
    //ctor
}

HashTableDeserializerException::~HashTableDeserializerException()
{
    //dtor
}

const char* HashTableDeserializerException::what() const throw()
{
    return errorMessage.c_str();
}
