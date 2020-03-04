#include "Share.h"

Share::Share()
{
    //ctor
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

bool Share::Equals(Share& value)
{
    return name == value.name && token == value.token;
}
