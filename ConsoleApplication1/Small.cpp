#include "Small.h"

void Small::print() const
{
    std::cout << name_;
}

int Small::get_size() const
{
    return size_;
}

int Small::get_damage_value() const
{
    return default_durability_;
}

std::string Small::get_name() const
{
    return name_;
}

int Small::get_default_durability() const
{
    return default_durability_;
}