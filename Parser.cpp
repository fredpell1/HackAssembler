#include "Parser.h"

std::string Parser::removeComments(std::string line)
{
	size_t commentPos = line.find("//");
	if (commentPos != std::string::npos)
	{
		line = line.substr(0, commentPos);
	}
	return trim(line);
}

Parser::Parser(): inputFile(), inputFilename()
{
}

Parser::Parser(std::string inputFilename): inputFile(), inputFilename(inputFilename)
{
	inputFile.open(inputFilename);
}

Parser::~Parser() {
	if (inputFile.is_open()) {
		inputFile.close();
	}
}

std::string Parser::getNextLine() {
	std::string currentLine;
	getline(inputFile, currentLine);
	return currentLine;
}

bool Parser::hasNextLine() {
	return inputFile.is_open() && !inputFile.eof();
}

instructions Parser::getInstructionType(std::string line) {
	instructions instruction;
	line = trim(line);
	if (line.size() == 0) {
		instruction = instructions::Comments;
	}
	else 
	{
		switch (line.at(0))
		{
		case '@':  instruction = instructions::A; break;
		case '(': instruction = instructions::L; break;
		case '/': instruction = instructions::Comments; break;
		default: instruction = instructions::C; break;
		}

	}
	return instruction;
}

std::string Parser::extractSymbol(std::string line, instructions type)
{
	std::string symbol;
	line = trim(line);
	assert(type == instructions::A || type == instructions::L);
	switch (type)
	{
	case instructions::A:
		symbol = line.substr(1);
		break;
	case instructions::L:
		symbol = line.substr(1, line.size() - 2); // skip first and last
		break;
	}
	return symbol;
}

std::string Parser::extractDest(std::string line, instructions type)
{
	assert(type == instructions::C);
	line = trim(line);
	size_t equalPos = line.find("=");
	if (equalPos != std::string::npos)
	{
		return removeComments(line.substr(0, equalPos));
	}
	return "null";
}

std::string Parser::extractComp(std::string line, instructions type)
{
	assert(type == instructions::C);
	size_t equalPos = line.find("=");
	size_t semiColonPos = line.find(";");
	line = removeComments(line);
	if (equalPos == std::string::npos && semiColonPos == std::string::npos)
	{
		return line;
	}
	else if (equalPos != std::string::npos && semiColonPos == std::string::npos)
	{
		return line.substr(equalPos+1, std::string::npos);
	}
	else if (equalPos == std::string::npos && semiColonPos != std::string::npos)
	{
		return line.substr(0, semiColonPos);
	}
	else 
	{
		return line.substr(equalPos + 1, semiColonPos - equalPos -2);

	}


}

std::string Parser::extractJump(std::string line, instructions type)
{
	assert(type == instructions::C);
	size_t semiColonPos = line.find(";");
	line = removeComments(line);
	if (semiColonPos != std::string::npos)
	{
		return line.substr(semiColonPos + 1, std::string::npos);
	}
	return "null";
}







