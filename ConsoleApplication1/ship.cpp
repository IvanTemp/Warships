#include <iostream>
#include <string>
#include <vector>
#include "ship.h"


ship::ship(const std::string& nm, const std::string& tp, const int IDen) :name(nm), type(tp), durability(0), ID(IDen)
{
    //Вопрос правильно ли вот так. Ведь на лекции int age мы инициалиризрооваплиотмсиоамиролап выше (:name(nm), role(rl), age(0))
    if (tp == "Aircraft Carrier") durability = 16;
    else if (tp == "Heavy Cruiser") durability = 18;
    else if (tp == "Tsundere") durability = 10;
    else if (tp == "Small") durability = 6;
}

void ship::Print() const
{
    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "[" << ID << "] " << name << ": ";
    std::cout << "Class: " << type << "; ";
    std::cout << "Durability: " << durability;
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

void ship::SetDurability(const int durabty)
{
    durability = durabty;
}

int ship::GetDurability() const
{
    return durability;
}

int ship::GetID() const
{
    return ID;
}
