#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iostream>
#include <queue>
#include "Comparator.hpp"

enum Color
{
    Red,
    Black
};

template <typename T>
class RBNode
{
public:
    T data;
    inline static size_t counter = 0;
    RBNode<T> *parent;
    RBNode<T> *left;
    RBNode<T> *right;
    Color color;

    RBNode()
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    RBNode(T data) : data(data)
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = Red;
        counter += sizeof(RBNode<T>) + sizeof(T) + sizeof(RBNode<T>) * 3 + sizeof(Color);
    }
    bool operator==(RBNode<T> r)
    {
        return (this->data == r.data && this->parent == r.parent && this->left == r.left && this->right == r.right);
    }
};

template <typename T>
class RedBlackTree
{
protected:
    void rotateLeft(RBNode<T> *&, RBNode<T> *&);
    void rotateRight(RBNode<T> *&, RBNode<T> *&);
    void fixViolation(RBNode<T> *&, RBNode<T> *&);

public:
    RBNode<T> *root;
    inline static RBNode<T> nullnode = RBNode<T>();

    RedBlackTree() : root(nullptr){};
    RedBlackTree(const RedBlackTree<T> &rvl);
    ~RedBlackTree();

    void insert(const T &data);
    void inorder();
    RBNode<T> find(T data);
    void levelOrder();
};
template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
    delete root;
}

template <typename T>
void RedBlackTree<T>::rotateLeft(RBNode<T> *&root, RBNode<T> *&pt)
{
    RBNode<T> *pt_right = pt->right;

    pt->right = pt_right->left;

    if (_(pt->right != nullptr))
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (_(pt->parent == nullptr))
        root = pt_right;

    else if (_(pt == pt->parent->left))
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

template <typename T>
void RedBlackTree<T>::rotateRight(RBNode<T> *&root, RBNode<T> *&pt)
{
    RBNode<T> *pt_left = pt->left;

    pt->left = pt_left->right;

    if (_(pt->left != nullptr))
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (_(pt->parent == nullptr))
        root = pt_left;

    else if (_(pt == pt->parent->left))
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// This function fixes violations
// caused by BST insertion
template <typename T>
void RedBlackTree<T>::fixViolation(RBNode<T> *&root, RBNode<T> *&pt)
{
    RBNode<T> *parent_pt = nullptr;
    RBNode<T> *grand_parent_pt = nullptr;

    while (
        _(pt != root) && _(pt->color != Black) && _(pt->parent != nullptr) && _(pt->parent->color == Red)) // BUG: Segfault
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case : A
			Parent of pt is left child
			of Grand-parent of pt */
        if (_(parent_pt == grand_parent_pt->left))
        {
            RBNode<T> *uncle_pt = grand_parent_pt->right;

            /* Case : 1
			The uncle of pt is also Red
			Only Recoloring requiRed */
            if (_(uncle_pt != nullptr) && _(uncle_pt->color == Red))
            {
                grand_parent_pt->color = Red;
                parent_pt->color = Black;
                uncle_pt->color = Black;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
				pt is right child of its parent
				Left-rotation requiRed */
                if (_(pt == parent_pt->right))
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
				pt is left child of its parent
				Right-rotation requiRed */
                rotateRight(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        /* Case : B
		Parent of pt is right child
		of Grand-parent of pt */
        else
        {
            RBNode<T> *uncle_pt = grand_parent_pt->left;

            /* Case : 1
				The uncle of pt is also Red
				Only Recoloring requiRed */
            if (_(uncle_pt != nullptr) && _(uncle_pt->color == Red))
            {
                grand_parent_pt->color = Red;
                parent_pt->color = Black;
                uncle_pt->color = Black;
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
				pt is left child of its parent
				Right-rotation requiRed */
                if (_(pt == parent_pt->left))
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                /* Case : 3
				pt is right child of its parent
				Left-rotation requiRed */
                rotateLeft(root, grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = Black;
}

// Function to insert a new node with given data
template <typename T>
void RedBlackTree<T>::insert(const T &data)
{
    RBNode<T> *pt = new RBNode<T>(data);
    // Do a normal BST insert
    root = BSTInsert(root, pt);
    // fix Red Black Tree violations
    fixViolation(root, pt);
}

// Function to do inorder and level order traversals
template <typename T>
void RedBlackTree<T>::inorder() { inorderHelper(root); }

template <typename T>
void RedBlackTree<T>::levelOrder() { levelOrderHelper(root); }

template <typename T>
RBNode<T> RedBlackTree<T>::find(T data) { return inorderFindHelper(root, data); }

template <typename T>
RBNode<T> inorderFindHelper(RBNode<T> *root, T data)
{
    auto *current = root;
    while (_(__(current->data != data)))
    {
        if (_(__(current != nullptr)))
        {
            if (_(__(current->data > data)))
                current = current->left;
            else
                current = current->right;

            if (_(__(current == nullptr)))
                return RedBlackTree<T>::nullnode;
        }
    }
    return *current;
}

template <typename T>
RBNode<T> *BSTInsert(RBNode<T> *root, RBNode<T> *pt)
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

// A recursive function to do inorder traversal
template <typename T>
void inorderHelper(RBNode<T> *root)
{
    if (_(root == nullptr))
        return;

    inorderHelper(root->left);
    std::cout << root->data << " ";
    inorderHelper(root->right);
}

template <typename T>
void ToSortedVector(std::vector<T> &v, RBNode<T> *node)
{
    if (_(node == nullptr))
        return;

    ToSortedVector(v, node->left);
    v.push_back(node->data);
    ToSortedVector(v, node->right);
}

// Utility function to do level order traversal
template <typename T>
void levelOrderHelper(RBNode<T> *root)
{
    if (_(root == nullptr))
        return;

    std::queue<RBNode<T> *> q;
    q.push(root);

    while (!q.empty())
    {
        RBNode<T> *temp = q.front();
        std::cout << temp->data << " ";
        q.pop();

        if (_(temp->left != nullptr))
            q.push(temp->left);

        if (_(temp->right != nullptr))
            q.push(temp->right);
    }
}

#endif // _RED_BLACK_TREE_HPP_
