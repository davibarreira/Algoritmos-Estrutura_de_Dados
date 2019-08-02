#include "list.h"

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
