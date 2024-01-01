#ifndef QUEUE_SIMU_STACK_H
#define QUEUE_SIMU_STACK_H

#include <queue>

template <class T>
class QueueSimuStack
{
public:
    void push(T x);
    T pop();
    T top() const;
    bool empty() const;

private:
    std::queue<int> q;
};

template <class T>
void QueueSimuStack<T>::push(T x)
{
    q.push(x);
    for (int i = 0; i < q.size() - 1; ++i)
    {
        q.push(q.front());
        q.pop();
    }
}

template <class T>
T QueueSimuStack<T>::pop()
{
    T x = q.front();
    q.pop();
    return x;
}

template <class T>
T QueueSimuStack<T>::top() const
{
    return q.front();
}

template <class T>
bool QueueSimuStack<T>::empty() const
{
    return q.empty();
}

#endif // QUEUE_SIMU_STACK_H