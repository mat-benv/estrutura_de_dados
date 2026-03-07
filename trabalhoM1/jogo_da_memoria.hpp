#include <string>
#include "lista_duplamente_encadeada.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

enum {
    //tipo da carta
    NORMAL, //0
    BONUS, //1
    PENALIDADE //2
};

typedef struct{
    int id;
    string simbolo;
    bool oculta;
    int tipo;
} Carta;

typedef struct{
    string simbolo;
    int duracao;
    string efeito;
} Bonus;

typedef struct{
    string nome;
    int pontos;
    ListaDinamica<Bonus> bonus;
    string pares;
} Jogador;

void inicializa_tabuleiro(ListaDinamica<Carta> &tabuleiro, bool preenchido[]){

    cria(tabuleiro);
    
    string simbolos[15]{
        "🍎", "🍐", "🍊", "🍋", "🍌", 
        "🍉", "🍇", "🍓", "🫐", "🍈", 
        "🍒", "🍑", "🥭", "🍍", "🥥"
    };
    
    for(int i = 0; i < 30; i++){
        Carta c{
            i, 
            simbolos[i%15], 
            true, 
            NORMAL
        };
        insere(tabuleiro, c, rand() % (i+1));
    }
    
    string simbolos_especiais[6]{
        "⭐", // coringa
        "⚡", "⚡", //joga 2x
        "💀", //perde 1 ponto
        "🚫", "🚫" // perde a vez
    };

    int t;

    for(int i = 30; i < 36; i++){

        t = (i < 33) ? BONUS : PENALIDADE;

        Carta c{
            i,
            simbolos_especiais[i-30],
            true,
            t
        };

        insere(tabuleiro, c, rand() % (i+1));

    }

    for(int i = 0; i < 36; i++){
        preenchido[i] = true;
    }
}

//template<typename T>
void inicializa_jogador(Jogador &j, string nome){
    j.nome = nome;
    cria(j.bonus);
    j.pontos = 0;
}

Jogador jogador_da_vez(Jogador jogadores[], int jogada){
    int i = jogada % 2;
    return jogadores[i];
}

void desenha_tabuleiro(const ListaDinamica<Carta> &tabuleiro, bool preenchido[]){
    cout << "Tabuleiro:\n";
    Nodo<Carta> *p = tabuleiro.inicio;
    Carta c;
    int i = 0;
    while(p->prox != NULL){
        cout << "|";

        if(preenchido[i]){
            c = p->elemento;
            if(c.oculta){
                cout << setw(2) << "🎴";
            } else {
                cout << setw(2) << c.simbolo;
            }
        p = p->prox;
        }else{
            cout << setw(2) << " ";
        }
        cout << "| ";
        i++;
        if(i%6 == 0){
            for(int j = i - 5; j <= i; j++){
                cout << "|" << setw(2) << j << "| ";
            }
            cout << "\n\n";
        }
    }  
}

int procura_bonus(Jogador j, string simbolo){
    Nodo<Bonus>* b;
    ListaDinamica<Bonus> lista_b;
    lista_b = j.bonus;
    b = lista_b.inicio;
    int pos = 1;

    while(b != NULL){
        if(b->elemento.simbolo == simbolo){
            return pos;
        }
        b = b->prox;
        pos++;
    }
    return -1;
}

void jogada(ListaDinamica<Carta> &tabuleiro, Jogador jogadores[], int turno, bool preenchido[]){
    Jogador j;
    
    int o1, o2;

    j = jogador_da_vez(jogadores, turno);

    int pb = procura_bonus(j, "🚫");

    if(pb > 0){
        cout << j.nome << " perdeu a vez.\n";
        remove(j.bonus, pb);
        cin.get();
        return;
    }
    
    desenha_tabuleiro(tabuleiro, preenchido);
    
    do{
        cout << j.nome << ", digite o numero da primeira carta que quer virar: ";
        cin >> o1;
    }while(not preenchido[o1]);

    Carta c2 = virar_carta(tabuleiro,o1);
    desenha_tabuleiro(tabuleiro,preenchido);

    do{
        cout << j.nome << ", digite o numero da segunda carta que quer virar: ";
        cin >> o2;
    }while(not preenchido[o2] || o2 == o1);

    Carta c2 = virar_carta(tabuleiro,o2);
    desenha_tabuleiro(tabuleiro,preenchido);

}

bool fim_de_jogo(bool vet[]){
    for(int i=0; i<36; i++){
        if(vet[i] == true)
            return false;
    }
    return true;
}

template <typename T> 
Nodo<T>* acessa_posicao(ListaDinamica<T> lista, int pos){
    Nodo<T>* p = lista.inicio;
    for(int i = 0; i < pos; i++){
        p = p->prox;
    }
    return p;
}

Carta virar_carta(ListaDinamica<Carta> &lista, int pos){
    Nodo<Carta>* p = acessa_posicao(lista,pos);
    p->elemento.oculta = false;
    return p->elemento;
}

void desvirar_carta(ListaDinamica<Carta> &lista, int pos){
    Nodo<Carta>* p = acessa_posicao(lista,pos);
    p->elemento.oculta = true;
}

bool verifica_se_eh_par(Carta c1, Carta c2){
    if(c1.tipo == NORMAL && c2.tipo == NORMAL){
        if(c1.simbolo == c2.simbolo){
            return true;
        }
    }
    return false;
}

