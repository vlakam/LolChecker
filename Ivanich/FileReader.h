#include <string>
#include <vector>
#include <fstream>
#pragma once
struct UserData
{
	std::string username;
	std::string password;
	std::string region;
};

class CFileReader
{
public:
	CFileReader(std::string fileName);
	~CFileReader();
	std::string getRandom(int length, bool _c);
	UserData getNext();
	UserData getCurrent();
	bool is_exists();
	int currentLine;
	std::string currentFile;
	std::vector<UserData> fileLines;
};