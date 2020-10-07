#ifndef _RB_H_
#define _RB_H_

#include <bits/stdc++.h>
using namespace std;

#define VERMELHO 'v'
#define PRETO 'p'

template<class Chave, class Item>
class No_RB {

    private:

        Chave chave;
        Item valor;
        
    public:

        char cor;

        // ponteiros
        No_RB* pai;
        No_RB* esq;
        No_RB* dir;

        No_RB();
        void setChave(Chave chave);
        Chave getChave();
        void setValor (Item valor);
		Item getValor ();
};

template<class Chave, class Item>
class RB {

    private:

    No_RB<Chave, Item>* raiz;

    // rotaciona para a direita e retorna a nova raiz
    No_RB<Chave,Item>* rotDir (No_RB<Chave,Item>* root);
    // rotaciona para a esquerda e retorna a nova raiz
    No_RB<Chave,Item>* rotEsq (No_RB<Chave,Item>* root);
    // chamada recursivamente pelo ~RB()
    void delRB (No_RB<Chave,Item>* root);
    // chamada pela insere
    No_RB<Chave,Item>* put (No_RB<Chave,Item>* root, Chave chave, Item valor);
    No_RB<Chave,Item>* del (No_RB<Chave,Item>* root, Chave ch);
    int soma (No_RB<Chave,Item>* root, Chave ch);

    public:

    No_RB<Chave, Item>* getRaiz ();
    RB (string nome);
    ~RB();
    void insere (Chave chave, Item valor);
    Item devolve (Chave chave);
    int rank (Chave chave);
    void leArquivo (string No_RB);
    void show (No_RB<Chave, Item>* root);
    void remove (Chave chave);
    Chave seleciona (int k);
};


#endif

string limpa (string palavra);

/***** No_RB *****/

// No_RB()
template<class Chave, class Item>
No_RB<Chave,Item>::No_RB() {

    this->chave = "";
    this->valor = 0;
    this->dir = this->esq = this->pai = nullptr;
    this->cor = VERMELHO;

}

template<class Chave, class Item>
No_RB<Chave, Item>* RB<Chave,Item>::getRaiz () {
    return this->raiz;
}

// setChave()
template <class Chave, class Item>
void No_RB<Chave,Item>::setChave (Chave chave) {
	this->chave = chave;
}

// getChave()
template <class Chave, class Item>
Chave No_RB<Chave,Item>::getChave() {
	return this->chave;
}

// setValor()
template <class Chave, class Item>
void No_RB<Chave,Item>::setValor (Item valor) {
	this->valor += valor;
}

// getValor()
template <class Chave, class Item>
Item No_RB<Chave,Item>::getValor() {
	return this->valor;
}

/***** RB *****/

// RB()
template<class Chave, class Item>
RB<Chave,Item>::RB (string No_RBme) {
    this->raiz = nullptr;

    leArquivo(No_RBme);
}

// insere
template<class Chave, class Item>
void RB<Chave,Item>::insere (Chave chave, Item valor) {
    this->raiz = put (this->raiz, chave, valor);
}

// put ()
template<class Chave, class Item>
No_RB<Chave,Item>* RB<Chave,Item>::put (No_RB<Chave,Item>* root, Chave chave, Item valor) {

    // se a raiz é nula, só criamos o No
    if (root == nullptr) {
        root = new No_RB<Chave,Item>;
        root->setValor(valor);
        root->setChave(chave);
        return root;
    }

    // vamos ver se já está na tabela
    No_RB<Chave,Item>* p = this->raiz;

    // procuramos a palavra
    while (p != nullptr) {
        if (p->getChave() > chave && p->esq != nullptr)
            p = p->esq;
        else if (p->getChave() > chave && p->esq == nullptr)
            break;
        else if (p->getChave() < chave && p->dir != nullptr)
            p = p->dir;
        else if (p->getChave() < chave && p->dir == nullptr)
            break;
        else { // se está na tabela, atualizamos o valor
            p->setValor(valor);
            return this->raiz;
        }
    }

    // então vamos criar o novo nó
    No_RB<Chave,Item>* novo = new No_RB<Chave,Item>;
    novo->setChave(chave);
    novo->setValor(valor);
    novo->pai = novo->dir = novo->esq = nullptr;

    // p tem que ser o pai do novo Nó
    (chave < p->getChave()) ? (p->esq = novo) : (p->dir = novo);
    novo->pai = p;

    // agora temos que acertar as cores

    No_RB<Chave,Item>* filho = novo;

    while (p != nullptr) {

        if (p->cor == PRETO) 
            return this->raiz;

        No_RB<Chave,Item>* avo = p->pai;

        // se não tem avô
        if (avo == nullptr) {
            p->cor = PRETO;
            return this->raiz;
        }
        No_RB<Chave,Item>* tio = (p == avo->esq) ? (avo->dir) : (avo->esq);

        // se o tio é nulo ou preto
        if (tio == nullptr || tio->cor == PRETO) {


            if (p == avo->esq && filho == p->dir) {// rotacionamos o filho com o pai
                avo->esq = rotEsq(p);
                filho->pai = avo;
                p = avo->esq;
                filho = p->esq;

            }
            else if (p == avo->dir && filho == p->esq) {
                avo->dir = rotDir(p);
                filho->pai = avo;
                p = avo->dir;
                filho = p->dir;
            }

            avo = (p == avo->esq) ? (rotDir(avo)) : (rotEsq(avo));

            avo->cor = PRETO;
            if (avo->dir != nullptr)
                avo->dir->cor = VERMELHO;
            if (avo->esq != nullptr)
                avo->esq->cor = VERMELHO;

            if (avo->dir == this->raiz || avo->esq == this->raiz)
                return avo;

            if (avo->pai != nullptr) {
                (avo->pai->getChave() > avo->getChave()) ? (avo->pai->esq = avo) : (avo->pai->dir = avo);
            }

            return this->raiz;

        }
        else { // se o tio é vermelho

            avo->cor = VERMELHO;
            avo->esq->cor = avo->dir->cor = PRETO;
            
            filho = avo;
            p = avo->pai;

        }
    }
    return this->raiz;
}

// rank ()
template <class Chave, class Item>
int RB<Chave, Item>::rank (Chave chave) {

    return (this->devolve(chave) != 0) ? (soma (this->raiz, chave)) : (-1);
}

template<class Chave, class Item>
int RB<Chave,Item>::soma (No_RB<Chave,Item>* root, Chave ch) {

    if (root == nullptr)
        return 0;

    if (root->getChave() < ch)
        return 1 + soma (root->esq, ch) + soma (root->dir, ch);

    return soma(root->esq, ch);
    
}

// rotDir()
template<class Chave, class Item>
No_RB<Chave,Item>* RB<Chave,Item>::rotDir (No_RB<Chave,Item>* root) {

    No_RB<Chave,Item>* newRoot = root->esq;
    // acertamos os ponteiros
    if (newRoot->dir != nullptr)
        newRoot->dir->pai = root;
    newRoot->pai = root->pai;
    root->pai = newRoot;

    root->esq = newRoot->dir;
    newRoot->dir = root;
    
    return newRoot; // retornamos a nova raiz
}

// rotEsq()
template<class Chave, class Item>
No_RB<Chave,Item>* RB<Chave,Item>::rotEsq (No_RB<Chave,Item>* root) {

    No_RB<Chave,Item>* newRoot = root->dir;
    // acertamos os ponteiros
    if (newRoot->esq != nullptr)
        newRoot->esq->pai = root;
    newRoot->pai = root->pai;
    root->pai = newRoot;
    root->dir = newRoot->esq;
    newRoot->esq = root;
    // retornamos a nova raiz
    return newRoot;
}

// remove()
template<class Chave, class Item>
void RB<Chave,Item>::remove (Chave chave) {
    this->raiz = del (raiz, chave);
}

template<class Chave, class Item>
No_RB<Chave,Item>* RB<Chave,Item>::del (No_RB<Chave,Item>* root, Chave ch) {

    No_RB<Chave,Item>* alvo = root;

    while  (alvo != nullptr) {
        if (alvo->getChave() > ch)
            alvo = alvo->esq;
        else if (alvo->getChave() < ch)
            alvo = alvo->dir;
        else
            break;
    }

    // alvo, se não for nulo é quem queremos remover
    if (alvo == nullptr)
        return root;
    
    if (alvo->esq != nullptr && alvo->dir != nullptr) {
        // se tem os dois filhos, vamos trocar pelo último filho da sub-árvore esquerda
        No_RB<Chave,Item>* aux = alvo->esq;
        while (aux->dir != nullptr) {
            aux = aux->dir;
        }
        alvo->setChave(aux->getChave());
        alvo->setValor(aux->getValor()-alvo->getValor());
        alvo = aux; // então temos que remover esse aux
    }

    // Caso 1: folha vermelha
    if ((alvo->dir == nullptr && alvo->esq == nullptr) && alvo->cor == VERMELHO) {
        if (alvo->pai != nullptr)
            (alvo == alvo->pai->esq) ? (alvo->pai->esq = nullptr) : (alvo->pai->dir = nullptr);
        delete alvo;
        return root;    
    }
    
    // Então é folha preta
    No_RB<Chave,Item>* p = alvo->pai;

    bool filhoEsq = (alvo == p->esq) ? (true) : (false); 

    if (alvo->esq != nullptr || alvo->dir != nullptr) {
        if (p == nullptr) {
            root = (alvo->esq != nullptr) ? (alvo->esq) : (alvo->dir);
            root->pai = nullptr;
            delete alvo;
            return root;
        }
        if (filhoEsq) {
            p->esq = (alvo->esq != nullptr) ? (alvo->esq) : (alvo->dir);
            p->esq->cor = PRETO;
            p->esq->pai = p;
            delete alvo;
            return root;
        }
        p->dir = (alvo->esq != nullptr) ? (alvo->esq) : (alvo->dir);
        p->dir->cor = PRETO;
        p->dir->pai = p;
        delete alvo;
        return root;
    }

    if (p != nullptr)
        (filhoEsq) ? (p->esq = nullptr) : (p->dir = nullptr);
    delete alvo;


    while (p != nullptr) {

        No_RB<Chave,Item>* irmao = (filhoEsq) ? (p->dir) : (p->esq);

        // Caso 2.1: Irmão preto[ou nulo] com filhos pretos[ou nulos]

        if (irmao == nullptr) {
            // Se o pai é vermelho, OK
            if (p->cor == VERMELHO) {
                p->cor = PRETO;
                return root;
            }
            // Então o dp passou pro pai
            if (p->pai != nullptr)
                filhoEsq = (p->pai->esq == p) ? (true) : (false);
            
            p = p->pai;
            
        }
        No_RB<Chave,Item>* sobProx = (filhoEsq) ? (irmao->esq) : (irmao->dir);
        No_RB<Chave,Item>* sobLong = (filhoEsq) ? (irmao->dir) : (irmao->esq);

        if ((sobLong == nullptr && sobProx == nullptr && irmao->cor == PRETO) || (irmao->cor == PRETO && sobLong != nullptr && sobLong->cor == PRETO && sobProx != nullptr && sobProx->cor == PRETO)) {
            irmao->cor = VERMELHO;
            if (p->cor == VERMELHO) {
                p->cor = PRETO;
                return root;
            }
            if (p->pai != nullptr)
                filhoEsq = (p->pai->esq == p) ? (true) : (false);
            p = p->pai;
            
        } 

        // Caso 2.2: irmão vermelho
        else if (irmao->cor == VERMELHO) {
            p->cor = VERMELHO;
            irmao->cor = PRETO;
            p = (filhoEsq) ? (rotEsq(p)) : (rotDir(p));
            if (p->pai != nullptr)
                (p->getChave() < p->pai->getChave()) ? (p->pai->esq = p) : (p->pai->dir = p);
            p = (filhoEsq) ? (p->esq) : (p->dir);
            
        }

        // Caso 2.3: irmão preto com sobrinho mais perto vermelho e mais longe preto
        else if (irmao->cor == PRETO && (sobLong == nullptr || sobLong->cor == PRETO)) {
            irmao->cor = VERMELHO;
            sobProx->cor = PRETO;
            (filhoEsq) ? (p->dir = rotDir(p->dir)) : (p->esq = rotEsq(p->esq));
        }
        
        // Caso 2.4: irmão preto com sobrinho mais longe vermelho 
        else if (sobLong != nullptr && sobLong->cor == VERMELHO) {
            irmao->cor = p->cor;
            p->cor = PRETO;
            p = (filhoEsq) ? (rotEsq(p)) : (rotDir(p));
            sobLong->cor = PRETO;
            if (p->pai == nullptr)
                return p;
            (p->pai->getChave() < p->getChave()) ? (p->pai->dir = p) : (p->pai->esq = p);
            return root;
        }
    }
    return root;
}

// seleciona ()
template<class Chave, class Item>
Chave RB<Chave,Item>::seleciona (int k) {

    No_RB<Chave, Item>* aux = this->raiz;

    while (aux != nullptr) {
        int r = rank(aux->getChave());
        if (r == k)
            return aux->getChave();
        if (r < k)
            aux = aux->dir;
        else
            aux = aux->esq;
    }

    string s;
    return s;

}

// devolve
template<class Chave, class Item>
Item RB<Chave,Item>::devolve (Chave chave) {

    No_RB<Chave,Item>* aux = this->raiz;

    while (aux != nullptr && aux->getChave() != chave) {
        if (aux->getChave() < chave)
            aux = aux->dir;
        else
            aux = aux->esq;
    }

    return (aux == nullptr) ? (0) : (aux->getValor());

}

// show
template<class Chave, class Item>
void RB<Chave,Item>::show (No_RB<Chave,Item>* root) {

    if (root == nullptr)
        return;

    show (root->esq);
    cout << "Rank: " << this->rank (root->getChave());
    cout << "Palavra: " << root->getChave();
    cout << " Nº: " << root->getValor() << endl;

    show (root->dir);

}

template<class Chave, class Item>
void RB<Chave,Item>::delRB (No_RB<Chave,Item>* root) {

    if (root == nullptr)
        return;
    delRB (root->esq);
    delRB (root->dir);
    delete root;

}

template<class Chave, class Item>
RB<Chave,Item>::~RB() {
    delRB(this->raiz);
}

// leArquivo ()
template<class Chave, class Item>
void RB<Chave,Item>::leArquivo (string No_RBme) {

    string palavra;
    string linha;

    fstream arquivo;
    arquivo.open(No_RBme);

    // se não foi possível abrir o arquivo
    if (arquivo.fail()) {

        cout << "Não foi possível abrir o arquivo!\n";
        exit(1); 
    }

    while (getline(arquivo,linha)) {

        stringstream s(linha);

        while (s >> palavra) {
            palavra = limpa(palavra);
            this->insere(palavra, 1);
        }
    }

    arquivo.close();


}

string limpa (string palavra) {

    int n = palavra.length();

    if (palavra[n-1] < 'A' || (palavra[n-1] > 'Z' && palavra[n-1] < 'a') || palavra[n-1] > 'z')
        palavra.pop_back();
    switch (palavra[0]) {
    case '!':
        palavra.erase(palavra.begin());
        break;
    case '?':
        palavra.erase(palavra.begin());
        break;
    case '.':
        palavra.erase(palavra.begin());
        break;
    case ',':
        palavra.erase(palavra.begin());
        break;
    case ':':
        palavra.erase(palavra.begin());
        break;
    case ';':
        palavra.erase(palavra.begin());
        break;
    case '(':
        palavra.erase(palavra.begin());
        break;
    case ')':
        palavra.erase(palavra.begin());
        break;
    case '\'':
        palavra.erase(palavra.begin());
        break;
    case '"':
        palavra.erase(palavra.begin());
        break;
    default:
        break;
    }
    return palavra;
}