/*
 * File: BinaryNode.h
 * ------------------
 * Created by jdeaton on 9/26/2017.
 */

#ifndef _binary_node_h
#define _binary_node_h

template <class T>
class BinaryNode<T> {

public:
    T value;

    void insertLeft(T& element);
    void insertRight(T& element);

private:
    std::shared_ptr<BinaryNode<T>> left;
    std::shared_ptr<BinaryNode<T>> right;
};

#endif