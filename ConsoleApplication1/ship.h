#pragma once

#include <vector>

//Game settings
#define width_height 10 //Width & height of field
#define Aircraft_Carrier_Durability 6
#define Heavy_Cruiser_Durability 7
#define Tsundere_Durability 5
#define Small_Durability 4

#define achievement_file "achievements.db"

#define Default_Damage 2
#define Aircraft_Carrier_Damage 3
#define Heavy_Cruiser_Damage 1
#define Tsundere_Damage 3
#define Small_Damage 2
#define DEBUG_MODE 1
///////////////

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
	unsigned int GetDurabilitySum()const;
	std::vector<int> GetDurability()const;
	void DmgtoInd(const int damage, const int index);
	int GetID()const;
	bool operator == (const ship& right)const;
	ship& operator= (const ship& right);
	ship operator++ (int); //увеличивает прочность корабля всего корабля на 1
	void Klee(const std::vector<std::pair<unsigned int, unsigned int>> coords, const bool side) const;
	static int GetCount() { return count; }
	void NUCLEAR_BOMB();

private:
	std::string name;
	std::vector<int> durability;
	std::string type;
	int ID; //Удалить к курсовой (Алексей, разве это удалять? не cID? cID - количество кораблей)
	static int count;
	const int cID; //удалить к курсовой
};