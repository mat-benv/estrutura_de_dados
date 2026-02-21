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
bool is_empty(StaticList<T, MAX> list){
    return list.card == 0;
}

template<typename T, int MAX>
bool is_space (StaticList<T, MAX> list){
    return list.cardinalidade < MAX;
}

template<typename T, int MAX>
int element_amount(StaticList<T,MAX> list){
    return list.card;
}

template<typename T, int MAX>
bool is_included(StaticList<T,MAX> list, T element){
    for(int i = 0; i < list.card; i++){
        if(element == list.elements[i]){
            return true;
        }
    }
    return false;
}

template<typename T, int MAX>
bool valid_position(StaticList<T,MAX> list, int pos){
    return (pos <= MAX && is_space(list));
}

