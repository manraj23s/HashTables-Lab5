//========================================================================
//
//  Laboratory 10 Test Plan 1                                HashTable.cpp
//  Purpose: Function implementations for the implementation of HashTable.h
//
//========================================================================

#include "TableHash.h"
#include <iostream>
using namespace std;

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table size is inherited and new tree formed
///Inputs: None
///Outputs: No output, table is instantiated with template of size
template <typename DataType, typename KeyType>
TableHash<DataType, KeyType>::TableHash(int initTableSize)
{
	sizeOfTable = initTableSize;
	tableData = new BSTree<DataType, KeyType>[sizeOfTable];
}


//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table size is inherited with pointer address
///Inputs: None
///Outputs: No output, table template is instantiated with address
template <typename DataType, typename KeyType>
TableHash<DataType, KeyType>::TableHash(const TableHash& other)
{
	sizeOfTable = other.sizeOfTable;
	tableData = new BSTree<DataType, KeyType>[sizeOfTable];
	*this = other;
}

//=========================================================================

///Preconditions: If address is not same, then clear table and form new table
///Postconditions: New table formed with correct values for meemory
///Inputs: None
///Outputs: No output, new table formed with correct memory address
template <typename DataType, typename KeyType>
TableHash<DataType, KeyType>& TableHash<DataType, KeyType>::operator=(const TableHash& other)
{
	//if not equal, clear table and instantiate new table with size requirement
	if (this != &other)
	{
		//clear
		wipeClear();
		if (sizeOfTable == other.sizeOfTable)
		{
			//for index until size, instantiate indexes until size reached
			for (int i = 0; i < sizeOfTable; i++)
				tableData[i] = other.tableData[i];
		}
		else
		{
			//destructor for table if not same requirements as template
			delete[]tableData;
			//new instantiation of above function
			sizeOfTable = other.sizeOfTable;
			tableData = new BSTree<DataType, KeyType>[sizeOfTable];
			//repeat if statement's declaration above
			for (int i = 0; i < sizeOfTable; i++)
				tableData[i] = other.tableData[i];
		}
	}
	//return memory address
	return *this;
}

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table's memory is wiped and values cleared
///Inputs: User input to wipe table
///Outputs: Indication that table is cleared (empty table).
template <typename DataType, typename KeyType>
TableHash<DataType, KeyType>::~TableHash()
{
	//clear table
	wipeClear();

	//destroy data of table (memory)
	delete[]tableData;
	tableData = NULL;
	sizeOfTable = 0;
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Values added to hash table
///Inputs: User input to add a value
///Outputs: Inserted value is outputted
template <typename DataType, typename KeyType>
void TableHash<DataType, KeyType>::addValue(const DataType& keyAdd)
{
	//user value is a new hash table value adding key function modulus by size of table
	int valueIndex = (keyAdd.hash(keyAdd.getKey()) % sizeOfTable);
	//value is indexed to new data item to add
	tableData[valueIndex].insert(keyAdd);
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Values removed from hash table
///Inputs: User input to remove a value
///Outputs: Removed value taken out and resultant table outputted
template <typename DataType, typename KeyType>
bool TableHash<DataType, KeyType>::deleteValue(const KeyType& keyDelete)
{
	//if table is not empty, remove value
	if (!isTableEmpty())
	{
		//user value is a new hash table value removing key function modulus by size of table
		int valueIndex = DataType::hash(keyDelete) % sizeOfTable;
		//return table with removed value and deleted key
		return(tableData[valueIndex].remove(keyDelete));
	}
	//if table is empty, return false
	return false;
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Values retrieved from hash table
///Inputs: User input to retrieve a value
///Outputs: Retrieved value outputted
template <typename DataType, typename KeyType>
bool TableHash<DataType, KeyType>::fetchValue(const KeyType& retrieveKey, DataType& valueReturn) const
{
	//if the table is not empty, retrieve a value
	if (!isTableEmpty())
	{
		//index user value is retrieved from hash key
		unsigned int valueIndex = DataType::hash(retrieveKey) % sizeOfTable;
		//return value from searched table keys
		return(tableData[valueIndex].retrieve(retrieveKey, valueReturn));
	}
	//if table is empty, return false
	return false;
}

//=========================================================================

///Preconditions: Table must be declared and valid with values stored
///Postconditions: Table is cleared of its memory and values
///Inputs: User input to clear table
///Outputs: Cleared table outputted empty
template <typename DataType, typename KeyType>
void TableHash<DataType, KeyType>::wipeClear()
{
	//if table not empty, wipe it
	if (!isTableEmpty())
	{
		//for each index until size of table, clear the indexes
		for (int i = 0; i < sizeOfTable; i++)
			//clear the index values
			tableData[i].clear();
	}
}

//=========================================================================

///Preconditions: Table should be valid and declared
///Postconditions: If table is empty, return true, if not, return false
///Inputs: User input to check if empty
///Outputs: Bool value if table is empty or not
template <typename DataType, typename KeyType>
bool TableHash<DataType, KeyType>::isTableEmpty() const
{
	//for each index, check if there is a value
	for (int i = 0; i < sizeOfTable; i++)
	{
		//if a table index is not empty, return false
		if (!tableData[i].isEmpty())
			return false;
	}
	//if the table is empty, return true
	return true;
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Table structure is outputted
///Inputs: User input of values and start program
///Outputs: Table structure outputted and updated with each user command
template <typename DataType, typename KeyType>
void TableHash<DataType, KeyType>::showStructure() const {
	//for each index, output the index's key values
	for (int i = 0; i < sizeOfTable; ++i)
	{
		//index: = 0: y, 1: x, etc.
		cout << i << ": ";
		//write keys to table to output
		tableData[i].writeKeys();
	}
}

//=========================================================================