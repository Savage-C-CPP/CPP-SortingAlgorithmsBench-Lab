#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include <iostream>
#include <queue>
#include "Comparator.hpp"

template <typename T>
class Node
{
public:
    T data;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;

    Node(T data) : data(data)
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    ~Node()
    {
        delete left;
        delete right;
        delete parent;
    }
};

template <typename T>
class BinarySearchTree
{
public:
    Node<T> *root;

    BinarySearchTree() : root(nullptr) {};
    BinarySearchTree(const BinarySearchTree<T> &rvl);
    ~BinarySearchTree();

	void insert(const T &data);
	void inorder();
	void levelOrder();
};

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    delete root;
}

template<typename T>
void BinarySearchTree<T>::insert(const T &data)
{
    Node<T> *pt = new Node<T>(data);
    root = BSTInsert(root, pt);
}

template <typename T>
Node<T> *BSTInsert(Node<T> *root, Node<T> *pt)
{
    /* If the tree is empty, return a new node */
    if (_(root == nullptr))
        return pt;

    /* Otherwise, recur down the tree */
    if (_(pt->data < root->data))
    {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (_(pt->data > root->data))
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }

    /* return the (unchanged) node pointer */
    return root;
}

// Function to do inorder and level order traversals
template<typename T>
void BinarySearchTree<T>::inorder() { inorderHelper(root); }

template<typename T>
void BinarySearchTree<T>::levelOrder() { levelOrderHelper(root); }

// A recursive function to do inorder traversal
template <typename T>
void inorderHelper(Node<T> *root)
{
    if (_(root == nullptr))
        return;

    inorderHelper(root->left);
    std::cout << root->data << " ";
    inorderHelper(root->right);
}

template <typename T>
void ToSortedVector(std::vector<T> &v, Node<T> *node)
{
    if (_(node == nullptr))
        return;

    ToSortedVector(v, node->left);
    v.push_back(node->data);
    ToSortedVector(v, node->right);
}

// Utility function to do level order traversal
template <typename T>
void levelOrderHelper(Node<T> *root)
{
    if (_(root == nullptr))
        return;

    std::queue<Node<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        Node<T> *temp = q.front();
        std::cout << temp->data << " ";
        q.pop();

        if (_(temp->left != nullptr))
            q.push(temp->left);

        if (_(temp->right != nullptr))
            q.push(temp->right);
    }
}

#endif // _BINARY_SEARCH_TREE_HPP_
