# ifndef Tree_H
# define Tree_H

#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <sstream> //for std::stringstream 



template <class T>
class Node
{
public:
   

	T  info;
	Node<T> *esq;
	Node<T> *dir;
	Node(T);
	Node();
	~Node();
};

#include "Node.cpp" //usado para a utilização de templates 

template <class T>
class Tree{
    private:
        Node<T>* raiz;
	    double PCFreq = 0.0;
	    __int64 CounterStart = 0;

        unsigned int node_quant=1;
        string id;


        void StartCounter();
        double GetCounter();

        Node<T>* pesquisa(Node<T>*&a, const T elemento);
        void insere(Node<T>*&a,T c);
        void Grau(Node<T>* a,T elemento);
        void removeNo(Node<T> *&a,T elemento);

        void rotacionarDireita(Node<T> *&p); 
        void rotacionarEsquerda(Node<T> *&p);
        Node<T>* maxdir(Node<T> *&a);

        void maiormenor(Node<T> *a);
        void menormaior(Node<T> *a);
        void ordem(Node<T>*a);
        void pre_ordem(Node<T>*a);
        void pos_ordem(Node<T>*a);
        void mostra(Node<T>*a,int n);
        void BreakBone(Node<T>*& atual);
        int alturaTree (Node<T> *atual);
        vector<Node<T>> vetor(Node<T> *p);

        
    public:
        
        Tree();
        Tree(T info);
        ~Tree();

        Node<T>* pesquisa(const T elemento);
        void largura();
        void computa(T vetor );
        void insere(T c);
        void Grau(T elemento);
       
        string getID();
        const int getNodeQuant();
        int alturaTree();

        void maiormenor();
        void menormaior();
        void removeNo( T elemento);
        
        void ordem();
        void pre_ordem();
        void pos_ordem();
      
        void mostra();
        void mostra(int n);
        void BalanceiaDSW();
        void BreakBone();
        
        
        
        
        void vetor();
        
        void VetorOrdenado(vector<Node<T>> dados, int primeiro, int ultimo, Node<T> *&p);
        void BalanceiaVO();
        void DSW();
}; 

#include "Tree.cpp"
#endif