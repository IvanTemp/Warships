#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Heavy_Cruiser :
    public type
{
public:
    virtual void print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;
private:
    const int size_ = 3;
    const std::string name_ = "Heavy Cruiser";
    const int default_durability_ = 7;
};

