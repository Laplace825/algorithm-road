#ifndef SEQ_LIST_H
#define SEQ_LIST_H
#include <stdexcept>

template <typename T>
class SeqList {
private:
    T* data; // 存储数据的数组
    int size; // 当前元素个数
    int capacity; // 容量

public:
    // 构造函数
    SeqList(int initialCapacity = 10);

    // 析构函数
    ~SeqList();

    // 获取当前元素个数
    int getSize() const;

    // 判断顺序表是否为空
    bool isEmpty() const;

    // 在指定位置插入元素
    void insert(int index, const T& element);

    // 删除指定位置的元素
    void remove(int index);

    // 获取指定位置的元素
    T& get(int index) const;

private:
    // 扩容
    void expandCapacity();
};

template <typename T>
SeqList<T>::SeqList(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    data = new T[capacity];
}

template <typename T>
SeqList<T>::~SeqList() {
    delete[] data;
}

template <typename T>
int SeqList<T>::getSize() const {
    return size;
}

template <typename T>
bool SeqList<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
void SeqList<T>::insert(int index, const T& element) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Invalid index");
    }

    if (size == capacity) {
        expandCapacity();
    }

    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }

    data[index] = element;
    size++;
}

template <typename T>
void SeqList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index");
    }

    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }

    size--;
}

template <typename T>
T& SeqList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index");
    }

    return data[index];
}

template <typename T>
void SeqList<T>::expandCapacity() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

#endif // SEQ_LIST_H