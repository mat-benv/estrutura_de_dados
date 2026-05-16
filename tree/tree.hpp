#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <iostream>

template<typename T>
struct Node{
    T key;
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
void destroyBranch(Node<T> *root){
    if(root != nullptr){
        destroyBranch(root->leftSubtree);
        destroyBranch(root->rightSubtree);
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
void insertNode(T key, Node<T>* &p){
    if(p == NULL){
        Node<T> *n = new Node<T>;
        n->key = key;
        n->leftSubtree = nullptr;
        n->rightSubtree = nullptr;
        p = n;
    }
    else{
        if(key < p->key) insertNode(key, p->leftSubtree);
        else if(key > p->key) insertNode(key, p->rightSubtree);
        else throw "DUPLICATE VALUE";
    }
}

template<typename T>
void insert(T key, BinarySearchTree<T> &tree){
    insertNode(key, tree.root);
    tree.card++;
}

template<typename T>
Node<T>* findKeyNode(Node<T> *node, const T &key){
    if(node == nullptr or node->key == key) return node;
    else{
        if(key > node->key) return findKeyNode(node->rightSubtree, key);
        else if(key < node->key) return findKeyNode(node->leftSubtree, key);
    }
}

template<typename T>
Node<T>* findKey(const BinarySearchTree<T> &tree, const T &key){
    return findKeyNode(tree.root, key);
}

template<typename T>
bool isLeaf(Node<T> *p){
    return (p != nullptr && p->leftSubtree == nullptr && p->rightSubtree == nullptr);
}

template<typename T>
void remove(BinarySearchTree<T> &tree, const T &key){
    Node<T>* p = findKeyNode(tree.root, key);
    if(isLeaf(p)){
        delete p;
        tree.card--;
    } else if(p->leftSubtree == nullptr){
        tree.root = p->rightSubtree;
        delete p;
        tree.card--;
    } else if(p->rightSubtree == nullptr){
        tree.root = p->leftSubtree;
        delete p;
        tree.card--;
    } else {
        Node<T> *q = p->leftSubtree;
        while(q->rightSubtree != nullptr){
            q = q->rightSubtree;
        }
        p = q;
        q = q->leftSubtree;
        tree.card--;
    }
}

template <typename T>
bool isEmpty(const BinarySearchTree<T> &tree){
    return tree.card == 0;
}

template <typename T>
int size(const BinarySearchTree<T> &tree){
    return tree.card;
}

template <typename T>
bool contains(const BinarySearchTree<T> &tree, T key){
    return findKey(tree, key) != nullptr;
}

template <typename T>
void showNode(Node<T> *node){
    if(node != nullptr){
        T x = node->key;
        std::cout << x << '\n';
        showNode(node->leftSubtree);
        showNode(node->rightSubtree);
    }
}

template <typename T>
void show(BinarySearchTree<T> &tree){
    showNode(tree.root);
}

#endif // TREE_HPP_INCLUDED