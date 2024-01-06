#include "merge_sort.h"
#include "quick_sort.h"
#include "insertion_sort.h"
#include "heap_sort.h"

#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <algorithm>

constexpr int bigStep = 100;
constexpr int smallStep = 1;
constexpr int maxSize_Big = 10000;
constexpr int maxSize_Small = 100;
constexpr int iterations = 100;

template <typename T>
int measureTime(std::vector<T>& arr, void algorithm(std::vector<T>&)) {
    std::vector<T> arr_copy;
    arr_copy.resize(arr.size());
    std::copy(arr.begin(), arr.end(), arr_copy.begin());

    auto start = std::chrono::steady_clock::now();
    algorithm(arr_copy);
    auto end = std::chrono::steady_clock::now();

    arr_copy.clear();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename T>
void hybrid_sort(std::vector<T>& arr, const std::vector<std::vector<int>>& times, const std::vector<int>& fastestAlgorithms) {
    // Add base case for arrays of size 0 or 1
    if (arr.size() <= 1) return;

    int size = arr.size();
    int index = std::lower_bound(times.begin(), times.end(), size, [](const auto& row, const auto& value) { return row[0] < value; }) - times.begin();

    switch (fastestAlgorithms[index]) {
    case 0:
        merge_sort(arr);
       // cout << "Merge " << endl;
        break;
    case 1:
        quick_sort(arr);
        //cout << "Quick " << endl;
        break;
    case 2:
        insertionSort(arr);
        //cout << "insertion Sort " << endl;
        break;
    case 3:
        heap_sort(arr);
        //cout << "heap " << endl;
        break;
    }
}


int main() {
    static std::vector<std::vector<int>> times;
    std::vector<int> fastestAlgorithms;

    // Measure the performance of the sorting algorithms on small arrays
    for (int len = smallStep; len < maxSize_Small + 1; len++) {
        std::vector<int> row;
        row.resize(4);

        for (int t = 0; t < iterations; t++) {
            std::random_device rd2;
            std::mt19937 gen(rd2());
            std::uniform_int_distribution<int> dist(-len, len);

            std::vector<int> arr;
            arr.resize(len);

            for (int index = 0; index < len; index++) {
                arr[index] = dist(gen);
            }

            row[0] += measureTime(arr, merge_sort);
            row[1] += measureTime(arr, quick_sort);
            row[2] += measureTime(arr, insertionSort);
            row[3] += measureTime(arr, heap_sort);
        }

        for (auto& time : row) {
            time /= iterations;
        }

        times.push_back(row);
    }

    // Measure the performance of the sorting algorithms on large arrays
    for (int len = bigStep; len < maxSize_Big + 1; len += bigStep) {
        std::vector<int> row;
        row.resize(4);

        for (int t = 0; t < iterations; t++) {
            std::random_device rd2;
            std::mt19937 gen(rd2());
            std::uniform_int_distribution<int> dist(-len, len);

            std::vector<int> arr;
            arr.resize(len);

            for (int index = 0; index < len; index++) {
                arr[index] = dist(gen);
            }

            row[0] += measureTime(arr, merge_sort);
            row[1] += measureTime(arr, quick_sort);
            row[2] += measureTime(arr, insertionSort);
            row[3] += measureTime(arr, heap_sort);
        }

        for (auto& time : row) {
            time /= iterations;
        }

        times.push_back(row);
    }

    std::ofstream random("RESULT.txt");

    for (int len = bigStep; len < maxSize_Big + 1; len += bigStep) {
        long long merge_Random = 0;
        long long quick_Random = 0;
        long long insertion_Random = 0;
        long long heap_Random = 0;

        for (int t = 0; t < iterations; t++) {
            std::random_device rd2;
            std::mt19937 gen(rd2());
            std::uniform_int_distribution<int> dist(-len, len);

            std::vector<int> arr;
            arr.resize(len);

            for (int index = 0; index < len; index++) {
                arr[index] = dist(gen);
            }

            merge_Random += measureTime(arr, merge_sort);
            quick_Random += measureTime(arr, quick_sort);
            insertion_Random += measureTime(arr, insertionSort);
            heap_Random += measureTime(arr, heap_sort);


        }

        merge_Random /= iterations;
        quick_Random /= iterations;
        insertion_Random /= iterations;
        heap_Random /= iterations;

        random << len << " " << merge_Random << " " << quick_Random << " " << insertion_Random << " " << heap_Random << std::endl;

        std::cout << len << " " << merge_Random << " " << quick_Random << " " << insertion_Random << " " << heap_Random << std::endl;

    }

    random.close();

    // Find the fastest sorting algorithm for each array size
    fastestAlgorithms.resize(times.size());

    for (int i = 0; i < times.size(); i++) {
        fastestAlgorithms[i] = std::min_element(times[i].begin(), times[i].end()) - times[i].begin();
    }

    // Test the hybrid sorting algorithm
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, maxSize_Big);

    std::vector<int> test_arr;
    test_arr.resize(maxSize_Big);

    for (int i = 0; i < maxSize_Big; i++) {
        test_arr[i] = dist(gen);
        //cout << dist(gen);
    }

    auto start = std::chrono::steady_clock::now();
    hybrid_sort(test_arr, times, fastestAlgorithms);
    auto end = std::chrono::steady_clock::now();


    cout << "Hybrid sorting algorithm time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    return 0;


}