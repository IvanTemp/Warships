#include "functions.h"

#define achievement_file "achievements.db"

void output_achievement_info(const std::vector<std::pair<std::string, bool>>& achievements) {
	int counter = 0;
	int count_of_common_achievements = 6;

	for (int i = 0; i < achievements.size(); i++) {
		if (achievements[i].second) counter++;
	}

	std::cout << "Achievements[" << (counter * 100) / achievements.size() << "%]: " << std::endl;

	for (int i = 0; i < achievements.size(); i++) {
		std::cout << i + 1 << ")";
		if (i < count_of_common_achievements) {
			std::cout << achievements[i].first << ": ";
			achievements[i].second ? std::cout << "Received\n" : std::cout << "Not received\n";
		}
		else {
			achievements[i].second ? std::cout << achievements[i].first << ": Received\n" : std::cout << "???\n";
		}
	}
	std::cout << std::endl;
}

std::vector<std::pair<std::string, bool>> read_achievements() {
	std::vector<std::pair<std::string, bool>> achievement_array;
	//								Place your achievements here
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Normal difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Win a PVE match on Hard difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Try to win a PVE match on Impossible difficulty", 0));
	achievement_array.emplace_back(std::make_pair("Play in standard PVP match", 0));
	achievement_array.emplace_back(std::make_pair("Win in Standard Warships - Primitive", 0));
	achievement_array.emplace_back(std::make_pair("Try to win in Standard Warships - Impossible", 0));
	achievement_array.emplace_back(std::make_pair("Win nameless mission with code 344460", 0));
	achievement_array.emplace_back(std::make_pair("Play in Shipsweeper", 0));
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	std::ofstream aqua(
		achievement_file, std::ios::in | std::ios::out | std::ios::app | std::ios::binary | std::ios::ate);
	aqua.close();
	std::ifstream achievement_in(achievement_file);
	std::string str;
	std::getline(achievement_in, str);
	for (int i = 0; i < str.size(); i++) {
		str[i] == '1' ? achievement_array[i].second = true : achievement_array[i].second = false;
	}
	achievement_in.close();
	std::ofstream achievement_out(achievement_file);
	for (auto& i : achievement_array) {
		achievement_out << i.second;
	}
	achievement_out.close();
	return achievement_array;
}

void give_achievement(std::vector<std::pair<std::string, bool>>& achievement_array, const int& num) {
	achievement_array[num].second = true;
	std::ofstream out(achievement_file);
	for (auto & value : achievement_array) {
		out << value.second;
	}
	out.close();
}

void ha_you_are_small_now(std::string& str) {
	for (int i = 0; i < str.size(); i++) {
		str[i] = std::tolower(str[i]);
	}
}

char int_to_letter(const int i) {
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alf[i];
}

int letter_to_int(const char chr) {
	if (chr >= '0' && chr <= '9') return chr - '0';
	std::string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < alf.length(); i++) if (alf[i] == chr) return i;
	return 0;
}

int difference_modulus(int first, int second) {
	if (first - second > 0) {
		return first - second;
	}
	else {
		return second - first;
	}
}

std::vector<int> first_order(const size_t count) {
	//count - length of order
	std::vector<int> order_list;
	bool buleidu = true; //if index hasn't already been
	for (int i = 0; i < count; i++) {
		buleidu = true;
		const int random_index = rand() % count;
		for (auto& j : order_list) {
			if (random_index == j) {
				buleidu = false;
			}
		}
		buleidu ? order_list.emplace_back(random_index) : i--;
	}
	return order_list;
}

std::pair<int, int> load_settings() {
	std::ifstream settings("settings.cfg");

	if (settings.peek() == EOF) {
		settings.close();
		std::ofstream settings("settings.cfg");
		settings << "Width&Height: 10" << std::endl;
		settings << "Seed: 0";
		std::cout << "==========================================" << std::endl;
		std::cout << "settings.cfg has been created / recreated!" << std::endl;
		std::cout << "==========================================" << std::endl;
		return std::make_pair(10, 0);
	}

	std::string value, parameter;
	std::pair<int, int> config = std::make_pair(0, 0);

	std::getline(settings, value);
	if (value.length() > 12) {
		parameter = value;
		parameter.erase(parameter.begin() + 13, parameter.end());
		if (parameter == "Width&Height:" && value.length() != 13) {
			value.erase(value.begin(), value.begin() + 14);
			if (!value.empty()) {
				config.first = std::stoi(value);
			}
		}
	}
	else {
		std::cout << "==============================================================================" << std::endl;
		std::cout << "Warning! Your settings file is corrupted. Program will create new settings.cfg" << std::endl;
		std::cout << "==============================================================================" << std::endl;
		settings.close();
		std::ofstream settings("settings.cfg");
		settings << "Width&Height: 10" << std::endl;
		settings << "Seed: 0";
		std::cout << "==========================================" << std::endl;
		std::cout << "settings.cfg has been created / recreated!" << std::endl;
		std::cout << "==========================================" << std::endl;
		return std::make_pair(10, 0);
	}

	std::getline(settings, value);
	if (value.length() > 4) {
		parameter = value;
		parameter.erase(parameter.begin() + 5, parameter.end());
		if (parameter == "Seed:" && value.length() != 4) {
			value.erase(value.begin(), value.begin() + 5);
			if (!value.empty()) {
				config.second = std::stoi(value);
			}
		}
	}
	else {
		std::cout << "==============================================================================" << std::endl;
		std::cout << "Warning! Your settings file is corrupted. Program will create new settings.cfg" << std::endl;
		std::cout << "==============================================================================" << std::endl;
		settings.close();
		std::ofstream settings("settings.cfg");
		settings << "Width&Height: 10" << std::endl;
		settings << "Seed: 0";
		std::cout << "==========================================" << std::endl;
		std::cout << "settings.cfg has been created / recreated!" << std::endl;
		std::cout << "==========================================" << std::endl;
		return std::make_pair(10, 0);
	}

	settings.close();
	return config;
}