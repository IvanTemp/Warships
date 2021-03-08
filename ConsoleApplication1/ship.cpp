#include <iostream>
#include <string>
#include <vector>
#include "ship.h"


ship::ship(const std::string& nm, const std::string& tp) :name(nm), type(tp), durability(1, 3)
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
    std::cout << "Ship name is " << name;
    std::cout << "(" << type << ")" << std::endl;
    std::cout << "Durability is";
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

void ship::SetDurab(const std::vector<int> durabty)
{
    durability = durabty;
}

std::vector<int> ship::GetDurab() const
{
    return durability;
}

void ship::SetXYType(const std::pair<int, int> cord, const std::string tp)
{
    coord[cord.first][cord.second] = tp;
}

