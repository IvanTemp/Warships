#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class HeavyCruiser :
	public BasicType
{
public:
	HeavyCruiser() { set_name("Heavy Cruiser"); };
	virtual int get_size()const override;
	virtual int get_damage_value() const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;
};