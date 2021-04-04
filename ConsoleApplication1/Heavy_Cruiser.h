#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Heavy_Cruiser :
    public type
{
public:
    virtual void Print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;
private:
    const int size = 3;
    const std::string name = "Heavy Cruiser";
    const int default_durability = 7;
};

