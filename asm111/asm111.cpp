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

void merge(double* array, int l, int m, int r) {
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

void merge_sort(double* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        merge_sort(array, l, m);
        merge_sort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
// MERGE SORT END

bool is_double(string n) {
    if (n.empty()) {
        return false;
    }
    bool decimal = false;
    for (int i = 0; i < n.length(); i++) {
        if (n[0] == '+' || n[0] == '-') {  // check for positive and negative
            continue;
        }
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

void copy_array(double src[], double des[], int start, int end) {
    int index = 0;
    for (int i = start; i <= end; i++) {
        des[index] = src[i]; // copy the array
        index++;
    }
}

int get_file_lines(string filename) {
    ifstream myfile;
    myfile.open(filename); // Open the file

    string line, val1, val2;
    int count = 0;
    int delim_pos;
    char delimeter = ',';

    getline(myfile, line);

    while (getline(myfile, line)) {
        // get two substrings separated by delimeter
        delim_pos = line.find(delimeter);
        val1 = line.substr(0, delim_pos);
        val2 = line.substr(delim_pos + 1);

        // skip corrupted data
        if (!is_double(val1) || !is_double(val2)) {
            continue;
        }

        count++;
    }

    myfile.close();

    return count; // Remove the header
}

void read_file_to_arrays(string filename, double arr_x[], double arr_y[]) {
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
        if (!is_double(val1) || !is_double(val2)) {
            continue;
        }

        arr_x[arr_index] = stof(val1);
        arr_y[arr_index] = stof(val2);

        arr_index++;
    }

    myfile.close();
}

double calc_mean(double arr[], int arr_size) {
    double sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i]; // Calculate the total sum
    }
    return sum / arr_size;
}

// FUNCTION 1: CALCULATE MEDIAN
double calc_median(double arr[], int arr_size) {
    double pos = (arr_size + 1.0) / 2.0 - 1;
    int first_pos = floor(pos);
    int second_pos = ceil(pos);

    return (arr[first_pos] + arr[second_pos]) / 2.0;
}

// FUCNTION 2: CALCULATE MODE
string calc_mode(double arr[], int arr_size) {
    double number = arr[0];
    int mode = number;
    int count = 1;
    int count_mode = 1;

    for (int i = 1; i < arr_size; i++)
    {
        if (arr[i] == number)
        { // Count occurrences of the current number
            ++count;
        }
        else
        { // Now this is a different number
            if (count > count_mode)
            {
                count_mode = count; // Mode is the biggest ocurrences
                mode = number;
            }
            count = 1; // Reset count for the new number
            number = arr[i];
        }
    }

    // check for last value
    if (count > count_mode)
    {
        count_mode = count;
        mode = number;
    }

    if (count_mode == 1) { // Only occurs once
        return "None";
    }
    else {
        return to_string(mode);
    }
    
}

// FUCNTION 3: CALCULATE VARIANCE & STANDARD DEVIATION
double calc_variance(double val[], int size, double& mean) {
    double variance = 0.0F;
    int i;
    for (i = 0; i < size; ++i)
        variance += pow(val[i] - mean, 2); // Calculate the value to the power of 2
    variance = variance / (size - 1);
    return variance;
}

double calc_deviation(double variance) {
    double std_deviation;
    std_deviation = sqrt(variance); // Calculate the squart root of the variance
    return std_deviation;
}

// FUCNTION 4: CALCULATE MEAN ABSOLUTE DEVIATION
double calc_mad(double arr[], int arr_size, double& mean) {
    double sum = 0;
    for (int i = 0; i < arr_size; i++)
        sum = sum + abs(arr[i] - mean); // Calculate the absolute value
    return sum / arr_size;
}

// FUCNTION 5: CALCULATE THIRD QUARTILE
double calc_third_quartile(double arr[], int arr_size) {
    // start position of the upper half
    int start_upper = (arr_size + 1) / 2;

    // size for the upper half array
    int temp_size = arr_size - start_upper;

    double pos = (temp_size + 1.0) / 2.0 - 1;

    int first_pos = start_upper + floor(pos);
    int second_pos = start_upper + ceil(pos);

    double result = (arr[first_pos] + arr[second_pos]) / 2;

    return result;
}

// FUCNTION 6: CALCULATE SKEWNESS
double calc_skewness(double arr[], int arr_size, double& std_deviation, double& mean) {
    double sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += pow(((arr[i] - mean) / std_deviation), 3);
    }
    double skewness = sum / arr_size;
    return skewness;
}

// FUCNTION 7: CALCULATE KURTOSIS
double calc_kurtosis(double arr[], int arr_size, double& mean, double& std_deviation) {
    double sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += pow(((arr[i] - mean) / std_deviation), 4);
    }
    double kurtosis = (sum / arr_size) - 3;
    return kurtosis;
}

// FUCNTION 8: CALCULATE COVARIANCE
double calc_covariance(double arr_x[], double arr_y[], int arr_size, double& mean_x, double& mean_y) {
    double sum = 0;

    for (int i = 0; i < arr_size; i++) {
        sum += (arr_x[i] - mean_x) * (arr_y[i] - mean_y);
    }

    return sum / (arr_size - 1);
}

// FUCNTION 9: CALCULATE PEARSON CORRELATION COEFFICIENT
double calc_correlation_coefficient(double arr_x[], double arr_y[], int arr_size) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_sqrx = 0, sum_sqry = 0;

    for (int i = 0; i < arr_size; i++) {
        sum_x += arr_x[i];
        sum_y += arr_y[i];
        sum_xy += arr_x[i] * arr_y[i];
        sum_sqrx += arr_x[i] * arr_x[i];
        sum_sqry += arr_y[i] * arr_y[i];
    }

    // correlation coefficient formula
    double result = (arr_size * sum_xy - sum_x * sum_y) /
        sqrt((arr_size * sum_sqrx - sum_x * sum_x) * (arr_size * sum_sqry - sum_y * sum_y));

    return result;
}

// FUCNTION 10: CALCULATE LINEAR REGRESSION
void calc_linear_regression(double& mean_x, double& mean_y, double& variance_x, double& variance_y, double& stdev_x, double& stdev_y, double& correlation) {

    double a = correlation * stdev_y / stdev_x;
    double b = mean_y - (a * mean_x);
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
    double* arr_x = new double[arr_size];
    double* arr_y = new double[arr_size];
    double* arr_x_sorted = new double[arr_size];
    double* arr_y_sorted = new double[arr_size];

    // Parse CSV into arrays
    read_file_to_arrays(filename, arr_x, arr_y);

    // Copy to another arrays
    copy_array(arr_x, arr_x_sorted, 0, arr_size - 1);
    copy_array(arr_y, arr_y_sorted, 0, arr_size - 1);

    // Sort the new copied arrays
    merge_sort(arr_x_sorted, 0, arr_size - 1);
    merge_sort(arr_y_sorted, 0, arr_size - 1);
    // End read file
    

    // MAIN FUNCTIONS
    // Calculate the mean
    double mean_x = calc_mean(arr_x, arr_size);
    double mean_y = calc_mean(arr_y, arr_size);

    // Question 1: Calculate the median
    double median_x = calc_median(arr_x_sorted, arr_size);
    double median_y = calc_median(arr_y_sorted, arr_size);

    // Question 2: Calculate the mode
    string mode_x = calc_mode(arr_x_sorted, arr_size);
    string mode_y = calc_mode(arr_y_sorted, arr_size);

    // Question 3: Calculate the variance & standard deviation
    double variance_x = calc_variance(arr_x, arr_size, mean_x);
    double variance_y = calc_variance(arr_y, arr_size, mean_y);
    double std_deviation_x = calc_deviation(variance_x);
    double std_deviation_y = calc_deviation(variance_y);

    // Question 4: Calculate the mean absolute deviation
    double mad_x = calc_mad(arr_x, arr_size, mean_x);
    double mad_y = calc_mad(arr_y, arr_size, mean_y);

    // Question 5: Calculate the third quartile
    double third_quartile_x = calc_third_quartile(arr_x_sorted, arr_size);
    double third_quartile_y = calc_third_quartile(arr_y_sorted, arr_size);

    // Question 6: Calculate the skewness
    double skewness_x = calc_skewness(arr_x, arr_size, std_deviation_x, mean_x);
    double skewness_y = calc_skewness(arr_y, arr_size, std_deviation_y, mean_y);

    // Question 7: Calculate the kurtosis
    double kurtosis_x = calc_kurtosis(arr_x, arr_size, mean_x, std_deviation_x);
    double kurtosis_y = calc_kurtosis(arr_y, arr_size, mean_y, std_deviation_y);

    // Question 8: Calculate the covariance
    double covariance = calc_covariance(arr_x, arr_y, arr_size, mean_x, mean_y);

    // Question 9: Calculate the correlation coefficient
    double correlation_coefficient = calc_correlation_coefficient(arr_x, arr_y, arr_size);

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
    calc_linear_regression(mean_x, mean_y, variance_x, variance_y, std_deviation_x, std_deviation_y, correlation_coefficient);
    team_detail(); // Print team detail

    //Remove dynamic arrays
    delete[] arr_x;
    delete[] arr_y;
    delete[] arr_x_sorted;
    delete[] arr_y_sorted;

    return 0;
}