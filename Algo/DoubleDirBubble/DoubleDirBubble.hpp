#ifndef __DOUBLE_DIR_BUBBLE_HPP__
#define __DOUBLE_DIR_BUBBLE_HPP__
#include <iostream>
#include <vector>

namespace ds {

template <typename Elem>
void DoubleBubbleSort(Elem arr[], size_t left, size_t right) {
    using std::swap;
    while (left <= right) {
        for (size_t i = left; i < right; i++) {
            if (arr[left] > arr[i]) {
                swap(arr[left], arr[i]);
            }
        }
        left++;
        for (size_t j = right - 1; j >= left; j--) {
            if (arr[right] < arr[j]) {
                swap(arr[right], arr[j]);
            }
        }
        right--;
    }
}

}  // namespace ds

#endif  // __DOUBLE_DIR_BUBBLE_HPP__
