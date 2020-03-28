#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

#include "Hashtable.h"
#include "Share.h"
#include "HashUtilities.h"
#include "Utilities.h"
#include "ShareContainer.h"
#include "DatenContainer.h"
#include "DummyTableTestClass.h"

#include "HashTableSerializer.h"

#include "Json/StringHelper.h"
#include "Json/JsonUtilities.h"
//#include "HashTableDeserializer.h"


//#include "Json/InsideStringLiteralState.h"
//#include "Json/JsonParser.h"


#define SIZE 2003


enum ConsoleCommands {
    ConsoleCommand_Help,
    ConsoleCommand_Add,
    ConsoleCommand_Delete,
    ConsoleCommand_Import,
    ConsoleCommand_Search,
    ConsoleCommand_Plot,
    ConsoleCommand_Save,
    ConsoleCommand_Load,
    ConsoleCommand_Quit
};

int main()
{
    std::vector<std::string> supportedCommands({"Help", "Add", "Delete", "Import", "Search", "Plot", "Save", "Load", "Quit"});
    DatenContainer Table(SIZE);
    std::string shareKey; // search variable, user input will be saved here and operations will be conducted with this string

    while(true)
    {
        std::string command;

        std::cout << "Aktienverwaltung" << std::endl;
        std::cout << "Enter a Command " << "(" << stdstring::join(supportedCommands, ", ") << "):" << std::endl;

        getline(std::cin, command);

        if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Add], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::string name, token, isin;
            bool success;

            std::cout << "[Aktie Erstellen] " << std::endl;

            std::cout << "Name: ";
            std::getline(std::cin, name);

            std::cout << "Token: ";
            std::getline(std::cin, token);

            std::cout << "ISIN: ";
            std::getline(std::cin, isin);

            Share *share = new Share(name, token, isin);
            success = Table.Insert(share);

            if(success)
                std::cout << *share << " wurde erfolgreich eingeuegt" << std::endl;
            else
            {
               std::cout << *share << " konnte nicht eingefuegt werden" << std::endl;
               delete share;
            }

            std::cout << "[Aktie Erstellen beendet] " << std::endl;
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Import], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::string  fileName;

            std::cout << "[Kursdaten Import] " << std::endl;

            std::cout << "Geben Sie den Namen oder das Kuerzel der Aktie an fuer die der Import durchgefuehrt werden soll: ";
            getline(std::cin, shareKey);

            if(Table.Find(shareKey) == NULL)
            {
                std::cout << shareKey << " koennte nicht gefunden werden" << std::endl;
                continue;  // jump back to loop begin and ignore following code
            }

            std::cout << "Geben Sie einen Dateinamen fuer die Import ein: ";
            getline(std::cin, fileName);

            std::cout << "Importiere die Datei: " << fileName << std::endl;

            std::ifstream inputStream (fileName);

            if(inputStream.is_open())
            {
                std::string row;
                std::getline(inputStream, row);

                std::vector<ShareEntry*> entries;

                while(std::getline(inputStream, row))
                {
                    ShareEntry* item = shareentryfactory::CreateFromCsvString(row);
                    entries.push_back(item);
                }

                if(entries.size() > 30)
                {
                    std::vector<ShareEntry*>::const_iterator beginDeletes = entries.begin();
                    std::vector<ShareEntry*>::const_iterator beginTakes = entries.end() - 30;
                    std::vector<ShareEntry*>::const_iterator last = entries.end();

                    std::vector<ShareEntry*> deletes(beginDeletes, beginTakes);
                    std::vector<ShareEntry*> takes(beginTakes, last);

                    //std::cout << "delete.size(): " << deletes.size() << " " << "takes.size(): " << takes.size();

                    for(unsigned int i = 0;i < deletes.size();++i)
                        delete deletes[i];

                    Table.Find(shareKey)->setEntries(takes);
                }
                else
                    Table.Find(shareKey)->setEntries(entries);
            }
            else
                std::cout << "Die Datei: " << fileName << " konnte nicht geoeffnet werden" << std::endl;

            std::cout << "[Kursdaten Import beendet] " << std::endl;
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Plot], stdstring::StringComparisonOption_CaseInSensitive))
        {

            std::cout << "Geben Sie den Namen oder das Kuerzel der Aktie deren letzten 30 Boersenschlusswerte angezeigt werden sollen: ";
            getline(std::cin, shareKey);

            if(Table.Find(shareKey) == NULL)
            {
                std::cout << shareKey << " koennte nicht gefunden werden" << std::endl;
                continue;  // if not found, loop will jump back to start
            }
            Table.Find(shareKey)->plotLast30Close();

        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Search], stdstring::StringComparisonOption_CaseInSensitive))
        {

            std::cout << "Geben Sie den Namen oder das Kuerzel der Aktie die gesucht werden soll: ";
            getline(std::cin, shareKey);

            if(Table.Find(shareKey) == NULL)
            {
                std::cout << shareKey << " koennte nicht gefunden werden" << std::endl;
                continue;  // if not found, loop will jump back to start
            }
            Table.Find(shareKey)->printInfo();

        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Delete], stdstring::StringComparisonOption_CaseInSensitive))
        {

            std::cout << "Geben Sie den name oder das Kuerzel der Aktie die geloescht werden soll: ";
            getline(std::cin, shareKey);
            Table.Delete(shareKey);
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Save], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::cout << "Speichere Aktien..." << std::endl;

            HashTableSerializer serializer;

            serializer.SerializeHashTable(Table.GetNameTable(), "Data/nameTable.json");
            serializer.SerializeHashTable(Table.GetTokenTable(), "Data/tokenTable.json");

            std::cout << "Speichern beendet." << std::endl;
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Load], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::cout << "Lade Aktien..." << std::endl;

            /*
            HashTableDeserializer deserializer;
            HashTable* nameTable = deserializer.Deserialize("nameTable.json", SIZE);
            Hashtable* tokenTable = deserializer.Deserialize("tokenTable.json", SIZE);*/

            std::cout << "Laden beendet..." << std::endl;
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Quit], stdstring::StringComparisonOption_CaseInSensitive))
        {
            break;
        }
        else
        {
            std::cout << "Das Command: \"" << command << "\" wurde nicht erkannt." << std::endl;
        }
    }


    // ------ test code --------



    /*Share share1("Microsoft", "msft", "123");
    //Share sharex("msft", "Microsoft", "23");  // gleiche aktie
    Share share2("Microsoft", "msft", "123");

    Table.Insert(&share1);
    Table.Delete("msft");
    Table.Insert(&share2);
    //Table.Find("msft")->printInfo(); */


    DummyTableTestClass table;
    table.Insert(50);
    table.Insert(100);
    table.Insert(150);
    table.Insert(200);
    table.Insert(250);

    std::cout << table.getIndex(50) << std::endl;
    std::cout << table.getIndex(100) << std::endl;
    std::cout << table.getIndex(150) << std::endl;
    std::cout << table.getIndex(200) << std::endl;
    std::cout << table.getIndex(250) << std::endl;





    return 0;
}


