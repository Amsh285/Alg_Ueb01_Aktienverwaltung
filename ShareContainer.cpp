#include "ShareContainer.h"

ShareContainer::ShareContainer(Share *value)
{
    if(value == nullptr)
        throw std::invalid_argument("value cannot null.");

    this->value = value;
    this->hasValue = true;
}

ShareContainer::~ShareContainer()
{
    //dtor
}

void ShareContainer::DeleteContent()
{
    delete this->value;
    this->hasValue = false;
}
