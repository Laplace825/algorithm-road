#ifndef ERASE_ELEM_ARRAY_H
#define ERASE_ELEM_ARRAY_H

// a O(n) algorithm to erase all the elem in the array
// a smart algorithm
template <typename T>
void erase(const T &elem, T *arr, int size)
{
    // erase all the elem appearing in the array
    // use two pointers
    if (size <= 0)
    {
        return;
        // you can throw an exception also
    }
    int fastIndex = 0;
    int slowIndex = 0;

    while (fastIndex < size)
    {
        if (arr[fastIndex] != elem)
        {
            arr[slowIndex++] = arr[fastIndex++];
        }
        else
        {
            fastIndex++;
        }
    }
    size = slowIndex; // after erase, the size of array is slowIndex
}

#endif // !ERASE_ELEM_ARRAY_H