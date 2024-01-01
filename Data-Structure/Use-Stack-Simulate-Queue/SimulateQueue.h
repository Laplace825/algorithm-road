#ifndef SIMULATE_QUEUE_H
#define SIMULATE_QUEUE_H

#include <stack>

template <class Elem>
class SimulateQueue {
protected:
    std::stack<Elem> stk1;
    std::stack<Elem> stk2;
public:
    bool isEmpty() const;
    void EnQueue(const Elem & e);
    Elem DeQueue();
};

template <class Elem>
bool SimulateQueue<Elem>::isEmpty() const{
    return stk1.empty() && stk2.empty();
}


template <class Elem>
void SimulateQueue<Elem>::EnQueue(const Elem & e)
{
    stk1.push(e);
}

template <class Elem>
Elem SimulateQueue<Elem>::DeQueue()
{
    if(isEmpty())
        throw "Queue is empty!";
    if(stk2.empty())
    {
        while(!stk1.empty()){
            stk2.push(stk1.top());
            stk1.pop();
        }
        Elem temp = stk2.top();
        stk2.pop(); 
        return temp;
    }
    else{
        Elem temp = stk2.top();
        stk2.pop(); 
        return temp;
    }
}

#endif