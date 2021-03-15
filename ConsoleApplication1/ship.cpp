#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "ship.h"


int ship::count = 0;


ship::ship(const int IDen) : ID(IDen), cID(count++)
{
}

ship::ship(const std::string& nm, const std::string& tp, const int IDen):name(nm), type(tp), durability(1, Small_Durability), ID(IDen), cID(count++)
{
    //Вопрос правильно ли вот так. Ведь на лекции int age мы инициалиризрооваплиотмсиоамиролап выше (:name(nm), role(rl), age(0))
    std::map<std::string, int> tptosize = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
    durability.resize(tptosize[type]);
    std::map<std::string, int> tptodur = { {"Aircraft Carrier", Aircraft_Carrier_Durability}, {"Heavy Cruiser", Heavy_Cruiser_Durability}, {"Tsundere", Tsundere_Durability}, {"Small", Small_Durability} };
    std::fill(durability.begin(), durability.end(), tptodur[type]);
}

void ship::Print(std::ostream& out) const
{
    out << "[" << ID << "]\t";
    out << name << "\t";
    if (name.size() < 6) out << "\t";
    out << "Type: " << type << "\t";
    if (type.size() < 9) out << "\t";
    out << "Durability: ";
    for (int i = 0; i < durability.size(); i++)
    {
        out << " " << durability[i];
    }
    out << std::endl;
}

void ship::Read(std::istream& in)
{
    std::string temp = "";
    std::getline(in, temp);
    ID = stoi(temp);
    std::getline(in, name);
    std::getline(in, type);
    //Вопрос правильно ли вот так. Инициализация после рида.
    std::map<std::string, int> tptosize = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
    durability.resize(tptosize[type]);
    std::map<std::string, int> tptodur = { {"Aircraft Carrier", Aircraft_Carrier_Durability}, {"Heavy Cruiser", Heavy_Cruiser_Durability}, {"Tsundere", Tsundere_Durability}, {"Small", Small_Durability} };
    std::fill(durability.begin(), durability.end(), tptodur[type]);
}

void ship::SetName(const std::string nm)
{
    name = nm;
}

std::string ship::GetName() const
{
    return name;
}

void ship::SetType(const std::string tp)
{
    type = tp;
}

std::string ship::GetType() const
{
    return type;
}

void ship::SetDurability(const std::vector<int> durabty)
{
    durability = durabty;
}

std::vector<int> ship::GetDurability() const
{
    return durability;
}

void ship::DmgtoInd(const int dmg, const int ind) {
    if (durability[ind] - dmg > 0) { durability[ind] -= dmg; }
}

int ship::GetID() const
{
    return ID;
}

bool ship::operator==(const ship& right) const
{
    bool durabilityIsEqual = false;
    std::string s = std::to_string(durability.size()) + std::to_string(right.durability.size());
    std::sort(s.begin(), s.end());
    for (int x = 0; x < s[0] - '0'; x++)
    {
        if (durability[x] == right.durability[x])
        {
            durabilityIsEqual = 1;
        }
        else
        {
            durabilityIsEqual = 0;
            break;
        }
    }
    return (name == right.name && type == right.type && ID == right.ID && durabilityIsEqual);
}

ship& ship::operator=(const ship& right)
{
    if (this != &right)
    {
        name = right.name;
        type = right.type;
        durability = right.durability;
    }
    return *this;
}


