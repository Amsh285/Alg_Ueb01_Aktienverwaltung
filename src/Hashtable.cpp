#include "Hashtable.h"
#include "../ShareContainer.h"
#include "../Share.h"
#include "../HashUtilities.h"

#include <string>
#include <iostream>


Hashtable::Hashtable(int tableSize)
{
    this->tableSize = tableSize;

    ContainerTable = new ShareContainer*[tableSize];  // creates array of pointers to shareContainers

    for(int i = 0;i < tableSize;++i)
        ContainerTable[i] = NULL;
}

Hashtable::~Hashtable()
{
    delete[] ContainerTable;
}

void Hashtable::Insert(ShareContainer* ShareContainerAdress, std::string key)
{
    int index = GetHashIndex(key);
    int originalIndex = index;  // save original index to probe with
    int i = 1;

    while(!isEmpty(index))  // find next empty spot
    {
        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    ContainerTable[index] = ShareContainerAdress;  // insert at this spot
}

int Hashtable::Find(std::string key)
{
    int index = GetHashIndex(key);
    int originalIndex = index;
    int i = 1;

    while(!isEmpty(index)) // search as long as current index is not empty
    {
        if(ContainerTable[index]->HasValue())
        {
            std::string scheissC = ContainerTable[index]->GetValue()->GetName();

            if(ContainerTable[index]->GetValue()->GetName() == key || ContainerTable[index]->GetValue()->GetToken() == key)
            {
                return index; // if key is name or token, one general implementation
            }
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

int Hashtable::GetHashIndex(std::string key)
{
    int hashIndex = HashUtilities::HashString(key);
    return std::abs(hashIndex % this->tableSize);
}




