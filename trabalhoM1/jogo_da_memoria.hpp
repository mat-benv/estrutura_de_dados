#include <string>
#include "lista_duplamente_encadeada.hpp"
#include <cstdlib>

enum {
    //tipo da carta
    NORMAL,
    BONUS,
    PENALIDADE
};

typedef struct{
    int id;
    std::string simbolo;
    bool oculta;
    int tipo;
} Carta;

typedef struct{
    char simbolo;
    int duracao;
    std::string efeito;
} Bonus;

template<typename T>
void inicializa_tabuleiro(ListaDinamica<Carta> &tabuleiro){

    cria(tabuleiro);
    
    std::string simbolos[17]{
        "🍎", "🍐", "🍊", "🍋", "🍌", 
        "🍉", "🍇", "🍓", "🫐", "🍈", 
        "🍒", "🍑", "🥭", "🍍", "🥥"
    };
    
    for(int i = 0; i < 30; i++){
        Carta c{
            i, 
            simbolos[i%16], 
            true, 
            NORMAL
        };
        insere(tabuleiro, rand() % (i+1));
    }
    
    std::string simbolos_especiais[6]{
        "⭐", "⭐", "⚡", "💀", "🚫", "🚫"
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

        insere(tabuleiro, rand() % (i+1));
        
    }
}