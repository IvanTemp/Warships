#pragma once

#include "BasicType.h"
#include <vector>

//Game settings
#define DEBUG_MODE 1 //0 - off; 1 - on
///////////////

class Ship {
public:
	//				  Constructors & Destructors
	Ship() : type_(nullptr) {};
	Ship(const std::string& name);
	Ship(const std::string& name, BasicType& type);
	~Ship() {};
	//////////////////////////////////////////////////////////////////

	//						  Operators
	bool operator == (const Ship& right)const;
	bool operator != (const Ship& right)const;
	Ship& operator= (const Ship& right);
	Ship operator++ (int); //repair function
	Ship operator-- (int); //anti repair function
	//////////////////////////////////////////////////////////////////

	//							 Set
	void set_durability(std::vector<int>);

	//							 Get
	int get_durability_sum()const;
	std::vector<int> get_durability()const;
	std::string get_name()const;
	BasicType* get_type()const;
	//////////////////////////////////////////////////////////////////

	//						  Input/Output
	void print(std::ostream& out)const;
	void read(std::istream& in);
	//////////////////////////////////////////////////////////////////

	//						  Damage ship
	void damage_by_index(const int damage, const int index);
	//////////////////////////////////////////////////////////////////

private:
	std::string name_;
	std::vector<int> durability_;
	BasicType* type_;
};

//Overloading I/O operators is only possible separately from the class
std::istream& operator>>(std::istream& in, Ship& shp);
std::ostream& operator<<(std::ostream& out, const Ship& shp);
//////////////////////////////////////////////////////////////////////