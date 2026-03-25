/*Desenvolva um programa para simular uma bilheteria de um cinema durante os 45 minutos que
antecedem a sessão. A cada minuto chegam de 2 a 4 pessoas, que são dispostas em uma fila. Antes
do início da abertura da bilheteria já se encontram 12 pessoas na fila. Existe apenas um atendente,
que demora 30 segundos para vender um bilhete.
Indique o número de pessoas que vieram assistir determinado filme e quantas pessoas estavam na
fila da bilheteria quando a sessão teve início.*/
#include <cstdlib>
#include "fila.hpp"

#define M 100

int main(){

    srand(time(0));
    Fila<int, M> fila;
    int total_people = 0;

    create(fila);

    for(int i = 0; i < 12; i++){
        insert(fila, 1);
        total_people++;
    }

    for(int i = 0; i < 90; i++){
        if(i%2 != 0){
            for(int j = (rand() % 3) + 2; j > 0; j--){
                insert(fila, 1);
                total_people++;
            }
        }
        if(! empty(fila)) remove(fila);
        show(fila);
    }

    std::cout << "Pessoas que vieram: " << total_people << '\n'
    << "Pessoas ainda na fila: " << size(fila);

    
    return 0;
}