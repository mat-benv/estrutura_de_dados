#include <iostream>

template<typename T>
struct Node{
    T element;
    Node<T>* prev;
    Node<T>* next;
};

template<typename T>
struct DynamicArray{
    int card;
    Node<T>* start;
    Node<T>* end;
};

template<typename T>
void create(DynamicArray<T> &array){
    array.card = 0;
    array.start = NULL;
    array.end = NULL;
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
    array.end = NULL;
}

template<typename T>
void insert(DynamicArray<T> &array, T element, int pos){
    if(pos < 1 || pos > array.card+1){
        throw "INVALID POSITION";
    }
    Node<T> *n = new Node<T>;
    n->element = element;
    n->next = NULL;
    n->prev = NULL;
    if(n == NULL){
        throw "NO MEMORY";
    }
    if(pos == 1){
        n->next = array.start;
        array.start = n;
        if(is_empty(array)){
            array.end = n;
        }        
    }else{
        Node<T> *p;
        Node<T> *q;
        p = array.start;
        for(int i = 2; i < pos; i++){
            p = p->next;
        }
        n->next = p->next;
        p->next = n;
        n->prev = p;
        q = n->next;
        if(q != NULL){
            q->prev = n;
        } else {
            array.end = n;
        }
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

    Node<T> *p;
    p = array.start;
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
bool exists(const DynamicArray<T> &array, const T &element){
    return find_position(array, element) != -1;
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
    Node<T> *p;
    Node<T> *q;
    if(pos == 1){
        p = array.start;
        array.start = p->next;
        q = p->next;
        q->prev = NULL;
        delete p;
        array.card--;
    } else if(pos == size(array)){
        p = array.end;
        array.end = p->prev;
        q = p->prev;
        q->next = NULL;
        delete p;
        array.card--;
    } else { //TODO FROM HERE
        p = array.start;
        q = p->next;
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

