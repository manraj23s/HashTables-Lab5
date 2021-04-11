#pragma once
//--------------------------------------------------------------------
//
//  Laboratory 9                                    BSTree.h
//
//  Class declarations for the linked implementation of the Binary
//  Search Tree ADT -- including the recursive helpers of the
//  public member functions
//
//--------------------------------------------------------------------

#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <iostream>
using namespace std;

template < typename DataType, class KeyType >    // DataType : tree data item
class BSTree                                     // KeyType : key field
{
public:

    //Constructor
    BSTree();                                                      // Default constructor
    BSTree(const BSTree<DataType, KeyType>& other);                // Copy constructor
    BSTree& operator= (const BSTree<DataType, KeyType>& other);    // Overloaded assignment operator

    //Destructor
    ~BSTree();

    //Binary search tree manipulation operations
    void insert(const DataType& newDataItem);                                //Insert data item
    bool retrieve(const KeyType& searchKey, DataType& searchDataItem) const; //Retrieve data item
    bool remove(const KeyType& deleteKey);       //Remove data item
    void writeKeys() const;                      //Output keys
    void clear();                                //Clear tree

    //Binary search tree status operations
    bool isEmpty() const;                        //Tree is empty
    //!! isFull() has been retired. Not very useful in a linked structure.

    //Output the tree structure -- used in testing/debugging
    void showStructure() const;

    //In-lab operations
    int getHeight() const;                              //Height of tree
    int getCount() const;			                    //Number of nodes in tree

protected:

    class BSTreeNode      //Inner class: facilitator for the BSTree class
    {
    public:
        //Constructor
        BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr);

        //Data members
        DataType dataItem;   //Binary search tree data item
        BSTreeNode* left,    //Pointer to the left child
            * right;         //Pointer to the right child
    };

    //Recursive helpers for the public member functions
    
    //Outputs the subtree whose root node is pointed to by p.
    void showHelper(BSTreeNode* p, int level) const;
    
    //Recursive helper function that helps set a tree to be equivalent to another tree.
    void copyTreeHelper(BSTreeNode*& dest, BSTreeNode* source);
    
    //Recursive helper for clear. Clears the subtree pointed to by p.
    void clearHelper(BSTreeNode*& ptr);
    
    //Recursive helper function for insert. Inserts newDataItem in the subtree pointed to by p.
    void insertHelper(BSTreeNode*& ptr, const DataType& newDataItem);
    
    //Recursive helper function for retrieve. Searches the subtree pointed to by p.
    bool retrieveHelper(BSTreeNode* ptr, const KeyType& searchKey, DataType& searchDataItem) const;
    
    //Recursive helper function for remove. Searches the subtree pointed to by p for the node with key deleteKey.
    bool removeHelper(BSTreeNode*& ptr, const KeyType& deleteKey);
    
    //Recursive helper for writeKeys. Outputs the keys in the subtree pointed to by p.
    void writeKeysHelper(BSTreeNode* ptr) const;
    
    //Recursive partner of the getCount() function. Returns the count of the subtree pointed to by p.
    int getCountHelper(BSTreeNode* ptr) const;  //ex 2
    
    //Recursive helper for height. Returns the height of the subtree pointed to by p.
    int getHeightHelper(BSTreeNode* ptr) const; //ex 2

    //Data member
    BSTreeNode* root;   //Pointer to the root node
};

#endif	//define BSTREE_H

