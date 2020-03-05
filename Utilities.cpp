#include "Utilities.h"

namespace stdstring
{
    std::string ToLower(const std::string& value)
    {
        std::string result = value;

        for(char& item : result)
            item = std::tolower(item);

        return result;
    }

    bool Equals(const std::string& left, const std::string& right, const StringComparisonOptions option)
    {
        if(option == StringComparisonOption_CaseSensitive)
            return left == right;
        else
            return ToLower(left) == ToLower(right);
    }

    std::string join(const std::vector<std::string> value, const std::string& separator)
    {
        std::string result = "";

        for(const std::string item : value)
        {
            std::string tmp = item;
            tmp.append(separator);

            result.append(tmp);
        }

        result.erase(result.length() - separator.length(), separator.length());
        return result;
    }
}
