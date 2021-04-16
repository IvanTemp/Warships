#pragma once
#include "Ship.h"
#include "functions.h"


class Fleet
{
public:
	//				Constructors & Destructors
	Fleet() : side_(count_++) {};
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<Ship>& v);
	~Fleet() {};


	//						Operators
	Fleet& operator +=(const Ship& ship); //add ship
	Fleet& operator -=(const Ship& ship); //del ship
	bool operator ==(const Fleet& flood);
	bool operator !=(const Fleet& flood);


	//							Get
	std::string get_name()const;
	std::vector<Ship> get_ship_vector()const;
	int get_health()const;
	bool get_side() const;
	Ship get_ship_by_index(const int id)const;
	void get_damage(const int dmg, const int x, const int y);


	//							Set
	void set_name(int index, const std::string name);


	//						Input/Output
	void print(std::ostream& out)const;
	void read(std::istream& in);
	void output_field_final(const Fleet& fleet2)const;
	void output_field_id()const;
	void output_field_index()const;
	void output_field_war()const;

	//						 Bot - AI
	void ai(const int id, const int difficulty, Fleet& fleet_of_player);


	//						Bot - find
	int find_small_ship_id();
	int find_heavy_cruiser_ship_id();
	int find_tsundere_ship_id();
	void find_founded_ships(std::vector <std::pair <int, int>>& memory);
	std::pair<int, int> find_ship_and_return_x_y(const int& id)const; //ID ON MAP! (id on map = id in ship_vector_ + 2)


	//					Bot - actions & damage
	void damage_by_index_bot(Ship sheep, int difficulty);
	void aircraft_attack_bot(const int dmg, int difficulty);
	void heavy_cruiser_attack_bot(const int dmg, int difficulty);


	//					Player - actions & damage
	void do_action(Fleet& whom, const unsigned& current_ship_id);
	void do_action_344460(Fleet& whom, Ship damager);
	void damage_by_index_player(Ship& sheep);
	void aircraft_attack_player(const int dmg);
	void heavy_cruiser_attack_player(const int dmg);
	void small_move_player(const std::pair<int, int>& start, const int& index);
	void small_move_bot(const std::pair<int, int>& coordinates, const std::pair<int, int>& start, const int& index);


	//						  Fields
	void generate_field();
	void clear_fields();
	std::string return_field_final(const unsigned& x, const unsigned& y)const;
	int return_field_id(const unsigned& x, const unsigned& y)const;
	int return_field_index(const unsigned& x, const unsigned& y)const;
	bool return_field_war(const unsigned& x, const unsigned& y)const;
	void initialize_field_final();
	void field_get_vision(const int x, const int y);
	void klee(const auto& coords);
	bool area_is_clear(const int x, const int y)const;


	//					  Debug functions
	void nuclear_bomb();


	//					  Will be deleted
	bool add_ship_to_fleet(const Ship& ship);
	void remove_ship_from_fleet(const Ship& ship);


private:
	static int count_;
	std::string name_;
	std::vector<Ship> ship_vector_;
	const bool side_;


	//															Fields
	std::string field_final_[width_height][width_height] = { "#", "#" }; //The field seen by the player
	std::pair<int, int> field_id_[width_height][width_height] = { (std::make_pair(0, 0)) }; //The field with id_(.first) and indexes(.second)
	bool field_war_[width_height][width_height] = { (false), (false) }; //The field with fog of war
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

std::istream& operator>>(std::istream& in, Fleet& shp);
std::ostream& operator<<(std::ostream& out, const Fleet& shp);