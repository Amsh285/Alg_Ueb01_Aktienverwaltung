#ifndef SHAREENTRY_H
#define SHAREENTRY_H

#include <string>

class ShareEntry
{
    public:
        ShareEntry();
        virtual ~ShareEntry();

    protected:

    private:
        std::string date;
        double open;
        double high;
        double low;
        double close;
        double volume;
        double adjustedClose;
};

#endif // SHAREENTRY_H
