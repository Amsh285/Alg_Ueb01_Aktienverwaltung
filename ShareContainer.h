#ifndef SHARECONTAINER_H
#define SHARECONTAINER_H

#include "Share.h"
#include "ShareContainer.h"

class ShareContainer
{
    public:
        ShareContainer();
        virtual ~ShareContainer();

        bool HasValue();
        Share *GetValue();
    protected:

    private:
        bool hasValue;
        Share *value;
};

#endif // SHARECONTAINER_H
