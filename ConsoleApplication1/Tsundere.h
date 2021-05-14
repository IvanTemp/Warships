#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class Tsundere :
	public BasicType
{
public:
	Tsundere() { set_name("Tsundere"); };
	virtual int get_size()const override;
	virtual int get_damage_value()const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;
};