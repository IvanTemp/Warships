#pragma once

class ship
{
public:
	ship(const std::string& name, const std::string& type);

	void Print()const;
	void SetName(const std::string name);
	std::string GetName()const;
	/*void SetDurab(int durabty) { this->durability = durabty; }
	int GetDurab()const { return durability; };*/
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurab(const std::vector<int> durability);
	std::vector<int> GetDurab()const;

private:
	std::string name;
	std::vector<int> durability;
	std::string type;
};