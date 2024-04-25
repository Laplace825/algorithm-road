#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

// define Node
template<class Ele>
struct Node{
    Ele data;
    Node<Ele> * next;
    Node():next(nullptr){};
    Node(const Ele& e , Node<Ele> * next);
};

template<class Ele>
Node<Ele>::Node(const Ele &e, Node<Ele> *nextNode)
:next(nextNode),data(e)
{}


// define LinkQueue
template<class Ele>
class LinkQueue {
private:
    Node<Ele>* front;
    Node<Ele>* back;
    int length;
public:
    LinkQueue();
    LinkQueue(int size);
    ~LinkQueue();
    void EnQueue(const Ele &e);
    const Ele & DeQueue();
    const Ele & gethead() const;
};

template<class Ele>
LinkQueue<Ele>::LinkQueue()
:front(nullptr),back(nullptr),length(0)
{}

template<class Ele>
LinkQueue<Ele>::LinkQueue(int size)
:front(nullptr),back(nullptr),length(0)
{}

template<class Ele>
LinkQueue<Ele>::~LinkQueue()
{
    for(Node<Ele> *p=front;front!=back;)
    {
        front=front->next;
        delete p;
        p=front;
    }
    delete back;
    length = 0;
    back = nullptr;
    front = nullptr;
}

template<class Ele>
void LinkQueue<Ele>::EnQueue(const Ele &e)
{
    length++;
    Node<Ele> * p = new Node<Ele>(e , nullptr);
    if(front == nullptr){
        front = back = p;
    }
    else{
        back->next = p;
        back = p;
    }
}


template<class Ele>
const Ele & LinkQueue<Ele>::DeQueue()
{
    // front (init) = 0
    if(length == 0) // front=0
        throw "pop fail:no element there";
    else
    {
        length--;
        Node<Ele> *p=front;
        front=front->next;
        if(front == nullptr)
            back = nullptr;
        return p->data;
    }
}

template<class Ele>
const Ele & LinkQueue<Ele>::gethead() const
{
    return front->data;
}

#endif //LINK_QUEUE_H
