#pragma once
#include "Ship.h"
#include "functions.h"


class Fleet {
public:
	//												 Constructors & Destructors
	Fleet();
	Fleet(const std::string&);
	Fleet(const std::string&, const std::vector<Ship>&);
	~Fleet() {};
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//														  Operators
	Fleet& operator +=(const Ship&); //add ship
	Fleet& operator -=(const Ship&); //delete ship
	bool operator ==(const Fleet&);
	bool operator !=(const Fleet&);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//															 Get
	std::string get_name() const;
	std::vector<Ship> get_ship_vector()const;
	int get_health_sum()const;
	Ship get_ship_by_index(const int)const;
	int get_health_in_perc()const;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//															 Set
	void oneing_durability();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//														 Input/Output
	void print(std::ostream&)const;
	void read(std::istream&);
	void output_field_final(const Fleet&)const;
	void output_field_final_shipsweeper(const Fleet&)const;
	void output_field_id()const;
	void output_field_index()const;
	void output_field_war()const;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//														   Bot - AI
	void ai(const int, const int, Fleet&);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//														  Bot - find
	int find_undead_small_ship_id();
	int find_undead_heavy_cruiser_ship_id();
	int find_undead_tsundere_ship_id();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//												   Bot - actions & damage
	void damage_by_index_bot_simple();
	void damage_by_index_bot_primitive();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//												  Player - actions & damage
	void do_action(Fleet&, const unsigned&);
	void do_action_344460(Fleet&, Ship);
	void damage_by_index_player_simple();
	int play_shipsweeper();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//															Fields
	void generate_field();
	void clear_fields();
	void initialize_field_final();
	void rebuild_fields_for_shipsweeper();
	bool check_bad_end_game_shipsweeper()const;
	bool check_good_end_game_shipsweeper()const;
	int count_remaining_markers_shipsweeper()const;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//														Debug functions
	void nuclear_bomb();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	std::string name_ = "Nameless";
	std::vector<Ship> ship_vector_;
	const int width_height = load_settings().first;

	//															Fields
	std::vector<std::vector<std::string>> field_final_; //The field seen by the player
	std::vector<std::vector<std::pair<int, int>>> field_id_; //The field with id_(.first) and indexes(.second) (in shipsweeper .second = field with marked cells)
	std::vector<std::vector<bool>> field_war_; //The field with fog of war
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:
	void resize_fields();
	void klee(const auto&);
	bool area_is_clear(const int, const int)const;
	void field_get_vision(const int, const int);
	void open_cells(const int, const int);
	void damage_by_index_bot(Ship, int);
	void damage_by_index_player(Ship&);
	void get_damage(const int, const int, const int);
	int	find_undead_aircraft_carrier_ship_id();
	void remember_founded_ships(std::vector <std::pair <int, int>>&);
	std::vector<std::pair<int, int>> find_ship_and_return_x_y_vector(const int& id)const; //ID ON MAP! (id on map = id in ship_vector_ + 2)
	void aircraft_attack_bot(const int, int);
	void heavy_cruiser_attack_bot(const int, int);
	void small_move_bot(const std::pair<int, int>&, const std::pair<int, int>&, const int&);
	void aircraft_attack_player(const int);
	void heavy_cruiser_attack_player(const int);
	void small_move_player(const std::pair<int, int>&, const int&);
	int area_is_clear_shipsweeper(const int x, const int y)const;
};

std::istream& operator>>(std::istream&, Fleet&);
std::ostream& operator<<(std::ostream&, const Fleet&);