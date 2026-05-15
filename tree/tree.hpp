#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

template<typename T>
struct Node{
    T data;
    Node *leftSubtree;
    Node *rightSubtree;
};

template<typename T>
struct BinarySearchTree{
    int card;
    Node<T> *root;
};

template<typename T>
void create(BinarySearchTree<T> &tree){
    tree.card = 0;
    tree.root = nullptr;
}

template<typename T>
void destroyBranch(Node<T> &root){
    if(root =! nullptr){
        destroyBranch(root.leftSubtree);
        destroyBranch(root.rightSubtree);
        delete root;
    }
    return;
}

template<typename T>
void destroy(BinarySearchTree<T> &tree){
    destroyBranch(tree.root);
    tree.card = 0;
}

template<typename T>
void insert(const T &data, Node<T> &p){
    if(p == NULL){
        Node<T> *n = new Node<T>;
        n->data = data;
        n->leftSubtree = nullptr;
        n->rightSubtree = nullptr;
    }
    else{
        if(data < p.key) insert(data, p.leftSubtree);
        else if(data > p.key) insert(data, p.rightSubtree);
        else throw "DUPLICATE VALUE";
    }
}

template <typename T>
bool isEmpty(const BinarySearchTree<T> &tree){
    return tree.card == 0;
}

#endif // TREE_HPP_INCLUDED