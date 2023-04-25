#include <iostream>
#include <sstream>
#include "avl.h"
using namespace std;

int main() {
    system("chcp 65001 > nul");
    avl_tree *t = new avl_tree;
    string s;
    stringstream ss;
    int no;

    cout << "Informe em uma unica linha todas as chaves que deseja inserir: ";
    getline(cin, s);
    ss << s;

    while (ss >> no){
        t->add_iterativo(no);
    }
    
    t->bshow();
}