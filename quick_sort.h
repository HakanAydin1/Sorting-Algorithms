#ifndef QUICK_SORT_H
#define QUICK_SORT_H


#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;


template <typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
    auto pivot = std::prev(last);
    auto i = first;
    for (auto j = first; j != pivot; ++j) {
        if (*j < *pivot) {
            std::iter_swap(i, j);
            ++i;
        }
    }
    std::iter_swap(i, pivot);
    return i;
}

template <typename RandomIt>
void quick_sort(RandomIt first, RandomIt last) {
    if (first != last) {
        auto pivot = partition(first, last);
        quick_sort(first, pivot);
        quick_sort(std::next(pivot), last);
    }
}

template <typename Container>
void quick_sort(Container& container) {
    quick_sort(std::begin(container), std::end(container));
}

#endif // QUICK_SORT_H
