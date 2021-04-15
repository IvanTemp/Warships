#pragma once

#include <vector>
#include "BasicType.h"

//Game settings
#define width_height 10 //Width & height of field
#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4

#define DEBUG_MODE 1

#define SEED 354735 //0 - Pseudo-random
///////////////

class Ship
{
public:
	Ship() : cid_(count_++), type_(nullptr), id_(0) {};
	Ship(const std::string& name, const int id);
	Ship(const std::string& name, BasicType& type, const int id);
	~Ship() {};

	void print(std::ostream& out)const;
	void read(std::istream& in);
	void set_name(const std::string &name);
	std::string get_name()const;
	void set_type(const BasicType* type);
	BasicType* get_type()const;
	void set_durability(const std::vector<int> &durability);
	unsigned int get_durability_sum()const;
	std::vector<int> get_durability()const;
	void damage_by_index(const int damage, const int index);
	int get_id()const;
	bool operator == (const Ship& right)const;
	bool operator != (const Ship& right)const;
	Ship& operator= (const Ship& right);
	Ship operator++ (int); //repair function
	Ship operator-- (int); //anti repair function
	static int get_count() { return count_; }

private:
	std::string name_;
	std::vector<int> durability_;
	BasicType* type_;
	int id_;
	static int count_;
	const int cid_;
};

//Overloading I/O operators is only possible separately from the class
std::istream& operator>>(std::istream& in, Ship& shp);
std::ostream& operator<<(std::ostream& out, const Ship& shp);