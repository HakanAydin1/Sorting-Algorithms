#ifndef HEAP_SORT_H
#define HEAP_SORT_H


#include <algorithm>
#include <ranges>
#include <vector>
using namespace std;


template <typename RandomIt>
void heapify(RandomIt first, RandomIt last, RandomIt i) {
    auto largest = i;
    auto left = std::next(i);
    auto right = std::next(left);
    if (left < last && *left > *largest) {
        largest = left;
    }
    if (right < last && *right > *largest) {
        largest = right;
    }
    if (largest != i) {
        std::iter_swap(i, largest);
        heapify(first, last, largest);
    }
}

template <typename RandomIt>
void heap_sort(RandomIt first, RandomIt last) {
    std::ranges::make_heap(first, last);
    std::sort_heap(first, last);
}

template <typename Container>
void heap_sort(Container& container) {
    heap_sort(std::begin(container), std::end(container));
}

#endif // HEAP_SORT_H
