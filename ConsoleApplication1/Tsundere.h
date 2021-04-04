#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Tsundere :
    public type
{
public:
    virtual void Print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;
private:
    const int size = 2;
    const std::string name = "Tsundere";
    const int default_durability = 5;
};

