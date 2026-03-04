/*Elabore uma unidade sintática para representar uma estrutura de fila estática e operações e relações
para criar uma fila, verificar se uma fila está vazia, verificar se há espaço na fila, recuperar o número
de elementos da fila, verificar se um determinado elemento está na fila, verificar se uma posição
qualquer é válida, recuperar um elemento da fila, recuperar a posição de um elemento da fila,
recuperar o primeiro elemento da fila, recuperar o último elemento da fila, inserir um elemento,
retirar um elemento e exibir os elementos da fila*/


template <typename T, int M>
struct Fila{
    int card;
    int start;
    int end;
    T elements[M];
};

template <typename T, int M>
void create(Fila<T,M> &fila){
    fila.card = 0;
    fila.start = 0;
    fila.end = 0;
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
int find_element(Fila<T,M> &fila, T element){
    if(empty(fila)) return -1;
    if(fila.end == M){
        for(int i = fila.start+1; i <= fila.end; i++){
            if(fila.elements[i-1] == element){
                return i-1;
            }
        }
    } else {
        int j = fila.start;
        for(int i = 0; i < size(fila); i++){
            if(j == M){
                j = 0;
            }
            if(fila.elements[j] == element){
                return j+1;
            }
            j++;
        }
    }

    return -1;
}