#ifndef SEQ_LIST_H
#define SEQ_LIST_H
#include <stdexcept>

template <typename T>
class SeqList {
private:
    // pointer to the array of elements
    T* data; 
    // number of elements currently in the list
    int size;
    // capacity of the list
    int capacity; 

public:
    // creates a list with the given initial capacity
    SeqList(int initialCapacity = 10);
    // deletes the list
    ~SeqList();
    // returns the number of elements in the list
    int getSize() const;
    // returns true if the list is empty
    bool isEmpty() const;
    // inserts an element at the given index
    void insert(int index, const T& element);
    // removes the element at the given index
    void remove(int index);
    // returns a reference to the element at the given index
    T& get(int index) const;

private:
    // increases the capacity of the list
    void expandCapacity();
};

template <typename T>
SeqList<T>::SeqList(int initialCapacity) {
    // initial capacity of the list
    capacity = initialCapacity;
    // initial size of the list
    size = 0;
    // initializes the data array
    data = new T[capacity];
}

template <typename T>
SeqList<T>::~SeqList() {
    // deletes the data array
    delete[] data;
}

template <typename T>
int SeqList<T>::getSize() const {
    // returns the number of elements in the list
    return size;
}

template <typename T>
bool SeqList<T>::isEmpty() const {
    // returns true if the list is empty
    return size == 0;
}

template <typename T>
void SeqList<T>::insert(int index, const T& element) {
    // checks if the index is valid
    if (index < 0 || index > size) {
        throw std::out_of_range("Invalid index");
    }

    // expand the capacity if needed
    if (size == capacity) {
        expandCapacity();
    }

    // shift the elements to the right
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }

    // insert the element at the given index
    data[index] = element;
    // increment the size
    size++;
}

template <typename T>
void SeqList<T>::remove(int index) {
    // checks if the index is valid
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index");
    }

    // shift the elements to the left
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    // decrement the size
    size--;
}

template <typename T>
T& SeqList<T>::get(int index) const {
    // checks if the index is valid
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index");
    }

    // returns a reference to the element at the given index
    return data[index];
}

template <typename T>
void SeqList<T>::expandCapacity() {
    // double the capacity
    capacity *= 2;
    // creates a new array
    T* newData = new T[capacity];
    // copies the elements from the old array to the new array
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    // deletes the old array
    delete[] data;
    // sets the new array as the data array
    data = newData;
}

#endif // SEQ_LIST_H