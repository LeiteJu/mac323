#ifndef _LD_H_
#define _LD_H_

#include <bits/stdc++.h>
using namespace std;

/***** cel_LD *****/

template<class Chave, class Item>
class cel_LD {

    private:

        Chave chave;
        Item valor;

        cel_LD<Chave, Item>* prox;
        cel_LD<Chave, Item>* ant;
    
    public:

        cel_LD();
        void setChave (Chave chave);
        void setValor (Item valor);
        Chave getChave ();
        Item getValor ();

        void setAnt (cel_LD<Chave,Item>* anterior);
        void setProx (cel_LD<Chave,Item>* next);
        cel_LD<Chave,Item>* getProx ();
        cel_LD<Chave,Item>* getAnt ();

};
/***** LD *****/

template<class Chave, class Item>
class LD {

    private:

        // cabeça da lista
        cel_LD<Chave,Item>* head;

    public:

        LD (string nome);
        ~LD();
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        void remove (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void show ();
        void leArquivo (string nome);
};

#endif 

/***** implementação cel_LD  *****/

// cel_LD()
template<class Chave, class Item>
cel_LD<Chave, Item>::cel_LD() {
    this->valor = 0;
    this->prox = this->ant = nullptr;
}

// setChave()
template<class Chave, class Item>
void cel_LD<Chave,Item>::setChave(Chave chave) {
    this->chave = chave;
}

// getChave()
template<class Chave, class Item>
Chave cel_LD<Chave,Item>::getChave() {
    return this->chave;
}

// setValor()
template<class Chave, class Item>
void cel_LD<Chave,Item>::setValor(Item valor) {
    this->valor += valor;
}

// getValor()
template<class Chave, class Item>
Item cel_LD<Chave,Item>::getValor () {
    return this->valor;
}

// setProx()
template<class Chave, class Item>
void cel_LD<Chave,Item>::setProx(cel_LD<Chave,Item>* next) {
    this->prox = next;
}

// getProx()
template<class Chave, class Item>
cel_LD<Chave,Item>* cel_LD<Chave,Item>::getProx () {
    return this->prox;
}

// setAnt()
template<class Chave, class Item>
void cel_LD<Chave,Item>::setAnt(cel_LD<Chave,Item>* anterior) {
    this->ant = anterior;
}

// getAnt()
template<class Chave, class Item>
cel_LD<Chave,Item>* cel_LD<Chave,Item>::getAnt () {
    return this->ant;
}

/***** implementação LD *****/

// LD()
template<class Chave, class Item>
LD<Chave,Item>::LD(string nome) {

    // criamos a cabeça
    this->head = new cel_LD<Chave, Item>;

    // acertamos os ponteiros
    head->setAnt(nullptr);
    head->setProx(nullptr);

    // lemos o arquivo e adicionamos as palavras na tabela
    leArquivo(nome);

}

// ~LD()
template<class Chave, class Item>
LD<Chave,Item>::~LD() {

    cel_LD<Chave,Item> * aux = this->head->getProx();

    while (aux != nullptr) {

        this->head->setProx(aux->getProx());
        delete aux;
        aux = head->getProx();

    }

    delete head;

}

// insere ()
template<class Chave, class Item>
void LD<Chave,Item>::insere (Chave chave, Item valor) {

    cel_LD<Chave,Item>* aux;
    aux = head;

    // percorremos a tabela
    while (aux->getProx() != nullptr) {

        aux = aux->getProx();

        // se já está na tabela, mudamos o valor
        if (aux->getChave() == chave) {
            aux->setValor(valor);
            return;
        }
        
    }

    // então vamos adicioná-lo
    cel_LD<Chave,Item>* novo = new cel_LD<Chave,Item>;

    // acertando os ponteiros
    aux->setProx(novo);
    novo->setAnt(aux);

    // colocando a chave e valor
    novo->setChave(chave);
    novo->setValor(valor);

}

// devolve()
template<class Chave, class Item>
Item LD<Chave,Item>::devolve (Chave chave) {

    cel_LD<Chave,Item>* aux = head->getProx();

    while (aux != nullptr) {

        // Achamos
        if (aux->getChave() == chave)
            return aux->getValor();

        aux = aux->getProx();
    }

    // se não está na tabela
    return 0;

}

// remove
template<class Chave, class Item>
void LD<Chave,Item>::remove(Chave chave) {

    cel_LD<Chave,Item>* aux = this->head;

    // percorremos a tabela
    while (aux->getProx() != nullptr) {

        aux = aux->getProx();

        // se achamos, removemos
        if (aux->getChave() == chave) {
            aux->getAnt()->setProx(aux->getProx());
            if (aux->getProx() != nullptr)
                aux->getProx()->setAnt(aux->getAnt());
            delete aux;
            return;
        }

    }

}

// show()
template<class Chave, class Item>
void LD<Chave,Item>::show() {

    cel_LD<Chave,Item>* aux = head->getProx();

    cout << "Mostrando a tabela\n";

    while (aux != nullptr) {
        cout << "Ranking: " << this->rank(aux->getChave()) << " Palavra: " << aux->getChave() << "\tOcorrencias " << aux->getValor() << endl;
        aux = aux->getProx();
    }
    cout << endl;
}

// rank
template<class Chave, class Item>
int LD<Chave,Item>::rank(Chave chave) {

    int menores = 0;
    cel_LD<Chave,Item>* aux = head->getProx();
    bool tab = false;

    while (aux != nullptr) {

        // somamos as chaves menores
        if (aux->getChave() < chave) 
            menores++;
        
        else if (aux->getChave() == chave)
            tab = true;

        aux = aux->getProx();
    }

    return (tab) ? (menores) : (-1);

}

// seleciona
template<class Chave, class Item>
Chave LD<Chave,Item>::seleciona (int k) {

    cel_LD<Chave,Item>* aux = head->getProx();

    // percorremos a tabela
    while (aux != nullptr) {

        // se é a k-ésima chave, devolvemos
        if (this->rank(aux->getChave()) == k)
            return aux->getChave();

        aux = aux->getProx();

    }

    // então não temos um k-ésimo termo
    return "";
}

template<class Chave, class Item>
void LD<Chave,Item>::leArquivo (string nome) {

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