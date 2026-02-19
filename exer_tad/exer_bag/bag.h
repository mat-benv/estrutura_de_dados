#include <iostream>

typedef struct{
    int card;
    int element[100];
    bool filled[100];
} Bag;

Bag create(){
    Bag bag;
    bag.card = 0;
    for(int i = 0; i < 100; i++){
        bag.filled[i] = false;
    }
    return bag;
}

int find_element(Bag bag, int element){
    int i = 0, j = 0; //where i counts actual elements and j iterates the whole allocated memory
    while(i < bag.card){
        if(bag.filled[j]){
            if(bag.element[j] == element){
                return j;
            }
            i++;
        }
        j++;
    }
    return -1; // if not found
}

int how_many(Bag bag, int element){
    int i = 0, j = 0, n = 0;
    while(i < bag.card){
        if(bag.filled[j]){
            if(bag.element[i] == element){
                n++;
            }
            i++;
        }
        j++;
    }
    return n;
}

bool exist(Bag bag, int element){
    int n;
    n = how_many(bag, element);
    if(n > 0) return true;
    return false;
}

bool is_space(Bag bag){
    if(bag.card == 100) return false;
    return true;
}

void put(Bag &bag, int element){
    int j = 0;
    if(is_space(bag)){
        while(j < 100){
            if(not bag.filled[j]){
                bag.element[j] = element;
                bag.filled[j] = true;
                bag.card++;
                return;
            }
            j++;
        }
    }
}

void remove(Bag &bag, int element){
    int n;
    n = find_element(bag, element);
    if(n != -1){
        bag.filled[n] = false;
        bag.card--;
    }
}

void remove_all(Bag &bag, int element){
    int n;
    n = how_many(bag, element);
    for(int i = 0; i < n; i++){
        remove(bag, element);
    }
}

void print_elements(Bag bag){
    int i = 0, j = 0;
    while(i < bag.card){
        if(bag.filled[j]){
            std::cout << bag.element[j] << std::endl;
            i++;
        }
        j++;
    }
}

void print_occurences(Bag bag){
    int i = 0, j = 0, n = 0, u = 0; //where i counts actual elements, j iterates memory, n receives amount of element and u counts unique elements
    bool found;
    int element[100], amount[100];
    while(i < bag.card){
        found = false;
        if(bag.filled[j]){
            for(int k = 0; k < u; k++){
                if(bag.element[j] == element[k]){
                    found = true;
                }
            }
            if(not found){
                n = how_many(bag, bag.element[j]);
                element[u] = bag.element[j];
                amount[u] = n;
                u++;
            }
            i++;
        }
        j++;
    }
    for(int k = 0; k < u; k++){
        std::cout << element[k] << ": " << amount[k] << std::endl;
    }
}