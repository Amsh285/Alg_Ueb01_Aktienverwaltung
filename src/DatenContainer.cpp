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

void DatenContainer::Insert(Share* newShare)
{
    int found = 0;
    found = nameTable->Find(newShare->GetName());

    if(found == -1)   // if name not found, check token
    {
        found = tokenTable->Find(newShare->GetToken());
        if(found == -1)  // if token not found, insert in both tables and return
        {
            ShareContainer* temp = new ShareContainer(newShare);
            nameTable->Insert(temp, temp->GetValue()->GetName());
            tokenTable->Insert(temp, temp->GetValue()->GetToken());
            currentNumber++;
            return;
        }
    }

        // if either name or token is allready in the table, procced with this code
    std::cout << "error, share " << newShare->GetName() << "(" << newShare->GetToken() << ") allready exists" << std::endl;
}

int DatenContainer::Find(std::string key)
{
    int index = 0;

    index = nameTable->Find(key);
    if(index == -1)
        index = tokenTable->Find(key);

    return index;
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



