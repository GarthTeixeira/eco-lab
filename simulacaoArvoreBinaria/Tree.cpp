
#include"Tree.h"

using namespace std;

template <class T> Tree<T>::Tree()
{
	raiz=NULL;
	std::ostringstream address;
	address << (void const *)this;
	id = address.str();
}

template <class T> Tree<T>::Tree(T info)
{
	raiz=new Node<T>(info);
	std::ostringstream address;
	address << (void const *)this;
	id = address.str();
}

template <typename T>
Tree<T>::~Tree()
{
	cout<<"\n Destroing Tree "<<endl;
	delete raiz;
	raiz=NULL;
}

template<typename T>
void Tree<T>::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}


template<typename T>
double Tree<T>::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


template <typename T>
void Tree<T>::insere(const T c) {
    insere(raiz,c);
	
	node_quant++;
 }

template <typename T>
void Tree<T>::insere(Node<T>*&a,const T c) {

	if(a==NULL){
	a=new Node<T>(c);
	return;
	}

	if (c == a->info)
	{
		cout << "\n elemento ja pressente na Tree \n";
		return;
	}
	if (c > a->info) {					// INSERINDO NO RAMO DIREITO
		if (a->dir == NULL)
		{ 
			a->dir = new Node<T>(c);			
		}
		else insere(a->dir,c);		
	}
	else {
		if (a->esq == NULL)				// INSERINDO NO RAMO ESQUERDO
		{
			a->esq = new Node<T>(c);
		}
		else insere(a->esq,c);	
	}
}

template<typename T>
void Tree<T>::computa(const T vetor ) {

	StartCounter();
	insere(raiz,vetor);
	cout <<"Inserction Time: "<< vetor <<": "<< GetCounter() << "seconds" << endl;

}


template<typename T>
Node<T>* Tree<T>::pesquisa(const T elemento)
{
	return pesquisa(raiz,elemento);
}


template<typename T>
Node<T>* Tree<T>::pesquisa(Node<T>*&a,const T elemento) {

	if (a != NULL) {
		if (elemento > a->info)
			return pesquisa(a->dir, elemento);
		else if (elemento <a->info)
			return pesquisa(a->esq, elemento);
		else if (elemento == a->info)
		{
			cout << "\n No retornado: " << endl;
			cout << "    " << a->info << "  " << endl;
			cout << "   / \\   " << endl;
			if (a->esq == NULL)
				cout << "NULL";
			else
				cout << "  " << a->esq->info;
			
			cout << "  ";

			if (a->dir == NULL)
				cout << "NULL";
			else
				cout << a->dir->info;
			cout << endl;

			return a;
		}
	}
	else
	{
		cout << "No " << elemento << " n foi encontrado";
	}
	return a;
}



template <typename T>
void Tree<T>::Grau(T elemento){

        Grau(raiz,elemento);

}

template <typename T>
void Tree<T>::Grau(Node<T>* a,T elemento) {

	int grau;
	if ( a != NULL) {
		Grau(a->esq,elemento);
		Grau(a->dir,elemento);

		if (elemento == a->info) {
			if (a->esq == NULL && a->dir == NULL)
				grau = 0;
			if (a->esq != NULL && a->dir == NULL)
				grau = 1;
			if (a->esq == NULL && a->dir != NULL)
				grau = 1;
			if (a->esq != NULL && a->dir != NULL)
				grau = 2;
			cout << "\n grau do no " << elemento << ':' << grau << endl;
		}
	}
	
}


/*template <typename T>
int Tree<T>::Nivel(T elemento) {

	int cont = nivel;

	if (this != NULL) {
		if (this->info != elemento) {
			cont++;
			this->esq->Nivel(elemento);
			this->dir->Nivel(elemento);
		}
		if (this->info == elemento)
			cout << "\n nivel do no: " << elemento << ':' << nivel << endl;
	}
	return cont;
}*/


template <typename T>
 void Tree<T>::maiormenor(){
	maiormenor(raiz->esq);
 }

template <typename T>
 void Tree<T>::maiormenor(Node<T> *a){
	if (a->dir != NULL)
		return maiormenor(a->dir);
	else
	{
		cout<<"\nThe Gratest of lessers: "<< a->info;
	}
 }

template <typename T>
 void Tree<T>::menormaior(){
	menormaior(raiz->dir);
 }

template <typename T>
 void Tree<T>::menormaior(Node<T> *a){
	if (a->esq != NULL)
		return menormaior(a->esq);
	else
	{
		cout<<"\nThe Smalest of Graters: "<< a->info;
	}
 }


template <typename T>
 Node<T>* Tree<T>::maxdir(Node<T> *&a)
{
	 if (a->dir != NULL)
		 return maxdir(a->dir);
	else
	{
		Node<T> *aux = a;
		if (a->esq != NULL)
			a = a->esq;
		else
			a = NULL;
		return aux;
	}

}

 template <typename T>
 void Tree<T>::removeNo( T elemento) {
	removeNo(raiz, elemento);
	node_quant--;
 }

template <typename T>
void Tree<T>::removeNo(Node<T> *&a, T elemento) {

	Node<T> *aux;

	if (a != NULL) {

		if (elemento >a-> info)
		{
			removeNo(a->dir, elemento);
		}
		else if (elemento < a->info)
		{
			removeNo(a->esq, elemento);	
		}
		else
		{
			if (a->esq == NULL && a->dir == NULL)
			{
				aux = a;
				delete aux;
				a = NULL;
			}
			else if (a->dir == NULL)
			{
				aux = a;
				a = a->esq;
				delete aux;
			} 
			else if (a->esq == NULL)
			{
				aux = a;
				a = a->dir;
				delete aux;
			}
			else
			{
				
				aux = maxdir(a->esq);
				T i = a->info;
				a->info = aux->info;
				aux->info=i;
				delete aux;
			}
		}
	}
}


template<typename T>
void Tree<T>::largura(){

	queue<Node<T>*> nivelActual, nivelSeguinte;
	nivelActual.push(raiz);

	while (!nivelActual.empty()) {
		Node<T>* n = nivelActual.front();
		nivelActual.pop();

		if (n) {
			cout << n->info << " ";
			nivelSeguinte.push(n->esq);
			nivelSeguinte.push(n->dir);
		}
		if (nivelActual.empty()) {
			cout << endl;
			swap(nivelActual, nivelSeguinte);
		}
	}
	cout << endl;
}

template <typename T>
void Tree<T>::ordem() {ordem(raiz);cout << endl;}

template <typename T>
void Tree<T>::ordem(Node<T>*a) { // CAMINHAMENTO EM ORDEM

	if (a->esq != NULL)
		ordem(a->esq);
	cout << "| " << a->info << " |";
	if (a->dir != NULL)
		ordem(a->dir);
}

template <typename T>
void Tree<T>::pre_ordem() {pre_ordem(raiz);cout << endl;}

template <typename T>
void Tree<T>::pre_ordem(Node<T>*a) { // CAMINHAMENTO EM ORDEM

	cout << "| " << a->info << " |";
if (a->esq != NULL)
		pre_ordem(a->esq);
	if (a->dir != NULL)
		pre_ordem(a->dir);
}



template <typename T>
void Tree<T>::pos_ordem() {pos_ordem(raiz);cout << endl;}
template <typename T>

void Tree<T>::pos_ordem(Node<T>*a) { // CAMINHAMENTO EM ORDEM

	if (a->esq != NULL)
		pos_ordem(a->esq);

	if (a->dir != NULL)
		pos_ordem(a->dir);

	cout << "| " << a->info << " |";

}

template <typename T>
void Tree<T>::mostra() {
mostra(raiz,0); 
}

template <typename T>
void Tree<T>::mostra(int n) {
cout<<'\n';	
mostra(raiz,n); 
cout<<'\n';	
}
template <typename T>
void Tree<T>::mostra(Node<T>*a,int n) {

	if(a){
	int i;
		mostra(a->esq,n+1);
	for (i = 0; i < n; i++) cout << "   ";
	cout <<'<'<< a->info<<'>'<<endl;
		mostra(a->dir,n+1);
	}
}

template <class T>
void Tree<T>::BalanceiaDSW(){
		int n=alturaTree(raiz);
		int m=pow(2,(int)log2(n+1))-1;

		rotacionarEsquerda(raiz);
		Node<T>* temp=raiz;
		for(int i=0;i<n-m-1; i++)
		{ 
		rotacionarEsquerda(temp->dir);
		temp=temp->dir;
		}
		while(m>1){
			m=m/2;
			rotacionarEsquerda(raiz);
			temp=raiz;
			for(int j=0;j<m-1;j++){ 
			rotacionarEsquerda(temp->dir);
			temp=temp->dir;}
		}
}

template <class T>
void Tree<T>::BreakBone(){
	 BreakBone(raiz);
	 mostra(raiz,alturaTree(raiz));
	 }


template <class T>
void Tree<T>::BreakBone(Node<T>*& atual){
	Node<T>*aux;
	if (atual != NULL){
		while (atual -> esq  != NULL){
		    if (atual -> esq -> dir == NULL){
			atual -> esq -> dir = atual;
			aux = atual -> esq;
			atual -> esq = NULL;
			atual=aux;
			}
	else
		{
		aux = atual -> esq;
		atual -> esq = atual -> esq -> dir;
		aux -> dir = atual;
		atual = aux;
		}
		}
		BreakBone (atual ->dir);
	}  }


	template <class T>
	void Tree<T>::rotacionarDireita(Node<T> *&p) {

        if (p != NULL) {
            Node<T>* tmp = p;
            if ((p->esq) != NULL) {
                p = p->esq;
            }
            if ((p->dir) != NULL) {
                tmp->esq = p->dir;
            } else
                tmp ->esq = NULL;
            p->dir = tmp;
        }
    }
	
	template <class T>
	 void Tree<T>:: rotacionarEsquerda(Node<T> *&p) {

        if (p != NULL) {
            Node<T>* tmp = p;
            if ((p->dir) != NULL) {
                p = p->dir;
            }
            if ((p->esq) != NULL) {
                tmp->dir = p->esq;
            }
            else
                tmp->dir = NULL;
            p->esq = tmp;
        }
    }


	template <class T>
	int  Tree<T>:: alturaTree ()
	{ 
		cout << "\n Atlura da Tree :"<< alturaTree(raiz)<<endl;
	return alturaTree (raiz);

	}
	template <class T>
	int  Tree<T>::alturaTree (Node<T> *atual)
    {
		if (atual == NULL)
            return 0;
		else{ 
		
		int nivel_e= alturaTree(atual->esq);
		
		int nivel_d= alturaTree(atual->dir);

		return (nivel_e>nivel_d)?nivel_e+1:nivel_d+1; 
		}
    }


	template <class T>
	void Tree<T> ::vetor() {
        vector<Node<T>*> v = vetor(raiz);
        cout << "iv" << endl;
        for (int i = 0; i < v.size(); i++)
            cout << v.at(i)->info << " ";
        cout << endl;
    }

	template <class T>
    vector<Node<T>> Tree<T>:: vetor(Node<T> *p) {
        vector<Node<T>> v, e;

        if (p != NULL) {
            e = vetor(p->esq);
            for (int i = 0; i < e.size(); i++)
                v.push_back(e[i]);
            e.clear();
            v.push_back(p->info);
            e = vetor(p->dir);
            for (int i = 0; i < e.size(); i++)
                v.push_back(e[i]);
            e.clear();
        }
        return v;
    }

	template <class T>
	void Tree<T>::VetorOrdenado(vector<Node<T>> dados, int primeiro, int ultimo, Node<T> *&p){
	cout<<dados.at(0).info;
	if(primeiro <= ultimo) {
	int meio = (primeiro + ultimo)/2;
	insere(p,dados.at(meio).info);
	VetorOrdenado(dados, primeiro, meio-1, p);
	VetorOrdenado(dados, meio+1, ultimo, p);
	}
	}
	template<class T>
	void Tree<T>::BalanceiaVO(){
		vector<Node<T>> v=vetor(raiz);
		delete raiz;
		
		cout<<v.at(0).info;
		raiz=NULL;
		VetorOrdenado(v, 0, v.size()-1, raiz);
	}
	template <class T>
	void Tree<T> ::DSW(){
		 BreakBone(raiz);
		 BalanceiaDSW();
	}

