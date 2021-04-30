#pragma once
#include "BasicType.h"
#include <string>
#include <iostream>

class AircraftCarrier :
	public BasicType
{
public:
	AircraftCarrier() {}
	virtual ~AircraftCarrier() {}
	virtual void print()const override;
	virtual int get_size()const override;
	virtual int get_damage_value() const override;
	virtual std::string get_name()const override;
	virtual int get_default_durability()const override;
	virtual void print_commands()const override;
	virtual std::string get_description()const override;

private:
	const int size_ = 4;
	std::string name_ = "Aircraft Carrier";
	int default_durability_ = 5;
	const int damage_ = 4;
};