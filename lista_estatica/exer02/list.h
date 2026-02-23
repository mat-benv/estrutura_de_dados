#include <iostream>
#include <algorithm>

template<typename T, int MAX>
struct StaticList{
    int card;
    T elements[MAX];
};

template<typename T, int MAX>
void cria(StaticList<T,MAX> &list){
    list.card = 0;
}

template<typename T, int MAX>
bool is_empty(const StaticList<T, MAX> &list){
    return list.card == 0;
}

template<typename T, int MAX>
bool is_space (const StaticList<T, MAX> &list){
    return list.card < MAX;
}

template<typename T, int MAX>
int element_amount(const StaticList<T,MAX> &list){
    return list.card;
}

template<typename T, int MAX>
bool is_included(const StaticList<T,MAX> &list, const T &element){
    for(int i = 0; i < list.card; i++){
        if(element == list.elements[i]){
            return true;
        }
    }
    return false;
}

template<typename T, int MAX>
bool valid_position(const StaticList<T,MAX> &list, const int &pos){
    return ((pos <= list.card) && (pos >= 1));
}

template<typename T, int MAX>
T find_element(const StaticList<T,MAX> &list, const int &pos){
    if(valid_position(list, pos)){
        return list.elements[pos-1];
    } else {
        throw "INVALID POSITION";
    }
}

template<typename T, int MAX>
int find_position(const StaticList<T,MAX> &list, const T element){
    if(is_included(list, element)){
        for(int i = 0; i < list.card; i++){
            if(element == list.elements[i]){
                return i+1;
            }
        }
    } else {
        throw "ELEMENT NOT FOUND";
    }
}

template<typename T, int MAX>
void insert(StaticList<T,MAX> &list, T element, int pos){
    if(not is_space(list)){
        throw "OVERFLOW";
    }
    if(not valid_position(list, pos)){
        throw "INVALID POSITION";
    }
    for(int i = list.card; i >= pos; i--){
        list.elements[i] = list.elements[i-1];
    }
    list.elements[pos-1] = element;
    list.card++;
}

template<typename T, int MAX>
void remove(StaticList<T,MAX> &list, int pos){
    if(is_empty(list)){
        throw "EMPTY LIST";
    }
    if(not valid_position(list, pos)){
        throw "INVALID POSITION";
    }
    for(int i = pos; i < list.card; i++){
        list.elements[i-1] = list.elements[i];
    }
    list.card--;
}

template<typename T, int MAX>
void show_list(const StaticList<T,MAX> &list){
    for(int i = 1; i <= list.card; i++){
        std::cout << list.elements[i-1] << std::endl;
    }
}

template<typename T, int MAX>
void order_list(StaticList<T,MAX> &list){
    for(int i = 0; i < list.card-1; i++){
        for(int j = list.card-1; j > i; j--){
            if(list.elements[i] > list.elements[j]){
                std::swap(list.elements[i], list.elements[j]);
            }
        }
    }
}

template<typename T, int MAX>
void outliers(const StaticList<T,MAX> &list, T &smallest, T &biggest){
    if(is_empty(list)){
        throw "LIST EMPTY";
    }else{
        smallest = list.elements[0];
        biggest = list.elements[0];
        for(int i = 1; i < list.card; i++){
            if(list.elements[i] < smallest){
                smallest = list.elements[i];
            }
            if(list.elements[i] > biggest){
                biggest = list.elements[i];
            }
        }
    }
}

template<typename T, int MAX>
void remove_duplicates(StaticList<T,MAX> &list){
    if(is_empty(list)){
        throw "LIST EMPTY";
    }
    for(int i = 0; i < list.card; i++){
        for(int j = i+1; j < list.card; j++){
            if(list.elements[i] == list.elements[j]){
                remove(list, j+1);
                j--;
                list.card--;
            }
        }
    }
}