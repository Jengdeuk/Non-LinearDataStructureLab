#include "Container/HashTable.h"

#include <iostream>
#include <string>

struct ItemData
{
	std::string name;
	std::string type;
	int value;
};

HashTable<ItemData> itemDictionary;

void LoadItemList(const char* filename)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rt");
	if (file == nullptr)
	{
		return;
	}

	char buffer[4096] = {};
	size_t readSize = fread(buffer, sizeof(char), 4096, file);
	buffer[readSize] = '\0';

	char* lineCtx = nullptr;
	char* line = nullptr;

	line = strtok_s(buffer, "\n", &lineCtx);
	while (line)
	{
		ItemData newItem;

		char* colCtx = nullptr;
		char* token = nullptr;
		token = strtok_s(line, ",", &colCtx);
		newItem.name = token;

		token = strtok_s(nullptr, ",", &colCtx);
		newItem.type = token;

		token = strtok_s(nullptr, "\n", &colCtx);
		sscanf_s(token, "%d", &newItem.value);

		itemDictionary.Add(newItem.name, newItem);

		line = strtok_s(nullptr, "\n", &lineCtx);
	}

	fclose(file);
}

int main()
{
	LoadItemList("ItemList.txt");

	itemDictionary.Find("Frost Spear");
	itemDictionary.Remove("Frost Spear");
	itemDictionary.Find("Frost Spear");

	itemDictionary.List();
}