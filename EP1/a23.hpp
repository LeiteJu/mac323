// Árvore 2-3
#ifndef _A23_H_
#define _A23_H_

#include <bits/stdc++.h>
using namespace std;

template<class Chave, class Item>
class No_23 {

    public:

        Chave chave1;
        Chave chave2;

        Item valor1;
        Item valor2;

        No_23<Chave,Item>* ap1;
        No_23<Chave,Item>* ap2;
        No_23<Chave,Item>* ap3;
        No_23<Chave,Item>* pai;

        bool doisNo;
        bool ehFolha;

        No_23();

};

template<class Chave, class Item>
class A23 {

    private:

        No_23<Chave,Item>* raiz;
        void leArquivo (string nome);
        No_23<Chave,Item>* put (No_23<Chave,Item>* root, Chave ch, Item val, bool &cresceu);
        Item get (No_23<Chave,Item>* root, Chave ch);
        int soma (No_23<Chave,Item>* root, Chave ch);
        Chave find (No_23<Chave,Item>* root,int k);
        void delA23 (No_23<Chave,Item>* root);
        No_23<Chave,Item>* del (No_23<Chave,Item>* root, Chave ch);

    public:

        A23 (string nome);
        void insere (Chave chave, Item valor);
        Item devolve (Chave chave);
        int rank (Chave chave);
        Chave seleciona (int k);
        void remove (Chave chave);
        void show (No_23<Chave,Item>* root);
        No_23<Chave,Item>* getRaiz ();
        ~A23();

};

#endif

/***** No_23 *****/
template<class Chave, class Item>
No_23<Chave,Item>::No_23() {
    this->chave1 = this->chave2 = "";
    this->valor1 = this->valor2 = 0;
    this->ap1 = this->ap2 = this->ap3 = this->pai = nullptr;
    this->ehFolha = true;
    this->doisNo = true;
}

/***** Arvore 23 *****/
template<class Chave,class Item>
A23<Chave,Item>::A23(string nome) {
    this->raiz = nullptr;
    leArquivo (nome);
}

template<class Chave, class Item>
void A23<Chave,Item>::insere (Chave chave, Item valor) {
    bool cresceu = false;
    this->raiz = put (this->raiz, chave, valor, cresceu);
}

template<class Chave, class Item>
No_23<Chave,Item>* A23<Chave,Item>::put (No_23<Chave,Item>* root, Chave ch, Item val, bool &cresceu) {

    // Caso A: raiz é nula
    if (root == nullptr) {
        root = new No_23<Chave,Item>;
        root->chave1 = ch;
        root->valor1 = val;
        cresceu = true;
        return root;
    }

    // se já está na árvore
    if (root->chave1 == ch) {
        root->valor1 += val;
        cresceu = false;
        return root;
    }
    if (!root->doisNo && root->chave2 == ch) {
        root->valor2 += val;
        cresceu = false;
        return root;
    }

    // Caso B: é folha
    if (root->ehFolha) {

        // Caso 1: é 2 nó 
        if (root->doisNo) { // inserimos no lugar certo
            if (root->chave1 < ch) {
                root->chave2 = ch;
                root->valor2 = val;
            }
            else {
                root->chave2 = root->chave1; 
                root->valor2 = root->valor1;
                root->chave1 = ch; 
                root->valor1 = val;
            }
            cresceu = false;
            root->doisNo = false;
            return root;
        }
        // Caso 2: é 3 nó
        No_23<Chave,Item>* meio = new No_23<Chave,Item>; 
        No_23<Chave,Item>* maior = new No_23<Chave,Item>;

        // Vamos acertar os ponteiros
        if (ch > root->chave2) { // chave1 < chave2 < ch 
            maior->chave1 = ch;
            maior->valor1 = val;
            meio->chave1 = root->chave2;
            meio->valor1 = root->valor2;
        }
        else if (ch < root->chave1) { // ch < chave1 < chave2
            maior->chave1 = root->chave2;
            maior->valor1 = root->valor2;
            meio->chave1 = root->chave1;
            meio->valor1 = root->valor1;
            root->chave1 = ch;
            root->valor1 = val;
        }
        else { // chave1 < ch < chave2
            maior->chave1 = root->chave2;
            maior->valor1 = root->valor2;
            meio->chave1 = ch;
            meio->valor1 = val;
            
        }

        meio->pai = root->pai;
        root->pai = maior->pai = meio;

        root->doisNo = true;
        meio->ap1 = root;
        meio->ap2 = maior;
        meio->ehFolha = false;
        cresceu = true;
        return meio;
    }
    // Caso C: não é folha
    if (root->doisNo) { // 1.: se for dois nó

        if (ch < root->chave1) {
            root->ap1 = put (root->ap1, ch, val, cresceu);
            if (cresceu) { // transformamos em 3 nó
                No_23<Chave,Item>* novo = root->ap1;
                root->chave2 = root->chave1;
                root->valor2 = root->valor1;
                root->doisNo = false;
                root->chave1 = novo->chave1;
                root->valor1 = novo->valor1;
                root->ap1 = novo->ap1;
                root->ap3 = root->ap2;
                root->ap2 = novo->ap2;
                root->ap1->pai = root->ap2->pai = root->ap3->pai = root;
                delete novo;
            }
            cresceu = false;
            return root;
        }
        // então ch > root->chave1
        root->ap2 = put (root->ap2, ch, val, cresceu);
        if (cresceu) {
            No_23<Chave,Item>* novo = root->ap2;
            root->chave2 = novo->chave1;
            root->valor2 = novo->valor1;
            root->doisNo = false;
            root->ap3 = novo->ap2;
            root->ap2 = novo->ap1;
            root->ap1->pai = root->ap2->pai = root->ap3->pai = root;
            delete novo;
        }
        cresceu = false;
        return root;
    }
    //Caso 2: é 3 no


    if (ch < root->chave1) {

        root->ap1 = put (root->ap1, ch, val, cresceu);

        // se não cresceu, retornamos
        if (!cresceu)
            return root;
        
        No_23<Chave,Item>* newRoot = new No_23<Chave,Item>;
        No_23<Chave,Item>* maior = new No_23<Chave,Item>;
        No_23<Chave,Item>* menor = root->ap1;

        maior->chave1 = root->chave2;
        maior->valor1 = root->valor2;
        maior->ap1 = root->ap2;
        maior->ap1->pai = maior;
        maior->ap2 = root->ap3;
        maior->ap2->pai = maior;

        newRoot->chave1 = root->chave1;
        newRoot->valor1 = root->valor1;

        newRoot->ehFolha = menor->ehFolha = maior->ehFolha = false;
        newRoot->pai = root->pai;
        newRoot->ap1 = menor;
        menor->pai = newRoot;
        newRoot->ap2 = maior;
        maior->pai = newRoot;

        delete root;
        return newRoot;

    }
    else if (ch > root->chave2) {

        root->ap3 = put (root->ap3, ch, val, cresceu);

        if (!cresceu)
            return root;
        
        No_23<Chave,Item>* newRoot = new No_23<Chave,Item>;
        newRoot->chave1 = root->chave2;
        newRoot->valor1 = root->valor2;

        No_23<Chave,Item>* maior = root->ap3;

        No_23<Chave,Item>* menor = new No_23<Chave,Item>;
        menor->chave1 = root->chave1;
        menor->valor1 = root->valor1;
        menor->ap1 = root->ap1;
        menor->ap1->pai = menor;
        menor->ap2 = root->ap2;
        menor->ap2->pai = menor;

        newRoot->ehFolha = menor->ehFolha = maior->ehFolha = false;
        newRoot->pai = root->pai;
        newRoot->ap1 = menor;
        menor->pai = newRoot;
        newRoot->ap2 = maior;
        maior->pai = newRoot;
        
        delete root;
        return newRoot;

    }
    
    root->ap2 = put (root->ap2, ch, val, cresceu);

    if (!cresceu)
        return root;

    No_23<Chave,Item>* newRoot = root->ap2;
    
    No_23<Chave,Item>* menor = new No_23<Chave,Item>;
    menor->chave1 = root->chave1;
    menor->valor1 = root->valor1;
    menor->ap1 = root->ap1;
    menor->ap1->pai = menor;
    menor->ap2 = newRoot->ap1;
    menor->ap2->pai = menor;

    No_23<Chave,Item>* maior = new No_23<Chave,Item>;
    maior->chave1 = root->chave2;
    maior->valor1 = root->valor2;
    maior->ap1 = newRoot->ap2;
    maior->ap1->pai = maior;
    maior->ap2 = root->ap3;
    maior->ap2->pai = maior;

    newRoot->ehFolha = menor->ehFolha = maior->ehFolha = false;
    newRoot->pai = root->pai;
    newRoot->ap1 = menor;
    menor->pai = newRoot;
    newRoot->ap2 = maior;
    maior->pai = newRoot;

    delete root;
    return newRoot;

}

template<class Chave, class Item>
Item A23<Chave,Item>::devolve (Chave chave) {
    return get (this->raiz, chave);
}

template<class Chave, class Item>
Item A23<Chave,Item>::get (No_23<Chave,Item>* root, Chave ch) {

    if (root == nullptr)
        return 0;
    if (root->chave1 > ch)
        return get (root->ap1, ch);
    if (root->chave1 == ch)
        return root->valor1;
    if (root->doisNo)
        return get (root->ap2, ch);
    if (root->chave2 == ch)
        return root->valor2;
    if (root->chave2 < ch)
        return get (root->ap3, ch);
    return get (root->ap2, ch);
}

template<class Chave, class Item>
int A23<Chave,Item>::rank (Chave chave) {
    if (devolve(chave) == 0)
        return -1;
    return soma (this->raiz, chave);
}

template <class Chave, class Item>
int A23<Chave,Item>::soma (No_23<Chave,Item>* root, Chave ch) {
    if (root == nullptr)
        return 0;
    if (root->doisNo) {
        if (root->chave1 < ch)
            return 1 + soma (root->ap1, ch) + soma (root->ap2, ch);
        return soma (root->ap1, ch) + soma (root->ap2, ch);
    }
    int x = 0;
    if (root->chave1 < ch)
        x++;
    if (root->chave2 < ch)
        x++;
    return x + soma (root->ap1, ch) + soma (root->ap2, ch) + soma (root->ap3, ch);
}

template<class Chave, class Item>
Chave A23<Chave,Item>::find (No_23<Chave,Item>* root, int k) {
    int aux;
    if (root == nullptr)
        return "";
    aux = rank(root->chave1);
    if (k < aux)
        return find (root->ap1, k);
    if (aux == k)
        return root->chave1;
    if (root->doisNo)
        return find (root->ap2, k);
    aux = rank (root->chave2);
    if (k < aux)
        return find (root->ap2, k);
    if (k == aux)
        return root->chave2;
    return find (root->ap3, k);
}

template <class Chave, class Item>
Chave A23<Chave,Item>::seleciona (int k) {
    return find (this->raiz, k);
}

template<class Chave, class Item>
void A23<Chave,Item>::remove (Chave chave) {
    this->raiz = del (raiz, chave);
}

template<class Chave, class Item>
No_23<Chave,Item>* A23<Chave,Item>::getRaiz () {
    return this->raiz;
} 

template<class Chave, class Item>
void A23<Chave,Item>::show (No_23<Chave,Item>* root) {

    if (root == nullptr) 
        return;

    show (root->ap1); // 1º apontador
    cout << "Rank: " << this->rank (root->chave1) << " Palavra: " << root->chave1 << " Nº: " << root->valor1 << endl;
    show (root->ap2); // 2º

    if (root->doisNo) // se for 2 nó, saímos
        return;
    cout << "Rank: " << this->rank (root->chave2) << "Palavra: " << root->chave2 << " Nº: " << root->valor2 << endl;
    show (root->ap3);
}

template<class Chave, class Item>
No_23<Chave,Item>* A23<Chave,Item>::del (No_23<Chave,Item>* root, Chave ch) {

    No_23<Chave,Item>* alvo = root;

    while (alvo != nullptr) {
        if (ch < alvo->chave1)
            alvo = alvo->ap1;
        else if (!alvo->doisNo && alvo->chave2 < ch)
            alvo = alvo->ap3;
        else if (alvo->chave1 == ch || (!alvo->doisNo && alvo->chave2 == ch))
            break;
        else
            alvo = alvo->ap2;
    }

    // Caso 0: não está na tabela
    if (alvo == nullptr)
        return root;


    // Se não for folha, trocamos pelo último filho da sub-árvore esquerda
    if (!alvo->ehFolha) {
        No_23<Chave,Item>* aux = (alvo->chave1 == ch) ? (alvo->ap1) : (alvo->ap2);
        bool achei = false;
        while (!achei) {
            if (aux->doisNo && aux->ap2 != nullptr)
                aux = aux->ap2;
            else if (!aux->doisNo && aux->ap3 != nullptr) 
                aux = aux->ap3;
            else 
                achei = true;
        }
        if (alvo->chave1 == ch) {
            alvo->chave1 = (aux->doisNo) ? (aux->chave1) : (aux->chave2);
            alvo->valor1 = (aux->doisNo) ? (aux->valor1) : (aux->valor2);
        }
        else {
            alvo->chave2 = (aux->doisNo) ? (aux->chave1) : (aux->chave2);
            alvo->valor2 = (aux->doisNo) ? (aux->valor1) : (aux->valor2);
        }
        (aux->doisNo) ? (aux->chave1 = ch) : (aux->chave2 = ch);
        alvo = aux;
    }

    // Caso 1: folha 3 nó 
    if (!alvo->doisNo) {
        if (alvo->chave1 == ch) {
            alvo->chave1 = alvo->chave2;
            alvo->valor1 = alvo->valor2;
        }
        alvo->doisNo = true;
        return root;
    }

    // Em todos os casos a seguir, o alvo é 2 nó

    No_23<Chave,Item>* p = alvo->pai;
    int filho;

    if (p == nullptr) {
        delete alvo;
        return nullptr;
    }
    
    if (p->ap1 == alvo) {
        filho = -1;
        p->ap1 = nullptr;
    }
    else if (p->ap2 == alvo) {
        filho = 0;
        p->ap2 = nullptr;
    }
    else { 
        filho = 1;
        p->ap3 = nullptr;
    }
    

    delete alvo;
    alvo = nullptr;

    while (p!= nullptr) {

        if (p->doisNo) {

            No_23<Chave,Item>* irmao = (filho == -1) ? (p->ap2) : (p->ap1);

            // Caso 2: pai 2 nó e irmão 2 nó
            if (irmao->doisNo) {

                if (irmao == p->ap1) {
                    
                    p->chave2 = p->chave1;
                    p->valor2 = p->valor1;
                    p->chave1 = irmao->chave1;
                    p->valor1 = irmao->valor1;
                    p->ap1 = irmao->ap1;
                    p->ap2 = irmao->ap2;
                    p->ap3 = alvo;

                }
                else {

                    p->chave2 = irmao->chave1;
                    p->valor2 = irmao->valor1;
                    p->ap1 = alvo;
                    p->ap2 = irmao->ap1;
                    p->ap3 = irmao->ap2;
                }
                p->doisNo = false;
                p->ehFolha = irmao->ehFolha;
                if (p->ap1 != nullptr)
                    p->ap1->pai = p;
                if (p->ap2 != nullptr)
                    p->ap2->pai = p;
                if (p->ap3 != nullptr)
                    p->ap3->pai = p;

                alvo = p;
                delete irmao;
                irmao = nullptr;
                p = p->pai;
                if (p != nullptr) {
                    if (p->ap1 == alvo)
                        filho = -1;
                    else if (p->ap2 == alvo)
                        filho = 0;
                    else 
                        filho = 1;
                }
            }

            // Caso 3: pai pobre e irmão rico
            else {

                No_23<Chave,Item>* newIrmao = new No_23<Chave,Item>;
                newIrmao->chave1 = p->chave1;
                newIrmao->valor1 = p->valor1;
                newIrmao->ehFolha = irmao->ehFolha;
                newIrmao->pai = p;
                irmao->doisNo = true;
                
                if (filho == -1) {
                    newIrmao->ap1 = alvo;
                    newIrmao->ap2 = irmao->ap1;

                    p->chave1 = irmao->chave1;
                    p->valor1 = irmao->valor1;
                    p->ap1 = newIrmao;
                    
                    irmao->chave1 = irmao->chave2;
                    irmao->valor1 = irmao->valor2;
                    irmao->ap1 = irmao->ap2;
                    irmao->ap2 = irmao->ap3;
                    irmao->ap3 = nullptr;
                }

                else {
                    newIrmao->ap1 = irmao->ap3;
                    newIrmao->ap2 = alvo;
                    p->chave1 = irmao->chave2;
                    p->valor1 = irmao->valor2;
                    p->ap2 = newIrmao;
                    irmao->ap3 = nullptr;
                }

                if (newIrmao->ap1 != nullptr)
                    newIrmao->ap1->pai = newIrmao;
                if (newIrmao->ap2 != nullptr)
                    newIrmao->ap2->pai = newIrmao;
                return root;
            }            

        }
        else { // o pai é 3 nó

            No_23<Chave,Item>* irmao = nullptr;

            if (alvo == p->ap1)
                irmao = p->ap2;
            else if (alvo == p->ap2)
                irmao = (!p->ap1->doisNo) ? (p->ap1) : (p->ap3);
            else
                irmao = p->ap2;
            
            // Caso 4: pai 3 nó e irmão 3 nó
            if (!irmao->doisNo) {
                No_23<Chave,Item>* newIrmao = new No_23<Chave,Item>;
                newIrmao->pai = p;
                if (alvo == p->ap1) {

                    newIrmao->chave1 = p->chave1;
                    newIrmao->valor1 = p->valor1;
                    
                    newIrmao->ap1 = alvo;
                    newIrmao->ap2 = irmao->ap1;

                    p->ap1 = newIrmao;
                    p->chave1 = irmao->chave1;
                    p->valor1 = irmao->valor1;

                    irmao->chave1 = irmao->chave2;
                    irmao->valor1 = irmao->valor2;
                    irmao->doisNo = true;
                    irmao->ap1 = irmao->ap2;
                    irmao->ap2 = irmao->ap3;
                    irmao->ap3 = nullptr;

                }
                else if (alvo == p->ap3) {
                    
                    newIrmao->chave1 = p->chave2;
                    newIrmao->valor1 = p->valor2;
                    newIrmao->ap2 = alvo;
                    newIrmao->ap1 = irmao->ap3;

                    p->valor2 = irmao->valor2;
                    p->chave2 = irmao->chave2;
                    p->ap3 = newIrmao;

                }
                else if (irmao == p->ap1) {
                    
                    newIrmao->chave1 = p->chave1;
                    newIrmao->valor1 = p->valor1;
                    newIrmao->ap2 = alvo;
                    newIrmao->ap1 = irmao->ap3;

                    p->chave1 = irmao->chave2;
                    p->valor1 = irmao->valor2;
                    p->ap2 = newIrmao;

                }
                else {

                    newIrmao->chave1 = p->chave2;
                    newIrmao->valor1 = p->valor2;
                    newIrmao->ap1 = alvo;
                    newIrmao->ap2 = irmao->ap1;

                    p->chave2 = irmao->chave1;
                    p->valor2 = irmao->valor1;
                    p->ap2 = newIrmao;

                    irmao->chave1 = irmao->chave2;
                    irmao->valor1 = irmao->valor2;
                    irmao->ap1 = irmao->ap2;
                    irmao->ap2 = irmao->ap3;
                }
                
                if (newIrmao->ap1 != nullptr)
                    newIrmao->ap1->pai = newIrmao;
                if (newIrmao->ap2 != nullptr)
                    newIrmao->ap2->pai = newIrmao;
                if (newIrmao->ap3 != nullptr)
                    newIrmao->ap3->pai = newIrmao;
                newIrmao->ehFolha = irmao->ehFolha;
                irmao->doisNo = true;
                irmao->ap3 = nullptr;
                return root;
            }

            // Caso 5: pai 3 nó e irmao 2 nó
            else {
                
                if (alvo == p->ap1) {

                    irmao->chave2 = irmao->chave1;
                    irmao->valor2 = irmao->valor1;
                    irmao->chave1 = p->chave1;
                    irmao->valor1 = p->valor1;
                    irmao->doisNo = false;
                    irmao->ap3 = irmao->ap2;
                    irmao->ap2 = irmao->ap1;
                    irmao->ap1 = alvo;

                    p->chave1 = p->chave2;
                    p->valor1 = p->valor2;
                    p->doisNo = true;
                    p->ap1 = p->ap2;
                    p->ap2 = p->ap3;
                    p->ap3 = nullptr;

                }
                else if (alvo == p->ap3) {
                    irmao->chave2 = p->chave2;
                    irmao->valor2 = p->valor2;
                    irmao->ap3 = alvo;
                    irmao->doisNo = false;
                    p->doisNo = true;
                    p->ap3 = nullptr;

                }
                else {

                    irmao->chave2 = irmao->chave1;
                    irmao->valor2 = irmao->valor1;
                    irmao->chave1 = p->chave2;
                    irmao->valor1 = p->valor2;
                    irmao->ap3 = irmao->ap2;
                    irmao->ap2 = irmao->ap1;
                    irmao->ap1 = alvo;
                    irmao->doisNo = false;

                    p->doisNo = true;
                    p->ap2 = p->ap3;
                    p->ap3 = nullptr;

                }

                if (irmao->ap1 != nullptr)
                    irmao->ap1->pai = irmao;
                if (irmao->ap2 != nullptr)
                    irmao->ap2->pai = irmao;
                if (irmao->ap3 != nullptr)
                    irmao->ap3->pai = irmao;
                return root;
            }
        }
    }
    return root;
}

template<class Chave, class Item>
void A23<Chave,Item>::delA23 (No_23<Chave,Item>* root) {
    if (root == nullptr)
        return;
    delA23 (root->ap1);
    delA23 (root->ap2);
    delA23 (root->ap3);
    delete root;
    return;
}

template<class Chave, class Item>
A23<Chave,Item>::~A23 () {
    delA23 (this->raiz);
}

template<class Chave, class Item>
void A23<Chave,Item>::leArquivo (string nome) {

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
            this->insere(palavra, 1);
        }
    }

    arquivo.close();
}