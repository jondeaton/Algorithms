/*
 * File: BinaryNode.h
 * ------------------
 * Created by jdeaton on 9/26/2017.
 */

#ifndef DATASTRUCTURES_BINARYNODE_H_H
#define DATASTRUCTURES_BINARYNODE_H_H

template <class T>
class BinaryNode<T> {

public:
    T value;

    void insertLeft(T element);
    void insertRight(T element);

private:
    std::shared_ptr<BinaryNode<T>> left;
    std::shared_ptr<BinaryNode<T>> right;
};

#endif //DATASTRUCTURES_BINARYNODE_H_H
