#include <iostream>
#include "lista_duplamente_encadeada.hpp"
#include "jogo_da_memoria.hpp"

using namespace std;

int main(){
    int turno = 0; //turno atual
    ListaDinamica<Carta> tabuleiro;
    Jogador zero, um;
    Jogador jogadores[2]{zero, um};
    bool tabuleiro_preenchido[36];

    inicializa_tabuleiro(tabuleiro, tabuleiro_preenchido);

    string nome;
    for(int i = 0; i < 2; i++){
        cout << "Digite o nome do Jogador " << i+1 << '\n';
        getline(cin, nome);
        inicializa_jogador(jogadores[i], nome);
    }

    return 0;
}