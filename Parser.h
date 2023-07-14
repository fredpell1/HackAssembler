#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
enum class instructions {A, C, L, Comments};



// trim from start
static inline std::string& ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string& rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string& trim(std::string& s) {
	return ltrim(rtrim(s));
}

class Parser
{
private:
	std::ifstream inputFile;
	std::string inputFilename;
	std::string removeComments(std::string line);
public:
	Parser();
	Parser(std::string inputFilename);
	~Parser();

	std::string getNextLine();

	bool hasNextLine();

	instructions getInstructionType(std::string line);

	std::string extractSymbol(std::string line, instructions type);

	std::string extractDest(std::string line, instructions type);

	std::string extractComp(std::string line, instructions type);

	std::string extractJump(std::string line, instructions type);

};

