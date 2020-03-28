#ifndef HASHTABLEDESERIALIZEREXCEPTION_H
#define HASHTABLEDESERIALIZEREXCEPTION_H

#include <stdexcept>
#include <string>

class HashTableDeserializerException : public std::exception
{
    public:
        HashTableDeserializerException(std::string errorMessage);
        virtual ~HashTableDeserializerException();

        virtual const char* what() const throw();
    protected:

    private:
        std::string errorMessage;
};

#endif // HASHTABLEDESERIALIZEREXCEPTION_H
