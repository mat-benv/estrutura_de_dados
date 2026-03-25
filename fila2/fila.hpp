/*Elabore uma unidade sintática para representar uma estrutura de fila estática e operações e relações
para criar uma fila, verificar se uma fila está vazia, verificar se há espaço na fila, recuperar o número
de elementos da fila, verificar se um determinado elemento está na fila, verificar se uma posição
qualquer é válida, recuperar um elemento da fila, recuperar a posição de um elemento da fila,
recuperar o primeiro elemento da fila, recuperar o último elemento da fila, inserir um elemento,
retirar um elemento e exibir os elementos da fila*/

#include <iostream>

template <typename T, int M>
struct Fila{
    int card;
    int start; //physical
    int end; //logical
    T elements[M];
};

template <typename T, int M>
void create(Fila<T,M> &fila){
    fila.card = 0;
    fila.start = M-1;
    fila.end = M-1;
}

template <typename T, int M>
bool empty(Fila<T,M> &fila){
    return fila.card == 0;
}

template <typename T, int M>
bool have_space(Fila<T,M> &fila){
    return fila.card < M;
}

template <typename T, int M>
int size(Fila<T,M> &fila){
    return fila.card;
}

template <typename T, int M>
int get_position(Fila<T,M> &fila, T element){
    if(empty(fila)) return -1;
    if(fila.end == M){
        for(int i = fila.start+1; i <= fila.end; i++){
            if(fila.elements[i-1] == element){
                return i-1;
            }
        }
    } else {
        int j = fila.start;
        for(int i = 0; i < fila.card; i++){
            j++;
            if(j >= M){
                j = 0;
            }
            if(fila.elements[j] == element){
                return i+1;
            }
        }
    }

    return -1;
}

template <typename T, int M>
bool exists(Fila<T,M> &fila, T element){
    int i = get_position(fila, element);
    return i > 0;
}

template <typename T, int M>
bool valid_position(Fila<T,M> &fila, int pos){
    return pos > 0 && pos <= fila.card;
}

template <typename T, int M>
int get_element(Fila<T,M> &fila, int pos){
    if(not valid_position(fila, pos)){
        throw "INVALID POSITION";
    }
    if((fila.start + pos) <= M-1){
        return fila.elements[fila.start + pos];
    } else {
        return fila.elements[pos - M + fila.start];
    }
}

template <typename T, int M>
T next_in_line(Fila<T,M> &fila){
    if(fila.start == M-1) return fila.elements[0];
    else return fila.elements[fila.start+1];
}

template <typename T, int M>
T last_in_line(Fila<T,M> &fila){
    return fila.elements[fila.end];
}

template <typename T, int M>
void insert(Fila<T,M> &fila, T element){
    if(! have_space(fila)){
        throw "OVERFLOW";
    }

    fila.end++;
    if(fila.end > M-1){
        fila.end = 0;
    }
    fila.elements[fila.end] = element;
    fila.card++;
}

template <typename T, int M>
void remove(Fila<T,M> &fila){
    if(empty(fila)){
        throw "UNDERFLOW";
    }
    fila.start++;
    if(fila.start > M-1){
        fila.start = 0;
    }
    fila.card--;
}

template <typename T, int M>
void show(Fila<T,M> &fila){
    if(empty(fila)){
        throw "LIST EMPTY";
    }
    int j = fila.start;
    for(int i = 0; i < fila.card; i++){
        j++;
        if(j > M-1){
            j = 0;
        }
        std::cout << fila.elements[j] << " ";
    }
    std::cout << std::endl;
}

template <typename T, int M>
bool same_elements(Fila<T,M> &fila1, Fila<T,M> &fila2){
    int j = fila1.start;
    for(int i = 0; i < fila1.card; i++){
        j++;
        if(j > M-1){
            j = 0;
        }
        if(! exists(fila2, fila1.elements[j])){
            return false;
        };
    }
    return true;
}