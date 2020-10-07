#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <bits/stdc++.h>
using namespace std;

#define it vector<Celula*>::iterator

#define out(a) ((a==true)?("sim"):("não"))


// célula do grafo
class Celula {

	public:

		string palavra;
		int indice;
        // lista das células adjacentes 
		vector<Celula*> adj; 

		// construtor 
		Celula (string palavra, int indice);
};

class Grafo {

	private:

		int k; // número mínimo de letras de uma palavra
		int v; // número de vértices do grafo
		int a; // número de arestas no grafo
		
		vector<Celula*> grafo;

		// busca em profundidade recursiva
		void dfsR (int v, bool marcado[]);

		// verifica se uma palavra já está no grafo, se está
		// retorna o índice, caso contrário, retorna -1
		int find (string palavra);

		// verifica se tem caminho entre a origem e o destino 
		// passando por vértices cujo pai é -1
		bool caminho (int origem, int dest, int pai[]);

		// variação da bfs que devolve se podemos chegar ao 'dest'
		// a partir da origem, mas sem passar pela aresta que une os 2
		bool bfsP (int origem, int dest, int pai[]);

	public:

		/* Inicializa um grafo com parâmetro k */
		Grafo (int k);

		/* Insere a palavra e retorna o número de arestas adicionados ao grafo,
		retorna -1 se a palavra já está no grafo ou tem tamanho menor que k*/
		int insere (string palavra);

		/* Retorna o número de vértices do grafo*/
		int vertices() {
			return this->v;		
		}

		/* Retorna o número de vértices do grafo*/
		int arestas() {
			return this->a;
		}

		// mostra o grafo
		void show ();

		// retorna o número de componentes de um grafo
		int componentes ();

		/* Retorna se o grafo é ou não conexo */
		bool conexo () {
		    return (this->componentes() == 1);
	    }

		/* Retorna o tamanho da componente conexa onde está a palavra*/
		int tamComp (string palavra);

		/* Retorna a menor distância entre as palavras a e b ou -1
		caso elas estejam desconexas ou não estejam no grafo */
		int dist (string a, string b);
 
		/* Retorna verdadeiro casa a palavra esteja em algum ciclo,
		falso caso contrário */
		bool emCiclo (string a);

		/* Retorna verdadeiro casa exista um ciclo que contenha ambas as palavras,
		falso caso contrário */
		bool emCiclo (string a, string b);

        // exibe na tela o tamanho medio das componentes, 
        // o tamanho da maior e o da menor
        void analise_componentes();

        // retorna a distância média entre os vértices do grafo
        float dist_media ();

        // exibe na tela as palavras do grafo
        void palavras ();

        bool tem_caminho (string a, string b);

        ~Grafo() {
            for (int i = 0; i < v; i++)
                delete grafo[i];
        }
};

#endif

// Celula ()
Celula::Celula(string palavra, int indice) {
    this->palavra = palavra;
    this->indice = indice;
}

// Funções para sabermos se duas palavras estão ligadas

// função que verifica se as palavras diferem  apenas pela inserção/remoção de uma letra
bool insercao (string a, string b) {

	int len_a = a.length(), len_b = b.length();
	int m = (len_a > len_b) ? (len_b) : (len_a);
	int dif = 0;

	if (len_a-len_b > 1 || (len_a-len_b) < (-1) || len_a == len_b)
		return false;

	// i: pointer para a string a
	// j: pointer para a string b
	for (int i = 0, j = 0; i < m; i++, j++) {
		if (a[i] != b[j]) {
			(m == len_a ? (i--) : (j--));
			dif++;
			if (dif > 1)
				return false;
		}
	}
    if (dif == 1 && a[len_a-1] != b[len_b-1]) {
        return false;
    }
	return true; 
}

// função que verifica se as palavras diferem pela troca de duas letras
bool troca (string a, string b) {
	
	int dif = 0, pos;
    int len_a = a.length();
    int len_b = b.length();

	if (len_a != len_b)
		return false;

	for (int i = 0; i < len_a; i++)
		if (a[i] != b[i]) {

			dif++;			
			if (dif > 1 && (a[pos] != b[i] || b[pos] != a[i]))
				return false;
			pos = i;
		}
	return dif == 2;
}

// função que verifica se as palavras diferem pela substituição de uma letra
bool substituicao (string a, string b) {

	int dif = 0;
    int len_a = a.length();
    int len_b = b.length();

	if (len_a != len_b)
		return false;

	for (int i = 0; i < len_a; i++) {

		if (a[i] != b[i]) {
			if (dif > 0)
				return false;
			dif++;
		}
	}
	return true;
}

Grafo::Grafo (int k) {

    this->k = k;
    this->v = 0;
    this->a = 0;

}

int Grafo::find(string palavra) {

	// se a palavra tem menos letras que o mínimo
	if ((int) palavra.length() < k) 
		return -1;

	for (int i = 0; i<this->v; i++)
		if (grafo[i]->palavra == palavra)
			return i;

	return -1;
}

int Grafo::insere (string palavra) {

    // se já está no grafo
    if (find(palavra) >= 0) {
        return -1;
    }

    // se a palavra tem menos letras que o mínimo
    if ((int) palavra.length() < k) {
        return -1;
    }

    // então vamos criar esse vértice
    Celula* nova = new Celula (palavra, v);

    int novas = 0; // arestas que serão adicionadas 

    // vamos achar os vértices adjacentes
    for (int i = 0; i < v; i++) {

        // se as palavras estão ligadas, inserimos na lista
        if (insercao(palavra, grafo[i]->palavra) || troca (palavra, grafo[i]->palavra) || substituicao (palavra, grafo[i]->palavra)) {
            novas++;
            nova->adj.push_back(grafo[i]);
            grafo[i]->adj.push_back(nova);
        }
    }
    grafo.push_back(nova);
    v++; // atualizamos o número de vértices
    a += novas; // e o número de arestas
    return novas;    
}

void Grafo::dfsR (int v, bool marcado[]) {
		
    marcado[v] = true;

    // olhamos para os vértices adjacentes
    for (it adj = grafo[v]->adj.begin(); adj != grafo[v]->adj.end(); ++adj) {

        int ind = (*adj)->indice;
        
        // se ele ainda não foi visitado, visitamos
        if (!marcado[ind])
            dfsR(ind, marcado);
    }
}

bool Grafo::caminho (int origem, int dest, int pai[]) {

    queue<int> fila;

    fila.push(origem);

    if (origem == dest)
        return true;

    while (!fila.empty()) {
        
        int atual = fila.front();
        fila.pop();

        // iteramos sobre os vizinhos
        for (it aux = grafo[atual]->adj.begin() ; aux != grafo[atual]->adj.end(); ++aux) {
            
            if ((*aux)->indice == dest) {
                pai[(*aux)->indice] = atual;

                while (!fila.empty()) {
                    fila.pop();
                }
                return true;
            }

            if (pai[(*aux)->indice] == -1) {
                pai[(*aux)->indice] = atual;
                fila.push((*aux)->indice);
            }

        }

    }
    return false;

}

bool Grafo::bfsP (int origem, int dest, int pai[]) {

    queue<int> fila;

    // colocamos na fila
    fila.push(origem);

    while (!fila.empty()) {

        int atual = fila.front();
        fila.pop();

        // iteramos sobre os vizinhos
        for (it aux = grafo[atual]->adj.begin() ; aux != grafo[atual]->adj.end(); ++aux) {

            // se não foi vizitado, colocamos na fila e preenchemos o pai
            if (pai[(*aux)->indice] == -1) {
                pai[(*aux)->indice] = atual;
                fila.push((*aux)->indice);
            }

            else if ((*aux)->indice == dest && atual != origem) {

                while (!fila.empty()) {
                    fila.pop();
                }

                return true;
            }

        }

    }

    return false;

}

void Grafo::show () {

    cout << "Grafo: \n\n";
    for (int i = 0; i < v; i++) {

        cout << grafo[i]->palavra << "\t";

        for (it aux = grafo[i]->adj.begin() ; aux != grafo[i]->adj.end(); ++aux)
            cout << "-\t" << (*aux)->palavra << "\t";
        
        cout << endl;
    }

}

int Grafo::componentes () {
    
    // número de componentes
    int comp = 0;

    // guardamos os vértices marcados
    bool marcado[this->v];

    for (int i = 0; i < this->v; i++)
        marcado[i] = false;

    for (int i = 0; i < this->v; i++)

        if (!marcado[i]) {
            comp++;
            dfsR(i, marcado);
        }
    return comp;
}

int Grafo::tamComp (string palavra) {
    
    // iteramos sobre os vértices do grafo
    for (int i = 0; i < this->v; i++)
        
        // achamos a palavra
        if (grafo[i]->palavra == palavra) {

            int comp = 0;

            bool marcados[this->v];

            for (int i = 0; i < this->v; i++)
                marcados[i] = false;

            dfsR(i, marcados);

            for (int i = 0; i < this->v; i++)
                if (marcados[i])
                    comp++;

            return comp;
        }

    return -1;
}

int Grafo::dist (string a, string b) {
    
    int ind_a = find(a);
    int ind_b = find(b);

    // verificamos se as palavras estão no grafo
    if (ind_a < 0 || ind_b < 0)
        return -1;

    // fila
    queue<int>fila;
    int ant[this->v];
    int distancia = 0;

    // inicializamos o dist
    for (int i = 0; i<this->v; i++)
        ant[i] = -1;

    // colocamos o a na fila
    fila.push(ind_a);
    ant[ind_a] = ind_a;

    while (!fila.empty()) {

        // tiramos o primeiro da fila
        int atual = fila.front();
        fila.pop();

        // se achamos a palavra b
        if (atual == ind_b) {
            while (atual != ind_a) {
                distancia++;
                atual = ant[atual];
            }
            return distancia;
        }

        // adicionamos os vizinhos na fila
        for (it aux = grafo[atual]->adj.begin() ; aux != grafo[atual]->adj.end(); ++aux) {

            // se o vizinho não foi marcado, adicionamos na fila
            if (ant[(*aux)->indice] == -1) {
                ant[(*aux)->indice] = atual;
                fila.push((*aux)->indice);
            }

        }

    }
    return -1;

}

bool Grafo::emCiclo (string a) {

    // guardamos o pai de cada vértice
    int pai[this->v];

    // índice da palavra a
    int ind = find(a);

    for (int i = 0; i<this->v; i++)
        pai[i] = -1;

    // se a não está no grafo ou tem menos que 2 vizinhos
    if (ind < 0 || grafo[ind]->adj.size() < 2)
        return false;
    
    pai[ind] = ind;

    // iteramos sobre os vizinhos de a
    for (it aux = grafo[ind]->adj.begin() ; aux != grafo[ind]->adj.end(); ++aux) {
        pai[(*aux)->indice] = ind;
        if (bfsP((*aux)->indice, ind, pai)) {
            return true;
        }
    }
    return false;
}

bool Grafo::emCiclo (string a, string b) {

    int ind_a = find(a);
    int ind_b = find(b);
    int pai[this->v];

    if (ind_a == -1 || ind_b == -1 || grafo[ind_a]->adj.size() < 2 || grafo[ind_b]->adj.size() < 2)
        return false;

    for (int i = 0; i < this->v; i++)
        pai[i]=-1;

    pai[ind_a] = ind_a;

    if (caminho(ind_a, ind_b, pai)) {

        int p[this->v];
        for (int i = 0; i < this->v; i++)
            p[i]=-1;

        for (int aux = ind_b; aux != ind_a; aux = pai[aux])
            p[aux] = pai[aux];
        p[ind_a] = pai[ind_a];

        for (it iter = grafo[ind_a]->adj.begin(); iter != grafo[ind_a]->adj.end(); ++iter) {
            if (p[(*iter)->indice] == -1 && caminho((*iter)->indice, ind_b,p))
                return true;
        }
    }
    return false;
}

void Grafo::analise_componentes(){

    int max = 0;
    int min = INT16_MAX;
    int total = 0;
    int ncomp = 0;

    bool visitados[this->v];

    for (int i = 0; i < this->v; i++)
        visitados[i] = false;

    for (int i = 0; i < this->v; i++) {
        if (!visitados[i]) {
            int atual = 0;
            ncomp++;
            dfsR(i, visitados);
            atual = tamComp(grafo[i]->palavra);
            total += atual;
            if (atual > max)
                max = atual;
            if (atual < min)
                min = atual;
        }
    }

    cout << "Tamanho médio das componentes: " << ((float) total/ (float) this->componentes()) << endl;
    cout << "Tamanho da maior componente: " << max << endl;
    cout << "Tamanho da menor componente: " << min << endl; 

}

float Grafo::dist_media () {
    
    queue<int> fila;
    int total = 0;
    int n = 0;

    for (int i = 0; i < this->v; i++) {

        int dist[this->v];

        for (int j = 0; j < this->v; j++)
            dist[j] = -1;
        fila.push(i);
        dist[i] = 0;

        while (!fila.empty()) {

            int atual = fila.front();
            fila.pop();

            for (it iter = grafo[atual]->adj.begin(); iter != grafo[atual]->adj.end(); ++iter) {

                if (dist[(*iter)->indice] == -1) {

                    dist[(*iter)->indice] = dist[atual] + 1;
                    total += dist[(*iter)->indice];
                    n++;
                    fila.push((*iter)->indice);
                }
            }

        }

    }

    return (n==0) ? (-1) : ((float)total/ (float) n);



}

void Grafo::palavras() {

    cout << "Palavras do Grafo:\n\n";

    for (int i = 0; i < this->v; i++)
        cout << "- " << grafo[i]->palavra << endl;

}

bool Grafo::tem_caminho (string a, string b) {

    int ind_a = find(a);
    int ind_b = find(b);
    bool marcado[this->v];

    if (ind_a == -1 || ind_b == -1)
        return false;

    for (int i = 0; i < this->v; i++)
        marcado[i] = false;

    dfsR(ind_a, marcado);

    return marcado[ind_b];
}
