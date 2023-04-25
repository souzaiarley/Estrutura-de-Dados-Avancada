#include <iostream>
#include <sstream>
#include "avl.h"
using namespace std;

int main() {
    system("chcp 65001 > nul");
    avl_tree *t1 = new avl_tree;
    avl_tree *t2 = new avl_tree;
    avl_tree *t3 = new avl_tree;
    string s;
    stringstream ss;
    int no;

    cout << "Informe em uma unica linha todas as chaves que deseja inserir para T1: ";
    getline(cin, s);
    ss << s;

    while (ss >> no){
        t1->add(no);
    }
    
    ss.clear();

    cout << "Informe em uma unica linha todas as chaves que deseja inserir para T2: ";
    getline(cin, s);
    ss << s;

    while (ss >> no){
        t2->add(no);
    }

    cout << "T1:\n";
    t1->bshow();
    cout << "T2:\n";
    t2->bshow();

    t3->intercalate(t1,t2);
    cout << "T3:\n";
    t3->bshow();
}