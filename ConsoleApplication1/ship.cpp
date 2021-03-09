#include <iostream>
#include <string>
#include <vector>
#include "ship.h"


ship::ship(const std::string& nm, const std::string& tp, const int IDen) :name(nm), type(tp), durability(1, 3), ID(IDen)
{
    //Вопрос правильно ли вот так. Ведь на лекции int age мы инициалиризрооваплиотмсиоамиролап выше (:name(nm), role(rl), age(0))
    if (tp == "Aircraft Carrier")
    {
        durability.resize(4);
        std::fill(durability.begin(), durability.end(), 4);
    }
    else if (tp == "Heavy Cruiser")
    {
        durability.resize(3);
        std::fill(durability.begin(), durability.end(), 5);
    }
    else if (tp == "Tsundere")
    {
        durability.resize(2);
        std::fill(durability.begin(), durability.end(), 5);
    }
}

void ship::Print() const
{
    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "[" << ID << "] " << name << ": ";
    std::cout << "Class: " << type << "; ";
    std::cout << "Durability: ";
    for (int i = 0; i < durability.size(); i++)
    {
        std::cout << " " << durability[i];
    }
    std::cout << "\n------------------------------------------------------------\n";
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
