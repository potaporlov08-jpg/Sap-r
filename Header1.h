#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

struct Kletka
{
	int sostoyanie;
	int mines_arround;
	int tip;

	Kletka() : sostoyanie(0), mines_arround(0), tip(0) {}

	void open() {
		if (sostoyanie == 0) {
			sostoyanie = 1;
		}
	}

	int flag() {
		if (sostoyanie == 0) {
			sostoyanie = 2;
			return 1;
		}
		if (sostoyanie == 2) {
			sostoyanie = 0;
			return -1;
		}
		return 0;
	}
};



struct Doska
{
	int m;
	int n;
	int mines;
	int resultat;
	int flagi = 0;
	std::vector <std::vector<Kletka>> pole;

	void creat_field(int rows, int cols) {
		m = cols;
		n = rows;
		pole.resize(n);
			for (int i = 0; i < n; i++) {
				pole[i].resize(m);
		}
	}



	void rasstanovka_min(int slojnost) {
		double dola = 0;
		if (slojnost == 1) {
			dola = 0.1;
		}
		else if (slojnost == 2) {
			dola = 0.15;
		}
		else if (slojnost == 3) {
			dola = 0.2;
		}
		int s = n * m;
		mines = dola * s;
		int c = 0;
		while (c < mines) {
			int i = rand() % n;
			int j = rand() % m;
			if (pole[i][j].tip == 0) {
				pole[i][j].tip = 1;
				c += 1;
			}
		}
	}

	void podschet_min() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (i != 0) {
					if (pole[i - 1][j].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (i != n - 1) {
					if (pole[i + 1][j].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (j != 0) {
					if (pole[i][j - 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (j != m - 1) {
					if (pole[i][j + 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (i != 0 && j != 0) {
					if (pole[i - 1][j - 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (i != n - 1 && j != 0) {
					if (pole[i + 1][j - 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (i != 0 && j != m - 1) {
					if (pole[i - 1][j + 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
				if (i != n - 1 && j != m - 1) {
					if (pole[i + 1][j + 1].tip == 1) {
						pole[i][j].mines_arround += 1;
					}
				}
			}
		}
	}

	int otkrit_kletku(int i, int j) {
		pole[i][j].open();
		if (pole[i][j].tip == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void print() {
		for (int i = 0; i < n + 1; ++i) {
			for (int j = 0; j < m + 1; ++j) {
				if (i == 0 && j == 0) {
					std::cout << "   ";
				}
				else if (i == 0) {
					std::cout << j - 1 << " ";
				}
				else if (j == 0) {
          if (i > 10 && i < 101) {
					  std::cout << i - 1 << " ";
          }
          else if (i <= 10) {
            std::cout << i - 1 << "  ";
          }
				}
				else if (pole[i - 1][j - 1].sostoyanie == 2) {
          if (j > 10 && j < 101) {
            std::cout << "F" << "  ";
          }
          else if (j <= 10) {
            std::cout << "F" << " ";
          }
				}
				else if (pole[i - 1][j - 1].sostoyanie == 0) {
          if (j > 10 && j < 101) {
            std::cout << "#" << "  ";
          }
          else if (j <= 10) {
            std::cout << "#" << " ";
          }
				}
				else if (pole[i - 1][j - 1].tip == 1) {
          if (j > 10 && j < 101) {
            std::cout << "*" << "  ";
          }
          else if (j <= 10) {
            std::cout << "*" << " ";
          }
				}
				else if (pole[i - 1][j - 1].tip == 0) {
					if (pole[i - 1][j - 1].mines_arround == 0) {
            if (j > 10 && j < 101) {
              std::cout << " " << "  ";
            }
            else if (j <= 10) {
              std::cout << " " << " ";
            }
					}
					else {
            if (j > 10 && j < 101) {
              std::cout << pole[i - 1][j - 1].mines_arround << "  ";
            }
            else if (j <= 10) {
              std::cout << pole[i - 1][j - 1].mines_arround << " ";
            }
					}
				}
			}
			std::cout << "\n";
		}
	}

	void postavit_flag(int i, int j) {
		flagi += pole[i][j].flag();
	}

	bool proverka_pobedy() {
		int otktiti = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (pole[i][j].sostoyanie == 1 && pole[i][j].tip != 1) {
					otktiti += 1;
				}
			}
		}
		if ((n * m - mines) == otktiti) {
			return true;
		}
		else {
			return false;
		}
	}

	void pokazat_vse_miny() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (pole[i][j].tip == 1) {
					pole[i][j].sostoyanie = 1;
				}
			}
		}
	}
	
};


struct Igra
{
	bool start;
	bool finish;
	Doska d;

	Igra() : start(false), finish(true) {}

	void podgotovka() {
		std::cout << "Игра Сапёр" << "\n";
		std::cout << "Укажите размер поля, на котором хотите играть." << "\n";
		std::cout << "введите в формате ряды x столбцы два числа: ";
		int n;
		int m;
		std::cin >> n >> m;
		std::cout << "\n";
		if (n <= 0 || m <= 0) {
			std::cout << "Размеры должны быть положительными.\n";
			return;
		}
		std::cout << "для хода нужно ввести букву (o - open, f - flag) и выбрать координаты\n";
		std::cout << "Выберите режим сложности (число) :\n";
		std::cout << "1.Новичок   2.Любитель   3.Профессионал\n";
		int level;
		std::cin >> level;
		start = true;
		finish = false;
		d.creat_field(n, m);
		d.rasstanovka_min(level);
		d.podschet_min();
	}

	void hod(char c, int i, int j) {
		if (i < 0 || i >= d.n || j < 0 || j >= d.m) {
			return;
		}
		if (c == 'f') {
			d.postavit_flag(i, j);
		}
		else if (c == 'o') {
			if (d.otkrit_kletku(i, j) == 1) {
				d.pokazat_vse_miny();
				start = false;
				finish = true;
			}
			else if (d.pole[i][j].mines_arround > 0) {
				return;
			}
			else {
				for (int p = -1; p <= 1; ++p) {
					for (int q = -1; q <= 1; ++q) {
						if (i + p >= 0 && i + p < d.n && j + q >= 0 && j + q < d.m) {
							if (d.pole[i + p][j + q].sostoyanie == 0) {
								if (d.pole[i + p][j + q].tip == 1) {
									continue;
								}
								if (d.pole[i + p][j + q].mines_arround > 0) {
									d.otkrit_kletku(i + p, j + q);
								}
								else {
									hod(c, i + p, j + q);
								}
							}
						}
					}
				}
			}
		}
	}



	void game() {
		podgotovka();
		while (start) {
			system("cls");
			d.print();
			std::cout << "Мины: " << d.mines << ", " << "флаги: " << d.flagi << "\n";
			std::cout << "Введите действие: ";
			char deistvie;
			int i;
			int j;
			std::cin >> deistvie >> i >> j;
			hod(deistvie, i, j);
			if (d.proverka_pobedy()) {
				start = false;
				finish = true;
			}
		}


		system("cls");
		d.print();
		if (d.proverka_pobedy()) {
			std::cout << "Победа!\n";
		}
		else {
			std::cout << "Вы проиграли!\n";
		}
		system("pause");
	}
};