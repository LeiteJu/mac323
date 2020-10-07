#include "aviao.hpp"
#include "fila.hpp"

using namespace std;

#define SEED 1.21965

int main () { 
    
    // simulação de t unidades de tempo
    // até k aviões podem fazer contato a cada tempo
    int t, k, i, n;  
    int pistas[3]= { 0, 0, 0};

    Fila<Aviao> fila;

    srand(SEED);

    cout << "Bem vindo ao Sistema do Aeroporto Internacional de Guarulhos City Town\n\n";
    cout << "Qual o tempo de simulação? ";
    cin >> t;
    cout << "Qual número máximo de aviões que podem fazer contato por tempo? ";
    cin >> k;

    for (i = 0; i < t; i++) { // tempo de simulação

        cout << "\nInstante " << i << endl << endl;

        // n aviões farão contato com a torre
        n = rand () % k;

        cout << "Nesse  instante, " << n << " aviões fizeram contato.\n\n";

        // vamos adicionar os aviões na fila
        for (int j = 0; j < n; j++) {
            
            celFila<Aviao>* celula = new celFila<Aviao>;
            Aviao item;

            // geramos o avião aleatório e mostramos na tela 
            item.randAviao();
            item.showAviao();

            // e colocamos na fila
            celula->setAviao(item);
            fila.addAviao(celula);
        }

        // selecionamos o avião que decolará/pousará e a pista
        fila.seleciona(pistas);

        // se necessário, mandamos aviões para outros aeroportos
        fila.direciona();

        // mostramos a fila de aviões
        if (!fila.vazia())
            cout << "\nAviões aguardando liberação: \n\n";
        fila.showFila();

        // mostramos as estatísticas
        fila.estisticas();


        // agora vamos atualizar a fila
        fila.attFila();

        // vamos atualizar as pistas agora
        for (int aux = 0; aux < 3; aux++)
            pistas[aux]++;


    }

}
