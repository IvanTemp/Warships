#pragma once
#include "ship.h"


class Fleet
{
public:
	Fleet() : side(count++) {};
	Fleet(const std::string& name);
	Fleet(const std::string& name, const std::vector<ship>& v);
	void Print(std::ostream& out)const;
	void Read(std::istream& in);
	void SetName(int index, const std::string name);
	std::string GetName()const;
	std::vector<ship> GetFleet()const;
	unsigned int GetHealth()const;
	bool AddShipToFleet(const ship& ship);
	bool RemoveShipFromFleet(const ship& ship);
	bool GetSide() const;
	ship GetShipByIndex(const int ID)const;
	void ConsDmgToIndBot(const int dmg, const int difficulty); // поменяй название cons = console, бот не использует консоль
	void ConsDmgToIndPlayer(const int dmg);
	void ConsDmgAircraft(const bool angle, const int dmg);
	void ConsDmgHeavyCruiser(const int dmg);
	void NUCLEAR_BOMB();

private:
	static int count;
	std::string name;
	std::vector<ship> fleet;
	const bool side;
};