#include "HashUtilities.h"

namespace HashUtilities
{
    int HashString(const std::string& value)
    {
        int hash = 0;

        std::string::size_type length = value.length();

        for(std::string::size_type i = 0;i < length;++i)
            hash += value[i] * pow(11, length - (i + 1));

        return hash;
    }
}
