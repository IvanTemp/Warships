#pragma once
#include <string>

class type
{
public:
	virtual void Print()const = 0;
	virtual int get_size()const = 0;
	virtual std::string get_name()const = 0;
	virtual int get_default_durability()const = 0;
	virtual ~type() {};
};

