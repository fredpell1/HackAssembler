#pragma once
#include <map>
#include "Parser.h"
#include <string>
#include <cstdlib>
#include <bitset>
#include "SymbolTable.h"
class CodeGenerator
{
private:
	Parser parser;
	SymbolTable table;
	std::map<std::string, std::string> destTable;
	std::map<std::string, std::string> jumpTable;
	std::map<std::string, std::string> compTable;
public:


	CodeGenerator();
	CodeGenerator(const Parser& parser)
		: CodeGenerator()
	{
		this->parser = parser;
	}

	std::string generate(std::string instruction, instructions type);

	std::string processCInstruction(std::string instruction, instructions type);
	std::string processAInstruction(std::string instruction, instructions type);
	std::string translateDest(std::string instruction);
	std::string translateComp(std::string instruction);
	std::string translateJump(std::string instruction);

	std::string convertToBinary(std::string instruction);
	std::string build();
	void build(std::ofstream & outputFile);
	void printSymbolTable();
	void fillSymbolTable();

};

