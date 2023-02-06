#pragma once

#include "BasicType.h"
#include <vector>
<<<<<<< HEAD

//Game settings
#define DEBUG_MODE 0 //0 - off; 1 - on
=======
#include "type.h"
#include "GameInformation.h"

//Game settings
#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4

#define achievement_file "achievements.db"
>>>>>>> master
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
<<<<<<< HEAD
	//////////////////////////////////////////////////////////////////
=======
	int get_id()const;
	bool operator == (const ship& right)const;
	bool operator != (const ship& right)const;
	ship& operator= (const ship& right);
	ship operator++ (int); //repair function
	void detonate_the_ship(const std::vector<std::pair<unsigned int, unsigned int>> coords, const bool side) const;
	static int get_count() { return count_; }
	void set_coordinates(const std::pair <unsigned int, unsigned int> new_coordinates);
	std::pair <unsigned int, unsigned int> get_coordinates()const;
	void nuclear_bomb();
>>>>>>> master

private:
	std::string name_;
	std::vector<int> durability_;
<<<<<<< HEAD
	BasicType* type_;
=======
	type* type_;
	int id_;
	static int count_;
	const int cid_;
	std::pair <unsigned int, unsigned int> coordinates_;
>>>>>>> master
};

//Overloading I/O operators is only possible separately from the class
std::istream& operator>>(std::istream& in, Ship& shp);
std::ostream& operator<<(std::ostream& out, const Ship& shp);
//////////////////////////////////////////////////////////////////////