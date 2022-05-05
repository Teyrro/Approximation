#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <functional>

using ValueAndAnswer = std::pair<double, double>;

class Interpolation {
private:
	double g(int currentIndex) {
		double dividend(1), divider(1);
		int i(0);
		int ptr = currentIndex;
		while (i < storageOfData.size()) {
			for (i; i < ptr; i++) {
				dividend *= value - storageOfData[i].first;
				divider *= storageOfData[currentIndex].first - storageOfData[i].first;
			}
			if (dividend == 0)
				return 0;
			ptr = storageOfData.size();
			i++;
		}
		return dividend / divider;
	}
public:
	std::vector<ValueAndAnswer> storageOfData;
	double getYbyX(ValueAndAnswer firstPoint, ValueAndAnswer secondPoint, double xValue);
	double value;
	double _answer;
	std::function<double(double)> FuncForInterp;

	double startInterval;
	double endInterval;

	//double virtual  FuncForInterp(double x) {
	//	double value;
	//	//value = sqrt(x);
	//	//value =pow(x, -1);
	//	//value = pow(x, 2);
	//	return value;
	//}

	Interpolation(std::string fileName) {
		std::ifstream input(fileName);
		unsigned short size;
		input >> size;
		storageOfData.resize(size);
		for (int i(0); i < size; i++) {
			input >> storageOfData[i].first;
		}
		for (int i(0); i < size; i++) {
			storageOfData[i].second = FuncForInterp(storageOfData[i].first);
		}

	}

	Interpolation(double startInterval, double endInterval, std::vector<double> x, std::function<double(double)> func) : FuncForInterp(func), startInterval(startInterval),
		endInterval(endInterval)
	{
		storageOfData.resize(x.size());
		for (int i(0); i < x.size(); i++) {
			storageOfData[i].first = x[i];
		}
		for (int i(0); i < x.size(); i++) {
			storageOfData[i].second = FuncForInterp(storageOfData[i].first);
		}

	}

	//Interpolation(std::string fileName, double startInterval, double endInterval, bool IsStrange) :
	//	startInterval(startInterval),
	//	endInterval(endInterval)
	//{
	//	std::ifstream input(fileName);
	//	unsigned short size;
	//	input >> size;

	//	if (IsStrange) {
	//		storageOfData.resize(size);
	//		for (int i(0); i < size; i++) {
	//			input >> storageOfData[i].first;
	//		}
	//		for (int i(0); i < size; i++) {
	//			input >> storageOfData[i].second;
	//		}
	//	}
	//	else {
	//		storageOfData.resize(size);
	//		for (int i(0); i < size; i++) {
	//			input >> storageOfData[i].first;
	//		}
	//		for (int i(0); i < size; i++) {
	//			storageOfData[i].second = FuncForInterp(storageOfData[i].first);
	//		}
	//	}

	//}

	virtual void  SetNewValue(double val) {
		value = val;
	}

	void OutputData();
	void OutputDataValue();
	void OutputDataValue(double x, double y);

	void FindAnswer() {
		double sum(0);
		for (int i(0); i < storageOfData.size(); i++) {
			sum += storageOfData[i].second * g(i);
		}
		_answer = sum;
		std::cout << _answer << "\n";
	};

	void CreateGraph(double startInterval, double endInterval, double step) {
		OutputData();

		OutputDataValue((int)(((endInterval - startInterval) + step * 0.1) / step), 0);
		for (auto i(startInterval); i + step * 0.1 < endInterval; i += step) {
			value = i;
			FindAnswer();
			OutputDataValue();
		}

		//OutputDataValue((int)(((endInterval - startInterval) + step * 0.1) / step), 0);
		//for (double i(startInterval); i + step * 0.1 < endInterval; i += step) {
		//	OutputDataValue(i, FuncForInterp(i));
		//}
	}


};