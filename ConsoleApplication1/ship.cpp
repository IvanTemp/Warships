#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Ship.h"
#include "AircraftCarrier.h"
#include "HeavyCruiser.h"
#include "Tsundere.h"
#include "Small.h"


int Ship::count_ = 0;

Ship::Ship(const std::string& nm, const int IDen) : name_(nm), id_(IDen), type_(nullptr), cid_(count_++)
{
}

Ship::Ship(const std::string& nm, BasicType& tp, const int IDen) : name_(nm), id_(IDen), type_(&tp), cid_(count_++)
{
	durability_.resize(type_->get_size());
	std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void Ship::print(std::ostream& out) const
{
	out << "[" << id_ << "]\t";
	out << name_ << "\t";
	if (name_.size() < 6) out << "\t";
	out << "Type: ";
		if (type_ != nullptr)
		{
			out << type_->get_name();
			if (type_->get_name().size() < 9) out << "\t";
		}
		else
		{
			out << "none BasicType";
		}
	out << "\t";
	out << "Durability: ";
	for (auto i : durability_)
	{
		out << " " << i;
	}
	out << std::endl;
}

void Ship::read(std::istream& in)
{
	std::string temp;
	std::getline(in, temp);
	id_ = stoi(temp);
	std::getline(in, name_);
	//std::getline(in, type_);
	temp = "";
	std::getline(in, temp);
	if (temp == "Aircraft Carrier") 
	{
		type_ = new AircraftCarrier();
	}
	else if (temp == "Heavy Cruiser")
	{
		type_ = new HeavyCruiser();
	}
	else if (temp == "Tsundere")
	{
		type_ = new Tsundere();
	}
	else if (temp == "Small")
	{
		type_ = new Small();
	}
	else
	{
		type_ = nullptr;
	}
	durability_.resize(type_->get_size());
	std::fill(durability_.begin(), durability_.end(), type_->get_default_durability());
}

void Ship::set_name(const std::string &name)
{
	name_ = name;
}

std::string Ship::get_name() const
{
	return name_;
}

void Ship::set_type(const BasicType* tp)
{
	type_ = (BasicType*)tp;
}

 BasicType* Ship::get_type() const
{
	return type_;
}

void Ship::set_durability(const std::vector<int> &durability)
{
	durability_ = durability;
}

int Ship::get_durability_sum() const {
	int sum = 0;
	for (auto& i : durability_) {
		sum += i;
	}
	return sum;
}

std::vector<int> Ship::get_durability() const
{
	return durability_;
}

void Ship::damage_by_index(const int dmg, const int ind) {
	if (durability_[ind] - dmg > 0) { durability_[ind] -= dmg; }
	else { durability_[ind] = 0; }
}

int Ship::get_id() const
{
	return id_;
}

bool Ship::operator==(const Ship& right) const
{
	return (type_->get_size() == right.type_->get_size() && id_ == right.id_ && durability_ == right.durability_);
}

bool Ship::operator!=(const Ship& right) const
{
	return !(*this == right);
}

Ship& Ship::operator=(const Ship& right)
{
	if (this != &right)
	{
		name_ = right.name_;
		type_ = right.type_;
		durability_ = right.durability_;
	}
	return *this;
}

Ship Ship::operator++(int)
{
	Ship copyThis(*this);
	for (auto& i : durability_)
	{
		if (i < this->get_type()->get_default_durability())
		{
			i++;
			if (i < this->get_type()->get_default_durability())
			{
				i++;
			}
		}
	}
	return copyThis;
}

Ship Ship::operator--(int)
{
	Ship copyThis(*this);
	for (auto& i : durability_)
	{
		if (i != 0)
		{
			i--;
		}
	}
	return copyThis;
}

std::istream& operator>>(std::istream& in, Ship& shp)
{
	shp.read(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const Ship& shp)
{
	shp.print(out);
	return out;
}