#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../ShareContainer.h"

#include <string>
#include <cmath>

class Hashtable
{
    public:
        Hashtable(int);
        virtual ~Hashtable();
        void Insert(ShareContainer*, std::string);
        bool Delete(std::string);
        int Find(std::string);
        Share* getShare(int);

        int GetTableSize() const { return tableSize; };
        ShareContainer** GetItems() const { return ContainerTable; };

    private:
        bool isEmpty(int);
        int GetHashIndex(std::string key);

        int tableSize;
        ShareContainer** ContainerTable;  // double pointer
};

#endif // HASHTABLE_H
