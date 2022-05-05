#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

class GaussMethod {

public:

	GaussMethod(std::vector<std::vector<double>> matrixValue) : mtrx(matrixValue) {
		H = mtrx.size();
		W = mtrx[0].size();
	}

	std::vector<double> FindAnswer() {
		try {
			lineNulling();
			findUnknown();
		}
		catch (const char* f) {
			std::cout << "Error: " << f << "\n";
		}
		catch (...) {
			std::cout << "Error: Undefind" << "\n";
		}
		return unknowns;
	}

private:

	std::vector<std::vector<double>> mtrx;
	std::vector<double> unknowns;
	int W, H;

	void printMatrix() {

		std::cout << std::fixed;

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				std::cout << std::setprecision(3) << mtrx[i][j] << '\t';
			}
			std::cout << '\n';
		}
		std::cout << '\n';

		std::cout << std::fixed;
	}

	void swapLine(int index1, int index2) {
		for (int i = 0; i < W; i++) {
			std::swap(mtrx[index1][i], mtrx[index2][i]);
		}
	}

	void findUnknown() {
		unknowns.resize(W - 1);

		for (int i = H - 1; i >= 0; i--) {
			int j = W - 1;
			mtrx[i][j] *= -1;
			for (j; j != i; j--) {
				unknowns[i] += mtrx[i][j];
			}

			if (mtrx[i][j] == 0) {
				throw "Singular matrix";
			}
			unknowns[i] /= -mtrx[i][j];

			for (int f = j; f >= 0; f--) {
				mtrx[f][j] *= unknowns[i];
			}
		}

		for (int i = 0; i < unknowns.size(); i++) {
			std::cout << "X" << i + 1 << " = " << unknowns[i] << "\n";
		}
	}

	void lineArithmetic(int lineIndex1, int columnIndex) {
		if (!mtrx[columnIndex][columnIndex])
			throw "Divide by zero";

		double coefficient = mtrx[lineIndex1][columnIndex] / mtrx[columnIndex][columnIndex];

		std::cout << "(" << lineIndex1 + 1 << ") ";
		std::cout.setf(std::ios::showpos);
		std::cout << coefficient;
		std::cout.unsetf(std::ios::showpos);
		std::cout << "(" << columnIndex + 1 << ")\n";

		for (int i = 0; i < W; i++) {
			mtrx[lineIndex1][i] -= (coefficient * mtrx[columnIndex][i]);
		}
	}

	void lineNulling() {
		for (int i = 0; i < W - 2; i++) {
			int j = i + 1;
			for (j; j < H; j++) {
				lineArithmetic(j, i);
			}
			std::cout << '\n';
			printMatrix();
		}
	}
};