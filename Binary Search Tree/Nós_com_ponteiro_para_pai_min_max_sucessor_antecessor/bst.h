#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    if (search(k) != nullptr) return false;
    if (root == nullptr){
        root = new Node(k, nullptr, nullptr, nullptr);
        return true;
    }
    else {
        Node *aux = root;
        while (aux != nullptr){
            if (k < aux->key){
                if (aux->left == nullptr){
                    Node *novo = new Node(k, nullptr, nullptr, aux);
                    aux->left = novo;
                    break;
                }
                aux = aux->left;
            }
            else if (k > aux->key){
                if (aux->right == nullptr){
                    Node *novo = new Node(k, nullptr, nullptr, aux);
                    aux->right = novo;
                    break;
                }
                aux = aux->right;
            }
        }
        aux = nullptr;
        delete aux;
        return true;
    }
    return false;
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    if (root == nullptr || root->key == k){
        return root;
    }
    Node *aux = root;
    while (aux != nullptr){
        if (aux->key == k){
            return aux;
        }
        if (k < aux->key){
            aux = aux->left;
        }
        else if (k > aux->key){
            aux = aux->right;
        }
    }
    return aux;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    return minimum(root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::minimum(Node *node) {
    if (node == nullptr){
        return nullptr;
    }
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    return maximum(root)->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    if (node == nullptr){
        return nullptr;
    }
    while (node->right != nullptr){
        node = node->right;
    }
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    if (search(k) == nullptr){
        return INT_MAX;
    }
    else if (successor(search(k)) == nullptr){
        return INT_MAX;
    }
    return successor(search(k))->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    if (node->right != nullptr){
        return minimum(node->right);
    }
    else {
        Node *aux = root;
        Node *menor = maximum(root);
        while (aux != node){
            if (node->key > aux->key){
                if (aux->key >= node->key && aux->key <= menor->key){
                    menor = aux;
                }
                aux = aux->right;
            }
            else if (node->key < aux->key){
                if (aux->key >= node->key && aux->key <= menor->key){
                    menor = aux;
                }
                aux = aux->left;
            }
        }
        if (menor->key <= aux->key){
            return nullptr;
        }
        return menor;
    }
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    if (search(k) == nullptr){
        return INT_MIN;
    }
    else if (predecessor(search(k)) == nullptr){
        return INT_MIN;
    }
    return predecessor(search(k))->key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node) {
    if (node->left != nullptr){
        return maximum(node->left);
    }
    else {
        Node *aux = root;
        Node *maior = minimum(root);
        while (aux != node){
            if (node->key > aux->key){
                if (aux->key <= node->key && aux->key >= maior->key){
                    maior = aux;
                }
                aux = aux->right;
            }
            else if (node->key < aux->key){
                if (aux->key <= node->key && aux->key >= maior->key){
                    maior = aux;
                }
                aux = aux->left;
            }
        }
        if (maior->key >= aux->key){
            return nullptr;
        }
        return maior;
    }
}

#endif 