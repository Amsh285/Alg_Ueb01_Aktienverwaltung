#include "Hashtable.h"
#include <iostream>
#include "../ShareContainer.h"
#include "../Share.h"
#include "../HashUtilities.h"
#include <string>


Hashtable::Hashtable(int tableSize)
{
    this->tableSize = tableSize;

    ContainerTable = new ShareContainer*[tableSize];  // creates array of pointers
}

Hashtable::~Hashtable()
{
    delete[] ContainerTable;
}

bool Hashtable::Insert(ShareContainer* ShareContainerAdress, std::string key)
{
    Share* ShareAdress = ShareContainerAdress->GetValue();
    int index = (HashUtilities::HashString(key)) % this->tableSize;
    int originalIndex = index;
    int i = 1;

    while(!isEmpty(index))
    {
        if(ShareAdress->Equals(ContainerTable[index]->GetValue()))
            return false;

        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    ContainerTable[index] = ShareContainerAdress;
    return true;
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

ShareContainer* Hashtable::getShare(int index)
{
    return ContainerTable[index];
}   // nur zum testen

bool Hashtable::isEmpty(int index)
{
    if(ContainerTable[index] == NULL)
        return true;
    else
        return false;
}






