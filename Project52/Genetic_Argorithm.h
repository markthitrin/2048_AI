#include "Neural_Network.h"

class Gene {
public:
	Gene() { ; }
	template <typename ...t>
	Gene(std::size_t _population, t... number) {
		population = _population;
		nn = new Neural_Network[population];
		for (int q = 0; q < _population; q++) {
			nn[q].setup_neuron(number...);
		}
		best_AI.setup_neuron(number...);
		score = new double[population];
		fitness = new double[population];
	}
	void setup_mutation_chance(const double& a) {
		mutation_chance = a;
	}
	void setup_population(const std::size_t& _poppulation) {
		if (population < _poppulation) {
			Neural_Network* _nn = new Neural_Network[_poppulation];
			for (int q = 0; q < population; q++) {
				_nn[q] = nn[q];
			}
			for (int w = population; w < _poppulation; w++) {
				_nn[w] = nn[std::rand() % population];
			}
			delete[] nn;
			nn = &_nn[0];
		}
		else if (population > _poppulation) {
			Neural_Network* _nn = new Neural_Network[_poppulation];
			for (int q = 0; q < _poppulation; q++) {
				_nn[q] = nn[q];
			}
			delete[] nn;
			nn = &_nn[0];
		}
		population = _poppulation;
		double* _score = new double[population];
		double* _fitness = new double[population];
		delete[] score;
		delete[] fitness;
		score = &_score[0];
	}
	std::size_t pick_one() {
		double random = double(std::rand() % 10000) / 10000;
		double count = 0;
		int q = 0;
		while (true) {
			count += fitness[q];
			if (count >= random) {
				return q;
			}
			++q;
		}
	}
	void mutate() {
		Neural_Network *copy = new Neural_Network[population];
		for (int q = 0; q < population; q++) {
			copy[q].input.setup_neuron(nn[0].input.neuron_size);
			copy[q].input.setup_weight(nn[0].input.nextneuron_size);
			copy[q].hidden_size = nn[0].hidden_size;
			copy[q].hidden = new Neural_Layer[copy[0].hidden_size];
			for (int w = 0; w < nn[0].hidden_size; w++) {
				copy[q].hidden[w].setup_neuron(nn[0].hidden[w].neuron_size);
				copy[q].hidden[w].setup_weight(nn[0].hidden[w].nextneuron_size);
			}
			copy[q].output.setup_neuron(nn[0].output.neuron_size);
			copy[q].output.setup_weight(nn[0].output.nextneuron_size);
			copy[q].bias = new double*[nn[0].hidden_size + 1];
			for (int w = 0; w < nn[0].hidden_size; w++) {
				copy[q].bias[w] = new double[nn[0].hidden[w].neuron_size];
			}
			copy[q].bias[nn[0].hidden_size] = new double[nn[0].output.neuron_size];
		}
		for (int q = 0; q < population; q++) {
			std::size_t position = pick_one();
			copy[q].copy(nn[position]);
			for (int w = 0; w < copy[position].input.neuron_size; w++) {
				for (int e = 0; e < copy[position].input.nextneuron_size; e++) {
					int num1 = double(rand() % 1000) / 1000;
					if (num1 <= mutation_chance) {
						copy[position].input.weight[w][e] += double((std::rand() - std::rand()) % 10000) / 10000 * mutation_rate;
						
					}
				}
			}
			for (int w = 0; w < copy[position].hidden_size; w++) {
				for (int e = 0; e < copy[position].hidden[w].neuron_size; e++) {
					for (int r = 0; r < copy[position].hidden[w].nextneuron_size; r++) {
						int num1 = double(rand() % 1000) / 1000;
						if (num1 <= mutation_chance) {
							copy[position].hidden[w].weight[e][r] += double((std::rand() - std::rand()) % 10000) / 10000 * mutation_rate;
							
						}
					}
				}
			}
			for (int w = 0; w < copy[position].output.neuron_size; w++) {
				for (int e = 0; e < copy[position].output.nextneuron_size; e++) {
					int num1 = double(rand() % 1000) / 1000;
					if (num1 <= mutation_chance) {
						copy[position].output.weight[w][e] += double((std::rand() - std::rand()) % 10000) / 10000 * mutation_rate;
						
					}
				}
			}
			for (int w = 0; w < copy[position].hidden_size; w++) {
				for (int e = 0; e < copy[position].hidden[w].nextneuron_size; e++) {
					int num1 = double(rand() % 1000) / 1000;
					if (num1 <= mutation_chance) {
						copy[position].bias[w][e] += double((std::rand() - std::rand()) % 10000) / 10000 * mutation_rate;
						
					}
				}
			}
			for (int w = 0; w < copy[position].output.neuron_size; w++) {
				int num1 = double(rand() % 1000) / 1000;
				if (num1 <= mutation_chance) {
					copy[position].bias[copy[position].hidden_size][w] += double((std::rand() - std::rand()) % 10000) / 10000 * mutation_rate;
					
				}
			}
		}
		for (int q = 0; q < population; q++) {
			nn[q].copy(copy[q]);
		}
		delete[] copy;
	}
	void print_info() {
		for (int q = 0; q < population; q++) {
			std::cout << "Neural_Network number : " << q << std::endl << std::endl;
			print_info(q);
			std::cout << std::endl << std::endl;
		}
		return;
	}
	void print_info(std::size_t position) {
		if (position >= population) {
			throw std::exception("Not enough population");
			return;
		}
		nn[position].print_info();
	}
	void set_fitness(const std::size_t& position, const double& value) {
		if (position + 1 > population)
			throw 1;
		fitness[position] = value;
		return;
	}
	void calculate_fitness() {
		unsigned int sum = 0;
		for (int q = 0; q < population; q++) {
			sum += pow(score[q]/100,4);
		}
		for (int q = 0; q < population; q++) {
			fitness[q] = pow(score[q]/100,4) / sum;
		}
	}
	void set_score(const std::size_t& position, const double& value) {
		score[position] = value;
	}
	void set_input(const std::size_t& nn_position,const std::size_t& input_position,const double& value) {
		nn[nn_position].input.value[input_position] = value;
	}
	void feedforward(const std::size_t& position) {
		nn[position].feedforward();
	}
	double get_output(const std::size_t& nn_position,const std::size_t& output_position) {
		return nn[nn_position].get_output(output_position);
	}
	double max_score() {
		double max = score[0];
		for (int q = 1; q < population; q++) {
			if (max < score[q]) {
				max = score[q];
			}
		}
		return max;
	}
	void setup_mutation_rate(const double& value) {
		mutation_rate = value;
	}
	void record() {
		double max = score[0];
		int position = 0;
		for (int q = 1; q < population; q++) {
			if (score[q] > max) {
				max = score[q];
				position = q;
			}
		}
		if (max > bestAI_score) {
			best_AI.copy(nn[position]);
		}
	}
	void set_input_bestAI(const std::size_t& input_position, double value) {
		best_AI.input.value[input_position] = value;
	}
	double get_output_bestAI(const std::size_t& output_position) {
		return best_AI.get_output(output_position);
	}
	void feedforward_bestAI() {
		best_AI.feedforward();
	}
private:
	Neural_Network* nn;
	double *score;
	double *fitness;
	std::size_t population = 0;
	double mutation_chance = 0.1;
	double mutation_rate = 1;
	Neural_Network best_AI;
	double bestAI_score;
};