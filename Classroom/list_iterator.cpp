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


template< typename T>
LinkedList<T>::LinkedList(initializer_list<T> values):pRoot(NULL), length(0) {
    for (auto v: values){
        this->insert(v);
    }
}

template<typename T>
bool LinkedList<T>::find(T x, Node<T> **&pNode) {
    pNode = &pRoot;
    while(*pNode) {
        if ((*pNode)->data==x) return true;
        pNode = &((*pNode)->pNext);
    }
    return 0;
}

template<typename T>
void LinkedList<T>::insert(T x) {
    Node<T> **pNode;
    if ((find(x, pNode))) return;
    Node<T> *newNode = new Node<T>(x);
    newNode->pNext = *pNode;
    *pNode = newNode;
    length++;
}

template<typename T>
void LinkedList<T>::print() {
    Node<T> *obj = pRoot;
    while(obj) {
        cout << obj->data << " ";
        obj=obj->pNext;
    }
    cout << endl;

}

template<typename T>
void LinkedList<T>::remove(T x) {
    Node<T> **pNode;
    if(!find(x, pNode)) return;
    *pNode = (*pNode)->pNext;
}

int main() {
    LinkedList<int> list = {1,2};
    // LinkedList<int> list;
    // LinkedList<string> list;
    // list.insert("davi");
    // list.insert("davi");
    // list.insert(10);
    // list.insert(5);
    // list.insert(-1);
    // list.insert(1);
    // list.insert(1000);
    // list.print();

    // list.remove(5);
    // list.print();
    // LinkedList<int> list;
    list.insert(10);
    list.insert(5);
    list.print();
    LinkedList<int>::Iterator it=list.begin();

    for(;it!=list.end();it++){
        cout << *it << " ";
    }

    return 0;
}
