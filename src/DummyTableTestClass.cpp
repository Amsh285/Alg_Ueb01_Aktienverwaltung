#include "DummyTableTestClass.h"

DummyTableTestClass::DummyTableTestClass()
{
    for(int i = 0; i < 50; i++)
        this->Array[i] = -1;
}

DummyTableTestClass::~DummyTableTestClass()
{
    //dtor
}

void DummyTableTestClass::Insert(int value)
{
    int originalIndex = 5;
    int index = 5;
    int i = 0;

    while(Array[index] != -1)
    {
        index = (originalIndex + (i*i)) % 50;
        i++;
    }

    this->Array[index] = value;

}

int DummyTableTestClass::getIndex(int value)
{
    int originalIndex = 5;
    int index = 5;
    int i = 0;

    while(Array[index] != value)
    {
        index = (originalIndex + (i*i)) % 50;
        i++;
    }

    return index;
}

void DummyTableTestClass::Delete(int value)
{
    int originalIndex = 5;
    int index = 5;
    int i = 0;

    while(Array[index] != value)
    {
        index = (originalIndex + (i*i)) % 50;
        i++;
    }

    this->Array[index] = -2;
}
