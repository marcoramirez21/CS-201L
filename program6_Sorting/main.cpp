#include "sorting_algorithms.h" // Include our custom header
#include <iostream>
#include <vector>
#include <chrono>   // For time measurement
#include <string>   // For string manipulation (e.g., algorithm names)
#include <numeric>  // For std::iota if needed for sequential arrays (not used directly in this random array case)

// Define array size. Can be changed for experimentation.
// Recommended sizes: 10,000, 50,000, 100,000
const int ARRAY_SIZE = 50000;

int main() {
    std::cout << "Starting sorting algorithm performance analysis with ARRAY_SIZE = " << ARRAY_SIZE << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    // Primary unsorted array
    std::vector<int> originalArray;
    generateRandomArray(originalArray, ARRAY_SIZE);

    // Temporary array for each sort
    std::vector<int> tempArray;

    // Using a lambda for easier time measurement and execution
    auto measureAndSort = [&](const std::string& algoName, void (*sortFunc)(std::vector<int>&)) {
        copyArray(originalArray, tempArray); // Get a fresh copy

        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(tempArray);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << algoName << " took: " << duration.count() << " seconds" << std::endl;

        // Optional: Verify if sorted (for debugging smaller arrays)
        // For large arrays, this is generally omitted for performance.
        /*
        bool isSorted = true;
        for (int i = 0; i < tempArray.size() - 1; ++i) {
            if (tempArray[i] > tempArray[i+1]) {
                isSorted = false;
                break;
            }
        }
        if (!isSorted) {
            std::cout << "WARNING: Array not sorted correctly by " << algoName << std::endl;
        }
        */
        };

    // Special handling for mergeSort and quickSort as they have different signatures
    auto measureAndSortRecursive = [&](const std::string& algoName, void (*sortFunc)(std::vector<int>&, int, int)) {
        copyArray(originalArray, tempArray); // Get a fresh copy

        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(tempArray, 0, tempArray.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << algoName << " took: " << duration.count() << " seconds" << std::endl;
        };


    // Execute and measure each sorting algorithm
    measureAndSort("Selection Sort", selectionSort);
    measureAndSort("Insertion Sort", insertionSort);
    measureAndSort("Bubble Sort", bubbleSort); // Bubble sort is often very slow for large arrays

    // For Merge Sort and Quick Sort, pass their respective helper lambdas
    measureAndSortRecursive("Merge Sort", mergeSort);
    measureAndSortRecursive("Quick Sort", quickSort);

    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "Analysis complete." << std::endl;

    return 0;
}