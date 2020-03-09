#include "Share.h"

Share::Share(std::string name, std::string token, std::string isin)
{
    this->name = name;
    this->token = token;
    this->isin = isin;
}

Share::~Share()
{
    //dtor
}

int Share::GetHashCode()
{
    int hash = 17;

    hash = hash * 23 + HashUtilities::HashString(name);
    hash = hash * 23 + HashUtilities::HashString(token);

    return hash;
}

bool Share::Equals(Share* value)
{
    return name == value->name && token == value->token;
}

std::ostream& operator<<(std::ostream& stream, const Share& value)
{
    std::string s;
    s.append("[Share]");
    s.append(" Name: ");
    s.append(value.name);

    s.append(" Token: ");
    s.append(value.token);

    s.append(" ISIN: ");
    s.append(value.isin);

    return stream << s;
}
