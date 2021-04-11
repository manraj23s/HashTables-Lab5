#pragma once
//========================================================================
//
//  Laboratory 10 Test Plan 1                                HashTable.h
//  Purpose: Class declaration for the functions of HashTable.h
//
//=========================================================================

#include <stdexcept>
#include <iostream>
#include "BSTree.cpp"
using namespace std;

//=========================================================================
//Hash table template
template <typename DataType, typename KeyType>
class TableHash {
public:
    //constructor
    TableHash(int initTableSize);
    //constructor with pointer
    TableHash(const TableHash& other);
    //operator function for constructir
    TableHash& operator=(const TableHash& other);

    //destructor
    ~TableHash();

    //insert
    void addValue(const DataType& newDataItem);
    //remove
    bool deleteValue(const KeyType& deleteKey);
    //retrieve
    bool fetchValue(const KeyType& searchKey, DataType& returnItem) const;
    //clear
    void wipeClear();

    //check if table empty
    bool isTableEmpty() const;

    //show structure of table
    void showStructure() const;

private:
    //size of table
    int sizeOfTable;
    //pointer of data table
    BSTree<DataType, KeyType>* tableData;
};
