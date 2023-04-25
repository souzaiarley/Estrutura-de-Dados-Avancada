#include <iostream>
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

// Esta função "interliga" todas as outras funcoes auxiliares permitindo que trabalhem em conjunto
// para gerar uma t3 vinda da intercalação de t1 e t2
void avl_tree::intercalate(avl_tree *t1, avl_tree *t2){
    // vectors que guardarão as chaves das árvores
    vector<int> vec1;
    vector<int> vec2;
    vector<int> vec3;

    // adiciona a vec1 e vec2 as chaves de t1 e t2 ordenadas, respectivamente
    vec1 = vec_keys(t1->root, vec1);
    vec2 = vec_keys(t2->root, vec2);

    // forma o terceiro vector, da uniao de vec 1 e vec2
    // todas as chaves que formarao a terceira árvore estão nele, sendo que estão ordenadas
    // lembrando que: não há repetições de chaves
    vec3 = merge_vectors(vec1, vec2);
    
    // A árvore é formada, de forma recursiva, a partir das chaves de vec3
    root = create_avl(root, vec3, 0, vec3.size()-1);
}

// Função auxiliar recursiva que retorna um vector com as keys ordenadas de uma árvore
// A árvore é percorrida na ordem simétrica, e suas keys são guardadas em vec
vector<int> avl_tree::vec_keys(Node *node, vector<int> &vec){
    if (node == nullptr){
        return vec;
    }
    vec_keys(node->left, vec);
    vec.push_back(node->key);
    vec_keys(node->right, vec);
    return vec;
}

// Função auxiliar que retorna um vector ordenado a partir dos elementos de
// outros dois vectors (realiza a última etapa do mergesort)
vector<int> avl_tree::merge_vectors(vector<int> vec1, vector<int> vec2){
    vector<int> vec3;
    int i = 0;  // indices de vec1
    int j = 0;  // indices de vec2

    // Faz as comparacoes dos elementos de vec1 e vec2 e vai colocando em vec3, em ordem crescente
    while (true){
        if (vec1[i] < vec2[j] && i < vec1.size()){
            if (vec3.size() == 0){vec3.push_back(vec1[i]);}
            else if (vec1[i] != vec3.back()){
                vec3.push_back(vec1[i]);
            }
            i++;
        }
        else {
            if (j < vec2.size()){
                if (vec3.size() == 0){vec3.push_back(vec2[j]);}
                else if (vec2[j] != vec3.back()){
                    vec3.push_back(vec2[j]);
                }
            }
            j++;
        }
        // caso de parada: todos os elementos de vec 1 e vec 2 foram analisados
        if (i > vec1.size()-1 && j > vec2.size()-1){
            break;
        }
    }
    return vec3;
}

// Função recursiva que constrói uma árvore AVL a partir de um vetor ordenado.

// Esta funcao é O(m+n) pois, vec possui todas as chaves da primeira e segunda árvores.
// Como é executada recursivamente tanto para a subárvore esquerda, como para a direita, 
// todos os nós a serem criados serão percorridos. Então trata-se de um percurso em
// árvore binária (pré-ordem, nesse caso) de complexidade O(m+n).
Node* avl_tree::create_avl(Node *node, vector<int> &vec, int p, int q){
    // caso de parada: todos os elementos de vec foram percorridos
    if (q < p){
        return nullptr;
    }
    // caso base: node será uma folha
    else if (p == q){
        node = new Node(vec[p], nullptr, nullptr);
        return node;
    }
    // recursao:
    int meio = (p+q)/2; // calcula qual o indice de vector que virá a ser root
    node = new Node(vec[meio], nullptr, nullptr); // cria root, com chave = vec[meio]
    node->left = create_avl(node->left, vec, p, meio-1); // chama recursivamente para a subárvore esquerda
    node->right = create_avl(node->right, vec, meio+1, q); // chama recursivamente para a subárvore direita
    node = fixup_node(node, vec[meio]);
    return node;
}