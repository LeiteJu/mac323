//Fila

#ifndef _FILA_H_
#define _FILA_H_

#include "aviao.hpp"

template<class obj>
class celFila {

    private:

        obj cont;
        celFila<obj>* prox;
        celFila<obj>* ant;

    public:

        celFila (); // construtor

        // seta um avião
        void setAviao (obj novo);

        // devolve o avião
        obj* getAviao ();

        // devolve um ponteiro pro prox
        celFila<obj>* getProx ();

        // devolve um ponteiro pro anterior
        celFila<obj>* getAnt ();

        // seta o ponteiro pro próximo
        void setProx (celFila<obj>* alvo);

        // seta o ponteiro pro anterior
        void setAnt (celFila<obj>* alvo);

};

template<class obj>
class Fila {

    private:

        celFila<obj> * head; // cabeça da fila
        int nPousaram; // numero de aviões que já pousaram
        int cPousaram; // quantidade de aviões que já pousaram

    public:

        Fila(); // construtor

        ~Fila(); // destrutor

        // adiciona um celFila na fila
        void addAviao (celFila<obj>* novo);

        // remove o item da fila
        void remove (celFila<obj>* item);

        // verifica se a fila está vazia
        bool vazia ();

        // atualiza a fila
        void attFila ();

        // showFila()
        void showFila ();

        // seleciona o avião que vai pousar
        void seleciona (int* pistas);

        // se tiver mais de 1 avião com combustível 1
        // direciona o segundo (e os demais) para outros aeroportos
        void direciona ();

        // printa as estatísticas
        void estisticas ();

};

/********   IMPLEMENTAÇÃO   CELFILA    ********/

// celFila()
template<class obj>
celFila<obj>::celFila() {

    this->prox = this->ant = nullptr;
}

// setAviao()
template<class obj>
void celFila<obj>::setAviao (obj novo) {

    cont = novo;
 
}
// getAviao()
template<class obj>
obj* celFila<obj>::getAviao () {

    return &cont;
}

// getProx()
template<class obj>
celFila<obj>* celFila<obj>::getProx() {

    return this->prox;
}

// getAnt()
template<class obj>
celFila<obj>* celFila<obj>::getAnt() {

    return this->ant;
}

// setAnt()
template<class obj>
void celFila<obj>::setAnt (celFila<obj>* alvo) {
    this->ant = alvo;
}

// setProx()
template<class obj>
void celFila<obj>::setProx (celFila<obj>* alvo) {
    this->prox = alvo;
}

/********   IMPLEMENTAÇÃO   FILA    ********/

// Fila()
template<class obj>
Fila<obj>::Fila() {

    this->head = new celFila<obj>; // criamos a cabeça da fila
    this->head->setProx(head);
    this->head->setAnt(head);
    this->cPousaram = this->nPousaram = 0;

}

// addAviao()
template<class obj>
void Fila<obj>::addAviao(celFila<obj>* novo) {

    novo->setAnt(head->getAnt()); // novo->ant aponta pro head->ant
    novo->setProx(head); // novo->prox aponta pra head
    head->getAnt()->setProx(novo); // head->ant->prox aponta pro novo
    head->setAnt(novo); // head->ant aponta para o novo

}

// vazia()
template<class obj>
bool Fila<obj>::vazia() {
    if (head->getProx() == head)
        return true;
    return false;
}

// remove()
template <class obj>
void Fila<obj>::remove(celFila<obj>*item) {

    if (!item->getAviao()->isDec()) {
        this->nPousaram++;
        this->cPousaram += item->getAviao()->comb();
    }

    item->getAnt()->setProx(item->getProx());
    item->getProx()->setAnt(item->getAnt());
    delete item;

}

// attFila()
template<class obj>
void Fila<obj>::attFila() {

    celFila<obj>* aux = head->getProx();

    while (aux != head) {

        if (aux->getAviao()->comb() < 0 && !aux->getAviao()->isDec()) {
            
            celFila<obj>* item = aux;

            cout << "\nAvião caiu por falta de combustível\n\n";
            aux->getAviao()->showAviao();
            aux = aux->getAnt();
            remove(item);

        }

        aux->getAviao()->attAviao();

        aux = aux->getProx();
    }
        
}

// showFila()
template <class obj>
void Fila<obj>::showFila() {

    celFila<obj>* aux = head->getProx();
    while (aux != head) {
        aux->getAviao()->showAviao();
        aux = aux->getProx();
    }

}

// direciona ()
template <class obj>
void Fila<obj>::direciona() {

    celFila<obj>* aux = head->getProx();
    int n = 0;

    while (aux != head) {

        if (aux->getAviao()->comb() == 1) {
            n++;
            if (n > 1) {

                celFila<obj>* item = aux;
                aux = aux->getAnt();
                cout << "\nAvião direcionado a outro aeroporto:\n\n";
                item->getAviao()->showAviao();
                this->remove(item);
            }
        }
        aux = aux->getProx();
    }

}

// seleciona()
template <class obj>
void Fila<obj>::seleciona (int *pistas) {

    if (this->vazia())
        return;

    int pista;
    bool selecionei = false;
    celFila<obj>* aux = head->getProx();
    celFila<obj>* alvo = head;

    if (pistas[0] >= 0)
        pista = 1;

    else if (pistas[1] >= 0)
        pista = 2;
    else 
        pista = 3;

    pistas[pista - 1] = -3;

    while (aux != head) {

        if (aux->getAviao()->comb() == 0) {

            cout << "\nAvião recebeu liberação para pousar/decolar na pista " << pista << endl << endl;
            aux->getAviao()->showAviao();
            remove(aux);
            return;
        }

        if (aux->getAviao()->isSOS() && !selecionei) {

            selecionei = true;
            alvo = aux;
        }

        aux = aux->getProx();
    }

    aux = aux->getProx();

    // se não tem nenhuma emergência
    while (!selecionei && aux != head) {
        
        if (pista != 3 || (aux->getAviao()->isDec() && pista == 3)) {
            selecionei = true;
            alvo = aux;
        }
        aux = aux->getProx();

    }

    // se não é possível remover ninguém
    if (!selecionei)
        return;

    cout << "\nAvião recebeu liberação para pousar/decolar na pista " << pista << endl << endl;
    alvo->getAviao()->showAviao();
    remove(alvo);

}

// estatísticas()
template<class obj>
void Fila<obj>::estisticas() {

    celFila<obj>* aux = head->getProx();
    int nDec = 0, nPou = 0, comb = 0, nSOS = 0;
    float tDec = 0, tPou = 0;

    while (aux != head) {

        if (aux->getAviao()->isDec()) {
            nDec++;
            tDec += aux->getAviao()->tEspera();
        }

        else {
            nPou++;
            tPou += aux->getAviao()->tEspera();
            comb += aux->getAviao()->comb();
        }

        if (aux->getAviao()->isSOS())
            nSOS++;

        aux = aux->getProx();
    }

    cout << "\nEstatísticas: \n\n";

    // tempo de espera dos que ainda estão na fila
    cout << "Tempo médio de espera para pouso: ";
    (nPou > 0) ? (cout << setprecision(3) << tPou/nPou << endl) : (cout << "0\n");

    cout << "Tempo médio de espera para decolagem: ";
    (nDec > 0) ? (cout << setprecision(3) << tDec/nDec << endl) : (cout << "0\n");

    // combustível dos que estão esperando para pousar
    if (nPou > 0)
        cout << "Quantidade média de combustível dos aviões aguardando para pousar: " << (float) comb/nPou << endl;
    
    if (nPousaram > 0) 
        cout << "Quantidade média de combustível dos aviões que já pousaram: " << (float) this->cPousaram/this->nPousaram << endl;
    
    (nSOS > 0) ?
    (cout << "Número de aviões aguardando liberação em situação de emrgência: " << nSOS << endl) : 
    (cout << "Não há aviões aguardando liberação em situação de emergência\n");

    cout << endl;
}

// ~Fila()
template<class obj>
Fila<obj>::~Fila() {

    celFila<obj>* aux = head->getProx();

    while (aux != head) {
        this->remove(aux);
        aux = head->getProx();
    }

    delete head;

}

#endif 