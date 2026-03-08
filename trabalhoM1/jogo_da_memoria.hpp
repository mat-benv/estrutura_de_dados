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
        insere(tabuleiro, c, (rand() % (i+1)) + 1);
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

        insere(tabuleiro, c, (rand() % (i+1)) + 1);

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
    j.pares = "";
}

Jogador jogador_da_vez(Jogador jogadores[], int jogada){
    int i = jogada % 2;
    return jogadores[i];
}

void desenha_tabuleiro(ListaDinamica<Carta> &tabuleiro, bool preenchido[]){
    cout << "Tabuleiro:\n";
    Nodo<Carta> *p = tabuleiro.inicio;
    Carta c;
    int i = 0;
    while(i < 36){
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
            cout << '\n';
            for(int j = i - 5; j <= i; j++){
                cout << "|" << setw(2) << j << "| ";
            }
            cout << "\n\n";
        }
    }
    cout << '\n';  
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

bool fim_de_jogo(bool vet[]){
    for(int i=0; i<36; i++){
        if(vet[i] == true)
            return false;
    }
    return true;
}

template <typename T> 
Nodo<T>* acessa_posicao(ListaDinamica<T> &lista, bool preenchido[], int pos){
    Nodo<T>* p = lista.inicio;
    for(int i = 1; i < pos; i++){
        if(preenchido[i-1]){
            p = p->prox;
        }
    }
    return p;
}

Carta virar_carta(ListaDinamica<Carta> &lista, bool preenchido[], int pos){
    Nodo<Carta>* p = acessa_posicao(lista, preenchido, pos);
    p->elemento.oculta = false;
    return p->elemento;
}

void desvirar_carta(ListaDinamica<Carta> &lista, bool preenchido[], int pos){
    Nodo<Carta>* p = acessa_posicao(lista, preenchido, pos);
    p->elemento.oculta = true;
}

bool verifica_se_eh_par(Carta c1, Carta c2){
    if(c1.simbolo=="⭐" || c2.simbolo=="⭐")
        return true;
    if(c1.tipo == NORMAL && c2.tipo == NORMAL){
        if(c1.simbolo == c2.simbolo){
            return true;
        }
    }
    return false;
}

void aplica_bonus(Jogador &j, Carta c){
    Bonus b;
    if(c.simbolo =="⚡"){
        b.simbolo="⚡";
        b.duracao=1;
        b.efeito="jogada extra";
        insere(j.bonus,b,1);
    }

    if(c.simbolo=="🚫"){
        b.simbolo="🚫";
        b.duracao=1;
        b.efeito="perde a vez";
        insere(j.bonus,b,1);
    }

    if(c.simbolo=="💀"){
        b.simbolo="💀";
        b.duracao=1;
        b.efeito="perde um ponto";
        insere(j.bonus,b,1);
        j.pontos--;
    }
    //bonus do coringa aplicado na funcao eh par 
}

int acha_carta(bool preenchido[], int pos_tab){
    int pos_lista = 0;
    for(int i = 0; i < pos_tab; i++){
        if(preenchido[i]){
            pos_lista++;
        }
    }
    return pos_lista;
}

void remove_carta(ListaDinamica<Carta> &tabuleiro, bool vet[],int p){
    int n = acha_carta(vet, p);
    remove(tabuleiro, n);
    if(p >= 1 && p <= 36){
        vet[p-1] = false;
    }
}

void aplica_ponto(Jogador j, Carta c){
    j.pares += c.simbolo;
    j.pontos++;
}

void remove_ponto(Jogador j){
    if(j.pontos > 0){
        j.pontos--;
        cout << j.nome << " perdeu um ponto. \n";
    } else {
        cout << j.nome << " não tem pontos para perder. :( \n";
    }
}

void bonus_estrela(ListaDinamica<Carta> &tabuleiro, bool preenchido[], Carta c1, Carta c2){
    int id;
    if(c1.simbolo == "⭐"){
        if(c2.simbolo != "⭐"){
            id = c2.id;
        } else {
            return;
        }
    } else if(c2.simbolo == "⭐"){
        if(c1.simbolo != "⭐"){
            id = c1.id;
        } else {
            return;
        }
    }

    if(id < 15){
        id = id + 15;
    } else {
        id = id - 15;
    }

    Nodo<Carta>* p;
    int i = 1;
    p = tabuleiro.inicio;
    while(p != NULL){
        if(id == p->elemento.id){
            remove_carta(tabuleiro, preenchido, i);
            return;
        }
        i++;
    }
    
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
    }while(not preenchido[o1-1] || (o1 < 1 || o1 > 36));

    system("clear");

    Carta c1 = virar_carta(tabuleiro, preenchido, o1);

    desenha_tabuleiro(tabuleiro,preenchido);

    do{
        cout << j.nome << ", digite o numero da segunda carta que quer virar: ";
        cin >> o2;
    }while(not preenchido[o2-1] || (o2 == o1) || (o1 < 1 || o1 > 36));

    system("clear");

    Carta c2 = virar_carta(tabuleiro,preenchido,o2);
    desenha_tabuleiro(tabuleiro,preenchido);

    if(c1.tipo!= NORMAL){
        aplica_bonus(j, c1);
        remove_carta(tabuleiro, preenchido, o1);
        desvirar_carta(tabuleiro,preenchido, o2);
    }
    if(c2.tipo!= NORMAL){
        aplica_bonus(j, c2);
        remove_carta(tabuleiro, preenchido, o2);
        desvirar_carta(tabuleiro,preenchido, o1);
    }
    if(verifica_se_eh_par(c1, c2)){
        cout<<"Par encontrado!"<<endl;
        aplica_ponto(j, c1);
        remove_carta(tabuleiro, preenchido, o1);
        remove_carta(tabuleiro, preenchido, o2-1);
        if(c1.simbolo == "⭐" || c2.simbolo == "⭐"){
            bonus_estrela(tabuleiro, preenchido, c1, c2);
            pb = procura_bonus(j, "⭐");
            if(pb>0){
                cout<<j.nome<<" fez par com coringa!"<<endl;
                remove(j.bonus,pb);
            }
        }  
    }else{
        cout<<"As cartas não formam par!"<<endl;
        desvirar_carta(tabuleiro,preenchido, o1);
        desvirar_carta(tabuleiro,preenchido, o2);
    }

    pb = procura_bonus(j, "💀");
    if(pb>0){
        cout<<"Carta Penalidade encontrada - 💀"<<endl;
        remove_ponto(j);
        remove(j.bonus,pb);
    }

    pb = procura_bonus(j, "⚡");
    if(pb>0){
        cout<<j.nome<<" ganhou uma jogada extra!"<<endl;
        remove(j.bonus,pb);
        jogada(tabuleiro,jogadores,turno,preenchido);
    }
    cin.ignore();
}

void fim_de_jogo(Jogador jogadores[]){


    cout << "Placar:\n";
    for(int i = 0; i < 2; i++){
        cout << jogadores[i].nome << ": \n"
        << jogadores[i].pontos << " pontos.\n"
        << "Pares: " << jogadores[i].pares << "\n\n";
    }

    if(jogadores[0].pontos > jogadores[1].pontos){
        cout << jogadores[0].nome << " venceu!.";

    } else if(jogadores[0].pontos < jogadores[1].pontos){
        cout << jogadores[1].nome << " venceu!.";

    } else {
        cout << jogadores[0].nome << " e " << jogadores[1].nome << " empataram!";
    }
}