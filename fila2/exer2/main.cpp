#include "../fila.hpp"
#include <iostream>
#include <cstdlib>

/*Implemente um programa para simular um ponto de táxi durante 10 horas, cujas características são: a) a cada
5 minutos chega um número aleatório de táxis (entre 0 e 3 táxis); b) a cada 3 minutos chega um número
aleatório de passageiros (entre 0 e 2 passageiros); e c) a cada minuto, se houverem táxis e passageiros para
serem transportados, um passageiro toma um táxi.
Considere a estrutura de fila estática para representar as filas de passageiros e de táxis.
O programa deve informar o número de táxis utilizados (que fizeram o transporte de passageiros) e o tempo
médio de espera dos passageiros atendidos.*/

#define M 100

int main(){

    Fila<int,M> passageiros, taxis;
    int taxis_usados = 0, tempo_espera = 0;
    double media_espera = 0;

    create(passageiros);
    create(taxis);

    srand(time(0));

    for(int m = 0; m < 600; m++){
        if(!empty(passageiros) && !empty(taxis)){
            remove(passageiros);
            remove(taxis);
            taxis_usados++;
            media_espera += tempo_espera;
            tempo_espera = 0;
        }

        if(m % 5 == 0){
            for(int t = rand() % 4; t > 0; t--){
                queue_insert(taxis, m);
            }
        }

        if(m % 3 == 0){
            for(int p = rand() % 3; p > 0; p--){
                queue_insert(passageiros, m);
            }
        }

        tempo_espera++;
    }

    media_espera = media_espera/(double)taxis_usados;


    std::cout << "Taxis usados: " << taxis_usados
    << "\nTempo médio de espera: " << media_espera << " minutos.\n";


    return 0;
}