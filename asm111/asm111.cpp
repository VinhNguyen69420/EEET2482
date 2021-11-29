#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;


/*
    MERGE SORT
    [1]K. Chavan, "C++ Program to Implement Merge Sort", Tutorialspoint.com, 2021. [Online]. Available: https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort. [Accessed: 29- Nov- 2021].
*/
void swapping(int& a, int& b) { // swap the content of a and b
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void merge(float* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    // size of left and right sub-arrays
    nl = m - l + 1;
    nr = r - m;
    int* larr = new int[nl];
    int* rarr = new int[nr];
    // fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    // merge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }
        else {
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) { // extra element in left array
        array[k] = larr[i];
        i++;
        k++;
    }
    while (j < nr) { // extra element in right array
        array[k] = rarr[j];
        j++;
        k++;
    }
    delete[] larr;
    delete[] rarr;
}

void mergeSort(float* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
// MERGE SORT END

bool is_float(string n) {
    bool decimal = false;
    for (int i = 0; i < n.length(); i++) {
        if (n[i] == '.') {
            if (!decimal) {
                decimal = true;
            } else if (decimal || i == 1) {
                return false;
            }
        } else if (n[i] == '\n' || n[i] == '\r') {  // skip carriage return and new line character
            continue;
        } else if (n[i] < '0' || n[i] > '9') {
            return false;
        }
    }
    return true;
}

void copy_array(float src[], float des[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        des[i] = src[i]; // copy the array
    }
}

int get_file_lines(string filename) {
    ifstream myfile;
    myfile.open(filename); // Open the file

    string line, val1, val2;
    int count = 0;
    int delim_pos;
    char delimeter = ',';

    while (getline(myfile, line)) {
        // get two substrings separated by delimeter
        delim_pos = line.find(delimeter);
        val1 = line.substr(0, delim_pos);
        val2 = line.substr(delim_pos + 1);

        // skip corrupted data
        if (!is_float(val1) || !is_float(val2)) {
            continue;
        }

        count++;
    }

    myfile.close();

    return count - 1; // Remove the header
}

void read_file_to_arrays(string filename, float arr_x[], float arr_y[]) {
    ifstream myfile;
    myfile.open(filename);

    string line, val1, val2;
    int arr_index = 0;
    int delim_pos;
    char delimeter = ',';

    // skip first header line
    getline(myfile, line);

    while (getline(myfile, line)) {
        // get two substrings separated by delimeter
        delim_pos = line.find(delimeter);
        val1 = line.substr(0, delim_pos);
        val2 = line.substr(delim_pos + 1);

        // skip corrupted data
        if (!is_float(val1) || !is_float(val2)) {
            continue;
        }

        arr_x[arr_index] = stof(val1);
        arr_y[arr_index] = stof(val2);

        arr_index++;
    }

    myfile.close();
}

float calc_mean(float arr[], int arr_size) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i]; // Calculate the total sum
    }
    return sum / arr_size;
}

// FUNCTION 1: CALCULATE MEDIAN
float calc_median(float arr[], int arr_size) {
    float pos = ((arr_size - 1.0) / 2.0);
    int first_pos = floor(pos);
    int second_pos = ceil(pos);

    return (arr[first_pos] + arr[second_pos]) / 2.0;
}

// FUCNTION 2: CALCULATE MODE
string calc_mode(float arr[], int arr_size) {
    float number = arr[0];
    int mode = number;
    int count = 1;
    int countMode = 1;

    for (int i = 1; i < arr_size; i++)
    {
        if (arr[i] == number)
        { // Count occurrences of the current number
            ++count;
        }
        else
        { // Now this is a different number
            if (count > countMode)
            {
                countMode = count; // Mode is the biggest ocurrences
                mode = number;
            }
            count = 1; // Reset count for the new number
            number = arr[i];
        }
    }

    // check for last value
    if (count > countMode)
    {
        countMode = count;
        mode = number;
    }

    if (countMode == 1) { // Only occurs once
        return "None";
    }
    else {
        return to_string(mode);
    }
    
}

// FUCNTION 3: CALCULATE VARIANCE & STANDARD DEVIATION
float calc_variance(float val[], int size, float& mean) {
    float variance = 0.0F;
    int i;
    for (i = 0; i < size; ++i)
        variance += pow(val[i] - mean, 2); // Calculate the value to the power of 2
    variance = variance / size;
    return variance;
}

float calc_deviation(float variance) {
    float stdDeviation;
    stdDeviation = sqrt(variance); // Calculate the squart root of the variance
    return stdDeviation;
}

// FUCNTION 4: CALCULATE MEAN ABSOLUTE DEVIATION
float calc_mad(float arr[], int arr_size, float& mean) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++)
        sum = sum + abs(arr[i] - mean); // Calculate the absolute value
    return sum / arr_size;
}

// FUCNTION 5: CALCULATE THIRD QUARTILE
float calc_third_quartile(float arr[], int arr_size) {
    const float QUANTILE = 0.75;
    float pos = arr_size * QUANTILE;

    int first_pos = floor(pos);
    int second_pos = ceil(pos);

    return (arr[first_pos] + arr[second_pos]) / 2.0;
}

// FUCNTION 6: CALCULATE SKEWNESS
float calc_skewness(float x[], int n, float& variance, float& mean) {
    float sum = 0;
    float dev = calc_deviation(variance);
    for (int i = 0; i < n; i++) {
        sum += pow(((x[i] - mean) / dev), 3);
    }
    float skewness = sum / n;
    return skewness;
}

// FUCNTION 7: CALCULATE KURTOSIS
float calc_kurtosis(float arr[], int arr_size, float& mean, float& variance, float& std_deviation) {
    float sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += pow((arr[i] - mean) / std_deviation, 4);
    }

    return (sum / arr_size) - 3;
}

// FUCNTION 8: CALCULATE COVARIANCE
float calc_covariance(float arr_x[], float arr_y[], int arr_size, float& mean_x, float& mean_y) {
    float sum = 0;

    for (int i = 0; i < arr_size; i++) {
        sum += (arr_x[i] - mean_x) * (arr_y[i] - mean_y);
    }

    return sum / (arr_size - 1);
}

// FUCNTION 9: CALCULATE PEARSON CORRELATION COEFFICIENT
float calc_correlation_coefficient(float arr_x[], float arr_y[], int arr_size) {
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

// FUCNTION 10: CALCULATE LINEAR REGRESSION
void calc_linear_regression(float arr_x[], float arr_y[], int size, float& mean_x, float& mean_y, float& variance_x, float& variance_y, float& stdev_x, float& stdev_y, float& correlation) {

    float a = correlation * stdev_y / stdev_x;
    float b = mean_y - (a * mean_x);
    cout << setprecision(4) << fixed; // Takes 4 decimal only
    cout << "y = " << a << "x + " << b << endl; // Print out the regression
}

void team_detail() {
    cout << "" << endl;
    cout << "ASIGNMENT 1 - GROUP 25" << endl;
    cout << "s3825455, s3825455@rmit.edu.vn, Thien An, Nguyen Hoang" << endl;
    cout << "s3893635, s3893635@rmit.edu.vn, Minh Quan, Che" << endl;
    cout << "s3875336, s3875336@rmit.edu.vn, Nam Vinh, Nguyen" << endl;
    cout << "s3817907, s3817907@rmit.edu.vn, Anh Tuan, Nguyen" << endl;
}

int main(int argc, char* argv[]) {
    // Check if user input is correct
    if (argc != 2) {
        cerr << "Please provide a file name." << endl;
        return 0;
    }

    // Read from file and extract to arrays
    string filename = argv[1];

    // Test file
    ifstream myfile;
    myfile.open(filename);
    if (!myfile) {
        cerr << "File not found." << endl;
        return 0;
    }
    myfile.close();

    // Count the total lines
    int arr_size = get_file_lines(filename);

    // Create dynamic arrays
    float* arr_x = new float[arr_size];
    float* arr_y = new float[arr_size];
    float* arr_x_sorted = new float[arr_size];
    float* arr_y_sorted = new float[arr_size];

    // Parse CSV into arrays
    read_file_to_arrays(filename, arr_x, arr_y);

    // Copy to another arrays
    copy_array(arr_x, arr_x_sorted, arr_size);
    copy_array(arr_y, arr_y_sorted, arr_size);

    // Sort the new copied arrays
    mergeSort(arr_x_sorted, 0, arr_size - 1);
    mergeSort(arr_y_sorted, 0, arr_size - 1);
    // End read file
    

    // MAIN FUNCTIONS
    // Calculate the mean
    float mean_x = calc_mean(arr_x, arr_size);
    float mean_y = calc_mean(arr_y, arr_size);

    // Question 1: Calculate the median
    float median_x = calc_median(arr_x_sorted, arr_size);
    float median_y = calc_median(arr_y_sorted, arr_size);

    // Question 2: Calculate the mode
    string mode_x = calc_mode(arr_x_sorted, arr_size);
    string mode_y = calc_mode(arr_y_sorted, arr_size);

    // Question 3: Calculate the variance & standard deviation
    float variance_x = calc_variance(arr_x, arr_size, mean_x);
    float variance_y = calc_variance(arr_y, arr_size, mean_y);
    float std_deviation_x = calc_deviation(variance_x);
    float std_deviation_y = calc_deviation(variance_y);

    // Question 4: Calculate the mean absolute deviation
    float mad_x = calc_mad(arr_x, arr_size, mean_x);
    float mad_y = calc_mad(arr_y, arr_size, mean_y);

    // Question 5: Calculate the third quartile
    float third_quartile_x = calc_third_quartile(arr_x_sorted, arr_size);
    float third_quartile_y = calc_third_quartile(arr_y_sorted, arr_size);

    // Question 6: Calculate the skewness
    float skewness_x = calc_skewness(arr_x, arr_size, variance_x, mean_x);
    float skewness_y = calc_skewness(arr_y, arr_size, variance_y, mean_y);

    // Question 7: Calculate the kurtosis
    float kurtosis_x = calc_kurtosis(arr_x, arr_size, mean_x, variance_x, std_deviation_x);
    float kurtosis_y = calc_kurtosis(arr_y, arr_size, mean_y, variance_y, std_deviation_y);

    // Question 8: Calculate the covariance
    float covariance = calc_covariance(arr_x, arr_y, arr_size, mean_x, mean_y);

    // Question 9: Calculate the correlation coefficient
    float correlation_coefficient = calc_correlation_coefficient(arr_x, arr_y, arr_size);

    // Print
    cout << setprecision(4) << fixed; // Takes 4 decimal only
    cout << "median_x = " << median_x << " - " << "median_y = " << median_y << endl;
    cout << "mode_x = " << mode_x << " - " << "mode_y = " << mode_y << endl;
    cout << "var_x = " << variance_x << " - " << "var_y = " << variance_y << endl;
    cout << "stdev_x = " << std_deviation_x << " - " << "stdev_y = " << std_deviation_y << endl;
    cout << "mad_x = " << mad_x << " - " << "mad_y = " << mad_y << endl;
    cout << "q3_x = " << third_quartile_x << " - " << "q3_y = " << third_quartile_y << endl;
    cout << "skew_x = " << skewness_x << " - " << "skew_y = " << skewness_y << endl;
    cout << "kurt_x = " << kurtosis_x << " - " << "kurt_y = " << kurtosis_y << endl;
    cout << "cov(x_y) = " << covariance << endl;
    cout << "r(x_y) = " << correlation_coefficient << endl;
    calc_linear_regression(arr_x, arr_y, arr_size, mean_x, mean_y, variance_x, variance_y, std_deviation_x, std_deviation_y, correlation_coefficient);
    team_detail(); // Print team detail

    //Remove dynamic arrays
    delete[] arr_x;
    delete[] arr_y;
    delete[] arr_x_sorted;
    delete[] arr_y_sorted;

    return 0;
}