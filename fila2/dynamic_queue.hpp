/*Elabore uma unidade sintática para representar uma estrutura de fila estática e operações e relações
para criar uma fila, verificar se uma fila está vazia, verificar se há espaço na fila, recuperar o número
de elementos da fila, verificar se um determinado elemento está na fila, verificar se uma posição
qualquer é válida, recuperar um elemento da fila, recuperar a posição de um elemento da fila,
recuperar o primeiro elemento da fila, recuperar o último elemento da fila, inserir um elemento,
retirar um elemento e exibir os elementos da fila*/

#include <iostream>

template<typename T>
struct Node{
    T element;
    Node<T>* next;
};

template<typename T>
struct DynamicQueue{
    int card;
    Node<T>* start;
    Node<T>* end;
};

template<typename T>
void create(DynamicQueue<T> &queue){
    queue.card = 0;
    queue.start = NULL;
    queue.end = NULL;
}

template<typename T>
bool is_empty(const DynamicQueue<T> &queue){
    return queue.card == 0;
}

template<typename T>
int lenght(const DynamicQueue<T> &queue){
    return queue.card;
}

template<typename T>
int get_position(const DynamicQueue<T> &queue, const T &element){

    Node<T> *p;
    p = queue.start;
    int c = 1;

    while(p!= NULL){
        if(p->element == element){
            return c;
        }
        p = p->next;
        c++;
    }
    return -1;
}

template<typename T>
bool exists(const DynamicQueue<T> &queue, const T &element){
    return get_position(queue, element) != -1;
}

template<typename T>
bool valid_position(const DynamicQueue<T> &queue, const int &pos){
    return (pos > 0) && (pos <= queue.card);
}

template<typename T>
T get_element(const DynamicQueue<T> &queue, const int &pos){
    if(not valid_position(queue, pos)){
        throw "INVALID POSITION";
    } else {
        Node<T> *p = queue.start;
        for(int i = 1; i < pos; i++){
            p = p->next;
        }
        return p->element;
    }
}

template <typename T>
T next_in_line(DynamicQueue<T> &queue){
    if(! is_empty(queue)) queue.start->element;
    else throw "QUEUE EMPTY";
}

template <typename T>
T last_in_line(DynamicQueue<T> &queue){
    IF(! is_empty(queue)) queue.end->element;
    else throw "QUEUE EMPTY";
}

template<typename T>
void insert(DynamicQueue<T> &queue, T element){
    Node<T> *n = new Node<T>;
    if(n == NULL){
        throw "NO MEMORY";
    }
    n->element = element;
    n->next = NULL;
    n->prev = queue.end;
    Node<T> *q = queue.end;
    q->next = n;
    queue.end = n;
    queue.card++;
}

template<typename T>
void remove(DynamicQueue<T> &queue){
    Node<T> *p;
    Node<T> *q;
    p = queue.start;
    queue.start = p->next;
    q = p->next;
    q->prev = NULL;
    delete p;
    queue.card--;
}

template<typename T>
void mostra(const DynamicQueue<T> &queue){
    Node<T> *p = queue.start;
    while(p != NULL){
        std::cout << p->element << std::endl;
        p = p->next;
    }
}