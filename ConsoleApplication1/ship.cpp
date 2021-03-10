#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ship.h"





ship::ship(const std::string& nm, const std::string& tp, const int IDen):name(nm), type(tp), durability(1, Small_Durability), ID(IDen)
{
    //Вопрос правильно ли вот так. Ведь на лекции int age мы инициалиризрооваплиотмсиоамиролап выше (:name(nm), role(rl), age(0))
    if (tp == "Aircraft Carrier")
    {
        durability.resize(4);
        std::fill(durability.begin(), durability.end(), Aircraft_Carrier_Durability);
    }
    else if (tp == "Heavy Cruiser")
    {
        durability.resize(3);
        std::fill(durability.begin(), durability.end(), Heavy_Cruiser_Durability);
    }
    else if (tp == "Tsundere")
    {
        durability.resize(2);
        std::fill(durability.begin(), durability.end(), Tsundere_Durability);
    }
}

void ship::Print() const
{
    std::cout << "[" << ID << "]\t";
    std::cout << name << "\t";
    if (name.size() < 8) std::cout << "\t";
    std::cout << "Type: " << type << "\t";
    if (type.size() < 9) std::cout << "\t";
    std::cout << "Durability: ";
    for (int i = 0; i < durability.size(); i++)
    {
        std::cout << " " << durability[i];
    }
    std::cout << std::endl;
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


