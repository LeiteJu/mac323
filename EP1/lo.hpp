#ifndef _LO_H_
#define _LO_H_

#include <bits/stdc++.h>
using namespace std;

template<class Chave, class Item>
class cel_LO {

    private:

        Chave chave;
        Item valor;
 
        cel_LO<Chave, Item>* prox;
        cel_LO<Chave, Item>* ant;
    
    public:

        int rank;

        cel_LO();
        void setChave (Chave chave);
        void setValor (Item valor);
        Chave getChave ();
        Item getValor ();

        void setProx (cel_LO<Chave,Item>* next);
        cel_LO<Chave,Item>* getProx ();
        void setAnt (cel_LO<Chave,Item>* anterior);
        cel_LO<Chave,Item>* getAnt ();

};

template<class Chave, class Item>
class LO {

    private:

        // cabeça da lista
        cel_LO<Chave,Item>* head;

    public:

        LO(string nome);
        ~LO();
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        void remove (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void show ();
        void leArquivo (string nome);
};

#endif

/***** implementação cel_LO  *****/

// cel_LO()
template<class Chave, class Item>
cel_LO<Chave, Item>::cel_LO() {
    this->valor = 0;
    this->rank = 0;
    this->prox = this->ant = nullptr;
}

// setChave()
template<class Chave, class Item>
void cel_LO<Chave,Item>::setChave(Chave chave) {
    this->chave = chave;
}

// getChave()
template<class Chave, class Item>
Chave cel_LO<Chave,Item>::getChave() {
    return this->chave;
}

// setValor()
template<class Chave, class Item>
void cel_LO<Chave,Item>::setValor(Item valor) {
    this->valor += valor;
}

// getValor()
template<class Chave, class Item>
Item cel_LO<Chave,Item>::getValor () {
    return this->valor;
}

// setProx()
template<class Chave, class Item>
void cel_LO<Chave,Item>::setProx(cel_LO<Chave,Item>* next) {
    this->prox = next;
}

// getProx()
template<class Chave, class Item>
cel_LO<Chave,Item>* cel_LO<Chave,Item>::getProx () {
    return this->prox;
}

// setAnt()
template<class Chave, class Item>
void cel_LO<Chave,Item>::setAnt(cel_LO<Chave,Item>* anterior) {
    this->ant = anterior;
}

// getAnt()
template<class Chave, class Item>
cel_LO<Chave,Item>* cel_LO<Chave,Item>::getAnt () {
    return this->ant;
}

/***** implementação LO *****/

// LO()
template<class Chave, class Item>
LO<Chave,Item>::LO(string nome) {


    // criamos a cabeça
    this->head = new cel_LO<Chave, Item>;

    // acertamos os ponteiros
    head->setAnt(nullptr);
    head->setProx(nullptr);

    // lemos o arquivo e adicionamos as palavras na tabela
    leArquivo(nome);

}

// ~LO()
template<class Chave, class Item>
LO<Chave,Item>::~LO() {

    cel_LO<Chave,Item> * aux = this->head->getProx();

    while (aux != nullptr) {

        this->head->setProx(aux->getProx());
        delete aux;
        aux = head->getProx();

    }
    delete head;

}

// insere()
template<class Chave, class Item>
void LO<Chave,Item>::insere (Chave chave, Item valor) {

    cel_LO<Chave,Item>* aux = head;
    int menores = 0;

    // a celula deve ser inserida após o aux
    while (aux->getProx() != nullptr && aux->getProx()->getChave() <= chave) {

        aux = aux->getProx();
        menores++;

        // se já está na tabela, mudamos o valor
        if (aux->getChave() == chave) {
            aux->setValor(valor);
            return;
        }

    }

    // criamos a celula
    cel_LO<Chave,Item>* novo = new cel_LO<Chave,Item>;
  
    // acertamos os ponteiros
    novo->setProx(aux->getProx());
    novo->setAnt(aux);
    if (aux->getProx() != nullptr)
        aux->getProx()->setAnt(novo);
    aux->setProx(novo); 

    // colocamos a chave e o valor
    novo->setChave(chave);
    novo->setValor(valor);
    novo->rank = menores;

    // atualizamos o rank das outras
    aux = novo->getProx();
    while (aux != nullptr) {
        aux->rank++;
        aux = aux->getProx();
    }

}

// devolve()
template<class Chave, class Item>
Item LO<Chave,Item>::devolve (Chave chave) {

    cel_LO<Chave,Item>* aux = head->getProx();

    // percorremos a tabela
    while (aux != nullptr && aux->getChave() <= chave) {

        // Achamos
        if (aux->getChave() == chave)
            return aux->getValor();

        aux = aux->getProx();
    }

    // se não está na tabela
    return 0;

}

// remove()
template<class Chave, class Item>
void LO<Chave,Item>::remove (Chave chave) {

    cel_LO<Chave,Item>* aux = this->head->getProx();
    bool rem = false;

    // percorremos a tabela
    while (aux != nullptr) {

        // atualizamos o rank dos que sobraram
        if (rem) {
            aux->rank--;
        }

        // se achamos, removemos
        if (aux->getChave() == chave) {

            rem = true;
            cel_LO<Chave,Item>* lixo = aux;

            aux = aux->getAnt();
            
            lixo->getAnt()->setProx(lixo->getProx());
            if (lixo->getProx() != nullptr)
                lixo->getProx()->setAnt(lixo->getAnt());
            delete lixo;
        }

        // se passou e não removemos ninguém, ele não está na tabela
        if (aux->getChave() > chave && !rem)
            break;

        aux = aux->getProx();
    }

}

// show()
template<class Chave, class Item>
void LO<Chave,Item>::show() {

    cel_LO<Chave,Item>* aux = head->getProx();

    cout << "Mostrando a tabela\n";

    while (aux != nullptr) {
        cout << "Ranking: "<< aux->rank << " Palavra: " << aux->getChave() << "\tOcorrencias " << aux->getValor() << endl;
        aux = aux->getProx();
    }
    cout << endl;
}

// rank()
template<class Chave, class Item>
int LO<Chave,Item>::rank (Chave chave) {

    cel_LO<Chave,Item>* aux = head->getProx();

    // percorremos a tabela
    while (aux != nullptr && aux->getChave() <= chave) {

        // se achamos, devolvemos o rank
        if (aux->getChave() == chave)
            return aux->rank;

        aux = aux->getProx();

    }

    // se não está na tabela
    return -1;

}

// seleciona()
template<class Chave, class Item>
Chave LO<Chave,Item>::seleciona(int k) {
    
    cel_LO<Chave,Item>* aux = head->getProx(); 

    // percorremos a tabela
    while (aux != nullptr && aux->rank <= k) {

        // se achamos, retornamos
        if (k == aux->rank)
            return aux->getChave();

        aux = aux->getProx();

    }

    // então não temos um k-ésimo termo, devolvemos uma string vazia
    return "";
}

template<class Chave, class Item>
void LO<Chave,Item>::leArquivo (string nome) {

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