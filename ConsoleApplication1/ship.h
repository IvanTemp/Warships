#pragma once

#include <vector>
#include "type.h"

//Game settings
#define width_height 10 //Width & height of field
#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4

#define achievement_file "achievements.db"

#define DEBUG_MODE 1
///////////////

class ship
{
public:
	ship() : cid_(count_++), type_(nullptr), id_(0) {};
	ship(const std::string& name, const int id);
	ship(const std::string& name, type& type, const int id);
	~ship() {};

	void print(std::ostream& out)const;
	void read(std::istream& in);
	void set_name(const std::string &name);
	std::string get_name()const;
	void set_type(const type* type);
	type* get_type()const;
	void set_durability(const std::vector<int> &durability);
	unsigned int get_durability_sum()const;
	std::vector<int> get_durability()const;
	void damage_by_index(const int damage, const int index);
	int get_id()const;
	bool operator == (const ship& right)const;
	bool operator != (const ship& right)const;
	ship& operator= (const ship& right);
	ship operator++ (int); //repair function
	void klee(const std::vector<std::pair<unsigned int, unsigned int>> coords, const bool side) const;
	static int get_count() { return count_; }
	void nuclear_bomb();

private:
	std::string name_;
	std::vector<int> durability_;
	type* type_;
	int id_;
	static int count_;
	const int cid_;
};

//Overloading I/O operators is only possible separately from the class
std::istream& operator>>(std::istream& in, ship& shp);
std::ostream& operator<<(std::ostream& out, const ship& shp);