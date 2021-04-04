#pragma once
#include "type.h"
#include <string>
#include <iostream>

class Aircraft_Carrier :
    public type
{
public:
    Aircraft_Carrier() {}
    virtual ~Aircraft_Carrier() {}
    virtual void Print()const override;
    virtual int get_size()const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;

private:
    const int size = 4;
    std::string name = "Aircraft Carrier";
    int default_durability = 6;
};

