#include <iostream>
#include <initializer_list>

using namespace std;


template <class T>
struct Node{
    T data;
    Node *pNext;

    Node(T x):data(x), pNext(NULL){}
};

template <class T>
class LinkedList{
private:
    Node<T> *pRoot;
    int length;

public:
    LinkedList(): pRoot(NULL), length(0) {}
    LinkedList(initializer_list<T> values);
    bool find(T x, Node<T> **&pNode);
    void insert(T x);
    void print();
    void remove(T x);

    class Iterator
    {
    public:
        Node<T> *pNode;
        Iterator():pNode(NULL) {}
        Iterator(Node<T> *p):pNode(p) {}

        bool operator!=(Iterator it){
            return this->pNode != it.pNode;
        }

        Iterator operator++(T){
            this->pNode = pNode->pNext;
            return *this;
        }

        T& operator*() {
            return pNode->data;
        }

    };

    Iterator begin(){
        return this->pRoot;
    }

    Iterator end(){
        return NULL;
    }
};

