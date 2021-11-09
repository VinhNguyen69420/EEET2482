#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float val[5] = { 12.5, 7.0, 10.0, 7.8, 15.5 };
	float sum = 0.0, mean, variance = 0.0, stdDeviation;
	int i;
	for (i = 0; i < 5; ++i)
		sum += val[i];
	mean = sum / 5;
	for (i = 0; i < 5; ++i)
		variance += pow(val[i] - mean, 2);
	variance = variance / 5;
	stdDeviation = sqrt(variance);
	cout << "The data values are: ";
	for (i = 0; i < 5; ++i)
		cout << val[i] << " ";
	cout << endl;
	cout << "The standard deviation of these data values is " << stdDeviation << endl;
	cout << "The variance of these data values is " << variance << endl;

}