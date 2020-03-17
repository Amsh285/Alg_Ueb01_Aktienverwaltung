#include "Hashtable.h"
#include "../ShareContainer.h"
#include "../Share.h"
#include "../HashUtilities.h"

#include <string>
#include <iostream>


Hashtable::Hashtable(int tableSize)
{
    this->tableSize = tableSize;

    ContainerTable = new ShareContainer*[tableSize];  // creates array of pointers
}

Hashtable::~Hashtable()
{
    delete[] ContainerTable;
}

void Hashtable::Insert(ShareContainer* ShareContainerAdress, std::string key)
{
    int index = (HashUtilities::HashString(key)) % this->tableSize;
    int originalIndex = index;
    int i = 1;

    while(!isEmpty(index))
    {
        if(!(ContainerTable[index]->HasValue()))       // if bucket is not empty but has no value (deleted share)
        {
            delete ContainerTable[index];                // delete container to make room for new one
            break;                                       // break loop and insert
        }

        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    ContainerTable[index] = ShareContainerAdress;
}

int Hashtable::Find(std::string key)
{
    int index = (HashUtilities::HashString(key)) % this->tableSize;
    int originalIndex = index;
    int i = 1;

    while(ContainerTable[index] != NULL)
    {
        if(ContainerTable[index]->HasValue())
            if(ContainerTable[index]->GetValue()->GetName() == key || ContainerTable[index]->GetValue()->GetToken() == key)
            {
                // if key is name or token, one general implementation
                return index;
            }

        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    return -1; // if not found, return -1 (invalid index)
}

bool Hashtable::Delete(std::string key)
{
    int index = Find(key);
    if(index != -1)             //when found
    {
        ContainerTable[index]->DeleteContent();
        return true;   // returns true, when element found and deleted
    }
    return false;   // returns false, when element could not be found
}

Share* Hashtable::getShare(int index)
{
    return ContainerTable[index]->GetValue();
}

bool Hashtable::isEmpty(int index)
{
    if(ContainerTable[index] == NULL)
        return true;
    else
        return false;
}






