#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[middle + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void sequentialMergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        sequentialMergeSort(arr, left, middle);
        sequentialMergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void parallelMergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, middle);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, middle + 1, right);
            }
        }
        merge(arr, left, middle, right);
    }
}

int main() {
    // Read input from the user
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::vector<int> data(size);
    std::cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; i++) {
        std::cin >> data[i];
    }

    // Measure the performance of sequential merge sort
    double startTime = omp_get_wtime();
    sequentialMergeSort(data, 0, size - 1);
    double endTime = omp_get_wtime();
    double sequentialTime = endTime - startTime;

    // Generate a copy of the input data for parallel merge sort
    std::vector<int> dataParallel(data);

    // Measure the performance of parallel merge sort
    startTime = omp_get_wtime();
    parallelMergeSort(dataParallel, 0, size - 1);
    endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;

    // Output the sorted array
    std::cout << "Sequential Merge Sort Result: ";
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Parallel Merge Sort Result: ";
    for (int i = 0; i < size; i++) {
        std::cout << dataParallel[i] << " ";
    }
    std::cout << std::endl;

    // Output the performance results
    std::cout << "Sequential Merge Sort Time: " << sequentialTime << " seconds" << std::endl;
    std::cout << "Parallel Merge Sort Time: " << parallelTime << " seconds" << std::endl;

    return 0;
}

