#include "Hashtable.h"
#include <iostream>
#include "../ShareContainer.h"
#include "../Share.h"
#include "../HashUtilities.h"
#include <string>

Hashtable::Hashtable(int numberOfShares)
{
    this->tableSize = 2 * numberOfShares;
    while(!isPrime(tableSize))
        tableSize++;                // table size is the a prime bigger than 2 * maximum number of shares
                                    // ensures a load factor of less than 50%

    ContainerTable = new ShareContainer*[tableSize];  // creates array of pointers
    for(int i = 0; i < tableSize; i++)
        this->ContainerTable[i] = NULL;
}


Hashtable::~Hashtable()
{
    delete[] ContainerTable;
}



void Hashtable::Insert(ShareContainer* ShareContainerAdress, std::string key)
{
    Share* ShareAdress = ShareContainerAdress->GetValue();
    int HashCode = HashUtilities::HashString(key);
    int index = CalculateIndex(HashCode);
    int originalIndex = index;
    int i = 1;

    while(!isEmpty(index))
    {
        if(ShareAdress->Equals(ContainerTable[index]->GetValue()))
        {
            std::cout << "error, share already exists";
            return;
        }
        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    ContainerTable[index] = ShareContainerAdress;
}




int Hashtable::Search(std::string key)
{
    int index = Find(key);
    return index;   // -1 index ==> share doesn't exist
}

void Hashtable::Delete(std::string key)
{
    int index = Find(key);
    if(index != -1)                  //when found
        ContainerTable[index]->DeleteContent();
}


ShareContainer* Hashtable::getShare(int index)
{
    return ContainerTable[index];
}














// --------------- Pirvate Functions ------------------

bool Hashtable::isPrime(int number)
{
    for(int i = 2; i < number; i++)
    {
        if(number % i == 0)
            return false;
    }
    return true;
}



bool Hashtable::isEmpty(int index)
{
    if(ContainerTable[index] == NULL)
        return true;
    else
        return false;
}



int Hashtable::CalculateIndex(int hashCode)
{
    int index = hashCode % tableSize;
    return index;
}




int Hashtable::Find(std::string key)
{
    int hashCode = HashUtilities::HashString(key);
    int index = CalculateIndex(hashCode);
    int originalIndex = index;
    int i = 1;

    while(ContainerTable[index] != NULL)
    {
        if(ContainerTable[index]->HasValue())
            if(ContainerTable[index]->GetValue()->GetName() == key || ContainerTable[index]->GetValue()->GetToken() == key){
                // if key is name or token, one general implementation
                return index;
            }

        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    return -1; // if not found, return -1 (invalid index)
}




/*int Hashtable::Probe(int originalIndex)
{
    int index = originalIndex;
    for(int i = 1; !isEmpty(index); i++)
        index = (originalIndex + (i*i)) % tableSize;

    return index;
}  */





