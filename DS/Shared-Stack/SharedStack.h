#ifndef SHARED_STACK_H
#define SHARED_STACK_H

template <class Elem>
class SharedStack{
protected:
    Elem * data;
    int top1,top2;
    int maxSize;
    int size1,size2;
public:
    // use i=index to indicate which stack
    SharedStack(int sz = 10);
    ~SharedStack();
    bool isEmpty(int i = 0)const;
    bool isFull()const;
    void push(const Elem & elem,int i);
    const Elem & pop(int i);
    const Elem & getTop(int i) const;
    int getSize(int i)const;
    int getMaxSize()const;
};


template <class Elem>
SharedStack<Elem>::SharedStack(int sz)
    :data(new Elem[sz]),top1(-1),top2(sz),maxSize(sz),size1(0),size2(0)
{}

template <class Elem>
SharedStack<Elem>::~SharedStack(){
    delete [] data;
}

// i default 0 means to determine both of the stack is full
template <class Elem>
bool SharedStack<Elem>::isEmpty(int i)const{
    if(i == 1)
        return size1 == 0; 
    else if(i == 2)
        return size2 == 0;
    else {
        return size1 == 0 && size2 == 0;
    }
}

template<class Elem>
bool SharedStack<Elem>::isFull()const{
    return size1 + size2 == maxSize;
}

/*
init -1                                 sz
    top1                              top2
        0 1 2 3 4 5 - - -   6 7 8 9 10 

*/

template<class Elem>
void SharedStack<Elem>::push(const Elem & elem,int i){
    if(isFull()){
        throw "Stack is full";
    }
    if(i == 1){
        data[++top1] = elem;
        size1++;
    }else if(i == 2){
        data[--top2] = elem;
        size2++;
    }else{
        throw "Invalid index";
    }
}

template<class Elem>
const Elem & SharedStack<Elem>::pop(int i){
    if(isEmpty(i))
        throw "Stack is empty";
    if(i == 1){
        size1--;
        return data[top1--];
    }
    else if(i == 2){
        size2--;
        return data[top2++];
    }
    else{
        throw "Invalid index";
    }
}

template<class Elem>
const Elem & SharedStack<Elem>::getTop(int i)const{
    if(isEmpty(i))
        throw "Stack is empty";
    if(i == 1){
        return data[top1];
    }
    else if(i == 2){
        return data[top2];
    }
    else{
        throw "Invalid index";
    }
}

template<class Elem>
int SharedStack<Elem>::getSize(int i)const{
    if(i == 1)
        return size1;
    else if(i == 2)
        return size2;
    else
        throw "Invalid index";
}

template<class Elem>
int SharedStack<Elem>::getMaxSize()const{
    return maxSize;
}

#endif // SHARE_STACK_H