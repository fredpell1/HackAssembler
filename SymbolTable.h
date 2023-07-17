#pragma once
#include <map>
#include <string>
#include <bitset>
#include <iostream>
class SymbolTable
{
private:
	std::map<std::string, std::string> table;
	int currentAddress;

public:
	SymbolTable();
	void addToSymbolTable(std::string symbol);
	void addToSymbolTable(std::string symbol, int address);
	std::string getAddress(std::string symbol);
	friend std::ostream& operator<<(std::ostream& os, const SymbolTable& table);
};

