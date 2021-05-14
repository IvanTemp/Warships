#pragma once
#include <string>
#include <iostream>

class BasicType
{
public:
	virtual ~BasicType() {};
	std::string get_name() { return name_; };
	void set_name(std::string nm) { this->name_ = nm; };
	void print() { std::cout << name_; };
	virtual int get_size()const = 0;
	virtual int get_damage_value()const = 0;
	virtual int get_default_durability()const = 0;
	virtual void print_commands()const = 0;
	virtual std::string get_description()const = 0;
	
private:
	std::string name_;
};