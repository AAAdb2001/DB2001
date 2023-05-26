#include <iostream>
#include <vector>
#include <omp.h>

int parallelMin(const std::vector<int>& data) {
    int minVal = data[0];
    #pragma omp parallel for reduction(min: minVal)
    for (int i = 1; i < data.size(); i++) {
        if (data[i] < minVal) {
            minVal = data[i];
        }
    }
    return minVal;
}

int parallelMax(const std::vector<int>& data) {
    int maxVal = data[0];
    #pragma omp parallel for reduction(max: maxVal)
    for (int i = 1; i < data.size(); i++) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}

int parallelSum(const std::vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum;
}

double parallelAverage(const std::vector<int>& data) {
    int sum = parallelSum(data);
    return static_cast<double>(sum) / data.size();
}

int main() {
    // Read input from the user
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> data(n);
    std::cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> data[i];
    }

    // Perform parallel reduction operations
    int minVal = parallelMin(data);
    int maxVal = parallelMax(data);
    int sum = parallelSum(data);
    double average = parallelAverage(data);

    // Output the results
    std::cout << "Min: " << minVal << std::endl;
    std::cout << "Max: " << maxVal << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;

    return 0;
}
