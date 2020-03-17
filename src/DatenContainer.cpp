#include <iostream>

#include "DatenContainer.h"
#include "Hashtable.h"
#include "../ShareContainer.h"
#include "../Share.h"


DatenContainer::DatenContainer(int capacity)
{
    this->capacity = capacity;
    this->fillLevel = 0;
    this->currentNumber = 0;

    nameTable = new Hashtable(capacity);
    tokenTable = new Hashtable(capacity);
}

DatenContainer::~DatenContainer()
{
    delete nameTable;
    delete tokenTable;
}

bool DatenContainer::Insert(Share* newShare)
{
    int found = 0;
    found = nameTable->Find(newShare->GetName());

    if(found == -1)   // check for name in name table
    {
        found = tokenTable->Find(newShare->GetToken());
        if(found == -1)  // check for token in token table
        {
            found = tokenTable->Find(newShare->GetName());  // check for name in token table
            if(found == -1)
            {
                found = nameTable->Find(newShare->GetToken());   // check for token in name table
                if(found == -1)
                {
                    ShareContainer* temp = new ShareContainer(newShare);
                    nameTable->Insert(temp, temp->GetValue()->GetName());
                    tokenTable->Insert(temp, temp->GetValue()->GetToken());
                    currentNumber++;
                    return true;   // when inserted, return true
                }
            }
        }
    }

    return false;   // if not inserted, return false
}

Share* DatenContainer::Find(std::string key)
{
    int index = 0;
    Share* askedShare = NULL;

    index = nameTable->Find(key);
    if(index != -1)
    {
       askedShare = nameTable->getShare(index);
       return askedShare;   // if share found in name table, return
    }

    index = tokenTable->Find(key);   // else check in token table

    if(index != -1)
        askedShare = tokenTable->getShare(index);

    return askedShare;
}


void DatenContainer::Delete(std::string key)
{
    bool success = nameTable->Delete(key);

    if(!success)
        success = tokenTable->Delete(key);

    if(success)
    {
        std::cout << key << " deleted" << std::endl;

        currentNumber--;
        if(currentNumber < 0)
            currentNumber = 0;
    }
    else
        std::cout << "Share " << key  << " could not be found" << std::endl;
}

void DatenContainer::State()
{
    this->fillLevel = (double) this->currentNumber / this->capacity;

    std::cout << "there are currently " << this->currentNumber << " shares in the table" << std::endl;
    std::cout << "the fill level of the table is: " << this->fillLevel << std::endl;
}



