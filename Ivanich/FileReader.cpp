#include "FileReader.h"
#include <iostream>
#include <locale>

CFileReader::CFileReader(std::string fileName)
{
	this->currentLine = 0;
	this->currentFile = fileName;
}
CFileReader::~CFileReader()
{

}
bool CFileReader::is_exists()
{
	return this->fileLines.empty() ? false : true;
}
UserData CFileReader::getCurrent()
{
	return this->fileLines[this->currentLine - 1];
}
UserData CFileReader::getNext()
{
	UserData temp;
	temp.region = "euw";
	if(!this->fileLines.empty())
	{
		if(this->currentLine >= this->fileLines.size())
		{
			temp.username = "0";
			temp.password = "0";
			return temp;
		}
	}

	if(!this->fileLines.empty())
	{
		return this->fileLines[this->currentLine++];
	}

	std::ifstream file(this->currentFile);
	std::string str;

	if(file.is_open())
	{
		while(std::getline(file, str))
		{
			//this->fileLines.push_back(str);
			temp.username = str.substr(0, str.find(":"));
			temp.password = str.substr(str.find(":") + 1, str.size()); 
			this->fileLines.push_back(temp);
		}
	}
	
	return this->fileLines[this->currentLine++];
}
std::string CFileReader::getRandom(int length, bool _c = false)
{
	std::string abc = "abcdefghijklmnopqrstuvwxyz0123456789";
	std::string characters = "!@#$%^&*";
	std::string newStr;

	while(newStr.size() < length)
	{
		newStr += abc[rand() % (abc.size() - 1)];
	}

	if(_c)
	{
		newStr += characters[rand() % (characters.size() - 1)];
	}

	return (std::string) newStr;
}