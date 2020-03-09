#include "Hashtable.h"
#include <iostream>
#include "../ShareContainer.h"
#include "../Share.h"

Hashtable::Hashtable(int numberOfShares)
{
    this->tableSize = 2 * numberOfShares;
    while(!isPrime(tableSize))
        tableSize++;                // table size is the a prime bigger than 2 * maximum number of shares
                                    // ensures a load factor of less than 50%

    ContainerTable = new ShareContainer*[tableSize];  // creates array of pointers
}


Hashtable::~Hashtable()
{
    delete[] ContainerTable;
}



void Hashtable::Insert(ShareContainer* ShareContainerAddress)
{
    Share* ShareAdress = ShareContainerAddress->GetValue();
    int HashCode = ShareAdress->GetHashCode();
    int index = CalculateIndex(HashCode);  // get index from hashcode
    int originalIndex = index;      // save original index to probe with
    int i = 1;

    while(!isEmpty(index))
    {
        if(ShareAdress->Equals(ContainerTable[index]))
        {
            std::cout << "error, share already exists";
            return;
        }
        index = (originalIndex + (i*i)) % tableSize;
        i++;
    }

    ContainerTable[index] = ShareContainerAddress;
}

int Hashtable::Search(int hashCode)
{
    int index = Find(hashCode);
    return index;
}

void Hashtable::Delete(int hashCode)
{
    int index = Find(hashCode);
    if(index != -1)                  //when found
        ContainerTable->hasValue = false; //private, can't delete
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




int Hashtable::Find(int hashCode)
{
    int index = CalculateIndex(hashCode);
    int originalIndex = index;
    int i = 1;

    while(!isEmpty(ContainerTable[index]))
    {
        if(ContainerTable[index]->HasValue())
            if(ContainerTable[index]->GetValue()->Equals()) //??????? compare with what ??????
                return index;

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





