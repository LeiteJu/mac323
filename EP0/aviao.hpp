//Definindo a classe avião

#ifndef _AVIAO_H_
#define _AVIAO_H_

#include <bits/stdc++.h>
using namespace std;

class Aviao {  

    private:
    string cmp;         // companhia do avião
    int id;             // identificação do avião 
    string cod;         // identificação do aeroporto
    int t;              // tempo de voo
    int c;              // combustível  
    bool sos;           // é emergência?
    int espera;
    bool dec;           // é decolagem?


    public:
    
    //construtor provisório 
    Aviao();  

    // dados do plane
    void randAviao(); 
 
    // olha o combustível e tempo de voo e vê se é emergência
    bool isSOS (); 
    
    // É decolagem?
    bool isDec ();

    // devolve a quantidade de combustível
    int comb ();

    // devolve o tempo de espera
    int tEspera ();

    //atualiza tempo de espera, combustível, etc e aciona o isSOS
    void attAviao();   

    // printa os dados do avião
    void showAviao ();
};

#endif 