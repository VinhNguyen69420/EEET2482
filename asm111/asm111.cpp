#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <map>

using namespace std;

// QUICK SORT ( CITE ??? )
// A utility function to swap two elements
void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot */
int partition (float arr[], int low, int high) {
	float pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
 * arr[] --> Array to be sorted,
 * low --> Starting index,
 * high --> Ending index
 */
void quickSort(float arr[], int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
// END

void copy_array(float src[], float des[], int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        des[i] = src[i];
    }
}

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

void read_file_to_arrays(string filename, float arr_x[], float arr_y[]) {
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
        arr_x[arr_index] = stof(line.substr(0, delim_pos));
        arr_y[arr_index] = stof(line.substr(delim_pos + 1));

        arr_index++;
    }

    myfile.close();
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
    int count = 0, temp_count = 0;
    float value = arr[0], temp_val = arr[0];
    bool is_last = false;

    for (int i = 0; i < arr_size; i++) {
        is_last = i == arr_size - 1;
        // array is sorted, check condition every time the value change or is the last element
        if (temp_val != arr[i] || is_last) {
            // count is incremented at the end of the loop, add an extra for last loop
            if (is_last) {
                temp_count++;
            }
            if (temp_count > count) {
                count = temp_count;
                value = temp_val;
            }
            temp_val = arr[i];
            temp_count = 0;
        }

        temp_count++;
    }
    
    return value;
}

float get_third_quartile(float arr[], int arr_size) {
    const float THIRD_QUARTILE = 0.75;
    const float QUARTERS = 4;
    float pos = (float) ((arr_size + 1) * THIRD_QUARTILE) - 1;

    int first_pos = floor(pos);
    int second_pos = ceil(pos);
    return (arr[first_pos] + arr[second_pos]) / 2;
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
        sum += (arr1[i] - mean1) * (arr2[i] - mean2);
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
    float mean = get_mean(arr, arr_size);
    for (int i = 0; i < arr_size; i++)
        sum = sum + abs(arr[i] - mean);
    return sum / arr_size;
}
float get_skewness(float x[], int n, float variance) {
    float sum = 0;
    float mean = get_mean(x, n);
    float dev = calc_deviation(variance);
    for (int i = 0; i < n; i++) {
        sum += pow(((x[i] - mean)/dev), 3);
    }
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


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Please provide a file name." << endl;
        return 0;
    }

    // read from file and extract to arrays
    string filename = argv[1];

    // test file
    ifstream myfile;
    myfile.open(filename);
    if (!myfile) {
        cerr << "File not found." << endl;
        return 0;
    }

    // remove the first header line from total lines
    int arr_size = get_file_lines(filename) - 1;

    // create static arrays
    float arr_x[50000], arr_y[50000], arr_x_sorted[50000], arr_y_sorted[50000];

    read_file_to_arrays(filename, arr_x, arr_y);

    copy_array(arr_x, arr_x_sorted, arr_size);
    copy_array(arr_y, arr_y_sorted, arr_size);

    quickSort(arr_x_sorted, 0, arr_size - 1);
    quickSort(arr_y_sorted, 0, arr_size - 1);
    // end read file

    // calculating
    // q1
    //float median_x = get_median(arr_x, arr_size);
    //float median_y = get_median(arr_y, arr_size);
    // q2
    float mode_x = get_mode(arr_x_sorted, arr_size);
    float mode_y = get_mode(arr_y_sorted, arr_size);
    // q3
    float variance_x = calc_variance(arr_x, arr_size);
    float variance_y = calc_variance(arr_y, arr_size);
    float std_deviation_x = calc_deviation(variance_x);
    float std_deviation_y = calc_deviation(variance_y);
    // q4
    float mad_x = calc_mad(arr_x, arr_size);
    float mad_y = calc_mad(arr_y, arr_size);
    // q5
    float third_quartile_x = get_third_quartile(arr_x_sorted, arr_size);
    float third_quartile_y = get_third_quartile(arr_y_sorted, arr_size);
    // q6
    float skewness_x = get_skewness(arr_x, arr_size, variance_x);
    float skewness_y = get_skewness(arr_y, arr_size, variance_y);
    // q7
    float kurtosis_x = get_kurtosis(arr_x, arr_size);
    float kurtosis_y = get_kurtosis(arr_y, arr_size);
    // q8
    float covariance = get_covariance(arr_x, arr_y, arr_size);
    // q9
    float correlation_coefficient = get_correlation_coefficient(arr_x, arr_y, arr_size);
    // q10
    
    // print
    cout << "mode_x = " << mode_x << " - " << "mode_y = " << mode_y << endl;
    cout << "var_x = " << variance_x << " - " << "var_y = " << variance_y << endl;
    cout << "stdev_x = " << std_deviation_x << " - " << "stdev_y = " << std_deviation_y << endl;
    cout << "mad_x = " << mad_x << " - " << "mad_y = " << mad_y << endl;
    cout << "q3_x = " << third_quartile_x << " - " << "q3_y = " << third_quartile_y << endl;
    cout << "skew_x = " << skewness_x << " - " << "skew_y = " << skewness_y << endl;
    cout << "kurt_x = " << kurtosis_x << " - " << "kurt_y = " << kurtosis_y << endl;
    cout << "cov(x_y) = " << covariance << endl;
    cout << "r(x_y) = " << correlation_coefficient << endl;
    get_linear_progression(arr_x, arr_y, arr_size, arr_size, variance_x, variance_y, correlation_coefficient);

    team_detail();

    return 0;
}
