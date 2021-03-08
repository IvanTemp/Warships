#include <string>
#include <vector>
#include <iostream>
#include "ship.h"


int main()
{
	ship ship1("Enterprise", "Aircraft Carrier"), 
		ship2("Prinz Eugene", "Heavy Cruiser"), 
		ship3("FLX", "Tsundere"),
		ship4("Flaffey", "Small");
	ship1.Print();
	ship2.Print();
	ship3.Print();
	ship4.Print();
	ship2.SetDurab({ship2.GetDurab()[0]-2,7,9});
	//�������� ������ ����
	std::vector<ship> fleet;
	//�������� � ������ ���� ���� ���������
	fleet.push_back(ship1);
	fleet.push_back(ship2);
	fleet.push_back(ship3);
	fleet.push_back(ship4);
	//������� ����
	std::cout << "======Fleet=======" << std::endl;
	for (const auto& x : fleet)
	{
		x.Print();
	}
	return 0;
}