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

    nameTable = new Hashtable(capacity); // create both tables
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
       return askedShare;   // if share found in name table, return it
    }

    index = tokenTable->Find(key);   // else check in token table

    if(index != -1)
        askedShare = tokenTable->getShare(index);

    return askedShare;  // will return either share in token table or null if not found
}


void DatenContainer::Delete(std::string key)
{
    bool success = nameTable->Delete(key); // delete in name table and save status

    if(!success)
        success = tokenTable->Delete(key);  // try to delete in token table, if not found in name

    if(success) // if deleted, adjust statistics
    {
        std::cout << key << " deleted" << std::endl;

        currentNumber--;
        if(currentNumber < 0)
            currentNumber = 0;
    }
    else
        std::cout << "Aktie " << key  << " koennte nicht gefunden werden" << std::endl;
}

void DatenContainer::State()
{
    // prints fill level and current number of shares in the table
    this->fillLevel = (double) this->currentNumber / this->capacity;

    std::cout << "there are currently " << this->currentNumber << " shares in the table" << std::endl;
    std::cout << "the fill level of the table is: " << this->fillLevel << std::endl;
}



