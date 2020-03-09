#ifndef CSVLINEEXCEPTION_H
#define CSVLINEEXCEPTION_H

#include <string>

class CsvLineException : public std::exception
{
    public:
        CsvLineException();
        CsvLineException(std::string message);
        virtual ~CsvLineException();

        std::string GetMessage() const { return message; };
    protected:

    private:
        std::string message;
};

#endif // CSVLINEEXCEPTION_H
