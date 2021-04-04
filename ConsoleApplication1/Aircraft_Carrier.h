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
    virtual void print()const override;
    virtual int get_size()const override;
	virtual int get_damage_value() const override;
    virtual std::string get_name()const override;
    virtual int get_default_durability()const override;

private:
    const int size_ = 4;
    std::string name_ = "Aircraft Carrier";
    int default_durability_ = 6;
    const int damage_ = 3;
};