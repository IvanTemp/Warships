#pragma once
#include "ship.h"


class Fleet
{
public:
	Fleet() : side_(count_++) {};
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<ship>& v);
	void print(std::ostream& out)const;
	void read(std::istream& in);
	void set_name(int index, const std::string name);
	std::string get_name()const;
	std::vector<ship> get_ship_vector()const;
	unsigned int get_health()const;
	bool add_ship_to_fleet(const ship &ship);
	bool remove_ship_from_fleet(const ship &ship);
	bool get_side() const;
	ship get_ship_by_index(const unsigned int id)const;
	void damage_by_index_bot(const int dmg, const int difficulty);
	void damage_by_index_bot_v2(unsigned int id, int dmg, const int difficulty);
	void damage_by_index_player(const ship sheep);
	void aircraft_attack(const bool angle, const int dmg);
	void heavy_cruiser_attack(const int dmg);
	void nuclear_bomb();
	Fleet& operator +=(const ship& ship); //repair
	Fleet& operator -=(const ship& ship); //anti repair

private:
	static int count_;
	std::string name_;
	std::vector<ship> ship_vector_;
	const bool side_;
};

std::istream& operator>>(std::istream& in, Fleet& shp);
std::ostream& operator<<(std::ostream& out, const Fleet& shp);