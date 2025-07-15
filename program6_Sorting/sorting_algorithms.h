#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector> // Using vector for dynamic array behavior, more C++ idiomatic

/**
 * @brief Generates a random array of integers.
 * @param arr The vector to populate with random numbers.
 * @param size The desired size of the array.
 */
void generateRandomArray(std::vector<int>& arr, int size);

/**
 * @brief Copies the contents of one vector to another.
 * @param source The source vector.
 * @param destination The destination vector.
 */
void copyArray(const std::vector<int>& source, std::vector<int>& destination);

/**
 * @brief Prints the elements of an array.
 * @param arr The array to print.
 * @note This function is primarily for debugging smaller arrays.
 */
void printArray(const std::vector<int>& arr);

// Sorting Algorithms

/**
 * @brief Implements the Selection Sort algorithm.
 * @param arr The array to be sorted.
 */
void selectionSort(std::vector<int>& arr);

/**
 * @brief Implements the Insertion Sort algorithm.
 * @param arr The array to be sorted.
 */
void insertionSort(std::vector<int>& arr);

/**
 * @brief Implements the Merge Sort algorithm.
 * @param arr The array to be sorted.
 * @param l The leftmost index of the subarray.
 * @param r The rightmost index of the subarray.
 */
void mergeSort(std::vector<int>& arr, int l, int r);

/**
 * @brief Implements the Quick Sort algorithm.
 * @param arr The array to be sorted.
 * @param low The lowest index of the subarray.
 * @param high The highest index of the subarray.
 */
void quickSort(std::vector<int>& arr, int low, int high);

/**
 * @brief Implements the Bubble Sort algorithm.
 * @param arr The array to be sorted.
 */
void bubbleSort(std::vector<int>& arr);

// Helper functions for sorting algorithms

/**
 * @brief Merges two sorted subarrays into one sorted array.
 * Helper function for Merge Sort.
 * @param arr The array containing the subarrays.
 * @param l The starting index of the first subarray.
 * @param m The middle index (end of first, start of second - 1).
 * @param r The ending index of the second subarray.
 */
void merge(std::vector<int>& arr, int l, int m, int r);

/**
 * @brief Partitions the array around a pivot element.
 * Helper function for Quick Sort.
 * @param arr The array to be partitioned.
 * @param low The lowest index of the subarray.
 * @param high The highest index of the subarray (where the pivot is initially).
 * @return The partitioning index.
 */
int partition(std::vector<int>& arr, int low, int high);

/**
 * @brief Swaps two integer values.
 * @param a Reference to the first integer.
 * @param b Reference to the second integer.
 */
void swap(int& a, int& b);

#endif // SORTING_ALGORITHMS_H#pragma once
