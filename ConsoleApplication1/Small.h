#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class Small :
	public BasicType
{
public:
	virtual void print()const override;
	virtual int get_size()const override;
	virtual int get_damage_value()const override;
	virtual std::string get_name()const override;
	virtual int get_default_durability()const override;

	//added
	virtual void print_commands()const override;
private:
	const int size_ = 1;
	const std::string name_ = "Small";
	const int default_durability_ = 3;
	const int damage_ = 2;
};