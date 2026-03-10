#include <iostream>
using namespace std;

template<typename T>
struct Nodo{
    T elemento;
    Nodo<T>* ant;
    Nodo<T>* prox;
};

template<typename T>
struct ListaDinamica{
    int card;
    Nodo<T>* inicio;
    Nodo<T>* fim;
};

template<typename T>
void cria(ListaDinamica<T> &lista){
    lista.card = 0;
    lista.inicio = NULL;
    lista.fim = NULL;
}

template<typename T>
void apaga(ListaDinamica<T> &lista){
    Nodo<T> *p;
    while(lista.inicio != NULL){
        p = lista.inicio;
        lista.inicio = p->prox;
        delete p;
    }
    lista.card = 0;
    lista.fim = NULL;
}

template<typename T>
void insere(ListaDinamica<T> &lista, T elemento, int pos){
    if(pos < 1 || pos > lista.card+1){
        throw "POSICAO INVALIDA";
    }
    Nodo<T> *n = new Nodo<T>;
    n->elemento = elemento;
    n->prox = NULL;
    n->ant = NULL;
    if(n == NULL){
        throw "SEM MEMORIA";
    }
    if(pos == 1){
        n->prox = lista.inicio;
        lista.inicio = n;
        if(vazia(lista)){
            lista.fim = n;
        }        
    }else{
        Nodo<T> *p;
        Nodo<T> *q;
        p = lista.inicio;
        for(int i = 2; i < pos; i++){
            p = p->prox;
        }
        n->prox = p->prox;
        p->prox = n;
        n->ant = p;
        q = n->prox;
        if(q != NULL){
            q->ant = n;
        } else {
            lista.fim = n;
        }
    }
    lista.card++;
}

template<typename T>
bool vazia(const ListaDinamica<T> &lista){
    return lista.card == 0;
}

template<typename T>
int tamanho(const ListaDinamica<T> &lista){
    return lista.card;
}

template<typename T>
int achar_posicao(const ListaDinamica<T> &lista, const T &elemento){

    Nodo<T> *p;
    p = lista.inicio;
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
bool existe(const ListaDinamica<T> &lista, const T &elemento){
    return achar_posicao(lista, elemento) != -1;
}

template<typename T>
bool posicao_valida(const ListaDinamica<T> &lista, const int &pos){
    return (pos > 0) && (pos <= lista.card);
}

template<typename T>
T achar_elemento(const ListaDinamica<T> &lista, const int &pos){
    if(not posicao_valida(lista, pos)){
        throw "POSICAO INVALIDA";
    } else {
        Nodo<T> *p = lista.inicio;
        for(int i = 1; i < pos; i++){
            p = p->prox;
        }
        return p->elemento;
    }
}

template<typename T>
void remove(ListaDinamica<T> &lista, const int &pos){
    if(not posicao_valida(lista, pos)){
        throw "POSICAO INVALIDA";
    }
    if(lista.card == 1){
        Nodo<T> *unico = lista.inicio;
        lista.inicio = NULL;
        lista.fim = NULL;
        lista.card = 0;
        delete unico;
        return;
    }
    Nodo<T> *p;
    Nodo<T> *q;
    if(pos == 1){
        p = lista.inicio;
        lista.inicio = p->prox;
        q = p->prox;
        if(q != NULL){
            q->ant = NULL;
        }
        delete p;
        lista.card--;
    } else if(pos == lista.card){
        p = lista.fim;
        lista.fim = p->ant;
        q = p->ant;
        if(q != NULL){
            q->prox = NULL;
        }
        delete p;
        lista.card--;
    } else { 
        p = lista.inicio;
        for(int i = 1; i < pos-1; i++){
            p = p->prox;
        }
        q = p->prox; // node to remove
        p->prox = q->prox;
        if(q != NULL){
            p = q->prox;
            p->ant = q->ant;
        }
        delete q;
        lista.card--;
    }
}

template<typename T>
void mostra_debug(const ListaDinamica<T> &lista){
    Nodo<T> *p = lista.inicio;
    int i = 1;
    while(p != NULL){
        cout << p->elemento.simbolo << i << endl;
        p = p->prox;
        i++;
    }
}
