#include <iostream>
#include <cmath>
using namespace std;

float calc_variance(float val[]) {
	float sum = 0.0, mean, variance = 0.0;
	int i;
	for (i = 0; i < 5; ++i)
		sum += val[i];
	mean = sum / 5;
	for (i = 0; i < 5; ++i)
		variance += pow(val[i] - mean, 2);
	variance = variance / 5;
	return variance;
}

float calc_deviation(float variance) {
	float stdDeviation;
	stdDeviation = sqrt(variance);
	return stdDeviation;
}

int main() {
	float val[5] = { 12.5, 7.0, 10.0, 7.8, 15.5 };
	
	float variance, stdDeviation;
	variance = calc_variance(val);
	stdDeviation = calc_deviation(variance);
	cout << "The variance of these data values is " << variance << endl;
	cout << "The standard deviation of these data values is " << stdDeviation << endl;
	

}