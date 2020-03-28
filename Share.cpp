#include "Share.h"
#include <iostream>
#include <iomanip>
#include <ios>

Share::Share(std::string name, std::string token, std::string isin)
{
    this->name = name;
    this->token = token;
    this->isin = isin;
}

Share::~Share()
{
    //dtor
}

int Share::GetHashCode()
{
    int hash = 17;

    hash = hash * 23 + HashUtilities::HashString(name);
    hash = hash * 23 + HashUtilities::HashString(token);

    return hash;
}

/*bool Share::Equals(Share* value)
{
    return name == value->name && token == value->token;
} */

void Share::setEntries(std::vector<ShareEntry*> &entries)
{
    this->shareEntries = entries;
}

void Share::plotLast30Close() const
{
    std::cout << "\n -- die letzten 30 Boersenschlusswerte fuer " << this->GetName() << " --\n\n";
    if(this->shareEntries.empty())
        std::cout << "diese Aktie hat noch keine Eintraege\n" << std::endl;
    else
    {
        std::cout << "                      150                170                190                210+\n" << std::endl;
        for(int i = this->shareEntries.size() - 1; i > this->shareEntries.size() - 30; i--)
        {
            int j = 0;
            std::cout << this->shareEntries[i]->GetDate() << "            ";
            for(; j < this->shareEntries[i]->GetClose() - 150 ; j++)
                std::cout << "-";

            for(; j < 70;j++)
                std::cout << " ";

            std::cout << std::setw(6) << std::left << this->shareEntries[i]->GetClose() << "\n";
        }
        std::cout << "\n";
    }

}

void Share::printInfo() const
{
    std::cout << "\nName:                 " << this->GetName() << std::endl;
    std::cout << "Kuerzel:              " << this->GetToken() << std::endl;
    std::cout << "Wertpapierkennnummer: " << this->GetIsin() << std::endl;
    std::cout << "\n-----------letzter Eintrag----------- " << std::endl;

    if(this->shareEntries.empty())
        std::cout << "diese Aktie hat noch keine Eintraege\n" << std::endl;
    else
    {
       int last = this->shareEntries.size() - 1;

        std::cout << "Date:        " << this->shareEntries[last]->GetDate() << std::endl;
        std::cout << "Open:        " << this->shareEntries[last]->GetOpen() << std::endl;
        std::cout << "High:        " << this->shareEntries[last]->GetHigh() << std::endl;
        std::cout << "Low:         " << this->shareEntries[last]->GetLow() << std::endl;
        std::cout << "Close:       " << this->shareEntries[last]->GetClose() << std::endl;
        std::cout << "Volume:      " << this->shareEntries[last]->GetVolume() << std::endl;
        std::cout << "Adj. Close:  " << this->shareEntries[last]->GetAdjustedClose() << std::endl;
        std::cout << "----------------------------------\n\n";
    }

}

std::ostream& operator<<(std::ostream& stream, const Share& value)
{
    std::string s;
    s.append("[Share]");
    s.append(" Name: ");
    s.append(value.name);

    s.append(" Token: ");
    s.append(value.token);

    s.append(" ISIN: ");
    s.append(value.isin);

    return stream << s;
}
