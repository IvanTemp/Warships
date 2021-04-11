#pragma once
#include "Ship.h"
#include "functions.h"


class Fleet
{
public:
	Fleet() : side_(count_++) {};
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<Ship>& v);
	void print(std::ostream& out)const;
	void read(std::istream& in);
	void set_name(int index, const std::string name);
	std::string get_name()const;
	std::vector<Ship> get_ship_vector()const;
	unsigned int get_health()const;
	bool add_ship_to_fleet(const Ship& ship);
	bool remove_ship_from_fleet(const Ship& ship);
	bool get_side() const;
	Ship get_ship_by_index(const unsigned int id)const;
	void damage_by_index_bot(const int dmg, const int difficulty);
	void gura_ai(const int id, int dmg, const int difficulty, Fleet& fleet_of_bot);
	void damage_by_index_player(Ship &sheep);
	void heavy_cruiser_attack_bot(const int dmg, const int difficulty);
	void aircraft_attack(const bool angle, const int dmg);
	void heavy_cruiser_attack_player(const int dmg);
	void nuclear_bomb();
	Fleet& operator +=(const Ship& ship); //add ship
	Fleet& operator -=(const Ship& ship); //del ship
	std::string return_field_final(const unsigned& x, const unsigned& y)const;
	unsigned int return_field_id(const unsigned& x, const unsigned& y)const;
	unsigned int return_field_index(const unsigned& x, const unsigned& y)const;
	bool return_field_war(const unsigned& x, const unsigned& y)const;
	void initialize_field_final();
	void output_field_final(const Fleet& fleet2)const;
	void output_field_id_indexes()const;
	void output_field_war()const;
	void field_get_vision(const unsigned int x, const unsigned int y);
	std::pair<int, int> return_x_y(const int& id)const;
	void generate_fleet();
	void do_action(Fleet& whom, const unsigned& current_ship_id);
	void get_damage(const int dmg, const unsigned int x, const unsigned int y);
	void small_move_player(const unsigned int index);
	void small_move_bot(const std::pair<int, int> coordinates, const int index);
	bool area_is_clear(const unsigned int x, const unsigned int y)const;
	void klee(const auto& coords);

private:
	static int count_;
	std::string name_;
	std::vector<Ship> ship_vector_;
	const bool side_;
	//
	std::string field_final_[width_height][width_height] = { "#", "#" }; //The field seen by the player
	std::pair<unsigned int, unsigned int> field_id_[width_height][width_height] = { (std::make_pair(0, 0)) }; //The field with id_(.first) and indexes(.second)
	bool field_war_[width_height][width_height] = { (false), (false) }; //The field with fog of war
};

std::istream& operator>>(std::istream& in, Fleet& shp);
std::ostream& operator<<(std::ostream& out, const Fleet& shp);