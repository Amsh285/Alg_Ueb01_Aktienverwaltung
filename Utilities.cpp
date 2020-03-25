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

namespace shareentryfactory
{
    ShareEntry *CreateFromCsvString(const std::string& value)
    {
        int numberOfExpectedColumns = 7;
        int actualColumnCount = 1;

        std::string tmp = value;
        std::vector<std::string> shareEntryData;

        std::string delimiter = ",";
        size_t position = 0;

        while((position = tmp.find(delimiter)) != std::string::npos)
        {
            shareEntryData.push_back(tmp.substr(0, position));
            tmp.erase(0, position + delimiter.length());
            ++actualColumnCount;
        }

        std::string test = tmp.substr(0, tmp.size());
        shareEntryData.push_back(test);

        if(numberOfExpectedColumns != actualColumnCount)
            throw CsvLineException(
                "Die Csv- Zeile weiﬂt ein ungueltiges Format auf es wurden " + std::to_string(numberOfExpectedColumns) +
                " erwartet. Es wurden aber nur " + std::to_string(actualColumnCount) + " gefunden." );

        /*
        Todo: think about this possible exceptions in the following code.

        If no conversion could be performed, an invalid_argument exception is thrown.
        If the value read is out of the range of representable values by a double
        (in some library implementations, this includes underflows), an out_of_range exception is thrown.
        */

        return new ShareEntry(shareEntryData[0], std::stod(shareEntryData[1], nullptr), std::stod(shareEntryData[2], nullptr)
            , std::stod(shareEntryData[3], nullptr), std::stod(shareEntryData[4], nullptr)
            , std::stod(shareEntryData[5], nullptr), std::stod(shareEntryData[6], nullptr));
    }
}
