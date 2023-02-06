#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class Leviathan : public BasicType {
public:
	Leviathan() { set_name("Leviathan"); };
	virtual int get_size()const override;
	virtual int get_damage_value() const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;
};