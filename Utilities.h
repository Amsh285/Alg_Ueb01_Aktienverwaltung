#ifndef UTILITIES_H
#define UTILITIES_H

#include "CsvLineException.h"
#include "ShareEntry.h"

#include <vector>
#include <string>

namespace stdstring
{
    enum StringComparisonOptions
    {
        StringComparisonOption_CaseSensitive,
        StringComparisonOption_CaseInSensitive
    };

    std::string ToLower(const std::string& value);
    bool Equals(const std::string& left, const std::string& right, const StringComparisonOptions option);
    std::string join(const std::vector<std::string> value, const std::string& separator);
}

namespace shareentryfactory
{
    ShareEntry *CreateFromCsvString(const std::string& value);
}

#endif // UTILITIES_H
