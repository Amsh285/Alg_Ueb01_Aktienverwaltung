#ifndef DATENCONTAINER_H
#define DATENCONTAINER_H

#include <string>

#include "Hashtable.h"
#include "../ShareContainer.h"
#include "../Share.h"



    // Beschreibung:
    /*
    Daten Container verwaltet die Operationen in den 2 Hashtables (name und token)
    er erstellt die tables, er kümmert sich um Search, Delete, Insert in die richtige Tabelle, da wir zwei haben
    weiters zählt er mit, wie viele Shares aktuell drinnen sind und wie hoch der fuellgrad ist.
    er behandelt auch Probleme bei Insert von Aktien mit unterschiedlichem Namen und gleichem Kurzel bzw umgekehrt.
    vorher war dieser Fall nicht berücksichtigt in der Hashtable Klasse
    */

class DatenContainer
{
    public:
        DatenContainer(int);
        virtual ~DatenContainer();

        bool Insert(Share*);
        Share* Find(std::string);
        void Delete(std::string);
        void State();

        void SetNameTable(Hashtable* value) { nameTable = value; };
        void SetTokenTable(Hashtable* value) { tokenTable = value; };

        Hashtable* GetNameTable() const { return nameTable; };
        Hashtable* GetTokenTable() const { return tokenTable; };
    private:
        int currentNumber;
        double fillLevel;
        int capacity;
        Hashtable* nameTable;
        Hashtable* tokenTable;
};

#endif // DATENCONTAINER_H
