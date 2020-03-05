#ifndef SHARE_H
#define SHARE_H

#include "HashUtilities.h"
#include "ShareEntry.h"

#include <string>
#include <list>

class Share
{
    public:
        Share(std::string name, std::string token, std::string isin);
        virtual ~Share();

        std::string GetName() const { return name; };
        std::string GetToken() const { return token; };
        std::string GetIsin() const { return isin; };
        std::list<ShareEntry> GetShareEntries() const { return shareEntries; };

        int GetHashCode();
        bool Equals(Share& value);
    protected:

    private:
        std::string name;
        std::string token;
        std::string isin;
        std::list<ShareEntry> shareEntries;

        friend std::ostream& operator<<(std::ostream& stream, const Share& value);
};

#endif // SHARE_H
