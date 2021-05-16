#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class Small : public BasicType {
 public:
	Small() { set_name("Small"); };
	virtual int get_size()const override;
	virtual int get_damage_value()const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;
};