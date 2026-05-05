#include <iostream>

template<typename T>
struct Nodo{
    T elemento;
    Nodo<T>* prox;
    Nodo<T>* ant;
};

template<typename T>
struct DynamicStack{
    int card;
    Nodo<T>* inicio;
    Nodo<T>* fim;
};

template<typename T>
void cria(DynamicStack<T> &pilha){
    pilha.card = 0;
    pilha.inicio = NULL;
    pilha.fim = NULL;
}

template<typename T>
void apaga(DynamicStack<T> &pilha){
    Nodo<T> *p;
    while(pilha.inicio != NULL){
        p = pilha.inicio;
        pilha.inicio = p->prox;
        delete p;
    }
    pilha.card = 0;
    pilha.fim = NULL;
}

template<typename T>
bool isEmpty(const DynamicStack<T> &pilha){
    return pilha.card == 0;
}

template<typename T>
int tamanho(const DynamicStack<T> &pilha){
    return pilha.card;
}

template<typename T>
int getIndex(const DynamicStack<T> &pilha, const T &elemento){

    Nodo<T> *p;
    p = pilha.inicio;
    int c = 1;

    while(p!= NULL){
        if(p->elemento == elemento){
            return c;
        }
        p = p->prox;
        c++;
    }
    return -1;
}

template<typename T>
bool existe(const DynamicStack<T> &pilha, const T &elemento){
    return getIndex(pilha, elemento) != -1;
}

template<typename T>
bool posicao_valida(const DynamicStack<T> &pilha, const int &pos){
    return (pos > 0) && (pos <= pilha.card);
}

template<typename T>
T getElement(const DynamicStack<T> &pilha, const int &pos){
    if(not posicao_valida(pilha, pos)){
        throw "POSICAO INVALIDA";
    } else {
        Nodo<T> *p = pilha.inicio;
        for(int i = 1; i < pos; i++){
            p = p->prox;
        }
        return p->elemento;
    }
}

template <typename T>
T topElement(DynamicStack<T> &pilha){
    if(! isEmpty(pilha)) pilha.inicio->elemento;
    else throw "PILHA VAZIA";
}

template <typename T>
T bottomElement(DynamicStack<T> &pilha){
    if(! isEmpty(pilha)) pilha.fim->elemento;
    else throw "PILHA VAZIA";
}

template<typename T>
void insere(DynamicStack<T> &pilha, T elemento){
    Nodo<T> *n = new Nodo<T>;
    if(n == NULL){
        throw "SEM MEMORIA";
    }
    n->elemento = elemento;
    n->prox = pilha.inicio;
    n->ant = NULL;
    Nodo<T> *q = pilha.inicio;
    q->prox = n;
    pilha.fim = n;
    pilha.card++;
}

template<typename T>
void unstack(DynamicStack<T> &pilha){
    Nodo<T> *p;
    Nodo<T> *q;
    p = pilha.inicio;
    pilha.inicio = p->prox;
    q = p->prox;
    q->prev = NULL;
    delete p;
    pilha.card--;
}

template<typename T>
void mostra(const DynamicStack<T> &pilha){
    Nodo<T> *p = pilha.fim;
    while(p != NULL){
        std::cout << p->elemento << std::endl;
        p = p->ant;
    }
}