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
    char color;

    Node *parent;
    // Declara um vetor 2 ponteiro
    Node *pChild[2];

    // Inicializa o node e adiciona dois ponteiros que apontam para espaços de memória node nulos
    //                   _Node_ 
    //  Null <- pChild__|      |__pChild -> Null
    //
    Node(int x, char c):data(x), color(c) {
        parent = pChild[0] = pChild[1] = nullptr;
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
            *p = new Node(x,'r');
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

    void rb_insert(int x) {
        Node **p;
        Node **parent;
        // o find busca se o valor x ja esta na arvore. Se nao estiver,
        // o p aponta para um novo ponteiro de nodes que aponta para um node com valor x
        parent = &pRoot;
        if (!rb_find(x, p, parent)) {
            *p = new Node(x,'r');

            (*p)->parent = *parent;

            recolor(*p);
        }
    }

    void rb_print() {
        rb_print(pRoot);
        cout << endl;
    }

private:

    void recolor(Node *&p){
        Node *pai;
        Node *grand_p;
        Node *uncle;
        pai = p->parent;
        cout << "NODE "<< p->data<<" INSERIDO"<<">>";

        if (pai->color=='b')
        {
            cout << "CASO 1"<<endl;
            return;
        }

        grand_p = pai->parent; 
        // Node esta na esquerda do grand_p
        if (grand_p->data > p->data)
        {
            uncle = grand_p->pChild[1];
        }
        else{
            uncle = grand_p->pChild[0];
        }

        // aqui busca se uncle não é NIL e não é vermelho, ou seja, se nao eh preto
        if ((uncle) && (uncle->color=='r'))
        {
            if (uncle->color=='r')
            {
                cout << "CASO 2"<<endl;
                pai->color = 'b';
                uncle->color  = 'b';
                grand_p->color= 'r';

                recolor(grand_p);
            }
            // cout << "CASO INCORRETO"<<endl;
            // cout<<"uncle"<< uncle->data <<endl;
        }
        else{
            if (pai == grand_p)
            {
                pai->color  = 'b';
                grand_p->color = 'b';
                cout << "RAIZ"<<endl;
                return;
            }
            cout << "CASO 3"<<endl;

            // pai->color  = 'b';
            // grand_p->color = 'r';

            //right_rotate
        if (pai->data > p->data)
        {
            cout << "NODE" << p->data << " RIGHT_ROTATE"<<endl;
            right_rotate(p);
        }
        else{
            cout << "NODE" << p->data << " LEFT_ROTATE"<<endl;
            left_rotate(p);
        }
            // pai->parent     = grand_p->parent;
            // grand_p->parent = pai;

            // grand_p->pChild[0] = pai->pChild[1];
            // pai->pChild[1] = grand_p;
            // pai->pChild[1]  = grand_p;
        }
        // }
        // return;
    }

    void right_rotate(Node *&p){
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent; 

        p->parent      = grand_p;
        pai->parent    = p;
        p->pChild[1]->parent = pai;
        pai->pChild[0] = p->pChild[1];
        p->pChild[1]   = pai;
        grand_p->pChild[1] = p;
        cout << pai->data<<endl;
        recolor(pai);
    }

    void left_rotate(Node *&p){
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent; 

        pai->pChild[0]->parent = grand_p;
        grand_p->pChild[1] = pai->pChild[0];
        if (grand_p->parent == grand_p){
            pai->parent = pai;
            pRoot = pai;
            cout << "ROOT"<<endl;
        }
        else{
            pai->parent = grand_p->parent;
        }
        pai->pChild[0] = grand_p;
        grand_p->parent = pai;
        // recolor(grand_p);
    }




    bool rb_find(int x, Node **&p, Node **&parent) {

        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;

            parent = p;

            p = &((*p)->pChild[(*p)->data < x]);
        }
        return false;
    }

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
            // se o pai do node for nulo

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

    void rb_print(Node *p, int indent=0) {
        if (p) {
            rb_print(p->pChild[1], indent+6);
            cout << setw(indent) << ' ';
            cout<<p->parent->data<<"/";
            cout<< p->data << p->color<<endl;
            rb_print(p->pChild[0], indent+6);
        }
    }
};



// template<typename T>
class RBTree: public BST{
public:
    // Constructor with Initialization List
    // RBTree(initializer_list<T> values);
    RBTree(initializer_list<int> values);

    // Constructor with Variadic Templates
    template<typename ...Ts>
    RBTree(Ts... ts);

    void rb_insert(int x){
        BST::rb_insert(x);
        // insercao de cor for feita diretamente no insert na BST
    }

private:
    // The base case
    void process() {} // end recursion

    // The recursive case
    template <typename... Ts>
    void process(int t, Ts... ts);

};

// Constructor with Initialization List
// template<typename T>
// RBTree<T>::RBTree(initializer_list<T> values):BST(), pRoot(NULL), length(0) {
RBTree::RBTree(initializer_list<int> values):BST() {
    for (auto val: values) {
        BST::rb_insert(val);
    }
}

// Constructor with Variadic Templates
// template<typename T>
template<typename ...Ts>
// RBTree<T>::RBTree(Ts... ts): BST(), pRoot(NULL), length(0) {
RBTree::RBTree(Ts... ts): BST() {
    process(ts...);
}

// The recursive case
// template<typename T>
template <typename... Ts>
void RBTree::process(int t, Ts... ts) {
    BST::rb_insert(t);
    this->process(ts...);
}




void test(int **&pp) {
    cout << pp << endl;

}
int main() {

    // RBTree tree(48,38,31);
    RBTree tree(5,2,10,8,12,6,9,7);
    // tree.rb_insert(11);
    // tree.rb_insert(9);
    tree.rb_print();

    // BST bst;
    // bst.insert(6);
    // bst.insert(4);
    // bst.insert(7);
    // bst.insert(2);
    // bst.insert(5);
    // bst.insert(1);
    // bst.insert(3);

    // // Teste Davi
    // bst.insert(14);
    // bst.insert(18);
    // bst.insert(16);
    // bst.insert(15);
    // bst.insert(20);
    // bst.insert(9);
    // //

    // bst.print();


    // cout << "-----------------\n";
    // // Teste Davi
    // bst.remove(14);
    // //

    // bst.remove(4);
    // bst.print();

    // bst.remove(3);
    // bst.print();

    // bst.remove(6);
    // bst.print();


    // Node **pp;
    // Node *p;
    // Node *pc;
    // Node n(2,'r');
    // Node n2(3,'r');
    // p = &n;
    // pc= p;
    // cout << p << endl;
    // cout << pc << endl;
    // p->pChild[1] = &n2;
    // p = p->pChild[1];
    // p->parent = pc;
    // cout << p->data << endl;
    // cout << pc->data << endl;
    // cout << p->parent->data << endl;

    // pp = &p;
    // p = &n;
    // p->pChild[1] = &n2;
    // pc = p->pChild[1];
    // cout << *pp << endl;
    // cout << p->pChild[1]->data << endl;


    return 0;
}