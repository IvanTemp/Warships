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
	virtual  int get_damage_value() const override;
	virtual std::string get_name()const override;
	virtual int get_default_durability()const override;
private:
	const int size_ = 3;
	const std::string name_ = "Heavy Cruiser";
	const int default_durability_ = 6;
	const int damage_ = 1;
};