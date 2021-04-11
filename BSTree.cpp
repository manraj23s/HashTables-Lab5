//--------------------------------------------------------------------
//
//  Laboratory 9                                            BSTree.cpp
//
//BSTree.cpp creates a binary search tree with basic functions inherited from BSTree.h

#include <new>
#include <iostream>
#include "BSTree.h"

using namespace std;

//--------------------------------------------------------------------

/// Default Constructor for BST node, sets BST node values to given values
/// Preconditions: BST must be declared and accessible.
/// Postconditions: All data members of the BST node will be updated.
/// Inputs: nodeDataItem- Data item in node will be set to this value.
///			leftPtr- BST node pointer for left branch of the tree. Value set to left pointer.
///			rightPtr- BST node pointer for right branch of the tree. Value set to right pointer.
/// Outputs: Node items updated with memory from BST.h data members to be accessible
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem, BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	// Update node items
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

//--------------------------------------------------------------------

///Default Constructor for BST, sets root pointer of BST to NULL.
///Preconditions: None
///Postconditions: The root pointer will now be pointing to NULL.
///Input: None
///Output: The root pointer is initialized to NULL.
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
{
	// Initialize root to null
	root =NULL;
}

//--------------------------------------------------------------------

///Copy constructor for BST sets root to NULL, which allows overloaded constructor to create copy of BST.
///Preconditions: Function has to be called with valid BST as parameter.
///Postconditions: Tree will be created and updated as a given copy of the current BST.
///Input: Given BST to be copied assigned to this.
///Output: Overloadedconstructor can create a copy of BST and can output given tree.
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{
	//Root initialized to null
	root = NULL;
	//Assign given tree to current tree
	*this = other;
}

//--------------------------------------------------------------------

///Function overloads assignment operator so that one BST may be assigned to another, and clears current tree to copy given tree.
///Preconditions: Source BST must be declared and a valid tree.
///Postconditions: New tree will be a copy of the given tree.
///Inputs: Given source BST to be copied.
///Output: Returns updated tree object. Also can clear tree if necessary and call copy helper with root.
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>::operator=(const BSTree<DataType, KeyType>& other)
{
	//Clear current tree if needed
	if (root != NULL)
	{
		clear();
	}
	//Copy helper called with root
	copyTreeHelper(root, other.root);

	//Return tree object
	return *this;
}

//--------------------------------------------------------------------

///Destructor calls clear function to clear tree.
///Preconditions: BST must be declared.
///Postconditions: Tree will have nodes deleted and root will be pointed to NULL.
///Inputs: Tree with allocated memory in nodes.
///Outputs: Tree will have memory cleared in nodes, and nodes will point to null.
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree()
{
	//Clear used tree memory.
	clear();
}

//--------------------------------------------------------------------

///Insert function calls insert helper function to insert given data item into the tree.
///Preconditions: BST must be declared and function must be called with valid data item of DataType.
///Postconditions: Tree will be updated with new value to insert.
///Inputs: newDataItem of DataType to be inserted in the proper location in the tree.
///Outputs: The tree is updated to output inserted data items into the tree.
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
	insertHelper(root, newDataItem);
}

//--------------------------------------------------------------------

///Retrieve function which calls retrieve helper function with root pointer to retrieve the search data item of the search key.
///Preconditions: BST must be declared and function called with valid parameters for search key and data item.
///Postconditions: Tree is unchanged and searchDataItem will be updated with the data of searchKey, if there.
///Inputs: Given searchKey is to be searched for in BST.
///Outputs: searchDataItem data item is updated with searchKey data in the tree if there. Boolean returns true if key is found, false if not.
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	return(retrieveHelper(root, searchKey, searchDataItem));
}

//--------------------------------------------------------------------

///* Remove function which calls remove helper function with root pointer to remove the data item of the given key.
///Preconditions: -# Binary tree must be declared. -# Function must be called with valid parameter for delete key.
///Postconditions: -# Tree will be updated, with the given key deleted.
///Inputs: deleteKey Constant key value of the key to be deleted.
///Outputs: @return Boolean value. Returned true if key is found and deleted. Returned false if key is not found.
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	return(removeHelper(root, deleteKey));
}

//--------------------------------------------------------------------

///Write Keys function displays keys of BST in order. If tree is empty, there will be no output. 
///This function calls the write keys helper function with a root ptr to display BST keys.
///Preconditions: BST must be declared.
///Postconditions: Tree will not change.
///Inputs: Declared BST
///Outputs: Helps to display keys of the whole tree.
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys() const
{
	writeKeysHelper(root);
	cout << endl;
}

//--------------------------------------------------------------------

///Clear function calls clear helper with root ptr which clears and deallocate whole tree.
///Preconditions: Binary tree must be declared.
///Postconditions: Tree will be cleared and root pointer will point to null.
///Inputs: The BST with allocated memory, helped by clear helper.
///Outputs: Cleared tree and null root pointer.
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear()
{
	clearHelper(root);
}

//--------------------------------------------------------------------

///isEmpty function checks whether the tree is empty, so if root pointer is null.
///Preconditions:  Binary tree must be declared. 
///Postconditions: Tree will not change.
///Inputs: Declared BST with root and nodes.
///Outputs: Boolean value returns true if null root and empty tree. Returns false otherwise.
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
{
	return(root == NULL);
}

//--------------------------------------------------------------------

///getCount determines the number of data items in BST. 
///This function calls getCountHelper with root pointer, which returns # of items in the entire tree.
///Preconditions: BST must be declared.
///Postconditions: Tree will be unchanged.
///Inputs: BST with node and root pointer.
///Outputs: Integer value of # of items in the tree.
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount() const
{
	return(getCountHelper(root));
}

//--------------------------------------------------------------------

///showStructure Function shows structure of the tree. Tells if tree is empty. Calls showStructureHelper function.
///Preconditions: Binary tree must be declared.
///Postconditions: Tree will be unchanged.
///Inputs: Valid and declared BST.
///Outputs: Outputs the keys in a binary search tree, or "Empty tree." Uses reverse inorder traversal.
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showStructure() const
{
	if (root == 0)
		cout << "Empty tree" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}

//--------------------------------------------------------------------

//Recursive Helpers
///Show structure helper function recursively displays structure of BST.
///Preconditions: Binary tree must be declared. Binary tree will not be empty. Function must be called with a valid binary search tree pointer.
///Postconditions: Tree will be unchanged.
///Inputs: Valid and declared BST from right to middle to left.
///Outputs: BST structure displayed recursively
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::showHelper(BSTreeNode* p, int level) const
{
	int j;   // Loop counter
	if (p != 0)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)              // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();     // Output key
		if ((p->left != 0) &&                    // Output greater or less than
			(p->right != 0))
			cout << "<";
		else if (p->right != 0)
			cout << "/";
		else if (p->left != 0)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}

//--------------------------------------------------------------------

///copyHelper function recursively copies nodes of source tree to destination tree.
///Preconditions: BST must be declared and contain valid data.
///Postconditions: Source tree is not changed. Destination BST will be a copy of the source tree.
///Inputs: Left and right nodes of source tree to be copied recursively.
///Outputs: No output, but destination BST created.
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode*& dest, BSTreeNode* src)
{
	if (src != NULL)
	{
		// Create new node with source data
		dest = new BSTreeNode(src->dataItem, NULL, NULL);

		// Copy left and right nodes recursively
		copyTreeHelper(dest->left, src->left);
		copyTreeHelper(dest->right, src->right);
	}
}

//--------------------------------------------------------------------

///clearHelper function recursively clears the tree from the given pointer. Upon completion, the entire tree from the given node will be cleared.
///Preconditions: BST must be declared and function must be called with valid BST pointer.
///Postconditions: Binary tree is cleared and all nodes from "this" pointer are deallocated, which leaves null given pointer.
///Inputs: A pointer that is not NULL.
///Outputs: Nullified binary tree pointers.
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& ptr)
{
	if (ptr != NULL)
	{
		// Clear left and right nodes
		clearHelper(ptr->left);
		clearHelper(ptr->right);

		// Delete current pointer and set to null
		delete ptr;
		ptr = NULL;
	}
}

//--------------------------------------------------------------------

///insertHelper function recursively inserts given data item in location of tree by checking the correct key value.
///Precondtions: BST must be declared and function must be called with valid BST pointer and DataType item.
///Postconditions: Binary search tree may be updated to include the new data item.
///Inputs: Valid BST node with non-null pointer.
///Outputs: No output, but inserts data item into tree by checking keys.
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode*& ptr, const DataType& newDataItem)
{
	if (ptr == NULL)
		ptr = new BSTreeNode(newDataItem, NULL, NULL);
	else if (newDataItem.getKey() < ptr->dataItem.getKey())
		insertHelper(ptr->left, newDataItem);
	else if (newDataItem.getKey() > ptr->dataItem.getKey())
		insertHelper(ptr->right, newDataItem);
	else
		ptr->dataItem = newDataItem;
}

//--------------------------------------------------------------------

///retrieveHelper function recursively retrieves data item of given key, if found.
///Preconditions: BST must be declared and function called with valid BST pointer, key of KeyType, DataType data item for searching.
///Postconditions: BST will not change. searchDataItem will updated with data from tree, there is a key.
///Inputs: A valid BST search pointer that is not null.
///Outputs: Data retrieved of a given key, if it exists.
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode* ptr, const KeyType& searchKey, DataType& searchDataItem) const
{
	if (ptr == NULL)
		return false;
	else if (searchKey < ptr->dataItem.getKey())
		return(retrieveHelper(ptr->left, searchKey, searchDataItem));
	else if (searchKey > ptr->dataItem.getKey())
		return(retrieveHelper(ptr->right, searchKey, searchDataItem));
	else
	{
		searchDataItem = ptr->dataItem;
		return true;
	}
}

//--------------------------------------------------------------------

///removeHelper function recursively removes BST node containing a given key, if key exists.
///Preconditions: BST must be declared and function called with valid BST pointer and keyType key.
///Postconditions: BST updated if key is found and if found, node of given key is deleted. Rest of the tree unchanged.
///Inputs: A valid BST pointer that has non-null value.
///Outputs: Updated BST with removed key.
template < typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& ptr, const KeyType& deleteKey)
{
	BSTreeNode* temp;
	if (ptr == NULL)
		return false;
	else if (deleteKey < ptr->dataItem.getKey())
		return(removeHelper(ptr->left, deleteKey));
	else if (deleteKey > ptr->dataItem.getKey())
		return(removeHelper(ptr->right, deleteKey));
	else
	{
		if (ptr->left == NULL && ptr->right == NULL)
		{
			delete ptr;
			ptr = NULL;
			return true;
		}
		else if (ptr->left != NULL && ptr->right == NULL)
		{
			temp = ptr;
			ptr = ptr->left;
			delete temp;
			return true;
		}
		else if (ptr->left == NULL && ptr->right != NULL)
		{
			temp = ptr;
			ptr = ptr->right;
			delete temp;
			return true;
		}
		else
		{
			temp = ptr->left;
			while (temp->right != NULL)
			{
				temp = temp->right;
			}
			ptr->dataItem = temp->dataItem;
			removeHelper(ptr->left, temp->dataItem.getKey());
		}
	}
}

//--------------------------------------------------------------------

///writeKeysHelper function recursively helps display keys of BST in order.
///Preconditions: BST must be declared and pointer should have a non-null value to conduct its role.
///Postconditions: helper assigns pointer to the left with the data item, then the right,
///Inputs: A valid BST pointer that has a value.
///Outputs: Updated BST with displayed key for whole tree.
template < typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode* ptr) const
{
	if (ptr != NULL)
	{
		writeKeysHelper(ptr->left);
		cout << (ptr->dataItem).getKey() << ' ';
		writeKeysHelper(ptr->right);
	}
}

//--------------------------------------------------------------------
//                         Programming Exercise 2
//--------------------------------------------------------------------

///getHeight function determines the height of BST. If empty tree, returns zero height. 
///Calls the getHeightHelper function with root pointer to determine the height of the tree recursively.
///Preconditions: Binary tree must be declared.
///Postconditions: Tree will be unchanged.
///Inputs: BST with root and node values.
///Outputs: Integer value of the height of BST.
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight() const
{
	return(getHeightHelper(root));
}

//--------------------------------------------------------------------

///getCountHelper function recursively determines number of data items in BST.
///Preconditions: BST must be declared.
///Postconditions: Tree is unchanged.
///Inputs: BST with node and root pointers.
///Outputs: Integer value of number of items in tree.
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode* ptr) const
{
	if (ptr == NULL)
		return 0;
	else
		return(1 + getCountHelper(ptr->left) + getCountHelper(ptr->right));
}

//--------------------------------------------------------------------

///getHeightHelper function recursively determines the height of BST by checking pointer value and determining height.
///Preconditions: BST must be declared.
///Postconditions: BST is unchanged, just observed.
///Inputs: A BST witg root and node values.
///Outputs: An integer value for the height of the BST.
template < typename DataType, typename KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode* ptr) const
{
	if (ptr == NULL)
	{
		return 0;
	}
	else
	{
		if (getHeightHelper(ptr->left) > getHeightHelper(ptr->right))
		{
			return(1 + getHeightHelper(ptr->left));
		}
		else
		{
			return(1 + getHeightHelper(ptr->right));
		}
	}
}