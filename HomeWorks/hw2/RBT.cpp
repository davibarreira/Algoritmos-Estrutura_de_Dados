#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>

using namespace std;


/*
----------------------- ESTRUTURA DO CÓDIGO ------------------------
A classe RBT (redblack tree) foi implementada como inheritance
da classe BST já previamente fornecida. Além disso, foi feita uma 
modificação no struct Node, criando um novo pointeiro *parent.
Foram criadas novas funções específicas para a RBT dentro da classe
BST, sendo adicionado "rb_" no início do seu nome. As funções foram:
* rb_find();
* rb_remove();
* rb_insert();
* rb_print();

Além dessas funções, também foram criadas funções auxiliares para
ajustar o balanceamente e cor da RBT, chamadas:
* recolor();
* left_rotate_line();
* left_rotate_zig();
* right_rotate_line();
* right_rotate_zig();
Note que foram implementadas 4 funções de rotate, 1 para cada situação
possível de se encontrar.
OBS: A classe RBT sobrescreve o nome das funções rb_insert, rb_remove
e rb_print, para somente insert, remove e print.
OBS2: Na função print() da RBT, o código foi modificado para indicar
a cor do node como 'r' ou 'b'.
---------------------------------------------------------------------
*/

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

    bool find(int x) {
        Node **p;
        return find(x, p);
    }

    void insert(int x) {
        Node **p;
        if (!find(x, p)) {
            *p = new Node(x,'r');
        }
    }
    void remove(int x) {
        Node **p;
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
        parent = &pRoot;
        if (!rb_find(x, p, parent)) {
            *p = new Node(x,'r');

            (*p)->parent = *parent;

            recolor(*p);
        }
    }

    void rb_remove(int x) {
        Node **p;
        Node **parent;
        parent = &pRoot;
        if(rb_find(x, p, parent))
            rb_remove(*p);
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

        if (pai->color=='b')
        {
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
                pai->color = 'b';
                uncle->color  = 'b';
                grand_p->color= 'r';

                recolor(grand_p);
            }
        }
        else{
            if (pai == grand_p)
            {
                pai->color  = 'b';
                grand_p->color = 'b';
                return;
            }

            //right_rotate
            if (pai->data > p->data)
            {
                if (pai->data > grand_p->data)
                {
                    right_rotate_zig(p);
                }
                else{

                    right_rotate_line(p);

                }
            }
            else{
                if (pai->data > grand_p->data)
                {
                    left_rotate_line(p);
                }
                else{
                    left_rotate_zig(p);
                }

            }
        }
    }
    void left_rotate_zig(Node *p){
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent;

        p->parent      = grand_p;
        pai->parent    = p;
        if (p->pChild[0])
        {
            p->pChild[0]->parent = pai;
        }
        pai->pChild[1] = p->pChild[0];
        p->pChild[0]   = pai;
        grand_p->pChild[0] = p;
        recolor(pai);
    }

    void right_rotate_zig(Node *p){
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent;

        p->parent      = grand_p;
        pai->parent    = p;
        if (p->pChild[1])
        {
            p->pChild[1]->parent = pai;
        }
        pai->pChild[0] = p->pChild[1];
        p->pChild[1]   = pai;
        grand_p->pChild[1] = p;
        recolor(pai);
    }

    void left_rotate_line(Node *&p){
        char temp;
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent;

        if(pai->pChild[0]){
            pai->pChild[0]->parent = grand_p;
        }
        grand_p->pChild[1] = pai->pChild[0];
        if (grand_p->parent == grand_p){
            pai->parent = pai;
            pRoot = pai;
        }
        else{
            pai->parent = grand_p->parent;
            grand_p->parent->pChild[1] = pai;
        }
        pai->pChild[0] = grand_p;
        grand_p->parent = pai;
        temp = grand_p->color;
        grand_p->color = pai->color;
        pai->color = temp;
    }

    void right_rotate_line(Node *&p){
        char temp;
        Node *pai;
        Node *grand_p;
        pai = p->parent;
        grand_p = pai->parent;

        if(pai->pChild[1]){
            pai->pChild[1]->parent = grand_p;
        }
        grand_p->pChild[0] = pai->pChild[1];
        if (grand_p->parent == grand_p){
            pai->parent = pai;
            pRoot = pai;
        }
        else{
            pai->parent = grand_p->parent;
            grand_p->parent->pChild[0] = pai;
        }
        pai->pChild[1] = grand_p;
        grand_p->parent = pai;
        temp = grand_p->color;
        grand_p->color = pai->color;
        pai->color = temp;
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

    bool find(int x, Node **&p) {
        p = &pRoot;
        while(*p) {
            if ((*p)->data==x) return true;

            p = &((*p)->pChild[(*p)->data < x]);
        }

        return false;
    }

    void remove(Node *&p) {
        if (!p->pChild[0] || !p->pChild[1])
            p = p->pChild[p->pChild[1]!=nullptr];

        else {
            Node **succesor = &(p->pChild[1]);
            find_min(succesor);
            p->data = (*succesor)->data;
            remove(*succesor);
        }
    }

    void rb_remove(Node *&p) {
        // x eh um helper, d é o nó que será deletado, porém é só um helper
        Node *x; // x helper
        Node *d; // node a ser deletado helper
        Node *r; // node replacement helper
        Node **succesor = &(p->pChild[1]);
        int INITIAL;
        int CASE;

        d = p;

        // PASSO 1 - SELECIONAR O X
        if ((p->pChild[0] == nullptr)&&(p->pChild[1] == nullptr))
        {
            INITIAL = 1;
            x = p->pChild[1];
            r = x;
        }
        else if ((p->pChild[0] == nullptr)||(p->pChild[1] == nullptr))
        {
            INITIAL = 2;
            x = p->pChild[p->pChild[1]!=nullptr];
            r = x;
        }
        else {
            INITIAL = 3;
            find_min(succesor);
            x = (*succesor)->pChild[1];
            r = (*succesor);
            p->data = (*succesor)->data;
        }

        // PASSO 2 - SEGUNDA CONDICAO

        // * P2_1
        if (r==nullptr)
        {
            if (d->color == 'r'){
                if (INITIAL == 3)
                {
                    rb_remove(*succesor);
                    return;
                }
                else
                {
                    p = r;
                    return;
                }
            }
        }
        else if((d->color=='r')&&(r->color=='r')){
            if (INITIAL == 3)
            {
                rb_remove(*succesor);
                return;
            }
            else
            {
                p = r;
                return;
            }
        }



        if (r!=nullptr)
        {

            // * P2_2
            if ((d->color == 'r')&&(r->color=='b'))
            {
                if (INITIAL == 3)
                {
                    r->color = 'r';
                    rb_remove(*succesor);
                }
                else
                {
                    r->color = 'r';
                }
                // proceder para caso apropriado
            }

                // * P2_3
            else if ((d->color=='b')&&(r->color=='r'))
            {
                if (INITIAL == 3)
                {
                    p->pChild[p->pChild[1]!=nullptr]->parent = p->parent;
                    p->color = 'b';
                    rb_remove(*succesor);
                    return;
                }
                else
                {
                    p->pChild[p->pChild[1]!=nullptr]->parent = p->parent;
                    p = r;
                    p->color = 'b';
                    return;
                }
            }

        }
        // * P2_4 - Se nenhum anterior ocorreu, então estamos em P2_4
        if (INITIAL == 3)
        {
            rb_remove(*succesor);
        }
        else{
            p = r;
            return;
        }


        Node *w; // irmao de x
        if (p->pChild[0]==x)
        {
            w = p->pChild[1];
        }
        else{
            w = p->pChild[0];
        }


        // CASE 0
        if (x!=nullptr)
        {
            if (x->color == 'd')
            {
                x->color = 'b';
                return;
            }
        }

        // CASO 1: Node x is black and its sibling w is red



        // CASO 2: Node x is black and its sibling w is black
        // and both w's children are black
        if (x==nullptr)
        {
            if (w == nullptr)
            {
                CASE = 2;
            }
            else if (w->color=='b')
            {
                if (w->pChild[0]==nullptr)
                {
                    if (w->pChild[1]==nullptr)
                    {
                        CASE = 2;
                    }
                    else if (w->pChild[1]->color == 'b'){
                        CASE = 2;
                    }
                }
                else if (w->pChild[1]==nullptr)
                {
                    if (w->pChild[0]==nullptr)
                    {
                        CASE = 2;
                    }
                    else if (w->pChild[0]->color == 'b'){
                        CASE = 2;
                    }
                }

            }
        }
        if (CASE == 2)
        {
            w->color = 'r';
            x = p;
            if (x->color == 'r'){
                x->color = 'b';
                return;
            }
            else {
                return;
            }
        }
    }


    void find_min(Node **&p) {

        while((*p)->pChild[0]){
            p = &((*p)->pChild[0]);
        }
    }
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

    void insert(int x){
        BST::rb_insert(x);
        // insercao de cor for feita diretamente no insert na BST
    }

    void print(){
        BST::rb_print();
    }

    void remove(int x){
        BST::rb_remove(x);
    }

private:
    // The base case
    void process() {} // end recursion

    // The recursive case
    template <typename... Ts>
    void process(int t, Ts... ts);

};

// Constructor with Initialization List
RBTree::RBTree(initializer_list<int> values):BST() {
    for (auto val: values) {
        BST::rb_insert(val);
    }
}

// Constructor with Variadic Templates
template<typename ...Ts>
RBTree::RBTree(Ts... ts): BST() {
    process(ts...);
}

// The recursive case
template <typename... Ts>
void RBTree::process(int t, Ts... ts) {
    BST::rb_insert(t);
    this->process(ts...);
}




void test(int **&pp) {
    cout << pp << endl;

}
int main() {

    RBTree tree(41,38,31,12,19,8);
    tree.rb_print();
    cout << "---------------------"<<endl;
    tree.remove(8);
    tree.rb_print();

    return 0;
}