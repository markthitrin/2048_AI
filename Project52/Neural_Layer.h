#pragma once
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
class Neural_Layer
{
public:
	Neural_Layer() { ; };
	Neural_Layer(const Neural_Layer& copy) : neuron_size(copy.neuron_size), nextneuron_size(copy.nextneuron_size) {
		if (neuron_size == 0)
			return;
		value = new double[neuron_size];
		if (nextneuron_size > 0)
			weight = new double*[neuron_size];
		for (int q = 0; q < neuron_size; q++) {
			value[q] = (copy.value)[q];
			if (nextneuron_size > 0) {
				weight[q] = new double[nextneuron_size];
				for (int w = 0; w < nextneuron_size; w++) {
					weight[q][w] = (copy.weight)[q][w];
				}
			}
		}
	}
	Neural_Layer(std::size_t _neuron_size) : neuron_size(_neuron_size) {
		value = new double[_neuron_size];
	}
	Neural_Layer(std::size_t _neuron_size, std::size_t _nextneuron_size) : neuron_size(_neuron_size), nextneuron_size(_nextneuron_size) {
		value = new double[_neuron_size];
		weight = new double*[_neuron_size];
		for (int i = 0; i < _neuron_size; i++) {
			weight[i] = new double[_nextneuron_size];
			for (int w = 0; w < _nextneuron_size; w++) {
				weight[i][w] = double(std::rand() % 1000) / 1000;
			}
		}
	}

	double operator[](int position) {
		return value[position];
	}
	void operator=(const Neural_Layer& copy) {
		neuron_size = copy.neuron_size;
		nextneuron_size = copy.nextneuron_size;
		value = new double[copy.neuron_size];
		weight = new double*[copy.neuron_size];
		for (int q = 0; q < copy.neuron_size; q++) {
			weight[q] = new double[copy.nextneuron_size];
			for (int w = 0; w < copy.nextneuron_size; w++) {
				weight[q][w] = copy.weight[q][w];
			}
		}
	}
	void setup_weight(const std::size_t& _nextneuron_size) {
		nextneuron_size = _nextneuron_size;
		weight = new double*[neuron_size];
		for (int q = 0; q < neuron_size; q++) {
			weight[q] = new double[nextneuron_size];
			for (int w = 0; w < nextneuron_size; w++) {
				weight[q][w] = double(std::rand() % 1000) / 1000;
			}
		}
	}
	void setup_neuron(const std::size_t& _neuron_size) {
		neuron_size = _neuron_size;
		value = new double[neuron_size];
	}
	double sigmoid(const std::size_t& position) {
		return 1 / (1 + exp(-value[position]));
	}
	double dsigmoid(const std::size_t& position) {
		return sigmoid(position) * (1 - sigmoid(position));
	}

	~Neural_Layer() {
		delete[] value;
		if (nextneuron_size != 0) {
			for (int q = 0; q < neuron_size; q++) {
				delete[] weight[q];
			}
			delete[] weight;
		}
	}
private:
	void destroy() {
		delete[] value;
		if (nextneuron_size != 0) {
			for (int q = 0; q < neuron_size; q++) {
				delete weight[q];
			}
			delete weight;
		}
	}
	friend class Neural_Network;
	friend class Gene;
	std::size_t neuron_size = 0;
	std::size_t nextneuron_size = 0;
	double *value = nullptr;
	double **weight = nullptr;// one pointer for each neural
							  // two pointer for next neural of each neural
};
