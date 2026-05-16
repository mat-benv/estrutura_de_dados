#include "../tree.hpp"
#include <cstdlib>

int main(){

    BinarySearchTree<int> A1, A2;

    create(A1);
    create(A2);
    srand(time(NULL));

    int n = rand() % 31 + 10;

    for(int i = 0; i < n; i++){
        int m = rand() % 71 + 10;
        if(m % 2 == 0){
            try {insert(m, A1);}
            catch (const char *msg) {std::cerr << msg << std::endl;}
            
        } else {
            try {insert(m, A2);}
            catch (const char *msg) {std::cerr << msg << std::endl;}
        }
    }

    show(A1);
    show(A2);

    return 0;
}