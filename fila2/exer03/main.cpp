/*Escreva um programa que simule um sistema computacional com as seguintes características.
Um número aleatório N é gerado no intervalo de 0 a 100, inclusive.
Caso 1. ( 0  N  49 ) Um processo é iniciado no sistema.
( 0  N  25 ) Um processo da classe A é inserido na fila A.
( 26  N  39 ) Um processo da classe B é inserido na fila B.
( 40  N  49 ) Um processo da classe C é inserido na fila C.
Caso 2. ( 50  N  100 ) Um processo termina a sua execução e um outro processo pode ser executado.
( 50  N  75 ) A partição A se torna disponível.
( 76  N  89 ) A partição B se torna disponível.
( 90  N  100 ) A partição C se torna disponível.
Se uma partição se tornar vazia e não houver processo que possa ser executado naquela partição, um novo
número aleatório é gerado e a simulação continua.
Faça a simulação para 100 iterações e a cada 5 iterações exiba o estado corrente de cada fila, o estado
corrente de cada partição e a quantidade de processos executados para cada classe de processos.
Considere a estrutura de fila estática para representar as filas envolvidas na simulação.*/

#include <iostream>
#include "../fila.hpp"
#include <cstdlib>

enum{
    FREE,
    BUSY
};

typedef struct{
    Fila<int,100> fila;
    bool status;
    int count;
} ProcessClass;

void create_process_class(ProcessClass &x){
    create(x.fila);
    x.status = FREE;
    x.count = 0;
}

void insert_process(ProcessClass &x){
    queue_insert(x.fila,1);
}

void end_process(ProcessClass &x){
    x.status = FREE;
    if(!empty(x.fila)){
        remove(x.fila);
        x.count++;
        x.status = BUSY;
    }
}


void show_status(ProcessClass &x){
    std::cout << "Queue: " << size(x.fila)
    << "\nStatus: " << (x.status ? "Busy" : "Free")
    << "\nDone: " << x.count << std::endl;
}

int main(){

    srand(time(0));
    ProcessClass A, B, C;

    create_process_class(A);
    create_process_class(B);
    create_process_class(C);

    for(int i = 0; i < 100; i++){
        int j = rand() % 101;
        if(j < 50){
            if(j < 26){
                insert_process(A);
            } else if (j < 40){
                insert_process(B);
            } else if (j < 50){
                insert_process(C);
            }
        } else {
            if(j < 76){
                end_process(A);
            } else if (j < 90){
                end_process(B);
            } else {
                end_process(C);
            }
        }
        if((i+1)%5 == 0){
            std::cout << "Process class A:\n";
            show_status(A);
            std::cout << "Process class B:\n";
            show_status(B);
            std::cout << "Process class C:\n";
            show_status(C);
            std::cout << std::endl;
        }
    }
    


    return 0;
}