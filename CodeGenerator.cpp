#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(): parser(), destTable(), jumpTable(), compTable(), table()
{
	destTable["null"] = "000";
	destTable["M"] = "001";
	destTable["D"] = "010";
	destTable["MD"] = "011";
	destTable["A"] = "100";
	destTable["AM"] = "101";
	destTable["AD"] = "110";
	destTable["AMD"] = "111";

	jumpTable["null"] = "000";
	jumpTable["JGT"] = "001";
	jumpTable["JEQ"] = "010";
	jumpTable["JGE"] = "011";
	jumpTable["JLT"] = "100";
	jumpTable["JNE"] = "101";
	jumpTable["JLE"] = "110";
	jumpTable["JMP"] = "111";

	compTable["0"] = "101010";
	compTable["1"] = "111111";
	compTable["-1"] = "111010";
	compTable["D"] = "001100";
	compTable["A"] = compTable["M"] = "110000";
	compTable["!D"] = "001101";
	compTable["!A"] = compTable["!M"] = "110001";
	compTable["-D"] = "001111";
	compTable["-A"] = compTable["-M"] = "110011";
	compTable["D+1"] = "011111";
	compTable["A+1"] = compTable["M+1"] = "110111";
	compTable["D-1"] = "001110";
	compTable["A-1"] = compTable["M-1"] = "110010";
	compTable["D+A"] = compTable["D+M"] = "000010";
	compTable["D-A"] = compTable["D-M"] = "010011";
	compTable["A-D"] = compTable["M-D"] = "000111";
	compTable["D&A"] = compTable["D&M"] = "000000";
	compTable["D|A"] = compTable["D|M"] = "010101";
}

std::string CodeGenerator::processCInstruction(std::string instruction, instructions type)
{
	std::string comp = translateComp(parser.extractComp(instruction, type));
	std::string dest = translateDest(parser.extractDest(instruction, type));
	std::string jump = translateJump(parser.extractJump(instruction, type));
	return "111" + comp + dest + jump;
}

std::string CodeGenerator::processAInstruction(std::string instruction, instructions type)
{
	auto isNumeric = [&instruction](std::string instruction) {return !instruction.empty() && instruction.find_first_not_of("0123456789") == std::string::npos; };
	std::string symbol = parser.extractSymbol(instruction, type);
	std::string binInstruction = convertToBinary(symbol);
	if (!isNumeric(symbol)) {
		binInstruction = table.getAddress(symbol);
	}
	return binInstruction;
}

std::string CodeGenerator::translateDest(std::string instruction)
{
	return destTable[instruction];
}

std::string CodeGenerator::translateComp(std::string instruction)
{
	auto containsM = [&instruction](std::string instruction){return instruction.find("M") != std::string::npos; };
	std::string aBit = containsM(instruction) ? "1" : "0";
	return aBit + compTable[instruction];
}

std::string CodeGenerator::translateJump(std::string instruction)
{
	return jumpTable[instruction];
}

std::string CodeGenerator::convertToBinary(std::string instruction)
{
	int instructionAsInt = std::strtoul(instruction.c_str(), nullptr, 10);
	std::string binaryInstruction = std::bitset<15>(instructionAsInt).to_string();
	return "0" + binaryInstruction;
}


std::string CodeGenerator::generate(std::string instruction, instructions type)
{
	std::string binaryInstruction;
	switch (type)
	{
	case instructions::A:
		binaryInstruction = processAInstruction(instruction, type);
		break;
	case instructions::C:
		binaryInstruction = processCInstruction(instruction, type);
		break;
	case instructions::L:
		binaryInstruction = "";
		break;
	case instructions::Comments:
		binaryInstruction = "";
		break;
	default:
		binaryInstruction = "";
		break;
	}

	return binaryInstruction;
}

std::string CodeGenerator::build()
{
	parser.reset();
	while (parser.hasNextLine())
	{
		std::string line = parser.getNextLine();
		instructions type = parser.getInstructionType(line);
		if (type != instructions::Comments && type!=instructions::L) {
			std::cout << generate(line, type) << "\n";

		}
	}
	return "";
}

void CodeGenerator::build(std::ofstream & outputFile)
{
	if (!outputFile.is_open()) return;
	parser.reset();
	while (parser.hasNextLine())
	{
		std::string line = parser.getNextLine();
		instructions type = parser.getInstructionType(line);
		if (type != instructions::Comments && type != instructions::L) {
			outputFile << generate(line, type) << "\n";

		}
	}
	outputFile.close();
}

void CodeGenerator::printSymbolTable()
{
	std::cout << table << std::endl;
}

void CodeGenerator::fillSymbolTable()
{
	parser.reset();
	int i = 0;
	while (parser.hasNextLine()) {
		std::string line = parser.getNextLine();
		instructions type = parser.getInstructionType(line);
		
		if (type == instructions::L)
		{
			std::string symbol = parser.extractSymbol(line, type);
			table.addToSymbolTable(symbol,i);
		}
		if (type != instructions::Comments && type != instructions::L)
		{
			i++;
		}
	}
	parser.reset();
	while (parser.hasNextLine())
	{
		std::string line = parser.getNextLine();
		instructions type = parser.getInstructionType(line);
		if (type == instructions::A)
		{
			std::string symbol = parser.extractSymbol(line, type);
			auto isNumeric = [&symbol](std::string symbol) {return !symbol.empty() && symbol.find_first_not_of("0123456789") == std::string::npos; };
			if (!isNumeric(symbol))
			{
				table.addToSymbolTable(symbol);
			}
		}
	}
}

