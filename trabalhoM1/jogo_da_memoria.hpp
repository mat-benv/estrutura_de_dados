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
    int id; //identificador único
    string simbolo; //emoji
    bool oculta; // estado
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
    ListaDinamica<Bonus> bonus; // lista dos bonus
    string pares; //pares feitos
} Jogador;

void inicializa_tabuleiro(ListaDinamica<Carta> &tabuleiro, bool preenchido[]){

    /*
    Prepara lista encadeada e lista de referência (estilo bag)
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinâmica que contém as cartas ainda em jogo.
        bool preenchido[]: vetor com referência para saber a presença da carta. É inicializado totalmente com True.
    */

    cria(tabuleiro);
    
    string simbolos[15]{
        "🍎", "🍐", "🍊", "🍋", "🍌", 
        "🍉", "🍇", "🍓", "🫐", "🍈", 
        "🍒", "🍑", "🥭", "🍍", "🥥"
    };
    /*string simbolos[15]{
        "AA", "BB", "CC", "DD", "EE",
        "FF", "GG", "HH", "II", "JJ",
        "KK", "LL", "MM", "NN", "PP"
    }*/
    
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

    /*string simbolos_especiais[6]{
        "**",
        "!!", "!!",
        "%%",
        "@@", "@@"
    }*/

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

    /*
    Prepara struct do jogador, o mais importe é que inicializa a lista dinâmica dos bonus/penalidades.
    Args:
        Jogador &j: struct do jogador
        string nome: Nome do jogador
    */

    j.nome = nome;
    cria(j.bonus);
    j.pontos = 0;
    j.pares = "";
}

void desenha_tabuleiro(ListaDinamica<Carta> &tabuleiro, bool preenchido[]){

    /*
    Mostra o tabuleiro em seu estado atual.
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinâmica que contém as cartas do jogo
        bool preenchido[]: vetor com referência para saber a presença da carta
    */

    cout << "Tabuleiro:\n";
    Nodo<Carta> *p = tabuleiro.inicio;
    Carta c;
    int i = 0;
    while(i < 36){
        cout << "|";

        if(preenchido[i]){
            if(p != NULL){
                c = p->elemento;
                if(c.oculta){
                    cout << setw(2) << "🎴";
                    //cout << setw(2) << "00";
                } else {
                    cout << setw(2) << c.simbolo;
                }
                p = p->prox;
            } else {
                cout << setw(2) << " ";
            }
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

int procura_bonus(Jogador &j, string simbolo){

    /*
    Verifica se determinado bônus/penalidade está presente na lista do jogador.
    Args:
        Jogador &j: struct do jogador
        string simbolo: simbolo do bônus a ser procurado.
    Returns:
        int: Posição lógica do simbolo na lista ou -1 se não estiver presente*/

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

    /*
    Verifica se o jogo terminou. No caso, se não há mais cartas no tabuleiro.
    Args:
        bool vet[]: vetor de referência do tabuleiro.
    Returns:
        bool: se o jogo acabou ou não*/

    for(int i=0; i<36; i++){
        if(vet[i] == true)
            return false;
    }
    return true;
}

template <typename T> 
Nodo<T>* acessa_posicao(ListaDinamica<T> &lista, bool preenchido[], int pos){
    /*
    Procura determinada carta na lista dinamica.
    Args:
        ListaDinamica<T> &lista: lista dinâmica que contém as cartas.
        bool preenchido[]: vetor de referência do tabuleiro, para iterar propriamente com posição lógica.
        int pos: posição lógica.
    Returns:
        Nodo<T>*: ponteiro para endereço da carta selecionada.
    */
    Nodo<T>* p = lista.inicio;
    for(int i = 1; i < pos; i++){
        if(preenchido[i-1]){
            p = p->prox;
        }
    }
    return p;
}

Carta virar_carta(ListaDinamica<Carta> &lista, bool preenchido[], int pos){
    /*
    Vira determinada carta para cima e devolve o struct dela
    Args:
        ListaDinamica<Carta> &lista: lista dinamica que contém as cartas ainda em jogo
        bool preenchido[]: lista de referência para presença da carta no tabuleiro
        int pos: posição lógica da carta
    Returns:
        Carta: struct da carta selecionada.
    */
    Nodo<Carta>* p = acessa_posicao(lista, preenchido, pos);
    p->elemento.oculta = false;
    return p->elemento;
}

void desvirar_carta(ListaDinamica<Carta> &lista, bool preenchido[], int pos){
    /*
    Muda o valor de oculta para True
    Args:
        ListaDinamica<Carta> &lista: lista dinamica que contém as cartas ainda em jogo
        bool preenchido[]: lista de referência para presença da carta no tabuleiro
        int pos: posição lógica da carta
    */
    Nodo<Carta>* p = acessa_posicao(lista, preenchido, pos);
    p->elemento.oculta = true;
}

bool verifica_se_eh_par(Carta c1, Carta c2){
    /*
    Verifica se dadas 2 cartas formam par, mesmo se com coringa.
    Args:
        Carta c1: primeira carta
        Carta c2: segunda carta
    Returns:
        bool: se é par ou não*/
    if((c1.simbolo=="⭐" && c2.tipo == NORMAL)|| (c2.simbolo=="⭐" && c1.tipo == NORMAL))
        return true;
    if(c1.tipo == NORMAL && c2.tipo == NORMAL){
        if(c1.simbolo == c2.simbolo){
            return true;
        }
    }
    return false;
}

void aplica_bonus(Jogador &j, Carta c){
    /*
    Adiciona bonus da carta na lista de bonus do jogador
    Args:
        Jogador &j: jogador
        Carta c: carta
    */
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
    /*
    Encontra posição lógica na lista encadeada
    Args:
        bool preenchido[]: vetor de referência para presença de cartas no tabuleiro
        int pos_tab: posição lógica do espaço que a carta está ocupando no tabuleiro
    Returns:
        int: posição lógica da carta na lista encadeada
    */
    int pos_lista = 0;
    for(int i = 0; i < pos_tab; i++){
        if(preenchido[i]){
            pos_lista++;
        }
    }
    return pos_lista;
}

void remove_carta(ListaDinamica<Carta> &tabuleiro, bool vet[], int p){
    /*
    Remove uma carta do jogo
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinamica que contém as cartas ainda em jogo
        bool vet[]: lista de referência para presença da carta no tabuleiro
        int p: posição lógica do espaço da carta no tabuleiro
    */
    int n = acha_carta(vet, p);
    remove(tabuleiro, n);
    if(p >= 1 && p <= 36){
        vet[p-1] = false;
    }
}

void aplica_ponto(Jogador &j, Carta c){
    /*
    Adiciona ponto para jogador e adiciona o simbolo da carta na lista de pares
    Args:
        Jogador &j: jogador
        Carta c: carta
    */
    j.pares = j.pares + c.simbolo;
    j.pontos++;
}

void remove_ponto(Jogador &j){
    /*
    Remove um ponto do jogador
    Args:
        Jogador &j: jogador
    */
    if(j.pontos > 0){
        j.pontos--;
        cout << j.nome << " perdeu um ponto. \n";
    } else {
        cout << j.nome << " não tem pontos para perder. :( \n";
    }
}

void remove_par(ListaDinamica<Carta> &tabuleiro, bool preenchido[], string simbolo){
    /*
    Procura par de determinada carta e o remove de jogo
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinamica que contém as cartas ainda em jogo
        bool preenchido[]: lista de referência para presença da carta no tabuleiro
        string simbolo: simbolo do par a ser encontrado
    */


    Nodo<Carta>* p;
    int i = 0;

    p = tabuleiro.inicio;

    while(i < 36){
        if(preenchido[i]){
            if(simbolo == p->elemento.simbolo){
                remove_carta(tabuleiro, preenchido, i+1);
                return;
            }
            p = p->prox;
        }
        i++;
    }

}

void bonus_estrela(ListaDinamica<Carta> &tabuleiro, bool preenchido[], Carta c1, Carta c2){
    /*
    Lida com o bonus coringa, removendo de jogo o par da carta que não é o coringa
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinamica que contém as cartas ainda em jogo
        bool preenchido[]: lista de referência para presença da carta no tabuleiro
        Carta c1: primeira carta
        Carta c2: segunda carta
    */
    int id;
    if(c1.simbolo == "⭐"){
        if(c2.simbolo != "⭐"){
            remove_par(tabuleiro, preenchido, c2.simbolo);
        } else {
            return;
        }
    } else if(c2.simbolo == "⭐"){
        if(c1.simbolo != "⭐"){
            remove_par(tabuleiro, preenchido, c1.simbolo);
        } else {
            return;
        }
    }
    
}

void jogada(ListaDinamica<Carta> &tabuleiro, Jogador &j, bool preenchido[]){

    /*
    Processa jogada
    Args:
        ListaDinamica<Carta> &tabuleiro: lista dinamica que contém as cartas ainda em jogo
        Jogador &j: jogador da vez
        bool preenchido[]: lista de referência para presença da carta no tabuleiro
    */

    int o1, o2;

    system("clear");
    //system("cls");

    int pb = procura_bonus(j, "🚫");

    if(pb > 0){
        cout << j.nome << " perdeu a vez.\n";
        remove(j.bonus, pb);
        return;
    }
    
    desenha_tabuleiro(tabuleiro, preenchido);
    
    do{
        cout << j.nome << ", digite o numero da primeira carta que quer virar: ";
        cin >> o1;
    }while(not preenchido[o1-1] || (o1 < 1 || o1 > 36));

    system("clear");
    //system("cls");

    Carta c1 = virar_carta(tabuleiro, preenchido, o1);

    desenha_tabuleiro(tabuleiro,preenchido);

    do{
        cout << j.nome << ", digite o numero da segunda carta que quer virar: ";
        cin >> o2;
    }while(not preenchido[o2-1] || (o2 == o1) || (o1 < 1 || o1 > 36));

    system("clear");
    //system("cls");

    Carta c2 = virar_carta(tabuleiro,preenchido,o2);
    desenha_tabuleiro(tabuleiro,preenchido);

    if(c1.tipo!= NORMAL){
        if(c2.simbolo != "⭐"){
            aplica_bonus(j, c1);
            desvirar_carta(tabuleiro, preenchido, o2);
            remove_carta(tabuleiro, preenchido, o1);
        }
    }
    if(c2.tipo!= NORMAL){
        if(c2.simbolo != "⭐"){
            aplica_bonus(j, c2);
            desvirar_carta(tabuleiro,preenchido, o1);
            remove_carta(tabuleiro, preenchido, o2);
        }
    }
    if(verifica_se_eh_par(c1, c2)){
        cout<<"Par encontrado!"<<endl;
        aplica_ponto(j, c1);
        
        if(o1 < o2){
            remove_carta(tabuleiro, preenchido, o2);
            remove_carta(tabuleiro, preenchido, o1);
        } else {
            remove_carta(tabuleiro, preenchido, o1);
            remove_carta(tabuleiro, preenchido, o2);
        }
        
        if(c1.simbolo == "⭐" || c2.simbolo == "⭐"){
            bonus_estrela(tabuleiro, preenchido, c1, c2);
            cout<<j.nome<<" fez par com coringa!"<<endl;
        } 
    }else{
        cout<<"As cartas nao formam par!"<<endl;
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
        jogada(tabuleiro,j,preenchido);
    }
    cin.ignore();
}

void fim_de_jogo(Jogador jogadores[]){
    /*
    Mostra placar e calcula vencedor
    Args:
        Jogador jogadores[]: vetor com os dois jogadores
    */

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

bool jogar_de_novo(){
    /*
    Pergunta se o usuario quer jogar de novo
    Returns:
        bool: se quer ou não jogar
    */
   string s;
   char c;
   do{
      do{
         cout << "Jogar de novo? S/N \n"; getline(cin, s);
      }while(s.length() > 1 or s.empty());
      c = toupper(s[0]);
   }while(c != 'S' and c != 'N');
   if(c == 'N') return false; 
   else return true;
}

/*template<typename T>
void mostra_debug(const ListaDinamica<T> &lista){
    Nodo<T> *p = lista.inicio;
    int i = 1;
    while(p != NULL){
        cout << p->elemento.simbolo << i << endl;
        p = p->prox;
        i++;
    }
}
*/