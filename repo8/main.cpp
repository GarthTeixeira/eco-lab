// NOME:Gabriel Arthur Teixeira Perpetuo, Arthur Luiz  
#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <queue>
#include <cmath>

#include "Tree.h"


using namespace std;

int main() {

	Tree<int> A(5);
	A.insere(4);
	A.insere(8);
	A.insere(6);
	A.insere(10);
	A.insere(2);
	A.insere(3);
	A.insere(-1);
	A.insere(-2);

	A.alturaTree();
	system("pause");
	return 0;
}
