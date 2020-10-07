#include <bits/stdc++.h>
#include "grafo.hpp"

using namespace std;

// Função que retira sinais de pontuação de uma palavra
string limpa (string palavra);

// adiciona as palavras do arquivo 'nome' no grafo 
void le_arquivo (Grafo* graph, string nome);

// faz a analise
void analise (Grafo* graph);

// retorna o grau medio dos vertices do grafo
double grau (Grafo* graph);

double densidade (Grafo* graph);

void teste (Grafo* graph);

int main (int argc, char *argv[]) {

    if (argc < 3) {
        cout << "Houve um erro!\n";
        cout << "Por favor, insira o tamanho mínimo das palavras do grafo e o nome do arquivo na linha de comando!\n";
        cout << "Exemplo: \n";
        cout << "./main 3 feliz_aniversario.txt\n";
        exit(1);
    }

    Grafo* graph = new Grafo(atoi(argv[1]));
    le_arquivo(graph, argv[2]);
    cout << "O arquivo foi lido.\n";
    analise(graph);
    teste(graph);
    delete graph;
}

void teste (Grafo* graph) {

    string opcao = "manual";

    cout << "\nTestes iterativos: \n\n";

    cout << "\nInstruções: \n";
    cout << "1. Digite 'show' para mostrar o grafo:\n";
    cout << "2. Digite 'lista' para mostrar a lista de palavras do grafo:\n";
    cout << "3. Digite 'ciclo' para saber se uma palavra se encontra em um ciclo\n";
    cout << "4. Digite 'caminho' para saber se existe um caminho entre duas palavras\n";
    cout << "5. Digite 'dupla' para saber se duas palavras estão no mesmo ciclo\n";
    cout << "6. Digite 'distancia' para saber a menor distancia entre 2 palavras\n";
    cout << "OBS: em 3, 4, 5 é necessário digitar a(s) palavra(a) depois\n\n";

    while (opcao != "END") {

        cout << "\nDigite a próxima instrução\n";
        cout << "ou 'manual' para exibir as instruções novamente\n";
        cout << "ou 'END' para encerrar\n";

        cin >> opcao;

        if (opcao == "manual") {

            cout << "\nInstruções: \n";
            cout << "1. Digite 'show' para mostrar o grafo:\n";
            cout << "2. Digite 'lista' para mostrar a lista de palavras do grafo:\n";
            cout << "3. Digite 'ciclo' para saber se uma palavra se encontra em um ciclo\n";
            cout << "4. Digite 'caminho' para saber se existe um caminho entre duas palavras\n";
            cout << "5. Digite 'dupla' para saber se duas palavras estão no mesmo ciclo\n";
            cout << "6. Digite 'distancia' para saber a menor distancia entre 2 palavras\n";
            cout << "OBS: em 3, 4, 5 é necessário digitar a(s) palavra(a) depois\n\n";
        }

        // Caso 1:
        else if (opcao == "show")
            graph->show();        

        // Caso 2:
        else if (opcao == "lista")
            graph->palavras();
        
        // Caso 3:
        else if (opcao == "ciclo") {
            string s;
            cin >> s;
            cout << "\nA palavra está em um ciclo? " << out(graph->emCiclo(s)) << endl;
        }

        // Caso 4:
        else if (opcao == "caminho") {
            string p1, p2;
            cin >> p1;
            cin >> p2;
            cout << "\nExiste caminho entre essas palavras: " << out(graph->tem_caminho(p1,p2)) << endl;
        }

        // Caso 5:
        else if (opcao == "dupla") {
            string p1, p2;
            cin >> p1;
            cin >> p2;
            cout << "\nExiste um ciclo que contenha as 2 palavras? " << out(graph->emCiclo(p1,p2)) << endl;
        }
        else if (opcao == "distancia") {
            string p1, p2;
            int d;
            cin >> p1;
            cin >> p2;
            d = graph->dist(p1,p2);
            (d==-1) ? (cout << "\nPalavras desconexas ou não pertencentes ao grafo\n") : (cout << "\nA distância entre as palavras é " << d << endl);
        }
        else if (opcao != "END")
            cout << "\nComando não reconhecido!\n";
    }

}

string limpa (string palavra){

    int n = palavra.length();
    bool ainda = true;

    // Verificamos se a primeira letra não é pontuação
    switch (palavra[0]) {
        case '.':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '*':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '_':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '[':
            palavra.erase(palavra.begin());
            n--;
            break;
        case ']':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '{':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '}':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '(':
            palavra.erase(palavra.begin());
            n--;
            break;
        case ')':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '\'':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '"':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '=':
            palavra.erase(palavra.begin());
            n--;
            break;
        case ',':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '!':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '?':
            palavra.erase(palavra.begin());
            n--;
            break;
        case ':':
            palavra.erase(palavra.begin());
            n--;
            break;
        case ';':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '-':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '#':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '0':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '1':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '2':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '3':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '4':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '5':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '6':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '7':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '8':
            palavra.erase(palavra.begin());
            n--;
            break;
        case '9':
            palavra.erase(palavra.begin());
            n--;
            break;
    }

    while (ainda) {

        switch (palavra[n-1]) {
            case '.':
                palavra.pop_back();
                n--;
                break;
            case '*':
                palavra.pop_back();
                n--;
                break;
            case '_':
                palavra.pop_back();
                n--;
                break;
            case '=':
                palavra.pop_back();
                n--;
                break;
            case '[':
                palavra.pop_back();
                n--;
                break;
            case ']':
                palavra.pop_back();
                n--;
                break;
            case '{':
                palavra.pop_back();
                n--;
                break;
            case '}':
                palavra.pop_back();
                n--;
                break;
            case '(':
                palavra.pop_back();
                n--;
                break;
            case ')':
                palavra.erase(palavra.begin());
                n--;
                break;
            case '\'':
                palavra.pop_back();
                n--;
                break;
            case '"':
                palavra.pop_back();
                n--;
                break;
            case ',':
                palavra.pop_back();
                n--;
                break;
            case '!':
                palavra.pop_back();
                n--;
                break;
            case '?':
                palavra.pop_back();
                n--;
                break;
            case ':':
                palavra.pop_back();
                n--;
                break;
            case ';':
                palavra.pop_back();
                n--;
                break;
            case '-':
                palavra.pop_back();
                n--;
                break;
            case '0':
                palavra.pop_back();
                n--;
                break;
            case '1':
                palavra.pop_back();
                n--;
                break;
            case '2':
                palavra.pop_back();
                n--;
                break;
            case '3':
                palavra.pop_back();
                n--;
                break;
            case '4':
                palavra.pop_back();
                n--;
                break;
            case '5':
                palavra.pop_back();
                n--;
                break;
            case '6':
                palavra.pop_back();
                n--;
                break;
            case '7':
                palavra.pop_back();
                n--;
                break;
            case '8':
                palavra.pop_back();
                n--;
                break;
            case '9':
                palavra.pop_back();
                n--;
                break;
            default:
                ainda=false;
                break;
        }

    }

    return palavra;
}

void le_arquivo (Grafo* graph, string nome) {

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
            palavra = limpa(palavra);
            graph->insere(palavra);
        }
    }

    arquivo.close();
}

double grau (Grafo* graph) {
    return  ((double) 2*graph->arestas())/ ((double) graph->vertices()); 
}

double densidade (Grafo* graph) {
    return ((double) 2*graph->arestas() / ((double) graph->vertices()*(graph->vertices() -1)));
}

void analise (Grafo* graph) {

    cout << "\nO grafo possui: " << graph->vertices() << " vertices\n";
    cout << "O grafo possui: " << graph->arestas() << " arestas\n";
    cout << "O grau médio do grafo: " << grau(graph) << endl;
    cout << "A densidade do grafo é: " << densidade(graph) << endl;
    cout << "O grafo possui: " << graph->componentes() << " componentes\n";
    graph->analise_componentes();
    cout << "O grafo é conexo? " << out(graph->conexo()) << endl;
    cout << "A distancia média entre duas palavras é: " << graph->dist_media() << endl;

}