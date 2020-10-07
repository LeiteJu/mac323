#ifndef _HS_H_
#define _HS_H_

#include <bits/stdc++.h>
using namespace std;

#define TAM 7000 // tamanho da tabela
#define PRIMO 41

template <class Chave, class Item>
class cel_HS {

    private:

        Chave chave;
        Item valor;
    
    public:

        bool vazia;
        cel_HS<Chave,Item>* prox;

        cel_HS();
        void setChave (Chave chave);
        Chave getChave ();
        void setValor (Item valor);
        Item getValor ();

};

template<class Chave, class Item>
class HS {

    private:

        cel_HS<Chave,Item> tabela[TAM];
        
        int hash (Chave chave);
        void leArquivo (string nome);
    
    public:

        HS(string nome);
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void remove (Chave chave);
        ~HS();
};

#endif

/***** cel_HS *****/

// cel_HS()
template<class Chave, class Item>
cel_HS<Chave,Item>::cel_HS() {
    this->chave ="";
    this->valor = 0;
    this->vazia = true;
    this->prox = nullptr;
}

// setChave()
template<class Chave, class Item>
void cel_HS<Chave, Item>::setChave (Chave chave) {
    this->chave = chave;
}

template<class Chave, class Item>
Chave cel_HS<Chave,Item>::getChave () {
    return this->chave;
}

template<class Chave, class Item>
void cel_HS<Chave,Item>::setValor (Item valor) {
    this->valor += valor;
}

template<class Chave, class Item>
Item cel_HS<Chave,Item>::getValor () {
    return this->valor;
}

/***** HS *****/

// HS()
template<class Chave, class Item>
HS<Chave,Item>::HS(string nome) {
    this->leArquivo(nome);
}

// insere ()
template<class Chave, class Item>
void HS<Chave,Item>::insere (Chave chave, Item valor) {

    int hs = this->hash (chave);
    cel_HS<Chave,Item> aux;

    aux = this->tabela[hs];

    // se a posição está vazia, inserimos
    if (aux.vazia) {
        tabela[hs].setChave (chave);
        tabela[hs].setValor (valor);
        tabela[hs].vazia = false;
        return;
    }

    // caso contrário verificamos se não está lá
    if (aux.getChave() == chave) {
        tabela[hs].setValor(valor);
        return;
    }

    // vamos verificar a lista ligada
    cel_HS<Chave,Item>* it = aux.prox;
    while (it != nullptr) {
        if (it->getChave() == chave) {
            it->setValor(valor);
            return;
        }
        it = it->prox;
    }
    
    // então não está na tabela ainda
    it = new cel_HS<Chave,Item>;
    it->setChave(chave);
    it->setValor(valor);
    it->prox = aux.prox;
    tabela[hs].prox = it;
}

// hash ()
template<class Chave, class Item>
int HS<Chave,Item>::hash (Chave chave) {
    int l, hs = 0;
    l = chave.length();

    for (int i = 0; i < l; i++) 
        hs = (hs*PRIMO+chave[i])%TAM;
    return (hs < 0) ? (-hs) : (hs);
}

// ~HS
template<class Chave, class Item>
HS<Chave,Item>::~HS() {
    cel_HS<Chave,Item>* aux;
    for (int i = 0; i < TAM; i++) {
        aux = tabela[i].prox;
        while (aux != nullptr) {
            cel_HS<Chave,Item>* del = aux;
            aux = aux->prox;
            delete(del);
        }

    }
}

// devolve()
template<class Chave, class Item>
Item HS<Chave,Item>::devolve (Chave chave) {

    int hs = this->hash(chave); // hash da chave

    if (tabela[hs].getChave() == chave)
        return tabela[hs].getValor();

    cel_HS<Chave, Item>* aux = tabela[hs].prox;
    while (aux != nullptr) {
        if (aux->getChave() == chave)
            return aux->getValor();
        aux = aux->prox;
    }
    return 0;
}

// rank()
template<class Chave, class Item>
int HS<Chave,Item>::rank (Chave chave) {
    // se não está na tabela
    if (this->devolve(chave) == 0)
        return -1;
    
    int menores = 0;
    for (int i = 0; i < TAM; i++) {
        cel_HS<Chave,Item>*aux = tabela[i].prox;
        if (!tabela[i].vazia && tabela[i].getChave() < chave)
            menores++;
        while (aux != nullptr) { // vamos ver os da lista
            if (aux->getChave() < chave)
                menores++;
            aux = aux->prox;
        }
    }
    return menores;
}

// seleciona
template<class Chave, class Item>
Chave HS<Chave,Item>::seleciona (int k) {

    for (int i = 0; i < TAM; i++) {
        if (rank(tabela[i].getChave()) == k)
            return tabela[i].getChave();
        cel_HS<Chave,Item>* aux = tabela[i].prox;
        while (aux != nullptr) {
            if (rank(aux->getChave()) == k)
                return aux->getChave();
            aux = aux->prox;
        }
    }
    return "";
}

template<class Chave, class Item>
void HS<Chave,Item>::remove (Chave chave) {
    
    int hs = this->hash(chave);
    // se a posição está vazia
    if (tabela[hs].vazia)
        return;
    // se está na tabela
    if (tabela[hs].getChave() == chave) {
        tabela[hs].setValor(-tabela[hs].getValor()); // zeramos o valor
        cel_HS<Chave,Item>* aux = tabela[hs].prox;
        if (aux != nullptr) { // passamos o primeiro da lista pra tabela
            this->tabela[hs].setChave (aux->getChave());
            this->tabela[hs].setValor (aux->getValor());
            this->tabela[hs].prox = aux->prox;
            delete aux;
            return;
        }
        else { // se a lista está vazia, a posição fica vazia
            tabela[hs].vazia = true;
            return;
        }
    }
    // Vamos verificar na lista
    cel_HS<Chave,Item>* pt = tabela[hs].prox;
    cel_HS<Chave,Item>* ant = nullptr;
    while (pt != nullptr) {
        if (pt->getChave() == chave) {
            (ant == nullptr) ? (tabela[hs].prox = pt->prox) : (ant->prox = pt->prox);
            delete pt;
            return;
        }
        ant = pt;
        pt = pt->prox;
    }
}


// leArquivo
template<class Chave, class Item>
void HS<Chave,Item>::leArquivo (string nome) {

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