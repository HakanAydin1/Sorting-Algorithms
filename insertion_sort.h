#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H


#include <vector>
using namespace std;

template <typename T>
void insertionSort(std::vector<T>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

#endif // INSERTION_SORT_H
