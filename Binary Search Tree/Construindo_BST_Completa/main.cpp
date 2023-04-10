#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "bst.h"
using namespace std;
#define MAX 70

// Funcao recursiva 'construirBST_balanceada'
// Essa funcao recebe como entrada:
// (1) Um ponteiro para uma BST vazia;
// (2) Um vetor de inteiros A[p..q] em ordem crescente com q-p+1 elementos. 
// Ao final da execucao dessa funcao, a BST deve ser uma arvore completa.
// Uma arvore completa com n nos tem altura menor ou igual a log_2(n+1).
void construirBST_balanceada(BST *t, int A[], int p, int q) {
    if (p == q){
        t->add(A[p]);
        return;
    }
    int meio = (p+q)/2;
    t->add(A[meio]);
	if (p <= meio-1){construirBST_balanceada(t, A, p, meio-1);}
    if (meio+1 <=q){construirBST_balanceada(t, A, meio+1, q);}
	return;
}

int main()
{
	BST arv;
	string skeys;
	vector<int> vec;
	int value;

	getline(cin, skeys); // read a string containing all keys separated by spaces

	stringstream ss { skeys };
	
	while(ss >> value) 
		vec.push_back(value);

	int n = vec.size();
	int A[MAX];

	for(int i = 0; i < n; i++) 
		A[i] = vec[i];
	
	construirBST_balanceada(&arv, A, 0, n-1);

	cout << "height: " << arv.height() << endl;
	arv.bshow();

	return 0;
}