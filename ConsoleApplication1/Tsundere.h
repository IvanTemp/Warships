#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Tsundere :
    public type
{
public:
    virtual void print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;
private:
    const int size_ = 2;
    const std::string name_ = "Tsundere";
    const int default_durability_ = 5;
};

