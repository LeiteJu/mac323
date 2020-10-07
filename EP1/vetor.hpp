#ifndef _VETOR_H_
#define _VETOR_H_

#include <bits/stdc++.h>
using namespace std;

template<class Chave, class Item>
class cel {

    private:

        Chave chave; // palavra
        Item valor; // ocorrencias

    public:

        cel();
        void setChave (Chave chave);
        Chave getChave ();
        void setValor (Item valor);
        Item getValor ();

};

template <class Chave, class Item>
class VD {

    private:

        int tam; // tamanho da tabela 
        vector<cel<Chave,Item>> vetor;

    public:

        VD (string nome);
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        void remove (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void show ();

};

template <class Chave, class Item>
class VO {

    private:

        int tam; // tamanho da tabela 
        vector<cel<Chave,Item>> vetor;

    public:

        VO (string nome);
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        void remove (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void show ();

};

#endif

/***** cel *****/

// cel()
template<class Chave, class Item>
cel<Chave,Item>::cel():valor(0){}

// setChave() 
template <class Chave, class Item>
void cel<Chave,Item>::setChave (Chave chave) {
    this->chave = chave;
}

// getChave()
template <class Chave, class Item>
Chave cel<Chave,Item>::getChave () {
    return this->chave;
}

// setValor()
template <class Chave, class Item>
void cel<Chave,Item>::setValor(Item valor) {
    this->valor = valor;
}

// getValor ()
template <class Chave, class Item>
Item cel<Chave,Item>::getValor() {
    return this->valor;
}

/***** Vetor Desordenado *****/

// VD ()
template<class Chave, class Item>
VD<Chave, Item>::VD(string nome) {
    
    tam = 0;

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

// insere()
template <class Chave, class Item>
void VD<Chave,Item>::insere (Chave chave, Item valor) {

    int i = 0;

    while (i < tam) {

        if (this->vetor[i].getChave() == chave) {
            this->vetor[i].setValor(vetor[i].getValor() + valor);
            return;
        }

        i++;
    } 

    cel<Chave,Item> aux;
    aux.setChave(chave);
    aux.setValor(valor);

    vetor.push_back(aux);

    this->tam++;
}

template<class Chave, class Item>
void VD<Chave,Item>::show() {

    int i = 0;

    cout << "Mostrando a tabela\n";

    while (i < tam) {

        cel<Chave,Item> aux;
        aux = vetor[i];
        cout <<"Nº: " << this->rank(aux.getChave()) <<" Palavra " << aux.getChave() << "\tOcorrencias " << aux.getValor() << endl;
        i++;

    }

    cout << endl;

}

// devolve()
template<class Chave, class Item>
Item VD<Chave,Item>::devolve(Chave chave) {

    int i = 0;
    while (i < tam) { // percorremos a tabela

        // se achamos, devolvemos
        if (this->vetor[i].getChave() == chave) 
            return this->vetor[i].getValor();

        i++;
    }
    // se não está na tabela
    return 0;
}

// remove()
template<class Chave, class Item>
void VD<Chave,Item>::remove (Chave chave) {

    int i = 0;
    while (i < tam) {

        if (chave == this->vetor[i].getChave()) {
            vetor.erase(vetor.begin()+i);
            tam--;
            return;
        }

        i++;

    }

}

// rank()
template<class Chave, class Item>
int VD<Chave,Item>::rank (Chave chave) {

    int menores = 0, i = 0;
    bool achamos = false;

    while (i < tam) {

        if (chave > this->vetor[i].getChave()) 
            menores++;
        else if (chave ==  this->vetor[i].getChave())
            achamos = true;
        
        i++;
    }

    return (achamos) ? (menores) : (-1);

}

// seleciona 
template <class Chave, class Item>
Chave VD<Chave,Item>::seleciona (int k) {

    int i = 0;
    while (i < tam) {

        if (this->rank(vetor[i].getChave()) == k)
            return vetor[i].getChave();

        i++;

    }

    return "";
}

/***** VETOR ORDENADO *****/

// VO ()
template<class Chave, class Item>
VO<Chave, Item>::VO(string nome) {
    tam = 0;

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

// insere()
template<class Chave, class Item>
void VO<Chave,Item>::insere (Chave chave, Item valor) {

    int i = 0;

    while (i < tam && this->vetor[i].getChave() <= chave) {

        // se já está na tabela
        if (this->vetor[i].getChave() == chave) {
            this->vetor[i].setValor(vetor[i].getValor() + valor);
            return;
        }

        i++;

    }

    cel<Chave,Item> aux;
    aux.setChave (chave);
    aux.setValor (valor);
 
    vetor.push_back(aux);

    bool trocou = true;
    i = tam;

    while (i > 0 && trocou) {

        trocou = false;
        if (vetor[i].getChave() < vetor[i-1].getChave()) {

            cel<Chave, Item> aux = vetor[i];
            vetor[i].setChave(vetor[i-1].getChave());
            vetor[i].setValor(vetor[i-1].getValor());
            vetor[i-1].setChave(aux.getChave());
            vetor[i-1].setValor(aux.getValor());
            trocou = true;
        }
        i--;

    }

    tam++;

}

// show()
template<class Chave, class Item>
void VO<Chave,Item>::show() {

    int i = 0;

    cout << "Mostrando a tabela\n";

    while (i < tam) {

        cel<Chave,Item> aux;
        aux = vetor[i];
        cout << "Nº: " << i <<" Palavra " << aux.getChave() << "\tOcorrencias " << aux.getValor() << endl;
        i++;

    }

    cout << endl;

}

// devolve()
template<class Chave, class Item>
Item VO<Chave,Item>::devolve(Chave chave) {

    int i = 0;
    while (i < tam && vetor[i].getChave() <= chave) { // percorremos a tabela

        // se achamos, devolvemos
        if (this->vetor[i].getChave() == chave) 
            return this->vetor[i].getValor();

        i++;
    }
    // se não está na tabela
    return 0;
}

// remove()
template<class Chave, class Item>
void VO<Chave,Item>::remove (Chave chave) {

    int i = 0;
    while (i < tam && vetor[i].getChave() <= chave) {

        if (chave == this->vetor[i].getChave()) {
            vetor.erase(vetor.begin()+i);
            tam--;
            return;
        }

        i++;

    }

}

// rank
template <class Chave, class Item>
int VO<Chave,Item>::rank (Chave chave) {

    for (int i = 0; i < tam && vetor[i].getChave() <= chave; i++) {
        if (vetor[i].getChave() == chave)
            return i;
    }

    return -1;

}

// seleciona 
template <class Chave, class Item>
Chave VO<Chave,Item>::seleciona (int k) {

    int i = 0;

    if (k < tam)

        while (i < tam) {

            if (this->rank(vetor[i].getChave()) == k)
                return vetor[i].getChave();

            i++;

        }

    return "";
}