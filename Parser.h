#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
enum class instructions {A, C, L, Comments};

class Parser
{
private:
	std::ifstream inputFile;
	std::string inputFilename;
	
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

