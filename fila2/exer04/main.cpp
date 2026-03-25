/*Simular o movimento de um supermercado durante 5 horas. A unidade de tempo da simulação é o minuto. Há
quatro caixas de atendimento, sendo uma delas caixa-expressa que somente atende clientes com, no máximo,
6 volumes.
O funcionamento das caixas é o seguinte
caixa 1 : atende 1 cliente a cada 4 minutos
caixa 2 : atende 1 cliente a cada 5 minutos
caixa 3 : atende 1 cliente a cada 7 minutos
caixa 4 (caixa-expressa) : atende 1 cliente a cada 2 minutos
O número de volumes de cada cliente é aleatório, entre 1 e 50. A cada minuto chega um cliente que escolhe
para ser atendido a caixa que tiver a menor fila. Caso haja mais de uma fila com o mesmo tamanho, o cliente
escolherá a que oferecer o menor tempo de atendimento.
No início da simulação há 4 clientes na caixa 1, 3 na caixa 2, 2 na caixa 3 e 4 na caixa 4.
Admita a estrutura de fila estática para representar as filas envolvidas na simulação.*/

#include <iostream>
#include "../fila.hpp"
#include <cstdlib>

#define TIME 300

void starting_length(Fila<int,100> &cx, int cust){
    for(int i = 0; i < cust; i++){
        insert(cx, 1);
    }
}

int shortest_line(Fila<int,100> cx[], int cust){
    int k = cust < 7 ? 3 : 0;

    for(int i = 0; i < 3; i++){
        if(size(cx[i]) < size(cx[k])){
            k = i;
        }
    }
    return k;
}

int main(){

    srand(time(0));

    Fila<int, 100> caixas[4];

    for(int i = 0; i < 4; i++){
        create(caixas[i]);
    }
    starting_length(caixas[0], 4);
    starting_length(caixas[1], 3);
    starting_length(caixas[2], 2);
    starting_length(caixas[3], 4);

    for(int i = 1; i <= TIME; i++){
        int cust = rand() % 50;

        int k = shortest_line(caixas, cust);

        insert(caixas[k], cust);

        if(i%2 == 0){
            if(! empty(caixas[3])) remove(caixas[3]);
        }
        if(i%4 == 0){
            if(! empty(caixas[0])) remove(caixas[0]);
        }
        if(i%5 == 0){
            if(! empty(caixas[1])) remove(caixas[1]);
        }
        if(i%7 == 0){
            if(! empty(caixas[2])) remove(caixas[2]);
        }

        for(int i = 0; i < 4; i++){
            try {
                show(caixas[i]);
            } catch (const char* msg){
                std::cerr << msg;
            }
            std::cout << std::endl;
        }
    }

    


    return 0;
}