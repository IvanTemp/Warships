#pragma once

//Настройки игры
#define width_height 10 //Ширина высота поля

#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4

class ship
{
public:
	ship(const std::string& name, const std::string& type, const int ID);

	void Print()const;
	void SetName(const std::string name);
	std::string GetName()const;
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurability (const std::vector<int> durability);
	std::vector<int> GetDurability()const;
	int GetID()const;

private:
	std::string name;
	std::vector<int> durability;
	std::string type;
	int ID = 0;
};