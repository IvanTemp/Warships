#pragma once

class ship
{
public:
	ship(const std::string& name, const std::string& type, const int ID);

	void Print()const;
	void SetName(const std::string name);
	std::string GetName()const;
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurability(const int durability);
	int GetDurability()const;
	int GetID()const;

private:
	std::string name;
	int durability;
	std::string type;
	int ID = 0;
};