#ifndef MERGE_SORT_H
#define MERGE_SORT_H


#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>
using namespace std;


template <typename RandomIt>
void merge(RandomIt first, RandomIt middle, RandomIt last) {
    std::vector left(first, middle);
    std::vector right(middle, last);
    auto left_it = std::begin(left);
    auto right_it = std::begin(right);
    while (left_it != std::end(left) && right_it != std::end(right)) {
        if (*left_it < *right_it) {
            *first = std::move(*left_it);
            ++left_it;
        }
        else {
            *first = std::move(*right_it);
            ++right_it;
        }
        ++first;
    }
    std::ranges::move(left_it, std::end(left), first);
    std::ranges::move(right_it, std::end(right), first);
}

template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    if (std::distance(first, last) > 1) {
        auto middle = std::next(first, std::distance(first, last) / 2);
        merge_sort(first, middle);
        merge_sort(middle, last);
        merge(first, middle, last);
    }
}

template <typename Container>
void merge_sort(Container& container) {
    merge_sort(std::begin(container), std::end(container));
}

#endif // MERGE_SORT_H
