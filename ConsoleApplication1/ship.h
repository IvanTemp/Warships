#pragma once

class ship
{
public:
	ship(const std::string& name, const std::string& type);

	void Print()const;
	void SetName(const std::string name);
	std::string GetName()const;
	void SetType(const std::string type);
	std::string GetType()const;
	void SetDurab(const std::vector<int> durability);
	std::vector<int> GetDurab()const;
	void SetXYType(const std::pair<int, int> cord, const std::string tp);
	std::string GetXYType(std::pair<int, int> cord)const;

private:
	std::string name;
	std::vector <int> durability;
	std::string type;
	std::vector <std::pair<int, int>> coord; //хранит x и y
};