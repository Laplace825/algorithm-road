#ifndef STACK_H
#define STACK_H

template <class Elem>
class Stack{
protected:
    Elem * data;
    int top;
    int length;
    int MaxSize;
public:
    Stack();
    Stack(int sz);
    ~Stack();
    bool isEmpty();
    void push(const Elem & e);
    const Elem & pop();
    const Elem & top() const{ return data[top];}
    int getlength() const{ return length;}
};

template<class Elem>
Stack<Elem>::Stack()
    :data(new Elem[10]),top(-1),length(0),MaxSize(10)
{}

template<class Elem>
Stack<Elem>::Stack(int sz)
:data(new Elem[sz]),top(-1),length(0),MaxSize(sz)
{}

template<class Elem>
Stack<Elem>::~Stack(){delete[] data;}

template<class Elem>
bool Stack<Elem>::isEmpty()
{
    return length == MaxSize;
}


template<class Elem>
void Stack<Elem>::push(const Elem & e){
    if(!isEmpty())
        throw "Stack Overflow";
    else{
        data[++top] = e;
        length++;
    }
}

template<class Elem>
const Elem & Stack<Elem>::pop() {
    if(isEmpty())
        throw "Stack Empty";
    else{
        length--;
        return data[top--] = e;
    }
}

#endif // STACK_H