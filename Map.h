#pragma once
#include "../Sem4_Lab1/List.h"
#include <queue>
#include "Iterator.h"
template <class K, class V>
class Map;
	
template <class K, class V>
struct Node
{
	K key;
	V value;
	Node* right;
	Node* left;
	Node* parent;
	bool isRed;

	friend Map<K, V>;

	Node(K key, V value)
	{
		right = nullptr;
		left = nullptr;
		parent = nullptr;
		isRed = true;
		this->key = key;
		this->value = value;
	};
};

template <class K, class V>
class Map
{
	Node<K, V>* root;
	void rightRotate(Node<K, V>* current);
	void leftRotate(Node<K, V>* current);
	void fixInsert(Node<K, V>* current);
	void fixDelete(Node<K, V>* current);
	void clearMap(Node<K, V>* current);



	class DFT_Iterator : public Iterator <Node <K, V>*>
	{
	public:
		DFT_Iterator(Node <K, V>*root) {
			current = root;
		};
		Node<K, V>* next() {
			if (current != nullptr) {
				Node<K, V>* n = current;
				if (current->right != nullptr)
					q.push(current);
				current = current->left;
				return n;
			}
			if (current == nullptr) {
				current = q.front();
				q.pop();
				current = current->right;
				next();
			}
		}
		bool has_next() {
			return (q.size() || current != nullptr);
		};

	private:
		queue<Node<K, V>*> q;
		Node<K, V>* current;
	};

	Iterator<Node <K, V>*>* create_dft_iterator() {
		return new DFT_Iterator(root);
	};




public:
	
	void insert(K key, V value);
	void remove(K key);
	Node<K, V>* findNode(K key);
	
	List<K>* get_keys()
	{
		List<K> * lstKey = new List<K>;
		if (root != nullptr) {
			auto *iter = create_dft_iterator();
			while (iter->has_next())
				lstKey->push_front(iter->next()->key);
		}
		return lstKey;
	};
	
	List<V>* get_values()
	{
		List<V> * lstValues = new List<V>;
		if (root != nullptr) {
			auto *iter = create_dft_iterator();
			while (iter->has_next())
				lstValues->push_front(iter->next()->value);
		}
		return lstValues;
	};

	Node<K, V>* get_root()
	{
		return root;
	};

	Map()
	{
		root = nullptr;
	};
	~Map()
	{
		clearMap(root);
		root = nullptr;
	};
};

