#include <iostream>
#include <bst.h>
#include <stdexcept>
using namespace std;

// public

BST::BST() = default;                    
BST(const BST& t) = delete;             
BST& operator=(const BST& t) = delete;  
~BST();                                 
void BST::add(int key){
    add(root, key);
}                
void BST::remove(int key){}               
bool BST::contains(int key){
    if (search(root, key) == nullptr){
        return false;
    }
    return true;
}                
int BST::minimum(){
    if (root == nullptr){
        std::runtime_error("erro: arvore vazia");
    }
    return minimum(root)->key;
}                 
int BST::maximum(){
    if (root == nullptr){
        std::runtime_error("erro: arvore vazia");
    }
    return maximum(root)->key;
}                         
int BST::successor(int k){
    
}
int BST::predecessor(int k){}
void BST::inorder(){}

// private

// Atributo privado
Node *root {nullptr};

// Funcoes-membro privadas
Node* BST::add(Node *node, int key){
    if (node == nullptr){
    node = new Node(key, nullptr, nullptr);
    return node;
}
else {
    if (node->key < key){
        return add(node->right, key);
    }
    else if (node->key > key){
        return add(node->left, key);
    }
}
}
Node* BST::search(Node *node, int key){
    if (node == nullptr || node->key == key){
        return node;
    }
    if (key > node->key){
        return search(node->right, key);
    }
    if (key < node->key){
        return search(node->left, key);
    }
}
Node* BST::clear(Node *node){

}
Node* BST::minimum(Node *node){
    if (node->left == nullptr){
        return node;
    }
    return minimum(node->left);
}
Node* BST::maximum(Node *node){
    if (node->right == nullptr){
        return node;
    }
    return maximum(node->right);
}
Node* BST::ancestral_sucessor(Node *x, Node *raiz){}
Node* BST::ancestral_predecessor(Node *x, Node* raiz){}
Node* BST::sucessor(Node *x, Node *raiz){}
Node* BST::predecessor(Node *x, Node* raiz){}
Node* BST::remove(int k, Node *node){}
Node* BST::removeRoot(Node *node){}
void BST::inorder(Node *node){}