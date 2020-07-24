#ifndef _GRAFO_H_
#define _GRAFO_H_

#define output(a) ((a==true)?("sim"):("não"))

#include <bits/stdc++.h>
using namespace std;

class Cel {

    private:

        // indice
        int ind; 

        // lista de celulas adjacentes
        Cel* next; 

    public: 

        // construtor
        Cel (int ind);

        // devolve o indice
        int getIndice ();
        
        // devolve o próximo da lista de adjacencia
        Cel* getNext();

        // adiciona um vértice na lista de adjacencia
        void setNext (Cel* prox);

};

class Grafo {

    private:

        int v; // numero de vertices
        string regex;

		// lista de vértices
        vector<Cel*> vertices;

        void processa ();

    public:

        // construtor
        Grafo (string regex);

        // destrutor
        ~Grafo () {

            for (int i = 0; i < this->v; i++) {

                Cel* aux = vertices[i]->getNext();

				// liberamos a lista de adjacentes
                while (aux != nullptr) {
                    Cel* lixo = aux;
                    aux = aux->getNext();
                    delete lixo;
                    lixo = nullptr;
                }

				// liberamos
                delete vertices[i];
            }


        }

        int getVertices() {
            return this->v;
        }

        // inclui um arco partir da origem até o destino
        void addArco (int origem, int destino);

		// mostra o grafo
        void show ();

        // busca em profundidade recursiva
        void dfs (int v, vector<bool>& marcados);
};

bool reconhece (Grafo* grafo, string texto, string regex);

#endif

// Implementação da célula

Cel::Cel(int ind) {
    this->ind = ind;
    this->next = nullptr;
}

int Cel::getIndice() {
    return this->ind;
}

Cel* Cel::getNext() {
    return this->next;
}

void Cel::setNext (Cel* prox) {
    this->next = prox;
}

// Implementação do grafo

void Grafo::addArco (int origem, int destino) {

    // criamos uma nova celula
    Cel* nova = new Cel (destino);

    // adicionamos na lista de adjacencia da origem
    nova->setNext(vertices[origem]->getNext());
    vertices[origem]->setNext(nova);

}

Grafo::Grafo (string regex) {

    this->regex =regex;
    this->v = 0;

    // adicionamos os vértices no grafo
    for (int i = 0; i < (int) this->regex.size()+1; i++) {
        Cel* nova = new Cel (i);
        vertices.push_back(nova);
        v++;
    }

    processa();

}

// forma o grafo a partir da regex
void Grafo::processa () {

    int n = regex.size();
    stack<int> pilha;

    for (int i = 0; i < n; i++) {

        int ant = i;

        if (regex[i] == '(' ||  regex[i] == '|')
            pilha.push(i);

        else if (regex[i] == ')') {

            int optopo = pilha.top();
            pilha.pop();

            if (regex[optopo] == '|') {
                ant = pilha.top();  // '(' correspondente
                pilha.pop();
                this->addArco(ant, optopo + 1);
                this->addArco(optopo, i);
            }
            else
                ant = optopo;
        }
        if (i < n-1 && regex[i+1] == '*') {
            this->addArco(ant, i+1);
            this->addArco(i+1,ant);
        }
        if ( (regex[i] == '*' || regex[i] == '(' || regex[i] == ')'))
            this->addArco(i,i+1);
    }
}

void Grafo::show() {

    for (int i = 0; i < v; i++) {

        cout << i << " ";

        Cel* aux = vertices[i]->getNext();

        while (aux != nullptr) {
            cout << "-\t" << aux->getIndice() << "\t";
            aux = aux->getNext();
        }

        cout << endl;

    }
}

void Grafo::dfs (int v, vector<bool>& marcados) {

    marcados[v] = true;

    Cel* aux = vertices[v]->getNext();

    // vizitamos os adjacentes
    while (aux != nullptr) {
        if (!marcados[aux->getIndice()])
            dfs (aux->getIndice(), marcados);
        aux = aux->getNext();
    }

}

bool reconhece (Grafo* grafo, string texto, string regex) {

    int n = regex.size();

    vector<bool> S (n+1, false);
    vector<int> T;

    // onde chegamos sem ler ninguem 
    grafo->dfs(0, S);

    for (int i = 0; i < (int) texto.size(); i++) {

        for (int j = 0; j < n; j++) {

            if (S[j] && regex[j] == texto[i])
                T.push_back(j+1);
        }

        S.assign(n+1, false);

        for (int j = 0; j < (int) T.size(); j++) {
            grafo->dfs(T[j], S);
        }
        T.clear();

    }

    return S[n];

}