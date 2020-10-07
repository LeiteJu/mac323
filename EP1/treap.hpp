#ifndef _TREAP_H_
#define _TREAP_H_

#include <bits/stdc++.h>
using namespace std;

#define MAX_TR 10169

// No_TR
template<class Chave, class Item>
class No_TR {

    private:

        Chave chave;
        Item valor;
        int prior;

    public:

        No_TR<Chave,Item>* esq;
        No_TR<Chave,Item>* dir;
        No_TR<Chave,Item>* pai;

        No_TR();
        Chave getChave ();
        void setChave (Chave chave);
        Item getValor ();
        void setValor (Item valor);
        int getPriority ();

};

template<class Chave, class Item>
class TR {

    private:

        No_TR<Chave,Item>* raiz;

        No_TR<Chave,Item>* rotDir (No_TR<Chave,Item>* root);
        No_TR<Chave,Item>* rotEsq (No_TR<Chave,Item>* root);
        No_TR<Chave,Item>* put (No_TR<Chave,Item>* root, Chave ch, Item val);
        void del_TR (No_TR<Chave,Item>* root);
        Item get (No_TR<Chave,Item>* root, Chave ch);
        int soma (No_TR<Chave,Item>* root, Chave ch);
        void leArquivo (string nome);
        No_TR<Chave,Item>* del (No_TR<Chave,Item>* root, Chave ch);

    public:

        TR (string nome);
        ~TR ();
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void remove (Chave chave);
        void show (No_TR<Chave,Item>* root);
        No_TR<Chave,Item>* getRaiz ();
        

};

#endif

/***** NO_TR *****/

// No_TR ()
template<class Chave, class Item>
No_TR<Chave,Item>::No_TR() {
	this->valor = 0;
    this->prior = rand() % MAX_TR;
	this->dir = this->esq = this->pai = nullptr;
}

// setChave()
template <class Chave, class Item>
void No_TR<Chave,Item>::setChave (Chave chave) {
	this->chave = chave;
}

// getChave()
template <class Chave, class Item>
Chave No_TR<Chave,Item>::getChave() {
	return this->chave;
}

// setValor()
template <class Chave, class Item>
void No_TR<Chave,Item>::setValor (Item valor) {
	this->valor += valor;
}

// getValor()
template <class Chave, class Item>
Item No_TR<Chave,Item>::getValor() {
	return this->valor;
}

// getPriority()
template <class Chave, class Item>
int No_TR<Chave,Item>::getPriority (){
    return this->prior;
}

/***** TREAP *****/
template <class Chave, class Item>
TR<Chave,Item>::TR (string nome) {

    this->raiz = nullptr;
    leArquivo(nome);
}

template <class Chave, class Item>
TR<Chave,Item>::~TR () {
    this->del_TR (this->raiz);
}

template<class Chave, class Item>
void TR<Chave,Item>::insere (Chave chave, Item valor) {
    this->raiz = put (this->raiz, chave, valor);
}

template<class Chave, class Item>
No_TR<Chave,Item>* TR<Chave,Item>::put (No_TR<Chave,Item>* root, Chave ch, Item val) {

    if (root == nullptr) {
        root = new No_TR <Chave,Item>;
        root->setChave (ch);
        root->setValor (val);
        root->dir = root->esq = root->pai = nullptr;
        return root;
    }

    if (ch == root->getChave ()) {
        root->setValor (val);
        return root;
    }

    if (ch < root->getChave()) {
        root->esq = put (root->esq, ch, val);
        if (root->esq->getPriority() > root->getPriority())
            root = rotDir (root);
        return root;
    }

    // então ch > root->getChave()
    root->dir = put (root->dir, ch, val);
    if (root->dir->getPriority() > root->getPriority())
        root = rotEsq (root);
    return root;

}

// devolve ()
template<class Chave, class Item>
Item TR<Chave,Item>::devolve (Chave chave) {
	return get (this->raiz, chave);
}

// acionada recursivamente pelo devolve
template<class Chave, class Item>
Item TR<Chave,Item>::get (No_TR<Chave,Item>* root, Chave chave) {

	if (root == nullptr)
		return 0;
	if (root->getChave() == chave)
		return root->getValor();
	if (chave < root->getChave())
		return get (root->esq, chave);
	return get (root->dir, chave);
}

// rotDir ()
template <class Chave, class Item>
No_TR<Chave,Item>* TR<Chave,Item>::rotDir (No_TR<Chave,Item>* root) {

    No_TR<Chave,Item>* newRoot = root->esq;
    // acertamos os ponteiros
    if (newRoot->dir != nullptr)
        newRoot->dir->pai = root;
    newRoot->pai = root->pai;
    root->pai = newRoot;

    root->esq = newRoot->dir;
    newRoot->dir = root;
    
    return newRoot; // retornamos a nova raiz
}

// rotEsq()
template<class Chave, class Item>
No_TR<Chave,Item>* TR<Chave,Item>::rotEsq (No_TR<Chave,Item>* root) {

    No_TR<Chave,Item>* newRoot = root->dir;
    // acertamos os ponteiros
    if (newRoot->esq != nullptr)
        newRoot->esq->pai = root;
    newRoot->pai = root->pai;
    root->pai = newRoot;
    root->dir = newRoot->esq;
    newRoot->esq = root;
    // retornamos a nova raiz
    return newRoot;
}

template<class Chave, class Item>
void TR<Chave,Item>::remove (Chave chave) {
    this->raiz = del (this->raiz, chave);
}

// del()
template<class Chave, class Item>
No_TR<Chave,Item>* TR<Chave,Item>::del (No_TR<Chave,Item>* root, Chave ch) {

    if (root == nullptr)
        return nullptr;
    
    // (1) a chave é menor
    if (ch < root->getChave()) {
        root->esq = del (root->esq, ch);
        return root;
    }
    // (2) a chave é maior
    if (ch > root->getChave()) {
        root->dir = del (root->dir, ch);
        return root;
    }  
    // (3) achamos
    No_TR<Chave,Item>* newRoot;
    // (a) e (b): tem apenas um filho
    if (root->esq == nullptr || root->dir == nullptr) {
        newRoot = (root->esq == nullptr) ? (root->dir) : (root->esq);
        if (newRoot != nullptr)
            newRoot->pai = root->pai;
        delete root;
        return newRoot;
    }
    // (c): tem os dois filhos
    if (root->esq->getPriority() < root->dir->getPriority()) {
        root = rotEsq (root);
        root->esq = del (root->esq, ch);
        return root;
    }
    root = rotDir (root);
    root->dir = del (root->dir, ch);
    return root;
}

// seleciona ()
template<class Chave, class Item>
Chave TR<Chave,Item>::seleciona (int k) {

    No_TR<Chave, Item>* aux = this->raiz;

    while (aux != nullptr) {
        int r = rank(aux->getChave());
        if (r == k)
            return aux->getChave();
        if (r < k)
            aux = aux->dir;
        else
            aux = aux->esq;
    }

    return "";

}

// rank ()
template<class Chave, class Item>
int TR<Chave,Item>::rank (Chave chave) {

	if (this->devolve(chave) == 0)
		return -1;
	return soma (this->raiz,chave);

}

// soma ()
template<class Chave, class Item>
int TR<Chave,Item>::soma (No_TR<Chave,Item>* root, Chave ch) {

	if (root == nullptr)
		return 0;

	if (ch <= root->getChave())
		return soma (root->esq,ch);

	// chave > root->chave
	return 1 + soma (root->esq, ch) + soma (root->dir, ch);	

}

template<class Chave, class Item>
void TR<Chave,Item>::show (No_TR<Chave,Item>* root) {
	
	if (root == nullptr)
		return;
	this->show (root->esq);
	cout << "\tPalavra: " << root->getChave() << "\tOcorrencias: " << root->getValor() << endl;
	this->show (root->dir);

}

// devolve a raiz
template<class Chave, class Item>
No_TR<Chave,Item>* TR<Chave,Item>::getRaiz() {
	return this->raiz;
}

// del ()
template<class Chave, class Item>
void TR<Chave,Item>::del_TR (No_TR<Chave,Item>* root) {

	if (root == nullptr)
		return;
	del_TR(root->esq);
	del_TR (root->dir);
	delete root;
}

// leArquivo
template<class Chave, class Item>
void TR<Chave,Item>::leArquivo (string nome) {

    string palavra;
    string linha;
    fstream arquivo;
    arquivo.open(nome);

    // se não foi possível abrir o arquivo
    if (arquivo.fail()) {
        cout << "Não foi possível abrir o arquivo!\n";
        exit(1); 
    }

    while (getline(arquivo,linha)) {
        stringstream s(linha);
        while (s >> palavra) {
            this->insere(palavra, 1);
        }
    }

    arquivo.close();
}