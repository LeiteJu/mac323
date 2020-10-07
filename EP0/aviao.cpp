#include "aviao.hpp"
#include "airport.hpp"
#include "companhia.hpp"

#define MAX 35

// Construtor do avião
Aviao::Aviao():t(-1),c(-1),sos(false), espera(0){}

// isSOS()
bool Aviao::isSOS () {

    //se está sem combustível
    if (this->c == 0) 
        this->sos = true;
    //se ele já esperou 10% do tempo de voo
    else if (0.1 * t == espera)  
        this->sos = true;

    return this->sos; 

} 

// atualiza os dados do aviao
// tempo de espera e combustivel
void Aviao::attAviao () {
    
    this->espera++;

    if (this->dec == false) {
      this->c--;  
    }
    this->isSOS();
}

// sorteia os dados do aviao
void Aviao::randAviao () {

    // sorteando a companhia aerea e os dígitos
    this->cmp = companhias[rand() % 14];

    this->id = (rand() % 899 + 100);

    // colocando o destino
    this->cod = airport[rand() % 29];

    // sorteamos se é decolagem ou pouso
    this->dec = (rand() % 47) % 2;

    // dependendo da resposta anterior sorteamos o tempo de voo / combustível
    (this->dec) ? (this->t=rand() % MAX + 3) : (this->c=rand() % MAX);

    // sorteamos se é emergência 
    this->sos = (rand() % 39) % 2;

}

// verifica se é decolagem
bool Aviao::isDec() {
    return this->dec;
}

// retorna o combustivel
int Aviao::comb() {
    return this->c;
}

// retorna o tempo de espera 
int Aviao::tEspera() {
    return this->espera;
}

// exibe os dados do aviao
void Aviao::showAviao() {

        cout << "Aviao\tID: " << this->cmp << this->id << "\t";
        cout << "Código: " << this->cod << "\t";
        if (this->dec) {
            cout << "Decolar \t";
            cout << "Tempo de voo: " << this->t << "  \t";
        }
        else {
            cout <<"Pousar  \t";
            cout << "Combustível: " << this->c << "   \t";
        }
        cout << "Tempo de espera: " << this->espera << "\t";
        if (this->sos) 
            cout << "É uma emergência!";
        cout << "\n";
  } 
