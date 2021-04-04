#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Small :
    public type
{
public:
    virtual void Print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;
private:
    const int size = 1;
    const std::string name = "Small";
    const int default_durability = 4;
};

