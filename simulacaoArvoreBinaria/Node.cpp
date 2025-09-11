#include "Tree.h"

using namespace std;

template<class T>
Node<T>::Node(T c)
{
	info = c;
	dir = NULL;
	esq = NULL;
}

template<class T>
Node<T>::Node()
{
	info = (T)' ';
	dir = NULL;
	esq = NULL;
}

template<class T>
Node<T>::~Node()
{
	cout << "\n Destroing Node : " << info ;
}
