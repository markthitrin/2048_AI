#include <iostream>
#include <windows.h>
#include <ctime>
#include <stdlib.h>
#include "Genetic_Argorithm.h"
bool find_space();
void up(bool is_test);
void down(bool is_test);
void left(bool is_test);
void right(bool is_test);
unsigned int map[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
unsigned int sub_map[4][4];
void print_map();
//top left == (0,0)
//bottom right == (3,3);
unsigned int get_number_digit(int x, int y) {
	unsigned int count = 0;
	unsigned int copy;
	copy = map[x][y];
	while (copy > 0) {
		copy = (copy - (copy % 10)) / 10;
		count++;
	}
	return count;
}
void up(bool is_test) {
	//std::cout << "up : " << std::boolalpha << is_test << std::endl;
	int test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++){
			test[q][w] = map[q][w];
		}
	}
	int sub_test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			sub_test[q][w] = sub_map[q][w];
		}
	}
	for (int q = 0; q < 4; q++) { //colum
		for (int w = 0; w < 4; w++) { // line
			if (map[q][w] != 0 && w != 0) {
				if (map[q][w - 1] == map[q][w]) {
					map[q][w - 1] *= 2;
					map[q][w] = 0;

					sub_map[q][w - 1] += 1;
					sub_map[q][w] = 0;
				}
				else {
					int _w = w;
					while (true) {
						if (_w == 0)
							break;
						else if (map[q][_w - 1] == 0) {
							map[q][_w - 1] = map[q][_w];
							map[q][_w] = 0;

							sub_map[q][_w - 1] = sub_map[q][_w];
							sub_map[q][_w] = 0;
						}
						else if (map[q][_w - 1] == map[q][_w]) {
							map[q][_w - 1] *= 2;
							map[q][_w] = 0;

							sub_map[q][_w - 1] += 1;
							sub_map[q][_w] = 0;
							while (true) {
								_w--;
								if (_w == 0)
									break;
								else if (map[q][_w - 1] == 0) {
									map[q][_w - 1] = map[q][_w];
									map[q][_w] = 0;

									sub_map[q][_w - 1] = sub_map[q][_w];
									sub_map[q][_w] = 0;
								}
							}
							break;
						}
						else {
							break;
						}
						_w--;
					}
				}
			}
		}
	}
	bool equal = !find_space();
	//std::cout << "up : " << std::boolalpha << equal << "\n\n";
	if (equal&&!is_test) {
		down(false);
	}
	if (equal&&is_test) {
		for (int q = 0; q < 4; q++) {
			for (int w = 0; w< 4; w++) {
				map[q][w] = test[q][w];
				sub_map[q][w] = sub_test[q][w];
			}
		}
		if (!equal) {
			throw 1;
		}
	}
}
void left(bool is_test) {
	//std::cout << "left : " << std::boolalpha << is_test << std::endl;
	int test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			test[q][w] = map[q][w];
		}
	}
	int sub_test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			sub_test[q][w] = sub_map[q][w];
		}
	}
	for (int w = 0; w < 4; w++) { //line
		for (int q = 0; q < 4; q++) { // colum
			if (map[q][w] != 0 && q != 0) {
				if (map[q - 1][w] == map[q][w]) {
					map[q - 1][w] *= 2;
					map[q][w] = 0;

					sub_map[q - 1][w] += 1;
					sub_map[q][w] = 0;
				}
				else {
					int _q = q;
					while (true) {
						if (_q == 0)
							break;
						else if (map[_q - 1][w] == 0) {
							map[_q - 1][w] = map[_q][w];
							map[_q][w] = 0;

							sub_map[_q - 1][w] = sub_map[_q][w];
							sub_map[_q][w] = 0;
						}
						else if (map[_q - 1][w] == map[_q][w]) {
							map[_q - 1][w] *= 2;
							map[_q][w] = 0;

							sub_map[_q - 1][w] += 1;
							sub_map[_q][w] = 0;
							while (true) {
								_q--;
								if (_q == 0)
									break;
								else if (map[_q - 1][w] == 0) {
									map[_q - 1][w] = map[_q][w];
									map[_q][w] = 0;

									sub_map[_q - 1][w] = sub_map[_q][w];
									sub_map[_q][w] = 0;
								}
							}
							break;
						}
						else {
							break;
						}
						_q--;
					}
				}
			}
		}
	}
	bool equal = !find_space();
	if (equal&&is_test) {
		for (int q = 0; q < 4; q++) {
			for (int w = 0; w< 4; w++) {
				map[q][w] = test[q][w];
				sub_map[q][w] = sub_test[q][w];
			}
		}
		if (!equal) {
			throw 1;
		}
	}
}
void down(bool is_test) {
	//std::cout << "down : " << std::boolalpha << is_test << std::endl;
	int sub_test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			sub_test[q][w] = sub_map[q][w];
		}
	}
	int test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			test[q][w] = map[q][w];
		}
	}
	for (int q = 0; q < 4; q++) { //colum
		for (int w = 3; w >= 0; w--) { // line
			if (map[q][w] != 0 && w != 3) {
				if (map[q][w + 1] == map[q][w]) {
					map[q][w + 1] *= 2;
					map[q][w] = 0;

					sub_map[q][w + 1] += 1;
					sub_map[q][w] = 0;
				}
				else {
					int _w = w;
					while (true) {
						if (_w == 3)
							break;
						else if (map[q][_w + 1] == 0) {
							map[q][_w + 1] = map[q][_w];
							map[q][_w] = 0;

							sub_map[q][_w + 1] = sub_map[q][_w];
							sub_map[q][_w] = 0;
						}
						else if (map[q][_w + 1] == map[q][_w]) {
							map[q][_w + 1] *= 2;
							map[q][_w] = 0;

							sub_map[q][_w + 1] += 1;
							sub_map[q][_w] = 0;
							while (true) {
								_w++;
								if (_w == 3)
									break;
								else if (map[q][_w + 1] == 0) {
map[q][_w + 1] = map[q][_w];
map[q][_w] = 0;

sub_map[q][_w + 1] = sub_map[q][_w];
sub_map[q][_w] = 0;
								}
							}
							break;
						}
						else {
						break;
						}
						_w++;
					}
				}
			}
		}
	}
	bool equal = !find_space();
	//std::cout << "down : " << std::boolalpha << equal << "\n\n";
	if (equal && !is_test) {
		left(false);
	}
	if (is_test) {
		for (int q = 0; q < 4; q++) {
			for (int w = 0; w< 4; w++) {
				map[q][w] = test[q][w];
 				sub_map[q][w] = sub_test[q][w];
			}
		}
		if (!equal) {
			throw 1;
		}
	}
}
void right(bool is_test) {
	//std::cout << "right : " << std::boolalpha << is_test << std::endl;
	int test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			test[q][w] = map[q][w];
		}
	}
	int sub_test[4][4];
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			sub_test[q][w] = sub_map[q][w];
		}
	}
	for (int w = 0; w < 4; w++) { //line
		for (int q = 3; q >= 0; q--) { // colum
			if (map[q][w] != 0 && q != 3) {
				if (map[q + 1][w] == map[q][w]) {
					map[q + 1][w] *= 2;
					map[q][w] = 0;

					sub_map[q + 1][w] += 1;
					sub_map[q][w] = 0;
				}
				else {
					int _q = q;
					while (true) {
						if (_q == 3)
							break;
						else if (map[_q + 1][w] == 0) {
							map[_q + 1][w] = map[_q][w];
							map[_q][w] = 0;

							sub_map[_q + 1][w] = sub_map[_q][w];
							sub_map[_q][w] = 0;
						}
						else if (map[_q + 1][w] == map[_q][w]) {
							map[_q + 1][w] *= 2;
							map[_q][w] = 0;

							sub_map[_q + 1][w] += 1;
							sub_map[_q][w] = 0;
							while (true) {
								_q++;
								if (_q == 3)
									break;
								else if (map[_q + 1][w] == 0) {
									map[_q + 1][w] = map[_q][w];
									map[_q][w] = 0;

									sub_map[_q + 1][w] = sub_map[_q][w];
									sub_map[_q][w] = 0;
								}
							}
							break;
						}
						else {
							break;
						}
						_q++;
					}
				}
			}
		}
	}
	bool equal = !find_space();
	//std::cout << std::boolalpha << equal << "\n\n";
	//std::cout << "right : " << std::boolalpha << equal << "\n\n";
	if (equal && !is_test) {
		up(false);
	}
	if (is_test) {
		for (int q = 0; q < 4; q++) {
			for (int w = 0; w< 4; w++) {
				map[q][w] = test[q][w];
				sub_map[q][w] = sub_test[q][w];
			}
		}
		if (!equal) {
			throw 1;
		}
	}
}
void print_map() {
	for (int q = 0; q < 29; q++) {
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int q = 0; q < 4; q++) {
		std::cout << "|      |      |      |      |\n";
		for (int w = 0; w < 4; w++) {
			std::cout << "|";
			if (map[w][q] != 0)
				std::cout << map[w][q];
			for (int e = 0; e < 6 - get_number_digit(w, q); e++) {
				std::cout << " ";
			}
		}
		std::cout << "|\n|      |      |      |      |\n";
		std::cout << "-----------------------------\n";
	}
}
bool find_space() {
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			if (map[q][w] == 0)
				return true;
		}
	}
	return false;
}
bool check_dead() {
	try {
		up(true);
		down(true);
		right(true);
		left(true);
	}
	catch (int) {
		return false;
	}
	return true;
}
void generate() {
	int random = (std::rand() % 16) + 1;
	int x = -1, y = 0;
	bool found = false;
	while (random > 0) {
		++x;
		if (x == 4) {
			++y;
			x = 0;
		}
		if (y == 4) {
			if (found) {
				y = 0;
			}
			else {
				throw 1;
				return;
			}
		}
		if (map[x][y] == 0) {
			random--;
			found = true;
		}
	}
	map[x][y] = 2;
	sub_map[x][y] = 1;
}
void reset_map(){
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			map[q][w] = 0;
			sub_map[q][w] = 0;
		}
	}
}
int get_output(Gene& Ai,const std::size_t& position) {
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			Ai.set_input(position, q * 4 + w, double(sub_map[q][w]));
		}
	}
	Ai.feedforward(position);
	double max = 0;
	max = Ai.get_output(position,0);
	int num1 = 0;
	for (int q = 0; q < 3; q++) {
		if (max < Ai.get_output(position, q + 1)) {
			max = Ai.get_output(position, q + 1);
			num1 = q + 1;
		}
	}
	return num1;
}
int get_output_bestAI(Gene& AI) {
	for (int q = 0; q < 4; q++) {
		for (int w = 0; w < 4; w++) {
			AI.set_input_bestAI(q * 4 + w, double(sub_map[q][w]));
		}
	}
	AI.feedforward_bestAI();
	double max = 0;
	max = AI.get_output_bestAI(0);
	int num1 = 0;
	for (int q = 0; q < 3; q++) {
		if (max < AI.get_output_bestAI(q + 1)) {
			max = AI.get_output_bestAI(q + 1);
			num1 = q + 1;
		}
	}
	return num1;
}
void play(Gene& AI) {
	reset_map();
	generate();
	while (true) {
		generate();
		if (check_dead()) {
			break;
		}
		int result = get_output_bestAI(AI);
		switch (result) {
		case 0:up(false); break;
		case 1:down(false); break;
		case 2:left(false); break;
		case 3:right(false); break;
		}
		print_map();
	}
	std::cout << "\n\nThe simulator has ended,pls check and see the result";
}
int main() {
	Gene AI(100, 16, 64, 4);
	double score_max = 0;
	int generation = 0;
	AI.setup_mutation_chance(0.2);
	AI.setup_mutation_rate(0.8);
	int loop = 0;
	while (loop<6000) {
		++generation;
		for (int q = 0; q < 100; q++) {
			reset_map();
			generate();
			while (true) {
				generate();
				//print_map();
				if (check_dead()) {
					break;
				}
				int result = get_output(AI,q);
				switch (result) {
				case 0:up(false); break;
				case 1:down(false); break;
				case 2:left(false); break;
				case 3 :right(false); break;
				}
				//if (q == 0) {
					//std::cout << "[0] : "<< result << std::endl;
				//}
				//print_map();
				//std::cout << result << "\n\n";
			}
			unsigned int score = 0;
			for (int q = 0; q < 4; q++) {
				for (int w = 0; w < 4; w++) {
					score += map[q][w];
				}
			}
			AI.set_score(q,score);
			std::cout << "AI Gen : " << generation << " has completed for : " << q /10<< "% " << "and score is : " << score << std::endl;
		}
		if (score_max < AI.max_score()) {
			score_max = AI.max_score();
		}
		std::cout << "AI Gen : " << generation << " has completed and best score of this gen is : " << AI.max_score() << "   and the best score of all the time is : " << score_max << std::endl;
		//AI.print_info(0);
		AI.record();
		AI.calculate_fitness();
		/*if (AI.max_score() >= 1500) {
			AI.setup_mutation_rate(0.08);
			AI.setup_mutation_chance(0.07);
		}
		if (AI.max_score() >= 2200) {
			AI.setup_mutation_rate(0.06);
			AI.setup_mutation_chance(0.06);
		}
		if (AI.max_score() >= 3000) {
			AI.setup_mutation_rate(0.04);
			AI.setup_mutation_chance(0.04);
		}
		if (AI.max_score() >= 4000) {
			AI.setup_mutation_rate(0.01);
			AI.setup_mutation_chance(0.01);
		}*/
		AI.mutate();
		loop++;
	}
	play(AI);
	play(AI);
	play(AI);
	play(AI);
	while (true) {

	}
	return 0;
}