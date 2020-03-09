#ifndef SHAREENTRY_H
#define SHAREENTRY_H

#include <string>

class ShareEntry
{
    public:
        ShareEntry(std::string date, double open, double high, double low, double close, double volume, double adjustedClose);
        virtual ~ShareEntry();

        std::string GetDate() { return date; };
        double GetOpen() { return open; };
        double GetHigh() { return high; };
        double GetLow() { return low; };
        double GetClose() { return close; };
        double GetVolume() { return volume; };
        double GetAdjustedClose() { return adjustedClose; };
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
