#pragma once

//Game settings
#define width_height 10 //Width / Height of field

#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4
#define DEBUG_MODE 0



class ship
{
public:
	ship();
	ship(const std::string& name, const std::string& type, const int ID);

	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(const std::string name);
	std::string GetName()const;
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurability (const std::vector<int> durability);
	std::vector<int> GetDurability()const;
	int GetID()const;
	bool operator == (const ship& right)const;

private:
	std::string name;
	std::vector<int> durability;
	std::string type;
	int ID;
};