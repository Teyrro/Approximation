#include "Interpolation.h"
#pragma region Interpolation

void Interpolation::OutputDataValue() {
	std::fstream myfile("../example.csv", std::ios::app);
	myfile << value << "; " << _answer << "\n";
}

void Interpolation::OutputDataValue(double x, double y) {
	std::fstream myfile("../example.csv", std::ios::app);
	myfile << x << "; " << y << "\n";
}


void Interpolation::OutputData() {
	std::ofstream myfile("../example.csv");

	//myfile << amountGraph << ";" << 0 << "\n";
	myfile << storageOfData.size() + 2 << ";" << 0 << "\n";
	myfile << -100;
	myfile << "; ";
	myfile << getYbyX(storageOfData[0], storageOfData[1], -100);
	myfile << "\n";

	for (auto& ptr : storageOfData) {
		myfile << ptr.first;
		myfile << "; ";
		myfile << ptr.second;
		myfile << "\n";
	}

	myfile << 100;
	myfile << "; ";
	myfile << getYbyX(storageOfData[storageOfData.size() - 2], storageOfData[storageOfData.size() - 1], 100);
	myfile << "\n";
	myfile.close();
}

double Interpolation::getYbyX(ValueAndAnswer firstPoint, ValueAndAnswer secondPoint, double xValue) {
	double k = (secondPoint.second - firstPoint.second) / (secondPoint.first - firstPoint.first);
	double b = firstPoint.second - k * firstPoint.first;
	return k * xValue + b;
}
#pragma endregion