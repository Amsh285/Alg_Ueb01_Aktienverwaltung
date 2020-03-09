#ifndef SHARE_H
#define SHARE_H

#include <string>

class Share
{
    public:
        Share();
        virtual ~Share();

        int GetHashCode();
        bool Equals(Share* value);
    protected:

    private:
        std::string name;
        std::string token;
        std::string isin;
};

#endif // SHARE_H
