#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <map>

using namespace std;

int get_file_lines(string filename) {
    ifstream myfile;
    myfile.open(filename);

    int count = 0;
    string line;

    while (getline(myfile, line)) {
        count++;
    }

    myfile.close();

    return count;
}

float get_mean(float arr[], int arr_size) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i];
    }
    return sum / arr_size;
}

float calc_variance(float val[], int size) {
    float sum = 0.0, mean, variance = 0.0;
    int i;
    for (i = 0; i < size; ++i)
        sum += val[i];
    mean = get_mean(val, size);
    for (i = 0; i < size; ++i)
        variance += pow(val[i] - mean, 2);
    variance = variance / size;
    return variance;
}

float calc_deviation(float variance) {
    float stdDeviation;
    stdDeviation = sqrt(variance);
    return stdDeviation;
}

float get_mode(float arr[], int arr_size) {
    int count = 0;
    float value = 0;

    for (int i = 0; i < arr_size; i++) {
        int tempcount = 0;
        for (int j = 0; j < arr_size; j++) {
            if (arr[i] == arr[j]) {
                tempcount++;
            }
        }
        if (tempcount > count) {

            count = tempcount;
            value = arr[i];
        }
        else if (tempcount == count && arr[i] < value){

            value = arr[i];

        }

    }
    return value;
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

float get_kurtosis(float arr[], int arr_size) {
    float mean = get_mean(arr, arr_size);
    float variance = calc_variance(arr, arr_size);
    float std_deviation = calc_deviation(variance);

    float sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += pow((arr[i] - mean) / std_deviation, 4);
    }

    return (sum / arr_size) - 3;
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
float get_skewness(float x[], int n, float variance) {
    float sum = 0;
    float mean = get_mean(x, n);
    float dev = calc_deviation(variance);
    for (int i = 0; i < n; i++) {
        sum += pow(((x[i] - mean)/dev), 3);
    }
    cout << dev << endl;
    float skewness = sum / n;
    return skewness;
}
void get_linear_progression(float arr_x[], float arr_y[], int size, int size2, float variance, float variance2, float correlation) {
    float mean_x = get_mean(arr_x, size);
    float stdev_x = calc_deviation(variance);
    float mean_y = get_mean(arr_y, size2);
    float stdev_y = calc_deviation(variance2);
    float a = correlation * stdev_y / stdev_x;
    float b = mean_y - (a * mean_x);
    cout << "y = " << a << "x + " << b << endl;
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
    // read from file and extract to arrays
    string filename = "data1.csv";

    // remove the first header line from total lines
    int arr_size = get_file_lines(filename) - 1;

    // create static arrays
    float arr1[arr_size];
    float arr2[arr_size];

    ifstream myfile;
    myfile.open(filename);

    string line;
    int arr_index = 0;
    char delimeter = ',';

    // skip first header line
    getline(myfile, line);

    while (getline(myfile, line)) {
        // get two substrings separated by delimeter
        int delim_pos = line.find(delimeter);
        arr1[arr_index] = stof(line.substr(0, delim_pos));
        arr2[arr_index] = stof(line.substr(delim_pos + 1));

        arr_index++;
    }

    myfile.close();
    // end read file

    // calculating
    float variance, variance2, stdDeviation, meanDeviation, quartile, quartile2, covariance, skewness, skewness2, correlation;
    variance = calc_variance(arr1, arr_size);
    variance2 = calc_variance(arr2, arr_size);
    stdDeviation = calc_deviation(variance);
    meanDeviation = calc_mad(arr1, arr_size);
    covariance = get_covariance(arr1, arr2, arr_size);
    // calculate third quartile
    quartile = get_third_quartile(arr1, arr_size);
    quartile2 = get_third_quartile(arr2, arr_size);
    skewness = get_skewness(arr1, arr_size, variance);
    skewness2 = get_skewness(arr2, arr_size, variance);
    correlation = get_correlation_coefficient(arr1, arr2, arr_size);

    cout << "The third quartile of array 1 is: " << quartile << endl;
    cout << "The third quartile of array 2 is: " << quartile2 << endl;
    cout << "The variance of these data values is: " << variance << endl;
    cout << "The standard deviation of these data values is: " << stdDeviation << endl;
    cout << "The mean absolute deviation of these data values is: " << meanDeviation << endl;
    cout << "The coveriance of these data values is: " << covariance << endl;
    cout << "The mode of x is  " << get_mode(arr1, arr_size) <<endl;
    cout << "The mode of y is  " << get_mode(arr2, arr_size) << endl;
    cout << "skew_x : " << skewness << " skew y: " << skewness2 << endl;
    get_linear_progression(arr1, arr2, arr_size, arr_size, variance, variance2, correlation);

    team_detail();

    return 0;
}
