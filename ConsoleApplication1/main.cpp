#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "ship.h"
#include "generator.h"
#include "fleet.h"


int main(int argc, char * argv[]) {
	std::cout << "This is a alpha build! Most of the implemented features will be enabled only after enabling DEBUG_MODE in ship.h!\n\n";

	srand(time(0));

	if (DEBUG_MODE) std::cout << "WARNING! DEBUG MODE ON! \n" << std::endl;

	ship ship1("Enterprise", "Aircraft Carrier", 2);
	//�������� ������ ����
	std::vector<ship> fleet_11;
	//�������� � ������ ��� ��������
	fleet_11.push_back(ship1);
	//������� ��� ���������
	fleet_11.push_back({ "Prinz Eugene", "Heavy Cruiser", 3 });
	fleet_11.push_back({ "Atago", "Heavy Cruiser", 4 });
	fleet_11.push_back({ "FLX1", "Tsundere", 5 });
	fleet_11.push_back({ "FLX2", "Tsundere", 6 });
	fleet_11.push_back({ "FLX3", "Tsundere", 7 });
	fleet_11.push_back({ "Flaffey1", "Small", 8 });
	fleet_11.push_back({ "Flaffey2", "Small", 9 });
	fleet_11.push_back({ "Flaffey3", "Small", 10 });
	fleet_11.push_back({ "Flaffey4", "Small", 11 });
	//�������� ���� � �����
	Fleet fleet_1("Eagle Union", fleet_11);
	//������� ���� �� ����� input.txt (����� � ���������� �������)
	Fleet fleet_2;
	if (argc > 2)
	{
		std::ifstream fin(argv[2]);
		fleet_2.Read(fin);
		fin.close();
	}
	//������� �� � ���� output.txt (����� � ���������� �������)
	if (argc > 1)
	{
		std::ofstream fout(argv[1]);
		fleet_1.Print(fout);
		fleet_2.Print(fout);
		fout.close();
	}
	//������� ���� �� �������
	/*Fleet fleet_4;
	fleet_4.Read(std::cin);
	fleet_4.Print(std::cout);*/
	//������� ���������� �������� (�� ����� ��� ���������� ������� ������������... ������� ����� �������� � ������ ������� � ����, � �����)
	std::cout << "Ships count: " << ship1.GetCount() << std::endl << std::endl; //(��� �������)��, ��� ���� � ����!(��� ����)��, �� ������� :(



	/*				��� ������������� ���� ������ ������������ ������(�� ������ ����)				*/
	
	if (DEBUG_MODE) 
	{
		fleet_1.Print(std::cout);
		fleet_2.Print(std::cout);
	}

	//Generate here
	for (int i = 0; i < fleet_1.GetFleet().size(); i++) {
		Generate_ship(fleet_1.GetShipByIndex(i), fleet_1.GetSide());
	}

	for (int i = 0; i < fleet_2.GetFleet().size(); i++) {
		Generate_ship(fleet_2.GetShipByIndex(i), fleet_2.GetSide());
	}
	///////////////

	//DEBUG FUNCTIONS
	if (DEBUG_MODE)
	{
		Output_Field_ID_Indexes(0);
		Output_Field_Durability(0);
		Output_Field_War(0);
		Output_Field_ID_Indexes(1);
		Output_Field_Durability(1);
		Output_Field_War(1);
	}
	/////////////////

	////INITIALISATION FIELDS
	Initialize_Field_Final(0);
	Initialize_Field_Final(1);
	/////////////////////////

	//DAMAGE TEST
	/*if (DEBUG_MODE) {
		std::cout << "DAMAGE TEST:" << std::endl << std::endl;
		std::cout << "Before attack in 5 5:" << std::endl << std::endl;
		Output_Field_Final(0, 0);
		std::cout << std::endl << std::endl;
		Output_Field_Final(1, 1);

		fleet_2.DmgToInd(5, 5, 3);

		std::cout << "After attack in 5 5:" << std::endl << std::endl;
		std::cout << std::endl;
		Output_Field_Final(0, 0);
		std::cout << std::endl << std::endl;
		Output_Field_Final(1, 1);
	}*/
	/////////////

	//FOG OF WAR TEST
	if (DEBUG_MODE) {
		std::cout << "FOG OF WAR TEST:" << std::endl << std::endl;
		std::cout << "FOR PLAYER: " << std::endl;
		Output_Field_Final(0, 0);
		Output_Field_Final(1, 0);

		std::cout << "FOR BOT: " << std::endl;
		Output_Field_Final(0, 1);
		Output_Field_Final(1, 1);
	}
	/////////////////

	Output_Field_Final(0, 0);
	Output_Field_Final(1, 0);

	//���������� ���� ����
	std::cout << "Start game?   ";
	system("pause");
	system("cls");
	while (fleet_1.GetHealth() and fleet_2.GetHealth())
	{
		//����� ����
		std::cout << fleet_1.GetName() << " turn" << std::endl;
		system("pause");
		system("cls");
		//����� ���� ������ 0
		Pepsi_Output_Field_Final(0);
		//������� ������ 0
		std::cout << "Your turn is? (Damage X Y) ";
		fleet_2.ConsDmgToInd();
		Persi_Field_Refresh_Durability(fleet_2);
		system("pause");
		system("cls");
		//����� ����
		std::cout << fleet_2.GetName() << " turn " << std::endl;
		system("pause");
		system("cls");
		//����� ���� ������ 1
		Pepsi_Output_Field_Final(1);
		//������� ������ 1
		std::cout << "Your turn is? (Damage X Y) ";
		fleet_1.ConsDmgToInd();
		Persi_Field_Refresh_Durability(fleet_1);
		system("pause");
		system("cls");
	}
	std::cout << "Someone won";
	return 0;
}