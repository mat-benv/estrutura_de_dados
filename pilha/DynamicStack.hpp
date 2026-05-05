#include <iostream>

template<typename T>
struct Node{
    T element;
    Node<T>* next;
};

template<typename T>
struct DynamicStack{
    int card;
    Node<T>* top;
};

template<typename T>
void create(DynamicStack<T> &stack){
    stack.card = 0;
    stack.top = NULL;
}

template<typename T>
void wipe(DynamicStack<T> &stack){
    Node<T> *p;
    while(stack.top != NULL){
        p = stack.top;
        stack.top = p->next;
        delete p;
    }
    stack.card = 0;
}

template<typename T>
bool isEmpty(const DynamicStack<T> &stack){
    return stack.card == 0;
}

template<typename T>
int getSize(const DynamicStack<T> &stack){
    return stack.card;
}

template<typename T>
int getIndex(const DynamicStack<T> &stack, const T &element){

    Node<T> *p;
    p = stack.top;
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
bool hasElement(const DynamicStack<T> &stack, const T &element){
    return getIndex(stack, element) != -1;
}

template<typename T>
bool validPosition(const DynamicStack<T> &stack, const int &pos){
    return (pos > 0) && (pos <= stack.card);
}

template<typename T>
T getElement(const DynamicStack<T> &stack, const int &pos){
    if(not validPosition(stack, pos)){
        throw "INVALID POSITION";
    } else {
        Node<T> *p = stack.top;
        for(int i = 1; i < pos; i++){
            p = p->next;
        }
        return p->element;
    }
}

template <typename T>
T topElement(DynamicStack<T> &stack){
    if(! isEmpty(stack)) stack.top->element;
    else throw "EMPTY STACK";
}

template <typename T>
T bottomElement(DynamicStack<T> &stack){
    if(! isEmpty(stack)) getElement(stack, getSize(stack));
    else throw "EMPTY STACK";
}

template<typename T>
void stack(DynamicStack<T> &stack, T element){
    Node<T> *n = new Node<T>;
    if(n == NULL){
        throw "NO MEMORY";
    }
    n->element = element;
    n->next = stack.top;
    stack.top = n;
    stack.card++;
}

template<typename T>
void unstack(DynamicStack<T> &stack){
    if(! isEmpty(stack)){
        Node<T> *p = stack.top;
        stack.top = p->next;
        delete p;
        stack.card--;
    } else {
        throw "STACK EMPTY";
    }
}

template<typename T>
void printStack(const DynamicStack<T> &stack){
    Node<T> *p = stack.top;
    while(p != NULL){
        std::cout << p->element << std::endl;
        p = p->next;
    }
}