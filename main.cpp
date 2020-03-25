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
    std::vector<std::string> supportedCommands({"Help", "Add", "Del", "Import", "Search", "Plot", "Save", "Load", "Quit"});
    DatenContainer Table(SIZE);

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
            // Insert me...
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
            std::string shareKey, fileName;

            std::cout << "[Kursdaten Import] " << std::endl;

            std::cout << "Geben Sie den Namen oder das Kuerzel der Aktie an fuer die der Import durchgefuehrt werden soll: ";
            getline(std::cin, shareKey);

            /*
            Share* shareInQuestion = Table.Find(shareKey);
            if(shareInQuestion == NULL)
                std::cout << shareKey << " koennte nicht gefunden werden" << std::endl;
            else*/

                // insert
                // wie geht es weiter ab diesem schritt? machen wir weiter mit list oder
                // ändern wir auf vector?


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

   /* DatenContainer Table(SIZE);

    Share share1("Microsoft", "msft", "123");
    Share sharex("msft", "Microsoft", "23");  // gleiche aktie
  /*  Share share3("Microsoft", "bibi", "12451");  // gleicher name
    Share share4("wewe", "msft", "23");      // gleiches kürzel
    Share share5("Google", "ggl", "123321"); */

   /* Table.Insert(&share1);
    Table.Insert(&sharex); */
  /*  Table.Insert(&share3);
    Table.Insert(&share4);
    Table.Insert(&share5); */

   /* std::cout << "\n\n";

    std::cout << Table.Find("Microsoft") << " " << Table.Find("msft") << std::endl;
   // Table.Delete("msft");
    std::cout << Table.Find("Microsoft") << " " << Table.Find("msft") << std::endl;
    //Share share2("Microsoft", "msft", "123");
    //Table.Insert(&share2);
    std::cout << Table.Find("Microsoft") << " " << Table.Find("msft") << std::endl;
    Table.State();

 */




    return 0;
}


