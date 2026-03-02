#pragma once

#include <iostream>
#include <queue>

template <typename KeyType, typename ValueType>
struct Pair
{
	KeyType key{};
	ValueType value{};
};

template <typename KeyType, typename ValueType>
struct Node
{
	Pair<KeyType, ValueType> data;
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
};

template <typename KeyType, typename ValueType>
class Map
{
private:
	using Pair = Pair<KeyType, ValueType>;
	using Node = Node<KeyType, ValueType>;
	
public:
	~Map()
	{
		Destroy();
	}

public:
	void Insert(const Pair& newData)
	{
		Node* outNode = nullptr;
		if (SearchNode(newData.key, outNode))
		{
			return;
		}

		if (!root)
		{
			root = new Node{ newData };
			return;
		}

		root = InsertNodeRecursive(root, nullptr, newData);
	}

	void Delete(const KeyType& key)
	{
		DeleteNodeRecursive(root, key, root);

		std::cout << key << "의 점수를 지웠습니다.\n\n";
	}

	void Find(const KeyType& key)
	{
		Node* findNode = nullptr;
		if (!SearchNode(key, findNode))
		{
			std::cout << "해당 플레이어가 존재하지 않습니다.\n\n";
			return;
		}

		std::cout << findNode->data.key << ", " << findNode->data.value << "점 입니다.\n\n";
	}

	void Top(const int k)
	{
		MakeMaxHeap();

		std::cout << "> Top " << k << " 랭크 출력.\n";
		int cnt = 0;
		while (!maxHeap.empty() && cnt < k)
		{
			std::cout << ++cnt << "등. " << maxHeap.top().second << ", " << maxHeap.top().first << "점\n";
			maxHeap.pop();
		}
		std::cout << '\n';

		std::priority_queue<std::pair<ValueType, KeyType>>().swap(maxHeap);
	}

private:
	bool SearchNode(const KeyType& key, Node*& outNode)
	{
		return SearchNodeRecursive(root, key, outNode);
	}

	void Destroy()
	{
		DestroyNodeRecursive(root);
	}

	void MakeMaxHeap()
	{
		MakeMaxHeapRecursive(root);
	}

private:
	Node* InsertNodeRecursive(Node* node, Node* parent, const Pair& newData)
	{
		if (!node)
		{
			return new Node{ newData, parent };
		}

		if (newData.key < node->data.key)
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}
		else
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	Node* SearchMinNode(Node* node)
	{
		while (node->left)
		{
			node = node->left;
		}

		return node;
	}

	void DeleteNodeRecursive(Node* node, const KeyType& key, Node*& outNode)
	{
		if (!node)
		{
			outNode = nullptr;
			return;
		}

		if (key < node->data.key)
		{
			DeleteNodeRecursive(node->left, key, node->left);
			return;
		}
		else if (key > node->data.key)
		{
			DeleteNodeRecursive(node->right, key, node->right);
			return;
		}

		if (!node->left && !node->right)
		{
			delete node;
			outNode = nullptr;
		}
		else if (node->left && node->right)
		{
			node->data = SearchMinNode(node->right)->data;
			DeleteNodeRecursive(node->right, node->data.key, node->right);
		}
		else if (node->left)
		{
			Node* left = node->left;
			left->parent = node->parent;
			outNode = left;
			delete node;
		}
		else if (node->right)
		{
			Node* right = node->right;
			right->parent = node->parent;
			outNode = right;
			delete node;
		}
	}

	bool SearchNodeRecursive(Node* node, const KeyType& key, Node*& outNode)
	{
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		if (key == node->data.key)
		{
			outNode = node;
			return true;
		}

		if (key < node->data.key)
		{
			return SearchNodeRecursive(node->left, key, outNode);
		}
		else
		{
			return SearchNodeRecursive(node->right, key, outNode);
		}
	}

	void DestroyNodeRecursive(Node* node)
	{
		if (!node)
		{
			return;
		}

		DestroyNodeRecursive(node->left);
		DestroyNodeRecursive(node->right);

		delete node;
	}

	void MakeMaxHeapRecursive(Node* node)
	{
		if (!node)
		{
			return;
		}

		maxHeap.emplace(node->data.value, node->data.key);

		MakeMaxHeapRecursive(node->left);
		MakeMaxHeapRecursive(node->right);
	}

private:
	std::priority_queue<std::pair<ValueType, KeyType>> maxHeap;

private:
	Node* root = nullptr;
};
