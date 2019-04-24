#include "Map.h"



template<class K, class V>
void Map<K, V>::rightRotate(Node<K, V>* current)
{
	Node<K, V>* left_child = current->left;
	current->left = left_child->right;

	if (current->left != nullptr)
		current->left->parent = current;

	left_child->parent = current->parent;

	if (current->parent == nullptr)
		root = left_child;
	else if (current == current->parent->left)
		current->parent->left = left_child;
	else
		current->parent->right = left_child;

	left_child->right = current;
	current->parent = left_child;
}

template<class K, class V>
void Map<K, V>::leftRotate(Node<K, V>* current)
{
	Node<K, V>* right_child = current->right;
	current->right = right_child->left;

	if (current->right != nullptr)
		current->right->parent = current;

	right_child->parent = current->parent;

	if (current->parent == nullptr)
		root = right_child;
	else if (current == current->parent->left)
		current->parent->left = right_child;
	else
		current->parent->right = right_child;

	right_child->left = current;
	current->parent = right_child;
	}

template<class K, class V>
Node<K, V>* Map<K, V>::findNode(K key)
{
	Node<K, V> *current = root;
	while (current != nullptr)
	{
		if (current->key == key)
			break;
		if (key > current->key)
			current = current->right;
		else if (key < current->key)
			current = current->left;
	}
	return current;
}


template<class K, class V>
void Map<K, V>::clearMap(Node<K, V>* current)
{
	if (current != nullptr)
	{
		if (current->right != nullptr) clearMap(current->right);
		if (current->left != nullptr) clearMap(current->left);
		delete current;
	}
}

/*************************************************************************************************************
	1.Each node is either red or black.
	2.The root is black. (This rule is sometimes omitted.) 
	3.All leaves (NIL) are black.
	4.If a node is red, then both its children are black.
	5.Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
***************************************************************************************************************/

template<class K, class V>
void Map<K, V>::insert(K key, V value)
{
	
		Node<K, V>* newNode = new Node<K, V>(key, value);
		
		//can't change the value
		if (findNode(key) != nullptr)
			return; 

		if (root == nullptr)
			root = newNode;
		else
		{
			Node<K, V>* current = root;
			Node<K, V>* parent = nullptr;
			while (current != nullptr) // go down to find place for node
			{
				parent = current;
				if (parent->key < key)
					current = parent->right;
				else
					current = parent->left;
			}
			// set pointers
			newNode->parent = parent;
			if (parent->key < newNode->key)
				parent->right = newNode;
			else
				parent->left = newNode;
			
		}
		fixInsert(newNode);

}

template<class K, class V>
void Map<K, V>::remove(K key)
{
	if (root == nullptr)
	{
		return;
	}

	Node<K, V>* to_delete = findNode(key);
	if (to_delete==nullptr)
		return;

	
	Node<K, V>* movingNode;
	Node<K, V>* temp;
	
	if (to_delete->left == nullptr || to_delete->right == nullptr)
		movingNode = to_delete;
	else //both child
	{
		if (to_delete->left != nullptr)
		{
			temp = to_delete->left;
			while (temp->right != nullptr)
				temp = temp->right;
		}
		else
		{
			temp = to_delete->right;
			while (temp->left != nullptr)
				temp = temp->left;
		}
		movingNode = temp; //find node without left child
	}


	if (movingNode->left != nullptr) //zero-one child
		temp = movingNode->left;
	else
		if (movingNode->right != nullptr)
			temp = movingNode->right;
		else
			temp = nullptr;

	if (temp != nullptr) //one child
		temp->parent = movingNode->parent;

	if (movingNode->parent == nullptr) // in case zero-one child of deleting node
		root = temp;
	else
	{
		if (movingNode == movingNode->parent->left)
			movingNode->parent->left = temp;
		else
			movingNode->parent->right = temp;
	}

	if (movingNode != to_delete)
	{
		to_delete->isRed = movingNode->isRed;
		to_delete->key = movingNode->key;
		to_delete->value = movingNode->value;
	}
	
	if (movingNode->isRed == 0)
		fixDelete(temp);
		

}

template<class K, class V>
void Map<K, V>::fixInsert(Node<K, V>* current)
{
	Node<K, V>* parent = nullptr;
	Node<K, V>* grandparent = nullptr;
	while (current != root && current->isRed && current->parent->isRed) 
	{
		parent = current->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) //if node is left son
		{
			Node<K,V>* uncle = grandparent->right;
			if (uncle != nullptr && uncle->isRed) //if uncle exist and red
			{
				uncle->isRed = 0;
				parent->isRed = 0;
				grandparent->isRed = 1;
				current = grandparent;
			}
			else 
			{
				if (current == parent->right) 
				{
					leftRotate(parent);
					current = parent;
					parent = current->parent;
				}
				rightRotate(grandparent);
				swap(parent->isRed, grandparent->isRed);
				current = parent;
			}
		}
		else //if node is right son
		{
			Node<K, V>* uncle = grandparent->left;
			if (uncle != nullptr && uncle->isRed) 
			{
				uncle->isRed = 0;
				parent->isRed = 0;
				grandparent->isRed = 1;
				current = grandparent;
			}
			else 
			{
				if (current == parent->left) 
				{
					rightRotate(parent);
					current = parent;
					parent = current->parent;
				}
				leftRotate(grandparent);
				swap(parent->isRed, grandparent->isRed);
				current = parent;
			}
		}
	}
	root->isRed = 0;
}

template<class K, class V>
void Map<K, V>::fixDelete(Node<K, V>* current)
{
	if (current != nullptr)
	{
		Node<K, V>* temp;
		while (current != root && !current->isRed)
		{
			
			if (current->parent->left == current) //if node is left child
			{
				temp = current->parent->right; //brother
				if (temp->isRed) //if brother is red
				{
					temp->isRed = false; //brother = black
					current->parent->isRed = true; //parent = red
					leftRotate(current->parent);
					temp = current->parent->right;
				}
				if (!temp->right->isRed && !temp->left->isRed)  // if both child are black
				{
					temp->isRed = true;
					current = current->parent;
				}
				else
				{
					if (!temp->right->isRed) //if right is black
					{
						temp->left->isRed = false;
						temp->isRed = true;
						rightRotate(temp);
						temp = current->parent->right;
					}
					temp->isRed = current->parent->isRed;
					current->parent->isRed = false;
					temp->right->isRed = false;
					leftRotate(current->parent);
					current = root;
				}
			}
			else //if node is left child
			{
				temp = current->parent->left; //brother
				if (temp->isRed) //brother is red
				{
					temp->isRed = true;
					current->parent->isRed = true;
					rightRotate(current->parent);
					temp = current->parent->left;
				}
				if (!temp->left->isRed && !temp->right->isRed) // both child are black
				{
					temp->isRed = true;
					current = current->parent;
				}
				else
				{
					if (!temp->left->isRed) //if left is black
					{
						temp->right->isRed = false;
						temp->isRed = true;
						leftRotate(temp);
						temp = current->parent->left;
					}
					temp->isRed = current->parent->isRed;
					current->parent->isRed = false;
					temp->left->isRed = false;
					rightRotate(current->parent);
					current = root;
				}
			}
			
		}
		current->isRed = false;
		root->isRed = false;
	}
}

