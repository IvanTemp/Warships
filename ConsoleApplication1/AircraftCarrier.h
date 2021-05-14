#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class AircraftCarrier :
	public BasicType
{
public:
	AircraftCarrier() { set_name("Aircraft Carrier"); };
	virtual int get_size()const override;
	virtual int get_damage_value() const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;

private:
};