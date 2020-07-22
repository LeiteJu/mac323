#include "grafo.hpp"
#include <bits/stdc++.h>
using namespace std;

void testes (Grafo* grafo, string regex);

string mod_regex (string regex);

int main () {

    string regex;


    cout << "Expressao Regular: ";
    cin >> regex;
    regex = mod_regex(regex);
    Grafo* grafo = new Grafo(regex);
    testes(grafo, regex);
    delete grafo;

}

void testes (Grafo* grafo, string regex) {

    string palavra;

    cout << "\nDigite as palavras a serem reconhecidas ou CRTL D para sair\n\n";

    cout << ">>> ";

    while (cin >> palavra) {
        cout << "\nA palavra foi reconhecida? " << output(reconhece(grafo, palavra, regex)) << endl << endl;
        cout << ">>> ";
    }

}

string mod_regex (string regex) {

    string expreg = "";
    stack<int> pilha;

    for (int i = 0; i < (int) regex.size(); i++) { 

        if (regex[i] == '+') {

            int ant = i-1;
            
            if (regex[i-1] == ')') {
                ant = pilha.top();
                pilha.pop();
            }

            for (int j = ant; j < i; j++) {
                expreg += regex[j];
            }

            expreg += '*';

        }

        else {

            if (regex[i] == '(')
                pilha.push(i);

            else if (regex[i] == ')' && i < (int) regex.size() && regex[i+1] != '+')
                pilha.pop();

            expreg += regex[i];
        }
    }


    return expreg;

}
