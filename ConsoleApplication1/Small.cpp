#include "Small.h"

void Small::Print() const
{
    std::cout << name;
}

int Small::get_size() const
{
    return size;
}

std::string Small::get_name() const
{
    return name;
}

int Small::get_default_durability() const
{
    return default_durability;
}
