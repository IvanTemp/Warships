//#include <iostream>
//#include <locale>
//#include <vector>
//#include <map>
//#include "generator.h"
//
//std::tuple <char, char> Field_Final[width_height][width_height] = { std::make_tuple('#', '#') }; //Поля, которое видит игрок и Терминатор
//std::tuple <unsigned int, unsigned int> Field_ID[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля с ID
//std::tuple <int, int> Field_War[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля с туманом войны
//std::tuple <unsigned int, unsigned int> Field_Durability[width_height][width_height] = { std::make_tuple(0, 0) }; //Поля с прочностью
//
//std::map <std::string, char> design = { {"Unknown", '#'}, {"Clear", ' '} };
//
//void Generate_Field_Final(bool side) {
//	for (unsigned int y = 0; y < width_height; y++) {
//		for (unsigned int x = 0; x < width_height; x++) {
//			if (side) {
//				if (std::get<1>(Field_War[x][y])) {
//					if (std::get<1>(Field_ID[x][y])) {
//						std::get<1>(Field_Final[x][y]) = std::get<1>(Field_Durability[x][y]);
//					}
//					else {
//						std::get<1>(Field_Final[x][y]) = design["Clear"];
//					}
//				}
//				else std::get<1>(Field_Final[x][y]) = design["Unknown"];
//			}
//			else {
//				if (std::get<0>(Field_War[x][y])) {
//					if (std::get<0>(Field_ID[x][y])) {
//						std::get<0>(Field_Final[x][y]) = std::get<0>(Field_Durability[x][y]);
//					}
//					else {
//						std::get<0>(Field_Final[x][y]) = design["Clear"];
//					}
//				}
//				else std::get<0>(Field_Final[x][y]) = design["Unknown"];
//			}
//		}
//	}
//}
//
//void Output_Field_ID(bool side) {
//	std::cout << "ID(NOT FOR USER): \n\n";
//	for (unsigned int y = 0; y < width_height; y++) {
//		std::cout << "         |";
//		for (unsigned int x = 0; x < width_height; x++) {
//			side ? std::cout << std::get<1>(Field_ID[x][y]) << "|" : std::cout << std::get<0>(Field_ID[x][y]) << "|";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Output_Field_War(bool side) {
//	std::cout << "War(NOT FOR USER): \n\n";
//	for (unsigned int y = 0; y < width_height; y++) {
//		std::cout << "         |";
//		for (unsigned int x = 0; x < width_height; x++) {
//			side ? std::cout << std::get<1>(Field_War[x][y]) << "|" : std::cout << std::get<0>(Field_War[x][y]) << "|";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Output_Field_Durability(bool side) {
//	std::cout << "Durability(NOT FOR USER): \n\n";
//	for (unsigned int y = 0; y < width_height; y++) {
//		std::cout << "         |";
//		for (unsigned int x = 0; x < width_height; x++) {
//			side ? std::cout << std::get<1>(Field_Durability[x][y]) << "|" : std::cout << std::get<0>(Field_Durability[x][y]) << "|";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Output_Field_Final(bool side) {
//	std::cout << "Final: \n\n";
//	for (unsigned int y = 0; y < width_height; y++) {
//		std::cout << "         |";
//		for (unsigned int x = 0; x < width_height; x++) {
//			side ? std::cout << std::get<1>(Field_Final[x][y]) << "|" : std::cout << std::get<0>(Field_Final[x][y]) << "|";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//void Generate_ship(ship sheep, bool side) {
//	srand(time(0));
//	std::map <std::string, int> TypeToLength = { {"Aircraft Carrier", 4}, {"Heavy Cruiser", 3}, {"Tsundere", 2}, {"Small", 1} };
//	bool stop = false, breaksIn = true, kostil = true;
//	int x = 0, y = 0, rotation = 0, length = TypeToLength[sheep.GetType()], ID = sheep.GetID(), durability = sheep.GetDurability();
//	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
//	while (!stop) {
//		breaksIn = true;
//		x = 0, y = 0, rotation = 2;
//		std::cout << "x = " << x << " y = " << y << " rotation = " << rotation << " ID: " << ID << " Durability: " << durability << std::endl; //TEST
//		switch (rotation) {
//		case 2: //South
//			if (y < width_height - length) {
//				for (int h = 0; h < length; h++) {
//					if (side) {
//						if (std::get<1>(Field_ID[x][y + h]) != 0) breaksIn = false;
//					}
//					else {
//						if (std::get<0>(Field_ID[x][y + h]) != 0) breaksIn = false;
//					}
//				}
//				if (breaksIn) {
//					if (y > 0) {
//						if (side) {
//							std::get<1>(Field_ID[x - 1][y - 1]) != 1 ? kostil = true : kostil = false;
//						}
//						else {
//							std::get<0>(Field_ID[x - 1][y - 1]) != 1 ? kostil = true : kostil = false;
//						}
//						if (x > 0 && kostil) {
//							side ? std::get<1>(Field_War[x - 1][y - 1]) = 1 : std::get<0>(Field_War[x - 1][y - 1]) = 1;
//						}
//						side ? std::get<1>(Field_War[x][y - 1]) = 1 : std::get<0>(Field_War[x][y - 1]) = 1;
//						if (side) {
//							std::get<1>(Field_ID[x + 1][y - 1]) != 1 ? kostil = true : kostil = false;
//						}
//						else {
//							std::get<0>(Field_ID[x + 1][y - 1]) != 1 ? kostil = true : kostil = false;
//						}
//						if (x < width_height - 1 && kostil) {
//							side ? std::get<1>(Field_War[x + 1][y - 1]) = 1 : std::get<0>(Field_War[x + 1][y - 1]) = 1;
//						}
//					}
//					for (int generated_length = 0; generated_length < length; generated_length++) {
//						if (side) {
//							std::get<1>(Field_ID[x - 1][y + generated_length]) != 1 ? kostil = true : kostil = false;
//						}
//						else {
//							std::get<0>(Field_ID[x - 1][y + generated_length]) != 1 ? kostil = true : kostil = false;
//						}
//						if (x > 0 && kostil) {
//							side ? std::get<1>(Field_War[x - 1][y + generated_length]) = 1 : std::get<0>(Field_War[x - 1][y + generated_length]) = 1;
//						}
//						side ? std::get<1>(Field_ID[x][y + generated_length]) = ID : std::get<0>(Field_ID[x][y + generated_length]) = ID;
//						side ? std::get<1>(Field_Durability[x][y + generated_length]) = durability : std::get<0>(Field_Durability[x][y + generated_length]) = durability;
//						side ? std::get<1>(Field_War[x][y + generated_length]) = 1 : std::get<0>(Field_War[x][y + generated_length]) = 1;
//						if (side) {
//							std::get<1>(Field_ID[x + 1][y + generated_length]) != 1 ? kostil = true : kostil = false;
//						}
//						else {
//							std::get<0>(Field_ID[x + 1][y + generated_length]) != 1 ? kostil = true : kostil = false;
//						}
//						if (x < width_height - 1 && kostil) {
//							side ? std::get<1>(Field_War[x + 1][y + generated_length]) = 1 : std::get<0>(Field_War[x + 1][y + generated_length]) = 1;
//						}
//					}
//					if (y < width_height - 1) {
//						side ? std::get<1>(Field_War[x][y + length]) = 1 : std::get<0>(Field_War[x][y + length]) = 1;
//						if (x < width_height - 1) {
//							if (side) {
//								std::get<1>(Field_ID[x + 1][y + length]) != 1 ? kostil = true : kostil = false;
//							}
//							else {
//								std::get<0>(Field_ID[x + 1][y + length]) != 1 ? kostil = true : kostil = false;
//							}
//						}
//						if (kostil) {
//							side ? std::get<1>(Field_War[x + 1][y + length]) = 1 : std::get<0>(Field_War[x + 1][y + length]) = 1;
//						}
//					}
//					stop += 1;
//				}
//				else continue;
//			}
//			else continue;
//			break;
//		}
//	}
//}