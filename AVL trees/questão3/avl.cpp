#include <iostream>
#include <stack>
#include "node.h"
#include "avl.h"
using namespace std;

// retorna a altura do nó
// se a arvore for vazia retorna 0
// caso contrario retorna o valor que esta no campo height
int avl_tree::height(Node *node) {
    if (node == nullptr) return 0;
    else return node->height;
}

int avl_tree::balance(Node *node) {
    return height(node->right) - height(node->left);
}

Node* avl_tree::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

Node* avl_tree::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // recalcular as alturas de p e de u
    p->height = 1 + max(height(p->left), height(p->right));
    u->height = 1 + max(height(u->left), height(u->right));
    return u;
}

// funcao publica que recebe uma chave e a insere somente se ela nao for repetida
void avl_tree::add(int key) {
    root = add(root, key);
}

// funcao recursiva privada que recebe uma raiz de arvore
// e uma chave e insere a chave na tree se e somente se
// ela nao for repetida. Claro, tem que deixar AVL novamente
Node* avl_tree::add(Node *p, int key) {
    if (p == nullptr){
        return new Node(key, nullptr, nullptr);
    }
    if (key == p->key){
        return p;
    }
    if (key < p->key){
        p->left = add(p->left, key);
    }
    else{
        p->right = add(p->right, key);
    }

    p = fixup_node(p, key);

    return p;
}

// o Algoritmo a seguir possui complexidade O(lg n) pois possui as seguintes propriedades:
//    - O algoritmo percorre apenas uma única ramificação da árvore, por meio da comparação das chaves
//    - Utiliza o método de Divisão e Conquista, quebrando o problema maior em subproblemas
//    - A ramificação da árvore é percorrida somente uma vez, tendo em vista o uso de uma stack que
// guarda os ancestrais do nó a ser adicionado, nao sendo necessário percorre-la denovo para encontra-los 
void avl_tree::add_iterativo(int key) {
    stack<Node*> pilha; // pilha que guardara todos os ancestrais do nó a ser adicionado
    Node *aux = root;   //  ptr auxiliar que percorrera a arvore

    if (root == nullptr){ // caso base: arvore vazia
        root = new Node(key, nullptr, nullptr);
        return;
    }

    // percorre a arvore ate encontrar o lugar correto de adicionar key e adiciona key
    while (aux != nullptr){
        pilha.push(aux);      // insere na pilha os ancestrais do nó a ser colocado
        if (key < aux->key){  // percorre a subarvore esquerda
            if (aux->left == nullptr){
                aux->left = new Node(key, nullptr, nullptr);  // adiciona key
                break;
            }
            aux = aux->left;
        }
        else if (key > aux->key){ // percorre a subarvore direita
            if (aux->right == nullptr){
                aux->right = new Node(key, nullptr, nullptr);  // adiciona key
                break;
            }
            aux = aux->right;
        }
        else {
            return; // retorna caso key ja exista na arvore (key == aux->key)
        }
    }

    // reajusta todos os ancestrais do nó adicionado, exceto a raiz
    while (!pilha.empty()){
        if (key > pilha.top()->key){
            pilha.top()->right = fixup_node(pilha.top()->right, key);
        }
        else if (key < pilha.top()->key){
            pilha.top()->left = fixup_node(pilha.top()->left, key);
        }
        pilha.pop();
    }
    // reajusta a raiz
    root = fixup_node(root, key);
}

Node* avl_tree::fixup_node(Node *p, int key) {
    // recalcula a altura de p
    p->height = 1 + max(height(p->left), height(p->right));

    // calcula o balanco de p
    int bal = balance(p);

    if (bal < -1 && key < p->left->key){
        return rightRotation(p);
    }
    else if (bal < -1 && key > p->left->key){
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    else if (bal > 1 && key > p->right->key){
        return leftRotation(p);
    }
    else if (bal > 1 && key < p->right->key){
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }

    return p;
}

void avl_tree::clear() {
    root = clear(root);
}

Node *avl_tree::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

avl_tree::~avl_tree() {
    clear();
}

void avl_tree::bshow() const {
    bshow(root, "");
}

void avl_tree::bshow(Node *node, std::string heranca) const {
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