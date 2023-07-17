#include "SymbolTable.h"

SymbolTable::SymbolTable(): table(), currentAddress()
{
	table["SP"] = std::bitset<16>(0).to_string();
	table["LCL"] = std::bitset<16>(1).to_string();
	table["ARG"] = std::bitset<16>(2).to_string();
	table["THIS"] = std::bitset<16>(3).to_string();
	table["THAT"] = std::bitset<16>(4).to_string();
	table["R0"] = std::bitset<16>(0).to_string();
	table["R1"] = std::bitset<16>(1).to_string();
	table["R2"] = std::bitset<16>(2).to_string();
	table["R3"] = std::bitset<16>(3).to_string();
	table["R4"] = std::bitset<16>(4).to_string();
	table["R5"] = std::bitset<16>(5).to_string();
	table["R6"] = std::bitset<16>(6).to_string();
	table["R7"] = std::bitset<16>(7).to_string();
	table["R8"] = std::bitset<16>(8).to_string();
	table["R9"] = std::bitset<16>(9).to_string();
	table["R10"] = std::bitset<16>(10).to_string();
	table["R11"] = std::bitset<16>(11).to_string();
	table["R12"] = std::bitset<16>(12).to_string();
	table["R13"] = std::bitset<16>(13).to_string();
	table["R14"] = std::bitset<16>(14).to_string();
	table["R15"] = std::bitset<16>(15).to_string();
	table["SCREEN"] = std::bitset<16>(16384).to_string();
	table["KBD"] = std::bitset<16>(24576).to_string();
	currentAddress = 16;
}

void SymbolTable::addToSymbolTable(std::string symbol)
{
	if (table.find(symbol) == table.end())
	{
		table[symbol] = std::bitset<16>(currentAddress++).to_string();
	}
}

void SymbolTable::addToSymbolTable(std::string symbol, int address)
{
	if (table.find(symbol) == table.end())
	{
		table[symbol] = std::bitset<16>(address).to_string();
	}
}

std::string SymbolTable::getAddress(std::string symbol)
{
	return table[symbol];
}

std::ostream& operator<<(std::ostream& os, const SymbolTable& table)
{
	for (auto it = table.table.begin(); it != table.table.end(); ++it) {
		os << it->first << ": " << it->second << std::endl;
	}
	return os;
}
