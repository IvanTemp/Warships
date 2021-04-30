#pragma once
#include <string>

class BasicType
{
public:
	virtual void print()const = 0;
	virtual int get_size()const = 0;
	virtual int get_damage_value()const = 0;
	virtual std::string get_name()const = 0;
	virtual int get_default_durability()const = 0;
	virtual ~BasicType() {};
	virtual void print_commands()const = 0;
	virtual std::string get_description()const = 0;
};