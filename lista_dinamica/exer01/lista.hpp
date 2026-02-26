#include <iostream>

template<typename T>
struct Node{
    T element;
    Node<T>* next;
};

template<typename T>
struct DynamicArray{
    int card;
    Node<T>* start;
};

template<typename T>
void create(DynamicArray<T> &array){
    array.card = 0;
    array.start = NULL;
}

template<typename T>
void wipe(DynamicArray<T> &array){
    Node<T> *p;
    while(array.start != NULL){
        p = array.start;
        array.start = p->next;
        delete p;
    }
    array.card = 0;
}

template<typename T>
void insert(DynamicArray<T> &array, T element, int pos){
    if(pos < 1 || pos > array.card+1){
        throw "INVALID POSITION";
    }
    Node<T> *n = new Node<T>;
    n->element = element;
    n->next = NULL;
    if(n == NULL){
        throw "NO MEMORY";
    }
    if(pos == 1){
        n->next = array.start;
        array.start = n;
    } else {
        Node<T> *prev;
        prev = array.start;
        for(int i = 2; i < pos; i++){
            prev = prev->next;
        }
        n->next = prev->next;
        prev->next = n;
    }
    array.card++;
}

template<typename T>
bool is_empty(const DynamicArray<T> &array){
    return array.card == 0;
}

template<typename T>
int size(const DynamicArray<T> &array){
    return array.card;
}

template<typename T>
int find_position(const DynamicArray<T> &array, const T &element){

    Node<T> *prev;
    prev = array.start;
    int c = 1;

    while(prev != NULL){
        if(prev->element == element){
            return c;
        }
        prev = prev->next;
        c++;
    }
    return -1;
}

template<typename T>
bool exists(const DynamicArray<T> &array, const T &element){
    return find_position(array, element) > -1;
}

template<typename T>
bool valid_position(const DynamicArray<T> &array, const int &pos){
    return (pos > 0) && (pos <= array.card);
}

template<typename T>
T find_element(const DynamicArray<T> &array, const int &pos){
    if(not valid_position(array, pos)){
        throw "INVALID POSITION";
    } else {
        Node<T> *p = array.start;
        for(int i = 1; i < pos; i++){
            p = p->next;
        }
        return p->element;
    }
}

template<typename T>
void remove(DynamicArray<T> &array, const int &pos){
    if(not valid_position(array, pos)){
        throw "INVALID POSITION";
    }
    Node<T> *p = array.start;
    if(pos == 1){
        array.start = p->next;
        delete p;
        array.card--;
    } else {
        Node<T> *q = p->next;
        for(int i = 2; i < pos; i++){
            p = p->next;
            q = p->next;
        }
        p->next = q->next;
        delete q;
        array.card--;
    }
}

template<typename T>
void show(const DynamicArray<T> &array, const int &pos){
    Node<T> *p = array.start;
    while(p != NULL){
        std::cout << p->element << std::endl;
        p = p->next;
    }
}

