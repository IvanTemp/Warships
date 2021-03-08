#include <iostream>
#include <locale>
#include <vector>

const int width_height = 10; //Высота и ширина поля(По умолчанию - 10)
const int Count_battleships = 1; //Количество четырёхпалубников(По умолчанию - 1)
const int Count_cruisers = 2; //Количество трёхпалубников(По умолчанию - 2)
const int Count_destroyers = 3; //Количество двухпалубников(По умолчанию - 3)
const int Count_boats = 4; //Количество однопалубников(По умолчанию - 4)

void Output(int Field[width_height][width_height]) {
	for (int i = 0; i < width_height; i++) {
		for (int j = 0; j < width_height; j++) {
			if (Field[i][j] == 2)
				Field[i][j] = 0;
			std::cout << Field[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Generate_battleship(int Field[width_height][width_height]) {
	srand(time(0));
	int i;
	int j;
	bool stop = 0, collision = 0;
	bool rotation; //True - вертикально, False - горизонтально
	for (int c = 0; c < Count_battleships; c++) {
		stop = 0;
		while (stop == 0) {
			i = -1 + rand() % width_height + 1;
			j = -1 + rand() % width_height + 1;
			rotation = -1 + rand() % 2 + 1;
			collision = false;
			if (rotation == 1) {
				if (i < 6) {
					for (int k = 0; k < 4; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i + k][j] == 1 || Field[i + k][j] == 2)
							collision = true;
					}
					if (collision != true) {
						if (i != 0) {
							if (j != 0)
								Field[i - 1][j - 1] = 2;
							Field[i - 1][j] = 2;
							if (j != width_height - 1)
								Field[i - 1][j + 1] = 2;
						}
						for (int k = 0; k < 4; k++)
							Field[i + k][j] = 1;
						if (j != 0) {
							for (int k = 0; k < 4; k++) {
								Field[i + k][j - 1] = 2;
							}
						}
						if (j != width_height - 1) {
							for (int k = 0; k < 4; k++) {
								Field[i + k][j + 1] = 2;
							}
						}
						if (i != 6) {
							if (j != 0)
								Field[i + 4][j - 1] = 2;
							Field[i + 4][j] = 2;
							if (j != width_height - 1)
								Field[i + 4][j + 1] = 2;
						}
						stop = true;
					}
				}
			}
			else {
				if (j < 6) {
					for (int k = 0; k < 4; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i][j + k] == 1 || Field[i + k][j] == 2)
							collision = true;
					}
					if (collision != true) {
						for (int k = 0; k < 4; k++)
							Field[i][j + k] = 1;
						if (i != 0) {
							for (int k = 0; k < 4; k++) {
								Field[i - 1][j + k] = 2;
							}
						}
						if (i != width_height - 1) {
							for (int k = 0; k < 4; k++) {
								Field[i + 1][j + k] = 2;
							}
						}
						if (j != 0) {
							if (i != 0)
								Field[i - 1][j - 1] = 2;
							Field[i][j - 1] = 2;
							if (i != width_height - 1)
								Field[i + 1][j - 1] = 2;
						}
						if (j != 6) {
							if (i != 0)
								Field[i - 1][j + 4] = 2;
							Field[i][j + 4] = 2;
							if (i != width_height - 1)
								Field[i + 1][j + 4] = 2;
						}
						stop = true;
					}
				}
			}
		}
	}
}

void Generate_cruiser(int Field[width_height][width_height]) {
	srand(time(0));
	int i;
	int j;
	bool stop = 0, collision = 0;
	bool rotation; //True - вертикально, False - горизонтально
	for (int c = 0; c < Count_cruisers; c++) {
		stop = 0;
		while (stop == 0) {
			i = -1 + rand() % width_height + 1;
			j = -1 + rand() % width_height + 1;
			rotation = -1 + rand() % 2 + 1;
			collision = false;
			if (rotation == 1) {
				if (i < 7) {
					for (int k = 0; k < 3; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i + k][j] == 1 || Field[i + k][j] == 2)
							collision = true;
					}
					if (collision != true) {
						if (i != 0) {
							if (j != 0)
								Field[i - 1][j - 1] = 2;
							Field[i - 1][j] = 2;
							if (j != width_height - 1)
								Field[i - 1][j + 1] = 2;
						}
						for (int k = 0; k < 3; k++)
							Field[i + k][j] = 1;
						if (j != 0) {
							for (int k = 0; k < 3; k++) {
								Field[i + k][j - 1] = 2;
							}
						}
						if (j != width_height - 1) {
							for (int k = 0; k < 3; k++) {
								Field[i + k][j + 1] = 2;
							}
						}
						if (i != 7) {
							if (j != 0)
								Field[i + 3][j - 1] = 2;
							Field[i + 3][j] = 2;
							if (j != width_height - 1)
								Field[i + 3][j + 1] = 2;
						}
						stop = true;
					}
				}
			}
			else {
				if (j < 7) {
					for (int k = 0; k < 3; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i][j + k] == 1 || Field[i][j + k] == 2)
							collision = true;
					}
					if (collision != true) {
						if (j < 7) {
							for (int k = 0; k < 3; k++)
								Field[i][j + k] = 1;
							if (i != 0) {
								for (int k = 0; k < 3; k++) {
									Field[i - 1][j + k] = 2;
								}
							}
							if (i != width_height - 1) {
								for (int k = 0; k < 3; k++) {
									Field[i + 1][j + k] = 2;
								}
							}
							if (j != 0) {
								if (i != 0)
									Field[i - 1][j - 1] = 2;
								Field[i][j - 1] = 2;
								if (i != width_height - 1)
									Field[i + 1][j - 1] = 2;
							}
							if (j != 7) {
								if (i != 0)
									Field[i - 1][j + 3] = 2;
								Field[i][j + 3] = 2;
								if (i != width_height - 1)
									Field[i + 1][j + 3] = 2;
							}
							stop = true;
						}
					}
				}
			}
		}
	}
}

void Generate_destroyer(int Field[width_height][width_height]) {
	srand(time(0));
	int i;
	int j;
	bool stop = 0, collision = 0;
	bool rotation; //True - вертикально, False - горизонтально
	for (int c = 0; c < Count_destroyers; c++) {
		stop = 0;
		while (stop == 0) {
			i = -1 + rand() % width_height + 1;
			j = -1 + rand() % width_height + 1;
			rotation = -1 + rand() % 2 + 1;
			collision = false;
			if (rotation == 1) {
				if (i < 8) {
					for (int k = 0; k < 2; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i + k][j] == 1 || Field[i + k][j] == 2)
							collision = true;
					}
					if (collision != true) {
						if (i != 0) {
							if (j != 0)
								Field[i - 1][j - 1] = 2;
							Field[i - 1][j] = 2;
							if (j != width_height - 1)
								Field[i - 1][j + 1] = 2;
						}
						for (int k = 0; k < 2; k++)
							Field[i + k][j] = 1;
						if (j != 0) {
							for (int k = 0; k < 2; k++) {
								Field[i + k][j - 1] = 2;
							}
						}
						if (j != width_height - 1) {
							for (int k = 0; k < 2; k++) {
								Field[i + k][j + 1] = 2;
							}
						}
						if (i != 7) {
							if (j != 0)
								Field[i + 2][j - 1] = 2;
							Field[i + 2][j] = 2;
							if (j != width_height - 1)
								Field[i + 2][j + 1] = 2;
						}
						stop = true;
					}
				}
			}
			else {
				if (j < 8) {
					for (int k = 0; k < 2; k++) { //Проверка, чтобы корабли не столкнулись и не были рядом
						if (Field[i][j + k] == 1 || Field[i][j + k] == 2)
							collision = true;
					}
					if (collision != true) {
						if (j < 8) {
							for (int k = 0; k < 2; k++)
								Field[i][j + k] = 1;
							if (i != 0) {
								for (int k = 0; k < 2; k++) {
									Field[i - 1][j + k] = 2;
								}
							}
							if (i != width_height - 1) {
								for (int k = 0; k < 2; k++) {
									Field[i + 1][j + k] = 2;
								}
							}
							if (j != 0) {
								if (i != 0)
									Field[i - 1][j - 1] = 2;
								Field[i][j - 1] = 2;
								if (i != width_height - 1)
									Field[i + 1][j - 1] = 2;
							}
							if (j != 8) {
								if (i != 0)
									Field[i - 1][j + 2] = 2;
								Field[i][j + 2] = 2;
								if (i != width_height - 1)
									Field[i + 1][j + 2] = 2;
							}
							stop = true;
						}
					}
				}
			}
		}
	}
}

void Generate_boat(int Field[width_height][width_height]) {
	srand(time(0));
	int i;
	int j;
	bool stop = 0, collision = 0;
	for (int c = 0; c < Count_boats; c++) {
		stop = 0;
		while (stop == 0) {
			i = -1 + rand() % width_height + 1;
			j = -1 + rand() % width_height + 1;
			collision = false;
			if (Field[i][j] == 1 || Field[i][j] == 2)
				collision = true;
			if (collision != true) {
				Field[i][j] = 1;
				if (i != 0) {
					if (j != 0)
						Field[i - 1][j - 1] = 2;
					Field[i - 1][j] = 2;
					if (j != width_height - 1)
						Field[i - 1][j + 1] = 2;
				}
				if (j != 0)
					Field[i][j - 1] = 2;
				if (j != width_height - 1)
					Field[i][j + 1] = 2;
				if (i != width_height - 1) {
					if (j != 0)
						Field[i + 1][j - 1] = 2;
					Field[i + 1][j] = 2;
					if (j != width_height - 1)
						Field[i + 1][j + 1] = 2;
				}
				stop = true;
			}
		}
	}
}

void Generate_ship(int Field[width_height][width_height], int length) {
	bool stop = false, breaksIn = true;
	int i, j, rotation;
	//rotation: 0 - North, 1 - East, 2 - South - 3 - West
	while (!stop) {
		breaksIn = true;
		i = -1 + rand() % width_height + 1, j = -1 + rand() % width_height + 1, rotation = 2;
		std::cout << i << " " << j << " " << rotation << std::endl; //TEST
		switch (rotation) {
		case 2: //South
			if (i < width_height - 4) {
				for (int h = 0; h < length; h++) {
					if (Field[i + h][j] != 0) breaksIn = false;
				}
				if (breaksIn) {
					if (i > 0) {
						if (j > 0) Field[i - 1][j - 1] = 2;
						Field[i][j - 1] = 2;
						if (j < width_height - 1) Field[i - 1][j + 1] = 2;
					}
					for (int temp_int = 0; temp_int < length; length++) {
						if (j > 0) Field[i + temp_int][j - 1] = 2;
						Field[i + temp_int][j] = 1;
						if (j < width_height - 1) Field[i + temp_int][j + 1] = 2;
					}
					if (i < width_height - 1) {
						if (j > 0) Field[i + length][j - 1] = 2;
						Field[i + length][j - 1] = 2;
						if (j < width_height - 1) Field[i + length][j + 1] = 2;
					}
					stop++;
				}
				else continue;
			}
			else continue;
			break;
		}
	}
}

void Generate_ships_in_random_places(int Field[width_height][width_height], int Count_battleships, int Count_cruisers, int Count_destroyers, int Count_boats) {
	for (int count = 0; count < Count_battleships; count++) {
		Generate_ship(Field, 4);
	}
}

//int main() {
//	srand(time(0));
//	int Field[width_height][width_height] = { 0 }; //Поле
//	//Generate_battleship(Field);
//	//Generate_cruiser(Field);
//	//Generate_destroyer(Field);
//	//Generate_boat(Field);
//	Generate_ships_in_random_places(Field, 1, 2, 3, 4);
//	Output(Field);
//}