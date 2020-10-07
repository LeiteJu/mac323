// interface 

#include <bits/stdc++.h> 
#include "util.hpp"   /* interface para este modulo */
#include "ld.hpp"
#include "lo.hpp"
#include "vetor.hpp"
#include "ab.hpp"
#include "rb.hpp"
#include "treap.hpp"
#include "a23.hpp"
#include "hs.hpp"

using namespace std;

template<class ST>
void testeOperacoes (ST st);

int main (int argc, char* argv[]) {

    string nome, tipo;
    double tempo;
    clock_t ini, fim;

    // se o usuário não digitou ou 3 argumentos
    if (argc < 3) {

        cout << "Uso\n";
        cout << "prompt> " << argv[0] << " nome-arquivo tipo-tabela\n";
        cout << "\tnome-arquivo = nome do arquivo com o texto\n";
        cout << "\ttipo-tabela = sigla de estrutura que deve ser usada\n";
        
        return 1; // EXIT_FAILURE
    }
    
    nome = argv[1];
    tipo = argv[2];

    cout << "Criando a ST...\n";

    if (tipo == "VD") {

        ini = clock();
        VD<string, int> *st = new VD<string, int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes(st);

        delete st;

    }

    else if (tipo == "VO") {

        ini = clock();
        VO<string, int> *st = new VO<string, int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes(st);

        delete st;

    }

    else if (tipo == "LD") {

        ini = clock();
        LD<string, int> *st = new LD<string, int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes(st);

        delete st;
    }
    // lista ordenada
    else if (tipo == "LO") {

        ini = clock();
        LO<string,int> *st = new LO <string,int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes(st);

        delete (st);
    }

    else if (tipo == "AB") {

        ini = clock();
        ABB <string,int> * st = new ABB <string, int>(nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n\n";
        testeOperacoes(st);

        delete st;
    }
    else if (tipo == "RB") {

        ini = clock();
        RB<string,int>* st = new RB<string,int>(nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes (st);

        delete st;
    }
    else if (tipo == "TR") {

        ini = clock();
        TR<string,int>* st = new TR<string,int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes (st);
        delete st;
    }
    else if (tipo == "A23") {
        ini = clock();
        A23<string,int>* st = new A23<string,int> (nome);
        fim = clock();

        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes (st);
        delete st;
    }

    else if (tipo == "HS") {
        ini = clock();
        HS<string, int>* st = new HS<string, int>(nome);
        fim = clock();
        
        tempo = ((double) (fim - ini)) / CLOCKS_PER_SEC;
        cout << "Arquivo lido e tabela de símbolos construída em " << tempo << " segundos.\n";
        testeOperacoes(st);
        delete st;
    }

    else {
        cout << "Estrutura não válida\n";
        return 1;
    }

    return 0;

}

template <class ST>
void testeOperacoes (ST st) {

    string linha;

    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "minST, delminST, getST <chave>; rankST <chave>, deleteST <chave>, selectST <int>\n";
    cout << "END para encerrar.\n";
    cout << ">>> ";

    while (true) {

        cin >> linha;

        if (linha == "minST") {
            string key = st->seleciona (0);
            if (key.empty())
                cout << "A ST já está vazia\n";
            else 
                cout << key << endl;
        
        }

        else if (linha == "delminST") {
            string key = st->seleciona (0);
            if (key.empty())
                cout << "A ST já está vazia\n";
            else {
                st->remove(key);
                cout << "\"" << key << "\" foi removida\n";
            }
        
        }

        else if (linha == "getST") {

            string key;
            cin >> key;

            if (key.empty())
                cout << "ERRO: operação necessita de uma palavra";
            else {
                int frequencia = st->devolve(key);
                cout << key << ": " << frequencia << endl; 
            }

        }

        else if (linha == "rankST") {
            string key;
            cin >> key;
            int r = st->rank(key);
            (r >= 0) ? (cout << r << endl) : (cout << "Essa palavra não se encontra na ST\n");
        }

        else if (linha == "deleteST") {
            string key;
            cin >> key;
            st->remove(key);
            cout << "\"" << key << "\" foi removida\n";
        }
        else if(linha == "selectST") {
            int k;
            cin >> k;
            string key = st->seleciona (k);
            (!key.empty()) ? (cout << "Posição " << k << " = "<< key << endl) : (cout << "Não há posicao " << k << " na ST\n");

        }
        else if (linha == "END")
            return;
        else {
            cout << "Erro: operação não reconhecida";
        }

        cout << endl << ">>> ";

    }

}