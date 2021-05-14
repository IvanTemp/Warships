#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class HeavyCruiser :
	public BasicType
{
public:
	virtual void print()const override;
	virtual int get_size()const override;
	virtual int get_damage_value() const override;
	virtual std::string get_name()const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;

private:
};