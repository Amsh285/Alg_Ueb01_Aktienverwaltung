#ifndef SHARECONTAINER_H
#define SHARECONTAINER_H

#include "Share.h"
#include <stdexcept>

class ShareContainer
{
    public:
        ShareContainer();
        ShareContainer(Share *value);
        virtual ~ShareContainer();

        bool HasValue();
        Share *GetValue();

        void DeleteContent();
    protected:

    private:
        bool hasValue;
        Share *value;
};

#endif // SHARECONTAINER_H
