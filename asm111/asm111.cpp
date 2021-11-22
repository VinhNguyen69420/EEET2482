#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

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

float get_mean(float arr[], int arr_size) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i];
    }
    return sum / arr_size;
}

float get_third_quartile(float arr[], int arr_size) {
    const float THIRD_QUARTILE = 3;
    const float QUARTERS = 4;
    float pos = (float) ((arr_size + 1) * THIRD_QUARTILE / QUARTERS) - 1;

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

float get_covariance(float arr1[], float arr2[], int arr_size) {
    float mean1 = get_mean(arr1, arr_size);
    float mean2 = get_mean(arr2, arr_size);

    float sum = 0;

    for (int i = 0; i < arr_size; i++) {
        float temp = (arr1[i] - mean1) * (arr2[i] - mean2);
        sum += temp;
    }

    return sum / (arr_size - 1);
}

float get_correlation_coefficient(float arr_x[], float arr_y[], int arr_size) {
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_sqrx = 0, sum_sqry = 0;

    for (int i = 0; i < arr_size; i++) {
        sum_x += arr_x[i];
        sum_y += arr_y[i];
        sum_xy += arr_x[i] * arr_y[i];
        sum_sqrx += arr_x[i] * arr_x[i];
        sum_sqry += arr_y[i] * arr_y[i];
    }

    // correlation coefficient formula
    float result = (arr_size * sum_xy - sum_x * sum_y) /
            sqrt((arr_size * sum_sqrx - sum_x * sum_x) * (arr_size * sum_sqry - sum_y * sum_y));

    return result;
}

float calc_mad(float arr[], int arr_size) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++)
        sum = sum + abs(arr[i] - get_mean(arr, arr_size));
    return sum / arr_size;
}

void team_detail() {
    cout << "" << endl;
    cout << "ASIGNMENT 1 - GROUP 25" << endl;
    cout << "s3825455, s3825455@rmit.edu.vn, Thien An, Nguyen Hoang" << endl;
    cout << "s3893635, s3893635@rmit.edu.vn, Minh Quan, Che" << endl;
    cout << "s3875336, s3875336@rmit.edu.vn, Nam Vinh, Nguyen" << endl;
    cout << "s3817907, s3817907@rmit.edu.vn, Anh Tuan, Nguyen" << endl;
}


int main() {
    float variance, stdDeviation, meanDeviation, quartile, quartile2, covariance;
	float val[5] = { 12.5, 7.0, 10.0, 7.8, 15.5 };
    float val2[5] = { 16.9, 8.0, 11.23, 6.9, 1.2 };
    int size = sizeof(val) / sizeof(val[0]);
	variance = calc_variance(val);
	stdDeviation = calc_deviation(variance);
    meanDeviation = calc_mad(val, size);
    covariance = get_covariance(val, val2, size);
    // calculate third quartile
    quartile = get_third_quartile(val, size);
    quartile2 = get_third_quartile(val2, size);
    
    cout << "The third quartile of array 1 is: " << quartile << endl;
    cout << "The third quartile of array 2 is: " << quartile2 << endl;
	cout << "The variance of these data values is: " << variance << endl;
	cout << "The standard deviation of these data values is: " << stdDeviation << endl;
    cout << "The mean absolute deviation of these data values is: " << meanDeviation << endl;
    cout << "The coveriance of these data values is: " << covariance << endl;


 
    team_detail();

}
