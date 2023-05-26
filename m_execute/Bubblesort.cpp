#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

void sequentialBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                #pragma omp critical
                {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // Measure the performance of sequential bubble sort
    double startSeq = omp_get_wtime();
    sequentialBubbleSort(arr);
    double endSeq = omp_get_wtime();
    double seqDuration = endSeq - startSeq;

    // Measure the performance of parallel bubble sort
    double startParallel = omp_get_wtime();
    parallelBubbleSort(arr);
    double endParallel = omp_get_wtime();
    double parallelDuration = endParallel - startParallel;

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Sequential Bubble Sort Time: " << seqDuration << " seconds" << std::endl;
    std::cout << "Parallel Bubble Sort Time: " << parallelDuration << " seconds" << std::endl;

    return 0;
}
