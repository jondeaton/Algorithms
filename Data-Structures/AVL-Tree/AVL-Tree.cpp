/*
 * File: AVL-Tree.tpp
 * ----------------------
 * Presents the template implementation of the self-balancing Binary Search tree.
 * The binary tree is balanced such that for any node, the height of it's two children
 * nodes differs by no more than one.
 */

template <class T>
AVLTree<T>::AVLTree() {}

template <class T>
void AVLTree<T>::insert(const T& element) {
    root = insert(root, elemnt);
}

template <class T>
void AVLTree<T>::remove(const T& element) {
    root = remove(root, element);
}

template <class T>
bool AVLTree<T>::contains(const T& elemnet) {
    return contains(root, element);
}

template <class T>
BSTNode AVLTree<T>::search(const T& element) {
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
BSTNode AVLTree<T>::insert(BSTNode node, const T& value) {
    if (node == nullptr) return std::shared_ptr<BinaryNode<T>>(new BinaryNode(value));

    if (value < node->value) node->left = insert(node->left, value);
    if (value > node->value) node->right = insert(node->right, value);
    else return node; // no duplicates

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
BSTNode AVLTree<T>::remove(BSTNode node, const T& value) {
    if (node == nullptr) return nullptr;

    if (value < node->value) node->left = remove(node->left, value);
    if (value > node->value) node->right = remove(node->right, value);

    if (node->value == value) { // found it
        if (node->left == nullptr) return node->right;
        if (node->right == nullptr) return node->left;
        else {
            node->value = next(node)->value;
            node->right = remove(node, node->value);
        }
    }

    updateHeight(node);
    return balance(node);
}

/**
 * Private Method: contains
 * ------------------------
 * Determines if the binary search tree contains a certain element.
 * @param node: The root node to serach below
 * @param element: The element to search for
 * @return: True if the element is contained in the tree, false otherwise
 */
template <class T>
bool AVLTree<T>::contains(BSTNode node, const T& element) {
    if (node == nullptr) return nullptr;
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
 * @param element:
 * @return
 */
template <class T>
BSTNode AVLTree<T>::search(BSTNode node, const T& element) {
    if (node == nullptr) return nullptr;
    if (node->value == element) return node;
    if (element < node->value) return search(node->left, element);
    if (element > node->value) return search(node->right, element);
    return nullptr;
}

/**
 * Private Method: rotateLeft
 * --------------------------
 * Rotates the tree counter-clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
BSTNode AVLTree<T>::rotateLeft(BSTNode node) {
    if (node->right == nullptr) return node; // Nothing to rotate onto
    auto root = node->right;
    node->right = node->right->left;
    root->left = node;
    return root;
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
BSTNode AVLTree<T>::balance(BSTNode node) {
    if (node == nullptr) return nullptr;

    int netBalance = getNetBalance(node);
    if (netBalance > 1) { // right is heavy
        int rightBalance = getNetBalance(node.right);
        if (rightBalance < 0) node->right = rotateRight(node->right);
        return leftRotate(node);
    } else if (netBalance < 1) { // left is heavy
        int leftBalance = getNetBalance(node->left);
        if (leftBalance > 0) node->left = rotateLeft(node->left);
        return rightRotate(node);
    } else return node;
}

/**
 * Private Method: rotateRight
 * --------------------------
 * Rotates the tree clockwise, returning the new root
 * @tparam T: Type of element stored in the tree node
 * @param node: Pointer to a binary search tree node to rotate
 * @return: The new root after having been rotated
 */
template <class T>
BSTNode AVLTree<T>::rotateRight(BSTNode node) {
    if (node->left == nullptr) return node; // Nothing to rotate onto
    auto root = node->left;
    node->left = root->right;
    root->right = node;
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
BSTNode AVLTree<T>::next(BSTNode node) {
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
void AVLTree<T>::updateHeight(BinaryNode<T>& node) {
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
int AVLTree<T>::getNetBalance(const BinaryNode<T>& node) {
    if (node->height == 0) return 0;
    if (node->right == nullptr) return - node->left->height;
    if (node->left == nullptr) return node->right->height;
    return node->right->height - node->left->height;
}