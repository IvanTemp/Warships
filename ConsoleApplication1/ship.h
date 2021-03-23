#pragma once

#include <vector>


//Game settings
#define width_height 10 //Width & height of field
#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4
#define Default_Damage 2
#define DEBUG_MODE 1

class ship
{
public:
	ship() :cID(count++) {};
	ship(const int ID);
	ship(const std::string& name, const std::string& type, const int ID);
	~ship() { }

	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(const std::string name);
	std::string GetName()const;
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurability (const std::vector<int> durability);
	std::vector<int> GetDurability()const;
	void DmgtoInd(const int damage, const int index);
	int GetID()const;
	bool operator == (const ship& right)const;
	ship& operator= (const ship& right);
	void Klee(const std::vector<std::pair<unsigned int, unsigned int>> coords, const bool side) const;
	static int GetCount() { return count; }
	void NUCLEAR_BOMB();

private:
	std::string name;
	std::vector<int> durability;
	std::string type;
	int ID;
	static int count;
	const int cID;
};