#pragma once

#include "Pair.h"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

template <typename ValueType>
class HashTable
{
private:
	using Entry = Pair<std::string, ValueType>;

public:
	void Add(const std::string& key, const ValueType& value)
	{
		int bucketIdx = GenerateHash(key) % bucketCount;

		for (const Entry& item : table[bucketIdx])
		{
			if (item.key == key)
			{
				return;
			}
		}

		table[bucketIdx].emplace_back(key, value);
	}

	void Remove(const std::string& key)
	{
		int bucketIdx = GenerateHash(key) % bucketCount;

		if (table[bucketIdx].empty())
		{
			return;
		}

		for (auto iter = table[bucketIdx].begin(); iter != table[bucketIdx].end(); ++iter)
		{
			if ((*iter).key == key)
			{
				table[bucketIdx].erase(iter);
				std::cout << key << "를 삭제했습니다.\n\n";
				return;
			}
		}
	}
	
	void Find(const std::string& key)
	{
		int bucketIdx = GenerateHash(key) % bucketCount;

		for (const Entry& item : table[bucketIdx])
		{
			if (item.key == key)
			{
				std::cout << "> 찾은 아이템\n";
				std::cout << "Name: " << item.value.name << '\n';
				std::cout << "Type: " << item.value.type << '\n';
				std::cout << "Value: " << item.value.value << "\n\n";
				return;
			}
		}

		std::cout << "아이템을 찾지 못했습니다.\n\n";
	}

	void List()
	{
		std::cout << "> 아이템 목록 출력\n";
		int count = 0;
		for (int i = 0; i < bucketCount; ++i)
		{
			if (table[i].empty())
			{
				continue;
			}

			for (const Entry& item : table[i])
			{
				std::cout << ++count << ". " << item.value.name << " (" << item.value.type << "), " << item.value.value << "\n";
			}
		}
	}

private:
	static int GenerateHash(const std::string& keyString)
	{
		int hash = 0;

		const int length = static_cast<int>(keyString.length());
		for (int i = 0; i < length; ++i)
		{
			hash = hash * 31 + keyString[i];
		}

		return std::abs(hash);
	}

private:
	static const int bucketCount = 97;
	std::vector<Entry> table[bucketCount];
};
