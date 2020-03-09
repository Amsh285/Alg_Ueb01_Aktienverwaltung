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
    std::vector<std::string> supportedCommands({"Help", "Add", "Del", "Import", "Search", "Plot", "Save", "Load", "Quit"});

    while(true)
    {
        std::string command;

        std::cout << "Aktienverwaltung" << std::endl;
        std::cout << "Enter a Command " << "(" << stdstring::join(supportedCommands, ", ") << "):" << std::endl;

        getline(std::cin, command);

        if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Add], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::string name, token, isin;

            std::cout << "[Aktie Erstellen] " << std::endl;

            std::cout << "Name: ";
            std::getline(std::cin, name);

            std::cout << "Token: ";
            std::getline(std::cin, token);

            std::cout << "ISIN: ";
            std::getline(std::cin, isin);

            Share *share = new Share(name, token, isin);
            // Insert me...

            std::cout << *share << std::endl;
            std::cout << "[Aktie Erstellen beendet] " << std::endl;
        }
        else if(stdstring::Equals(command, supportedCommands[ConsoleCommand_Import], stdstring::StringComparisonOption_CaseInSensitive))
        {
            std::string shareName, fileName;

            std::cout << "[Kursdaten Import] " << std::endl;

            std::cout << "Geben Sie den Namen der Aktie an fuer die der Import durchgefuehrt werden soll: ";
            getline(std::cin, shareName);


            // Todo: Check if Share Exists and extract Share.

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


            }
            else
                std::cout << "Die Datei: " << fileName << " konnte nicht geoeffnet werden" << std::endl;

            std::cout << "[Kursdaten Import beendet] " << std::endl;
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

    Hashtable nameTable(1000);
    Hashtable tokenTabel(1000);

    Share share1("Microsoft", "msft", "123");
    Share share2("Google", "ggl", "124");
    Share share3("Microsoft", "msft", "23");

    ShareContainer cntr1(&share1);
    ShareContainer cntr2(&share2);
    ShareContainer cntr3(&share3);

    nameTable.Insert(&cntr1, cntr1.GetValue()->GetName());
    tokenTabel.Insert(&cntr1, cntr1.GetValue()->GetToken());

    nameTable.Insert(&cntr2, cntr2.GetValue()->GetName());
    tokenTabel.Insert(&cntr2, cntr2.GetValue()->GetToken());

    nameTable.Insert(&cntr3, cntr3.GetValue()->GetName());
    tokenTabel.Insert(&cntr3, cntr3.GetValue()->GetToken());

    tokenTabel.Delete("msft");


    std::cout << tokenTabel.Search("msft") << "  " << tokenTabel.Search("ggl") << std::endl;
    std::cout << nameTable.Search("Microsoft") << "  " << nameTable.Search("Google");

    std::cout << "\n\n";

    int indexGoogle = nameTable.Search("Google");
    std::cout << nameTable.getShare(indexGoogle)->GetValue()->GetName() << std::endl;
    std::cout << nameTable.getShare(indexGoogle)->GetValue()->GetToken() << std::endl;
    std::cout << nameTable.getShare(indexGoogle)->GetValue()->GetIsin() << std::endl;


    return 0;
}


