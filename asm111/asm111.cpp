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

double get_mean(double arr[], int arr_size) {
    double sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i];
    }
    return sum / arr_size;
}

double get_quartile(double arr[], int arr_size, int quartile) {
    double pos = (double) ((arr_size + 1) * quartile / 4) - 1;

    // if position is not an int, take the mean of two numbers
    if (pos != (int) pos) {
        int first_pos = floor(pos);
        int second_pos = ceil(pos);
        return (arr[first_pos] + arr[second_pos]) / 2;
    }

    // else return the number at that position
    int int_pos = (int) pos;
    return arr[int_pos];
}

double get_covariance(double arr1[], double arr2[], int arr_size) {
    double mean1 = get_mean(arr1, arr_size);
    double mean2 = get_mean(arr2, arr_size);

    double sum = 0;

    for (int i = 0; i < arr_size; i++) {
        double temp = (arr1[i] - mean1) * (arr2[i] - mean2);
        sum += temp;
    }

    return sum / (arr_size - 1);
}

int main() {
	float val[5] = { 12.5, 7.0, 10.0, 7.8, 15.5 };
	
	float variance, stdDeviation;
	variance = calc_variance(val);
	stdDeviation = calc_deviation(variance);
	cout << "The variance of these data values is " << variance << endl;
	cout << "The standard deviation of these data values is " << stdDeviation << endl;
	

}
