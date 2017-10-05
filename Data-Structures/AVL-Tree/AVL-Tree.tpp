/*
 * File: AVL-Tree.tpp
 * ----------------------
 * Presents the template implementation of the self-balancing Binary Search tree.
 * The binary tree is balanced such that for any node, the height of it's two children
 * nodes differs by no more than one.
 */

#include "BinaryNode.h"
#include <memory>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

// Constructor
template <class T>
AVLTree<T>::AVLTree() { }

template <class T>
void AVLTree<T>::insert(const T& element) {
    root = insert(root, element);
}

template <class T>
void AVLTree<T>::remove(const T& element) {
    root = remove(root, element);
}

template <class T>
bool AVLTree<T>::contains(const T& element) {
    return contains(root, element);
}

template <class T>
Node<T> AVLTree<T>::search(const T& element) {
    return search(root, element);
}

// Private members

/**
 * Private Method: insert
 * ----------------------
 * Inserts an element into a node of a binary search tree, and balances the tree
 * @tparam T: The type of element contained in the node of the BST
 * @param node: Root node to insert element into. If nullptr, a new node will be created and returned
 * @param value: The value to store in the BST
 * @return: The (possibly new) root of the BST after insertion and balancing
 */
template <class T>
Node<T> AVLTree<T>::insert(Node<T> node, const T& value) {
    if (node == nullptr) return std::shared_ptr<BinaryNode<T>>(new BinaryNode<T>(value));

    if (value == node->value) return node; // no duplicates

    if (value < node->value) node->left = insert(node->left, value);
    if (value > node->value) node->right = insert(node->right, value);

    updateHeight(node);
    return balance(node);
}

/**
 * Private Method: remove
 * ----------------------
 * Removes a specified element from a binary search tree (BST) and re-balances the tree
 * @tparam T: Type of the element stored in the BST
 * @param node: The node to remove the value from
 * @param value: The value to remove the the node
 * @return: A new node after the removal and rebalancing
 */
template <class T>
Node<T> AVLTree<T>::remove(Node<T> node, const T& value) {
    if (node == nullptr) return nullptr;

    if (value < node->value) node->left = remove(node->left, value);
    if (value > node->value) node->right = remove(node->right, value);

    if (node->value == value) { // found it
        if (node->left == nullptr) return node->right;
        if (node->right == nullptr) return node->left;
        else {
            node->value = next(node->right)->value;
            node->right = remove(node->right, node->value);
        }
    }

    updateHeight(node);
    return balance(node);
}

/**
 * Private Method: contains
 * ------------------------
 * Determines if the binary search tree contains a certain element.
 * @param node: The root node to search below
 * @param element: The element to search for
 * @return: True if the element is contained in the tree, false otherwise
 */
template <class T>
bool AVLTree<T>::contains(const Node<T> node, const T& element) {
    if (node == nullptr) return false;
    if (node->value == element) return true;
    if (element < node->value) return contains(node->left, element);
    if (element > node->value) return contains(node->right, element);
    return false;
}

/**
 * Private Method: search
 * ----------------------
 * If the element is stored in the binary search tree, then the node containing the element
 * will be returned, otherwise a null pointer will be returned.
 * @tparam T: Type of the elements stored in the BST
 * @param node: Root node to search for the element in.
 * @param element: The element to search for
 * @return: A pointer to a node containing an equivalent element
 */
template <class T>
Node<T> AVLTree<T>::search(Node<T> node, const T& element) {
    if (node == nullptr) return nullptr;
    if (node->value == element) return node;
    if (element < node->value) return search(node->left, element);
    if (element > node->value) return search(node->right, element);
    return nullptr;
}

/**
 * Private Method: balance
 * -----------------------
 * Balances the AVL tree so that the two children differ in height by no more than one
 * @tparam T: The type of the elements stored in the nodes
 * @param node: The root node to balance about
 * @return: The new root node after having balanced the tree
 */
template <class T>
Node<T> AVLTree<T>::balance(Node<T> node) {
    if (node == nullptr) return nullptr;

    int netBalance = getNetBalance(node);
    if (netBalance > 1) { // right is heavy
        int rightBalance = getNetBalance(node->right);
        if (rightBalance < 0) node->right = rightRotate(node->right);
        return leftRotate(node);
    } else if (netBalance < 1) { // left is heavy
        int leftBalance = getNetBalance(node->left);
        if (leftBalance > 0) node->left = leftRotate(node->left);
        return rightRotate(node);
    } else return node;
}

/**
 * Private Method: leftRotate
 * --------------------------
 * Rotates the tree counter-clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
Node<T> AVLTree<T>::leftRotate(Node<T> node) {
    if (node->right == nullptr) return node; // Nothing to rotate onto
    auto root = node->right;
    node->right = node->right->left;
    root->left = node;
    updateHeight(node);
    updateHeight(root);
    return root;
}

/**
 * Private Method: rightRotate
 * --------------------------
 * Rotates the tree clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
Node<T> AVLTree<T>::rightRotate(Node<T> node) {
    if (node->left == nullptr) return node; // Nothing to rotate onto
    auto root = node->left;
    node->left = root->right;
    root->right = node;
    updateHeight(node);
    updateHeight(root);
    return root;
}

/**
 * Private Method: next
 * --------------------
 * Returns the (ordered) next node in the binary search tree.
 * @param node: The root node to get the next node from
 * @return: The next node in order
 */
template <class T>
Node<T> AVLTree<T>::next(Node<T> node) {
    if (node == nullptr) return nullptr;
    if (node->left == nullptr) return node;
    else return next(node->left);
}

/**
 * Private Method: updateHeight
 * ----------------------------
 * Updates the height of a node to be the one plus the
 * maximum of the heights of it's two children. Nodes with
 * no children have a height of zero.
 * @param node: A node to update the height on
 */
template <class T>
void AVLTree<T>::updateHeight(Node<T> node) {
    if (node == nullptr) return;
    int lh = node->left == nullptr ? -1 : node->left->height;
    int rh = node->right == nullptr ? -1 : node->right->height;
    node->height = 1 + (lh > rh ? lh : rh);
}

/**
 * Private Method: getNetBalance
 * -----------------------------
 * Gets the difference in heights of the right and left children of a node
 * @param node: Node to get the net balance at
 * @return: Difference between height of right and left children
 */
template <class T>
int AVLTree<T>::getNetBalance(const Node<T> node) {
    if (node == nullptr) return 0;
    if (node->height == 0) return 0;
    if (node->right == nullptr) return - node->left->height;
    if (node->left == nullptr) return node->right->height;
    return node->right->height - node->left->height;
}
