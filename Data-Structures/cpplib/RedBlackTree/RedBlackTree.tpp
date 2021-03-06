/*
 * File: RedBlackTree.tpp
 * ----------------------
 * Presents the template implementation of the RedBlackTree data structure.
 *a
 * Red-Black Tree is a self-balancing Binary Search Tree (BST) where every node follows following rules.
 * 1) Every node has a color either red or black.
 */

#include "BinaryNode.h"
#include "RedBlackTree.h"
#include <memory>
#include <tuple>
#include <limits>

template <class T>
using Node = std::shared_ptr<BinaryNode<T>>;

// Constructor
template <class T>
RedBlackTree<T>::RedBlackTree() { }

template <class T>
void RedBlackTree<T>::insert(const T& element) {
  root = insertAtBlack(root, element);
  setColor(root, black);
}

template <class T>
void RedBlackTree<T>::remove(const T& element) {
  root = remove(root, element);
  setColor(root, black);
}

template <class T>
bool RedBlackTree<T>::contains(const T& element) {
  return contains(root, element);
}

template <class T>
Node<T> RedBlackTree<T>::search(const T& element) {
  return search(root, element);
}

template <class T>
bool RedBlackTree<T>::verify() {
    bool isbst;
    std::tie(isbst, std::ignore, std::ignore) = is_bst(root);
    return isbst && is_rbt(root);
}

// Private members

/**
 * Private Method: insertAtBlack
 * ----------------------
 * Inserts an element into a node of a binary search tree, and balances the tree
 * @tparam T: The type of element contained in the node of the BST
 * @param node: Root node to insert element into. If nullptr, a new node will be created and returned
 * @param value: The value to store in the BST
 * @return: The (possibly new) root of the BST after insertion and balancing
 */
template <class T>
Node<T> RedBlackTree<T>::insertAtBlack(Node<T> node, const T& value) {
  if (node == nullptr) return std::shared_ptr<BinaryNode<T>>(new BinaryNode<T>(value, red));
  if (value == node->value) return node; // no duplicates

  if (value < node->value) { // regular insertion on the left
    if (node->left == nullptr || node->left->color == black)
      node->left = insertAtBlack(node->left, value); // black insertion
    else
      return insertAtRed(node->left, node, left, value); // red insertion

  } else { // regular insertion on the right
    if (node->right == nullptr || node->right->color == black)
      node->right = insertAtBlack(node->right, value);
    else
      return insertAtRed(node->right, node, right, value);
  }

  updateHeight(node);
  return node;
}

/**
 * Private Method: insertAtRed
 * ---------------------------
 * Insert an element at a red node
 * @tparam T: The type of element stored ine ach node
 * @param node: The node to insert at
 * @param parent: The parent of the node to insert at
 * @param side: The side of the parent that the insertion node is on
 * @param value: The value to insert
 * @return: The new parent node after insertion
 */
template <class T>
Node<T> RedBlackTree<T>::insertAtRed(Node<T> node, Node<T> parent, Side side, const T& value) {
  if (value < node->value) {
    node->left = insertAtBlack(node->left, value); // child must be black
    if (node->left->color == red) { // Insertion may have caused the black child to turn red
      Node<T> uncle = childOf(parent, otherSide(side));
      if (uncle != nullptr && uncle->color == red)
        recolor(parent); // recolor if uncle is red
      else
        return balance(parent, side, left); // rotate if uncle is black
    }
  }

  // Mirror image of the above logic
  if (value > node->value) {
    node->right = insertAtBlack(node->right, value);
    if (node->right->color == red) { // It may have changed color!
      Node<T> uncle = childOf(parent, otherSide(side));
      if (uncle != nullptr && uncle->color == red)
        recolor(parent); // Red uncle: simple recoloring
      else
        return balance(parent, side, right); // Black uncle: rotations
    }
  }
  updateHeight(parent);
  return parent;
}

/**
 * Private Method: recolor
 * -----------------------
 * Recolors the node to be red, and it's children to be black, and updates
 * the black heights of each of these nodes.
 * @tparam T: The type of element stored in the node
 * @param node: The node to recolor along with its children
 */
template <class T>
void RedBlackTree<T>::recolor(Node<T> node) {
  if (node == nullptr) return;

  if (node->left  != nullptr)
    setColor(node->left, black);
  if (node->right != nullptr)
    setColor(node->right, black);
  setColor(node, red);
}

/**
 * Private Method: balance
 * ----------------------
 * Rotates the tree at the given node in order to re-balance it
 * @tparam T: The type of element stored in each node
 * @param node: The node to rotate about.
 * @param side0: The direction that the node needs to be rotates away from
 * @param side1: The direction that the child of the node is leaning
 * @return: The new root node after the tree been balanced
 */
template <class T>
Node<T> RedBlackTree<T>::balance(Node<T> node, Side side0, Side side1) {
  if (side0 == left) {
    if (side1 == right) {
      node->left = rotate(node->left, left);
      updateHeight(node->left);
    }
    setColor(node, red);
    setColor(node->left, black);
    return rotate(node, right);

  } else {
    if (side1 == left) {
      node->right = rotate(node->right, right);
      updateHeight(node->right);
    }
    setColor(node, red);
    setColor(node->right, black);
    return rotate(node, left);
  }
}

/**
 * Private Method: remove
 * ----------------------
 * Removes a specified element from a binary search tree (BST) and re-balances the tree
 * @tparam T: Type of the element stored in the BST
 * @param node: The node to remove the value from
 * @param value: The value to remove the the node
 * @return: A new node after the removal and re-balancing
 */
template <class T>
Node<T> RedBlackTree<T>::remove(Node<T> node, const T& value) {
  if (node == nullptr) return nullptr; // not present in the tree

  // Search and remove from left
  if (value < node->value) {
    node->left = remove(node->left, value);
    if (getHeight(node->left) < getHeight(node->right)) // Left is double black
      return fixDoubleBlack(node, left);
    else {
      updateHeight(node);
      return node;
    }
  }

  // Search and remove from right
  if (value > node->value) {
    node->right = remove(node->right, value);
    if (getHeight(node->right) < getHeight(node->left)) // Right is double black
      return fixDoubleBlack(node, right);
    else {
      updateHeight(node);
      return node;
    }
  }

  // Removal of a leaf: doesn't matter if its red or black
  if (node->left == nullptr && node->right == nullptr)
    return nullptr;

  // Node has two children
  if (node->left != nullptr && node->right != nullptr) {
    node->value = next(node->right)->value;
    node->right = remove(node->right, node->value);
    if (getHeight(node->right) < getHeight(node->left)) // right is double black
      return fixDoubleBlack(node, right);
    else {
      updateHeight(node);
      return node;
    }
  }

  // Node has a single child
  if (node->left != nullptr) return node->left;
  else return node->right;
}

/**
 * Private Method: fixDoubleBlack
 * ---------------------------------
 * Fixes a node that has been colored double black during a deletion
 * @tparam T: Type of element stored in the node
 * @param node: The parent of the doube black node
 * @param side: The side of the parent that the double black node IS on
 * @return: New parent after fixing the double black node (may itself have turned double black!)
 */
template <class T>
Node<T> RedBlackTree<T>::fixDoubleBlack(Node<T> node, Side side) {
  Node<T> sibling = childOf(node, otherSide(side));

  // Red sibling
  if (sibling->color == red) {
    setColor(sibling, black);
    setColor(node, red);

    Node<T> root = rotate(node, side);
    if (side == left) {
        root->left = fixDoubleBlack(root->left, side);
        if (getHeight(root->left) < getHeight(root->right))
            return fixDoubleBlack(root, left);
    } else {
      root->right = fixDoubleBlack(root->right, side);
      if (getHeight(root->right) < getHeight(root->left))
          return fixDoubleBlack(root, right);
    }
    updateHeight(root);
    return root;
  }

  // Black sibling
  Side redChildSide = redChild(sibling);
  if (redChildSide != none) {
    return rotateDoubleBlack(node, otherSide(side), redChildSide);
  } else {
    setColor(sibling, red);
    updateHeight(node);
    setColor(node, black); // <-- just turned double black
    return node;
  }
}

/**
 * Private Method: rotateDoubleBlack
 * ---------------------------------
 * Fixes a double black by rotating
 * @tparam T: The type of element stored in each node
 * @param node: The node to rotate
 * @param side0: The side that the double black is not on
 * @param side1: The side that the red child of the non-double black node is on
 * @return: The new node after rotation performed
 */
template <class T>
Node<T> RedBlackTree<T>::rotateDoubleBlack(Node<T> node, Side side0, Side side1) {

  if (side0 == left) {
    if (side1 == left) { // Left Left
      setColor(node->left->left, black);
      if (node->color == red) {
          setColor(node, black);
          setColor(node->left, red);
      }
      return rotate(node, right);

    } else { // Left right
      setColor(node->left, red);
      setColor(node->left->right, black);
      node->left = rotate(node->left, left); // <-- rotate sub-tree
      updateHeight(node->left);

      if (node->color == red) {
          setColor(node, black);
          setColor(node->left, red);
      }

      setColor(node->left->left, black);
      return rotate(node, right);
    }

  } else {
    if (side1 == left) { // Right left
      setColor(node->right, red);
      setColor(node->right->left, black);
      node->right = rotate(node->right, right); // <-- rotate sub-tree
      updateHeight(node->right);

      if (node->color == red) {
          setColor(node, black);
          setColor(node->right, red);
      }

      setColor(node->right->right, black);
      return rotate(node, left);

    } else { // Right right
      setColor(node->right->right, black);
      if (node->color == red) {
          setColor(node, black);
          setColor(node->right, red);
      }
      return rotate(node, left);
    }
  }
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
bool RedBlackTree<T>::contains(const Node<T> node, const T& element) {
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
Node<T> RedBlackTree<T>::search(Node<T> node, const T& element) {
  if (node == nullptr) return nullptr;
  if (node->value == element) return node;
  if (element < node->value) return search(node->left, element);
  if (element > node->value) return search(node->right, element);
  return nullptr;
}

/**
 * Private Method: rotate
 * ----------------------
 * Rotate a node in a certain direction
 * @tparam T: Type of element stored in each node
 * @param node: The node to rotate
 * @param direction: The direction to rotate the node in
 * @return: The new root after rotation was performed
 */
template <class T>
Node<T> RedBlackTree<T>::rotate(Node<T> node, Side direction) {
  if (direction == left) return leftRotate(node);
  if (direction == right) return rightRotate(node);
  return node;
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
Node<T> RedBlackTree<T>::leftRotate(Node<T> node) {
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
Node<T> RedBlackTree<T>::rightRotate(Node<T> node) {
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
Node<T> RedBlackTree<T>::next(const Node<T> node) {
  if (node == nullptr) return nullptr;
  if (node->left == nullptr) return node;
  else return next(node->left);
}

/**
 * Private Method: setColor
 * ------------------------
 * Sets the color of a node while updating it's height accordingly
 * @tparam T: The type of element stored in the node
 * @param node: The node to set the color of
 * @param color: The color to set the node to
 */
template <class T>
void RedBlackTree<T>::setColor(Node<T> node, Color color) {
  if (node == nullptr) return; // nothing to do
  if (node->color == color) return; // nothing to do
  node->color = color;
  if (color == red) node->height--; // demotion
  else node->height++; // promotion
}

/**
 * Private Method: updateHeight
 * ----------------------------
 * Updates the height of a node to be the one plus the maximum of the heights of it's two children. Nodes with
 * no children have a height of zero.
 * @param node: A node to update the height on
 */
template <class T>
void RedBlackTree<T>::updateHeight(Node<T> node) {
  if (node == nullptr) return;
  node->height = getHeight(node);
}

/**
 * Private Method: getHeight
 * -------------------------
 * Re-calculates the black height of a node. This is defined to be the number of black nodes
 * between the current node (inclusive) and the leaf node. This will be set to the black height
 * of the node's children, if it is red, and one more than this value, if it is black.
 * The height of a null node is defined to be one.
 * @return: The black height of a node.
 */
template <class T>
size_t RedBlackTree<T>::getHeight(const Node<T> node) {
  if (node == nullptr) return 1; // Null nodes are black
  size_t selfHeight = node->color == black ? 1 : 0;
  if (node->left == nullptr) return 1 + selfHeight;
  else return selfHeight + node->left->height;
}

/**
 * Private Method: childOf
 * -----------------------
 * For getting the child of a node at a specific side
 * @tparam T: The type of element stored in the node
 * @param node: The node to get the child of
 * @param side: The side of the node to get a child from
 * @return: The child of the node on the specified side
 */
template <class T>
Node<T> RedBlackTree<T>::childOf(const Node<T> node, Side side) {
  if (side == left) return node->left;
  if (side == right) return node->right;
  return node;
}

/**
 * Private Method: otherSide
 * -------------------------
 * Turns left into right and right into left
 * @tparam T: The type of element stored in the red black tree
 * @param side: The side to invert
 * @return: Left if right is passed and vice versa.
 */
template <class T>
Side RedBlackTree<T>::otherSide(Side side) {
  return side == left ? right : left;
}

/**
 * Private Method: redChild
 * ------------------------
 * Determines if a node has a red child and returns the side that it is on
 * @tparam T: The type of element stored in each node
 * @param node: The node to find the red child of
 * @return: The side that the red child is one (left if boht), or none if no red children
 */
template <class T>
Side RedBlackTree<T>::redChild(const Node<T> node) {
  if (node == nullptr) return none;
  if (node->left != nullptr && node->left->color == red) return left;
  if (node->right != nullptr && node->right->color == red) return right;
  return none;
}

/**
 * Private Method: is_bst
 * ----------------------
 *  Verifies that a node is a binary search tree by making sure that it's value is 
 *  greater than and less than the maximum and minimum values of it's left and right 
 *  sub-trees, respectively
 *  @param node The root node of a BST to check if it's values are greater than or less than others
 *  @return tuple containing whether the tree with root node is a BST and the minimum and maximum
 *  values found in the entire tree
 */
template <class T>
std::tuple<bool, T, T> RedBlackTree<T>::is_bst(const Node<T> node) {

    if (node == nullptr) 
        return { true, std::numeric_limits<T>::max(), std::numeric_limits<T>::min() };

    bool left_is_bst, right_is_bst;
    T left_min, left_max, right_min, right_max;

    std::tie(left_is_bst, left_min, left_max) = is_bst(node->left);
    std::tie(right_is_bst, right_min, right_max) = is_bst(node->right);

    bool is_bst = left_is_bst && right_is_bst 
        && node->value >= left_max && node->value <= right_min;
    
    return { is_bst, std::min(node->value, left_min), std::max(node->value, right_max) };
}

/**
 * Private Method: is_rbt
 * ----------------------
 * Verifies that a node is properly formed by checking to make sure that:
 *  - If it is red, then it does not have a red child (red violation)
 *  - The black heights of its two children are equal (black height violation)
 *  - Both child nodes are properly formed
 *  Time complexity: O(n) (!!!)
 * @param node: The node to check for corruption
 * @return: True if the node (and all of it's children) are well formed, false otherwise
 */
template <class T>
bool RedBlackTree<T>::is_rbt(const Node<T> node) {
    if (node == nullptr) return true;
    
    // Correct value placements
    if (node->left != nullptr && node->left->value >= node->value)
        return false;

  if (node->right != nullptr && node->right->value <= node->value)
    return false;

  // Red violation
  if (node->color == red) {
    if (node->left != nullptr && node->left->color == red)
      return false;
    if (node->right != nullptr && node->right->color == red)
      return false;
  }

  // Incorrect height
  size_t expectedHeight = getHeight(node);
  if (node->height != expectedHeight){
    return false;
  }

  // Black height violation
  size_t leftHeight =  getHeight(node->left);
  size_t rightHeight = getHeight(node->right);
  if (leftHeight != rightHeight)
    return false;

  return is_rbt(node->left) && is_rbt(node->right); // check every sub-tree

}

