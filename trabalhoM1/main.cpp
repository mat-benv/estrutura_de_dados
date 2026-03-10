#include <iostream>
#include "jogo_da_memoria.hpp"


using namespace std;


int main(){
    setlocale( LC_ALL, "pt-BR" );
    srand(time(0));
    int turno = 0; //turno atual
        ListaDinamica<Carta> tabuleiro;
        Jogador zero, um;
        Jogador jogadores[2]{zero, um};
        bool preenchido[36];
        bool opt;

    do{
        
        inicializa_tabuleiro(tabuleiro, preenchido);

        string nome;
        for(int i = 0; i < 2; i++){
            do{
                cout << "Digite o nome do Jogador " << i+1 << '\n';
                getline(cin, nome);
                inicializa_jogador(jogadores[i], nome);
            }while(nome.empty());
        }

        do{
            
            cout << "\nEh a vez de " << jogadores[turno%2].nome << ". Aperte ENTER para jogar.\n";

            cin.get();

            jogada(tabuleiro, jogadores[turno%2], preenchido);
            turno++;
            
            //mostra_debug(tabuleiro);
        }while(not fim_de_jogo(preenchido));

        cout << "FIM DE JOGO!";
        fim_de_jogo(jogadores);

        opt = jogar_de_novo();

    }while(opt);
    
    apaga(tabuleiro);

    for(int i=0; i<2; i++)
        apaga(jogadores[i].bonus);
    return 0;
}