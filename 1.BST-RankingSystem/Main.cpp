#include "Containter/Map.h"

#include <string>

Map<std::string, int> leaderBoard;

void LoadLeaderBoard(const char* filename)
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
		Pair<std::string, int> newData;

		char* colCtx = nullptr;
		char* token = nullptr;
		token = strtok_s(line, ",", &colCtx);
		newData.key = token;

		token = strtok_s(nullptr, "\n", &colCtx);
		sscanf_s(token, "%d", &newData.value);

		leaderBoard.Insert(newData);

		line = strtok_s(nullptr, "\n", &lineCtx);
	}

	fclose(file);
}

int main()
{
	LoadLeaderBoard("LeaderBoard.txt");

	leaderBoard.Top(20);

	leaderBoard.Find("NightOracle");

	leaderBoard.Delete("NightOracle");
	leaderBoard.Delete("ChaosBringer");

	leaderBoard.Top(5);
}