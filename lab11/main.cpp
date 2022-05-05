#include <iostream>
#include "approximation.h"
#include "gauss.h"
#include "Interpolation.h"

double Func(double x) {
	double y;
	//y = pow(x, 2);
	//y = sqrt(x);
	//y = 2*x + 10;
	if (tan(x) == 0)
		return (pow(x, 3) + 3 * pow(x, 2) + 7 * x - 2) / 0.01;
	y = (pow(x, 2) + 7*x - 2) / tan(x);
	return y;
}
 // 3
double Functions(double x, int index) {
	switch (index) {
	case 0: return 1;
	case 1: return x;
	case 3: return exp(x);
	case 2: return sin(x);
	case 4: return pow(x, 2);
	case 5:
	case 6:
	default: throw;
	}
}

std::vector<double> GenerateX(double left, double right, double step) {
	std::vector<double> dots(((right - left) + step * 0.1) / step);
	for (int i(0); i < dots.size(); i++, left += step) {
		dots[i] = left;
	}
	return dots;
}

int main() {
	// узлы аппроксимации
	double left(12), right(20), h(1);
	std::vector<double> dots(GenerateX(left, right, h));

	// границы отрезка и шаг
	double leftBorder(12), rightBorder(19.2), step(0.1);
	int countFunc(5);

	Interpolation b(leftBorder, rightBorder, dots, Func);
	b.FindAnswer();
	b.CreateGraph(b.startInterval, b.endInterval, step);

	Approximation a(dots, countFunc, Functions, Func);
	a.CalculateApproximation(leftBorder, rightBorder, step);


	/*GaussMethod a(matrix);
	std::vector<double> coefficients = a.FindAnswer();

	std::cout << "\n\nanswer: ";
	for (int i = 0; i < coefficients.size(); i++) {
		std::cout << coefficients[i] << " ";
	}
	std::cout << "\n\n";*/
}