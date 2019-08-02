#include "list.h"
#include <iostream>
#include <initializer_list>

using namespace std;

int main() {
    LinkedList<int> list = {1,2};
    list.insert(10);
    list.insert(5);
    // list.print();
    LinkedList<int>::Iterator it=list.begin();

    for(;it!=list.end();it++){
        cout << *it << " ";
    }

    return 0;
}
