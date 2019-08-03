#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>


//temp
#include <array>
#include <cstdlib>
#include <cstdio>

//temp

using namespace std;

struct Node {
    int data;
    // Declara um vetor 2 ponteiro
    Node *pChild[2];

    // Inicializa o node e adiciona dois ponteiros que apontam para espaços de memória node nulos
    //                   _Node_ 
    //  Null <- pChild__|      |__pChild -> Null
    //
    Node(int x):data(x) {
        pChild[0] = pChild[1] = nullptr;
    }
};

class BST {
    // A ideia geral da classe eh definidr um *pRoot que aponta para um struct Node, que 
    // contem dois ponteiros que apontam inicialmente para nodes nulos. Sao os *pChild
    // A medida que se aplica o insert esse ponteiro *pChild vai apontando para outros nodes
    // que contem mais pChild, e assim vai se formando a arvore
    /*
            *pRoot ----->  Node { Valor X1 
                                  pChild[1] -------->  Node {Valor X2 |
                                                             pChild[1] --------> Node {Valor X4 | ... }
                                                             pChild[2] --------> Node {Valor X5 | ... }}

                                  pChild[2] -------->  Node {Valor X3 |  ... }
                                            }
    */


protected:
    // Define um ponteiro de node chamado pRoot
    Node *pRoot;

public:
    // Inicializa a BST fazendo o pRoot apontar para um espaço de node nulo
    BST():pRoot(nullptr) {}

    // Chama uma funcao find que ira buscar um valor na arvore
    bool find(int x) {
        Node **p;

        // funcao chama a find localizado no "private" e passa um ponteiro de ponteiro de node
        // Ao final da funcao, p aponta ou para o ponteiro com o node encontrado
        // ou aponta para o ponteiro pChild que deveria receber esse novo node;

        return find(x, p);
    }

    void insert(int x) {
        Node **p;
        // o find busca se o valor x ja esta na arvore. Se nao estiver,
        // o p aponta para um novo ponteiro de nodes que aponta para um node com valor x
        if (!find(x, p)) {
            *p = new Node(x);
        }
    }
    void remove(int x) {
        Node **p;
        // procura o valor x na arvore. Se encontrar, aplica a funcao
        // remove no endereço do ponteiro que aponta para o node com o valor a ser removido
        if(find(x, p))
            remove(*p);
    }

    void print() {
        print(pRoot);
        cout << endl;
    }

private:
    // Utilizar o & no argumento da funcao eh so um artificio para poder fazer p igual a *p
    // ou seja, na funcao abaixo, poderiamos fazer bool find(int x, Node **p){*p = &pRoot}, e seria igual
    // porem, com &p, podemos so usar p inves de *p (menos verborragico)
    bool find(int x, Node **&p) {
        // p eh um ponteiro que aponta para um ponteiro de node (no caso o pRoot aponta para um Node)
        // p --> pRoot --> Node
        p = &pRoot;
        // *p eh o endereço do Node. O primeiro *p eh o node que pRoot aponta, ou seja, o endereço no node raiz
        while(*p) {
            // se o valor do node apontado for x, find retorna true 
            if ((*p)->data==x) return true;

            // p recebe o node filho a direita ou a esquerda dependendo se o dado do node atual eh < que x
            // note que se data < x, retorna true = 1, ou seja, node da direita. Do contrario, 0, node da esquerda.
            p = &((*p)->pChild[(*p)->data < x]);
        }

        // Perceba que a funcao retorna true se tiver encontrado o node na arvore,
        // se nao o encontra, o node retorna false.
        return false;
    }

    // funcao recebe o ponteiro que aponta para o node a ser removido
    void remove(Node *&p) {
        // checa se pelo menos um dos nos filhos EH nulo, se algum for, entao
        // p recebe o valor do node da direita caso ele nao seja nulo, ou o node da esquerda
        // se o da direita for nulo
        if (!p->pChild[0] || !p->pChild[1])
            p = p->pChild[p->pChild[1]!=nullptr];

        // caso ambos os nodes NAO sejam nulos, entao
        // busca o sucessor do node a ser removido (menor numero a direita dele)
        // troca o valor do node a ser removido com o menor sucessor dele e aplica o codigo
        // de remove no sucessor. O codigo se repete ate nao tem mais sucessores
        else {
            // comeca pelo primeiro pChild a direita
            Node **succesor = &(p->pChild[1]);
            find_min(succesor);
            p->data = (*succesor)->data;
            remove(*succesor);
        }
    }

    // Busca pelo primeiro node que tenha pChild a esquerda
    void find_min(Node **&p) {

        // continua o loop ate nao ter mais pChild a esquerda
        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }

    // primeiro checa se o ponteiro aponta para um node valido ou nulo
    // se o ponteiro apontar para um node, chama a funcao printo no seu pChild da direita
    // recursivamente entra nos pChild a direita ate chegar num nulo. Nesse ponto, ele
    // printa varios "tabs" e o valor do Node.
    // Em seguida, entra no seu node a esquerda e repete.
    void print(Node *p, int indent=0) {
        if (p) {
            print(p->pChild[1], indent+6);
            cout << setw(indent) << ' ';
            cout<< p->data <<endl;
            print(p->pChild[0], indent+6);
        }
    }
};


// class RBTree: public BST
// {
// public:
//     // RBTree(initializer_list<int> values);
//     // int a;
//     vector<int> v;
//     RBTree(vector<int> v_init = {}): v(v_init), BST()
//     // RBTree(int m): a(m), BST()
//     {
//         for (auto values: v_init)
//         {
//             BST::insert(values);
//         }
//     }

// };



template<typename T>
class RBTree{
protected:
    Node *pRoot;
    int length;


public:
    // Constructor with Initialization List
    RBTree(initializer_list<T> values);

    // Constructor with Variadic Templates
    template<typename ...Ts>
    RBTree(Ts... ts);

private:
    // The base case
    void process() {} // end recursion

    // The recursive case
    template <typename... Ts>
    void process(T t, Ts... ts);

};

// Constructor with Initialization List
template<typename T>
RBTree<T>::RBTree(initializer_list<T> values):pRoot(NULL), length(0) {
    for (auto val: values) {
        this->push_back(val);
    }
}

// Constructor with Variadic Templates
template<typename T>
template<typename ...Ts>
RBTree<T>::RBTree(Ts... ts): pRoot(NULL), length(0) {
    process(ts...);
}


// The recursive case
template<typename T>
template <typename... Ts>
void RBTree<T>::process(T t, Ts... ts) {
    this->push_back(t);
    this->process(ts...);
}




void test(int **&pp) {
    cout << pp << endl;

}
int main() {

    BST bst;
    bst.insert(6);
    bst.insert(4);
    bst.insert(7);
    bst.insert(2);
    bst.insert(5);
    bst.insert(1);
    bst.insert(3);

    // Teste Davi
    bst.insert(14);
    bst.insert(18);
    bst.insert(16);
    bst.insert(15);
    bst.insert(20);
    bst.insert(9);
    //

    bst.print();


    cout << "-----------------\n";
    // Teste Davi
    bst.remove(14);
    //

    bst.remove(4);
    bst.print();

    bst.remove(3);
    bst.print();

    bst.remove(6);
    bst.print();



    return 0;
}