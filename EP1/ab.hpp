#ifndef _AB_H_
#define _AB_H_

#include <bits/stdc++.h>
using namespace std;

/***** NO *****/
template<class Chave, class Item>
class No {

    private:

        Chave chave;
        Item valor;
    
    public:

		No<Chave,Item>* dir;
		No<Chave,Item>* esq;

        No();
        void setChave(Chave chave);
        Chave getChave();
        void setValor (Item valor);
		Item getValor ();

};

template <class Chave, class Item>
class ABB {

	private:

		No<Chave,Item>* raiz;
		No<Chave,Item>* put (No<Chave,Item>* root, Chave chave, Item valor);
		Item get (No<Chave,Item>* root, Chave chave);
		No<Chave,Item>* del (No<Chave,Item>* root, Chave chave);
		int soma (No<Chave,Item>* root, Chave chave);
		void delABB (No<Chave,Item>* root);

	public:

		No<Chave,Item>* getRaiz ();
		ABB(string nome);		
		~ABB();
		void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        void remove (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
		void show (No<Chave,Item>* root);
		void leArquivo (string nome);

};

#endif

// No ()
template<class Chave, class Item>
No<Chave,Item>::No() {
	this->valor = 0;
	this->dir = this->esq = nullptr;
}

// setChave()
template <class Chave, class Item>
void No<Chave,Item>::setChave (Chave chave) {
	this->chave = chave;
}

// getChave()
template <class Chave, class Item>
Chave No<Chave,Item>::getChave() {
	return this->chave;
}

// setValor()
template <class Chave, class Item>
void No<Chave,Item>::setValor (Item valor) {
	this->valor += valor;
}

// getValor()
template <class Chave, class Item>
Item No<Chave,Item>::getValor() {
	return this->valor;
}

/***** ABB *****/

// ABB()
template <class Chave, class Item>
ABB<Chave,Item>::ABB(string nome) {

	this->raiz = nullptr;
	leArquivo(nome);

}

// insere()
template<class Chave, class Item>
void ABB<Chave,Item>::insere(Chave chave, Item valor) {
	//chama a recursiva
	this->raiz = put ( raiz, chave, valor);

}

// put ()
// adiciona recursivamente e devolve a raiz
template<class Chave, class Item>
No<Chave,Item>* ABB<Chave,Item>::put(No<Chave,Item>* root, Chave chave, Item valor) {

	if (root == nullptr) {
		root = new No<Chave,Item>;
		root->setChave(chave);
		root->setValor(valor);
		return root;
	}
	// se a palavra já existe, atualizamos o valor
	if (chave == root->getChave()) {
		root->setValor(valor);
		return root;
	}
	if (chave < root->getChave()) {
		root->esq = put (root->esq, chave, valor);
		return root;
	}
	//
	root->dir = put (root->dir, chave, valor);
	return root;
}

// show()
template<class Chave, class Item>
void ABB<Chave,Item>::show (No<Chave,Item>* root) {
	
	if (root == nullptr)
		return;

	this->show (root->esq);

	cout << "Nº: " << this->rank(root->getChave()) << "\tPalavra: " << root->getChave() << "\tOcorrencias: " << root->getValor() << endl;

	this->show (root->dir);

}

// devolve a raiz
template<class Chave, class Item>
No<Chave,Item>* ABB<Chave,Item>::getRaiz() {
	return this->raiz;
}

// delABB()
template<class Chave, class Item>
void ABB<Chave,Item>::delABB (No<Chave,Item>* root) {

	if (root == nullptr)
		return;

	delABB (root->esq);
	delABB (root->dir);

	delete root;

}

// ~ABB()
template<class Chave, class Item>
ABB<Chave,Item>::~ABB() {
	delABB(raiz);
}

// devolve ()
template<class Chave, class Item>
Item ABB<Chave,Item>::devolve (Chave chave) {
	return get (this->raiz, chave);
}

// get()
template<class Chave, class Item>
Item ABB<Chave,Item>::get (No<Chave,Item>* root, Chave chave) {

	if (root == nullptr)
		return 0;

	if (root->getChave() == chave)
		return root->getValor();

	if (chave < root->getChave())
		return get (root->esq, chave);
	
	return get (root->dir, chave);
}

// remove()
template<class Chave, class Item>
void ABB<Chave,Item>::remove (Chave chave) {
	this->raiz = del (this->raiz, chave);

}

// del()
template<class Chave, class Item>
No<Chave,Item>* ABB<Chave,Item>::del (No<Chave,Item>* root, Chave chave) {

	if (root == nullptr)
		return nullptr;

	if (chave < root->getChave()) {
		root->esq = del (root->esq, chave);
		return root;
	}

	if (chave > root->getChave()) {
		root->dir = del (root->dir, chave);
		return root;
	}
	// então achamos a palavra
	if (root->esq == nullptr) {
		No<Chave,Item>* aux = root->dir;
		delete root;
		return aux;
	}
	if (root->dir == nullptr) {
		No<Chave,Item>* aux = root->esq;
		delete root;
		return aux;
	}

	// queremos que aux seja o último filho da subárvore esquerda
	No<Chave,Item>* aux = root->esq;
	No<Chave,Item>* ant = root;

	while (aux->dir != nullptr) {
		ant = aux;
		aux = aux->dir;
	}

	if (ant != root) {
		ant->dir = aux->esq;
		aux->esq = root->esq;
	}

	aux->dir = root->dir;
	delete root;
	return aux;

}

// rank ()
template<class Chave, class Item>
int ABB<Chave,Item>::rank (Chave chave) {

	if (this->devolve(chave) == 0)
		return -1;
	return soma (this->raiz,chave);

}

// soma ()
template<class Chave, class Item>
int ABB<Chave,Item>::soma (No<Chave,Item>* root, Chave chave) {

	if (root == nullptr)
		return 0;

	if (chave <= root->getChave())
		return soma (root->esq,chave);

	// chave > root->chave
	return 1 + soma (root->esq, chave) + soma (root->dir, chave);	

}

// seleciona ()
template<class Chave, class Item>
Chave ABB<Chave,Item>::seleciona (int k) {

	No<Chave,Item>* aux = raiz;
	int atual = -1;

	while (aux != nullptr && atual != k) {

		atual = this->rank(aux->getChave());
		if (atual < k)
			aux = aux->dir;
		else if (atual > k)
			aux = aux->esq;
	}

	return (aux == nullptr) ? ("") : (aux->getChave());
}

// leArquivo
template<class Chave, class Item>
void ABB<Chave,Item>::leArquivo (string nome) {

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