#pragma once
#include "Neural_Layer.h"
#include <initializer_list>
class Neural_Network
{
public:
	Neural_Network() { ; };
	Neural_Network(std::initializer_list<unsigned int> list) {
		std::size_t Max;
		std::srand(std::time(0));
		if (list.size() < 2)
			throw std::exception("can not declear Netral Network with less than 2 layer");
		input.setup_neuron(*(list.begin()));
		input.setup_weight(*(list.begin() + 1));
		output.setup_neuron(*(list.end() - 1));
		hidden = new Neural_Layer[list.size() - 2];
		for (int q = 0; q < list.size() - 2; q++) {
			hidden[q].setup_neuron(*(list.begin() + q + 1));
			hidden[q].setup_weight(*(list.begin() + q + 2));
		}
		hidden_size = list.size() - 2;
		bias = new double*[hidden_size + 1];
		for (int q = 0; q < hidden_size + 1; q++) {
			unsigned int size = 0;
			if (q != hidden_size) {
				bias[q] = new double[hidden[q].neuron_size];
				size = hidden[q].neuron_size;
			}
			else {
				bias[q] = new double[output.neuron_size];
				size = output.neuron_size;
			}
			for (int w = 0; w < size; w++) {
				bias[q][w] = double(std::rand() % 1000) / 1000;
			}
		}
		set_up_error();
	}
	template <typename... t>
	Neural_Network(const std::size_t& number, t... list) {
		std::srand(std::time(0));
		input.setup_neuron(number);
		input.setup_weight(declare(list...));
		bias = new double*[hidden_size + 1];
		for (int q = 0; q < hidden_size + 1; q++) {
			unsigned int size = 0;
			if (q != hidden_size) {
				bias[q] = new double[hidden[q].neuron_size];
				size = hidden[q].neuron_size;
			}
			else {
				bias[q] = new double[output.neuron_size];
				size = output.neuron_size;
			}
			for (int w = 0; w < size; w++) {
				bias[q][w] = double(std::rand() % 1000) / 1000;
			}
		}
		set_up_error();
	}
	Neural_Network(const Neural_Network& copy) : input(copy.input), output(copy.output) {
		hidden_size = copy.hidden_size;
		learning_rate = copy.learning_rate;
		hidden = new Neural_Layer[hidden_size];
		bias = new double*[hidden_size + 1];
		for (int q = 0; q < hidden_size; q++) {
			hidden[q] = copy.hidden[q];
		}
		for (int q = 0; q < hidden_size + 1; q++) {
			bias[q] = new double[hidden[q].neuron_size];
			for (int w = 0; w < hidden[w].neuron_size; w++) {
				bias[q][w] = copy.bias[q][w];
			}
		}
	}
	~Neural_Network() {
		delete[] hidden;
	};

	double operator[](const std::size_t& position) { return output.value[position]; }

	double get_output(const std::size_t& position) {
		if (position > output.neuron_size - 1)
			throw std::exception("that output has not declared");
		return output.sigmoid(position);
	}
	void set_input(std::initializer_list<double> list) {
		if (list.size() > input.neuron_size)
			throw std::exception("too many");
		for (int q = 0; q < list.size(); q++) {
			input.value[q] = *(list.begin() + q);
		}
	}
	template <typename... t>
	void set_input(const std::size_t& number, t... list) {
		input.value[input.neuron_size - set_input_pri(list...)] = number;
	}
	void feedforward() {
		Neural_Layer* left;
		Neural_Layer* right;
		for (int q = 0; q < hidden_size + 1; q++) {
			if (hidden_size == 0) {
				left = &input;
				right = &output;
			}
			else if (q == 0) {
				left = &input;
				right = &(hidden[0]);
			}
			else if (q == hidden_size) {
				left = &(hidden[hidden_size - 1]);
				right = &output;
			}
			else {
				left = &(hidden[q - 1]);
				right = &(hidden[q]);
			}
			for (int w = 0; w < (*right).neuron_size; w++) {
				double total = 0;
				for (int e = 0; e < (*left).neuron_size; e++) {
					total += ((q == 0) ? ((*left).value[e] * (*left).weight[e][w]) : ((*left).sigmoid(e) * (*left).weight[e][w]));
				}
				total += bias[q][w];
				(*right).value[w] = total;
			}
		}
	}
	void learn(double* target) {
		Neural_Layer* left;
		std::size_t error_size;
		for (int q = hidden_size + 1; q >= 0; q--) {
			if (hidden_size == 0) {
				if (q == 1) {
					error_size = output.neuron_size;
					for (int w = 0; w < output.neuron_size; w++)
						error[w] = (output.sigmoid(w) - target[w]) * output.dsigmoid(w) * 2;
					continue;
				}
				else {
					error_size = output.neuron_size;
					left = &input;
				}
			}
			else {
				if (q == hidden_size + 1) {
					error_size = output.neuron_size;
					for (int w = 0; w < output.neuron_size; w++)
						error[w] = (output.sigmoid(w) - target[w]) * output.dsigmoid(w) * 2;
					continue;
				}
				else if (q == 0) {
					error_size = hidden[0].neuron_size;
					left = &input;
				}
				else if (q == hidden_size) {
					error_size = output.neuron_size;
					left = &(hidden[hidden_size - 1]);
				}
				else {
					error_size = hidden[q].neuron_size;
					left = &(hidden[q - 1]);
				}
			}
			for (int w = 0; w < error_size; w++) {
				double change = error[w] * learning_rate;
				for (int e = 0; e < (*left).neuron_size; e++)
					(*left).weight[e][w] -= (change * (*left).sigmoid(e));
				bias[q][w] -= change;
			}
			for (int w = 0; w < (*left).neuron_size; w++) {
				error_sub[w] = 0;
			}
			for (int w = 0; w < error_size; w++) {
				double sum_weight = 0;
				/*for (int e = 0; e < (*left).neuron_size; e++) {
					sum_weight = sum_weight + (*left).weight[e][w];
				}*/
				for (int e = 0; e < (*left).neuron_size; e++) {
					error_sub[e] += ((error[w] * (*left).weight[e][w] * (*left).dsigmoid(e)));// sum_weight);
				}
			}
			for (int w = 0; w < (*left).neuron_size; w++)
				error[w] = error_sub[w];
		}

	}
	template <typename ...t>
	void setup_neuron(std::size_t number, t... list) {
		std::srand(std::time(0));
		input.setup_neuron(number);
		input.setup_weight(declare(list...));
		bias = new double*[hidden_size + 1];
		for (int q = 0; q < hidden_size + 1; q++) {
			unsigned int size = 0;
			if (q != hidden_size) {
				bias[q] = new double[hidden[q].neuron_size];
				size = hidden[q].neuron_size;
			}
			else {
				bias[q] = new double[output.neuron_size];
				size = output.neuron_size;
			}
			for (int w = 0; w < size; w++) {
				bias[q][w] = double(std::rand() % 1000) / 1000;
			}
		}
		set_up_error();
	}
	void set_learning_rate(const double& _learning_rate) {
		learning_rate = _learning_rate;
	}
	void copy(const Neural_Network& copy) {
		for (int q = 0; q < input.neuron_size; q++) {
			for (int w = 0; w < input.nextneuron_size; w++) {
				input.weight[q][w] = copy.input.weight[q][w];
			}
		}
		for (int q = 0; q < copy.hidden_size; q++) {
			for (int w = 0; w < copy.hidden[q].neuron_size; w++) {
				for (int e = 0; e < copy.hidden[q].nextneuron_size; e++) {
					hidden[q].weight[w][e] = copy.hidden[q].weight[w][e];
				}
			}
		}
		for (int q = 0; q < copy.hidden_size; q++) {
			for (int w = 0; w < copy.hidden[q].neuron_size; w++) {
				bias[q][w] = copy.bias[q][w];
			}
		}
		for (int q = 0; q < copy.output.neuron_size; q++){
			bias[hidden_size][q] = copy.bias[hidden_size][q];
	}
	}
	void print_info() {
		for (int q = 0; q < input.neuron_size; q++) {
			std::cout << "input[" << q << "] : " << input.value[q] << std::endl;
			for (int w = 0; w < input.nextneuron_size; w++) {
				std::cout << "     ";
				std::cout << "input[" << q << "] to [" << w << "] : " << input.weight[q][w] << std::endl;
			}
		}
		for (int q = 0; q < hidden_size; q++) {
			for (int w = 0; w < hidden[q].neuron_size; w++) {
				std::cout << "hidden[" << w << "] " << "L[" << q << "] : " << hidden[q].sigmoid(w) << std::endl;
				std::cout << "bias : " << bias[q][w] << std::endl;
				for (int e = 0; e < hidden[q].nextneuron_size; e++) {
					std::cout << "     " << "hidden[" << w << "] " << "L[" << q << "] to [" << e << "] : " << hidden[q].weight[w][e] << std::endl;
				}
			}
		}
		for (int q = 0; q < output.neuron_size; q++) {
			std::cout << "output[" << q << "] : " << output.sigmoid(q) << std::endl;
			std::cout << "bias : " << bias[hidden_size][q] << std::endl;
		}
	}
private:
	void set_up_error() {
		std::size_t Max = input.neuron_size;
		for (int q = 0; q < hidden_size; q++) {
			if (hidden[q].neuron_size > Max) {
				Max = hidden[q].neuron_size;
			}
		}
		if (output.neuron_size > Max)
			Max = output.neuron_size;
		error = new double[Max];
		error_sub = new double[Max];
	}
	template <typename... t>
	int set_input_pri(const std::size_t& number, t... list) {
		int position = set_input_pri(list...);
		input.value[input.neuron_size - position];
		return position + 1;
	}
	int set_input_pri(const std::size_t& number) {
		input.value[input.neuron_size - 1] = number;
		return 2;
	}
	template <typename... t>
	unsigned int declare(const std::size_t& number, t... list) {
		int position = hidden_size++;
		int next_layer = declare(list...);
		hidden[position].setup_neuron(number);
		hidden[position].setup_weight(next_layer);
		bias[position] = new double[number];
		return number;
	}
	unsigned int declare(const std::size_t& number) {
		output.setup_neuron(number);
		if (hidden_size > 0)
			hidden = new Neural_Layer[hidden_size];
		bias = new double*[hidden_size + 1];
		bias[hidden_size] = new double[number];
		return number;
	}
	Neural_Layer input;
	Neural_Layer *hidden;
	Neural_Layer output;
	std::size_t hidden_size = 0;
	double **bias;
	double *error;
	double *error_sub;
	double learning_rate = 0.1;
	friend class Gene;
};




