#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <functional>
#include "gauss.h"

class Approximation {
	std::vector<std::pair<double, double>> dots;
	std::function<double(double, int)> Fns;
	int countFunc;
	std::vector<std::vector<double>> matrix;
	std::vector<double> coefficients;
	std::function<double(double)> Func;

	double FunctionX(int index1, int index2) {
		double tmpSum = 0;
		for (int i = 0; i < dots.size(); i++) {
			tmpSum += Fns(dots[i].first, index1) * Fns(dots[i].first, index2);
			std::cout << "(" << Fns(dots[i].first, index1) << " * " << Fns(dots[i].first, index2) << ") +";
		}
		std::cout << "\n";

		return tmpSum;
	}

	double FunctionY(int index) {
		double tmpSum = 0;
		for (int i = 0; i < dots.size(); i++) {
			tmpSum += dots[i].second * Fns(dots[i].first, index);
			//std::cout << "(" << dots[i].second << " * " << pow(dots[i].first, degrees[index]) << ") +";
		}
		std::cout << "\n";
		return tmpSum;
	}

	void FillDots(std::vector<double> xValue) {
		for (int i = 0; i < xValue.size(); i++) {
			dots[i].first = xValue[i];
			dots[i].second = Func(dots[i].first);
		}
	}

public:
	Approximation(std::vector<double> xValue, int countFunc, std::function<double(double, int)> functions, std::function<double(double)> func) 
	: Func(func), Fns(functions), countFunc(countFunc) {

		dots.resize(xValue.size());
		FillDots(xValue);

		matrix.resize(countFunc);
		for (int i = 0; i < countFunc; i++) {
			matrix[i].resize(countFunc + 1);
		}

		std::cout << "X:\n";
		for (int i = 0; i < dots.size(); i++) {
			std::cout << dots[i].first << ", ";
		}
		std::cout << "\n\nY:\n";
		for (int i = 0; i < dots.size(); i++) {
			std::cout << dots[i].second << ", ";
		}
		std::cout << "\n";

		for (int i = 0; i < countFunc; i++) {

			for (int j = 0; j < countFunc; j++) {
				matrix[i][j] = FunctionX(i, j);
				//std::cout << "| ";
			}
			matrix[i][matrix.size()] = FunctionY(i);
			//std::cout << '\n';
		}

		std::cout << "\nMatrix:\n";

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << '\n';
		}

		std::cout << "\nGaussMethod:\n";
		GaussMethod a(matrix);
		coefficients = a.FindAnswer();
	}

	void CalculateApproximation(double L, double R, double step) {
		double x = L;
		int size = ((R - L) + step * 0.1) / step;
		double tmpSum(0);
		//OutputData();
		std::fstream myfile("../example.csv", std::ios::app);
		OutputDataValue(size, 0);
		std::cout << "\nApproximation:\n";
		for (int i = 0; i < size; i++, x += step) {
			for (int j = 0; j < countFunc; j++) {
				tmpSum += coefficients[j] * Fns(x, j);
			}
			std::cout << "X_" << i << " = " << x << " ";
			std::cout << "Y_" << i << " = " << tmpSum << "\n";
			OutputDataValue(x, tmpSum);
			tmpSum = 0;
		}
		myfile.close();
	} 

	double getYbyX(std::pair<double, double> firstPoint, std::pair<double, double> secondPoint, double xValue) {
		double k = (secondPoint.second - firstPoint.second) / (secondPoint.first - firstPoint.first);
		double b = firstPoint.second - k * firstPoint.first;
		return k * xValue + b;
	}

	void OutputData() {
		std::ofstream myfile("../example.csv");
		myfile << dots.size() + 2 << ";" << 0 << "\n";
		myfile << -100;
		myfile << "; ";
		myfile << getYbyX(dots[0], dots[1], -100);
		myfile << "\n";

		for (auto& ptr : dots) {
			myfile << ptr.first;
			myfile << "; ";
			myfile << ptr.second;
			myfile << "\n";
		}

		myfile << 100;
		myfile << "; ";
		myfile << getYbyX(dots[dots.size() - 2], dots[dots.size() - 1], 100);
		myfile << "\n";
		myfile.close();
	}

	void OutputDataValue(double x, double y) {
		std::fstream myfile("../example.csv", std::ios::app);
		myfile << x << "; " << y << "\n";
	}
};