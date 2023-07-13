// assembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Parser.h"
int main()
{
    Parser parser("..\\max\\MaxL.asm");
    while (parser.hasNextLine())
    {
        std::string line = parser.getNextLine();
        instructions type = parser.getInstructionType(line);
        std::cout << line << "\t";
        switch (type)
        {
        case instructions::A:
            std::cout << "\t" << parser.extractSymbol(line, type) << "\t";
            std::cout << "A\n";
            break;

        case instructions::C: 
            std::cout << "\t dest: " << parser.extractDest(line, type) << "\t";
            std::cout << "\t comp:" << parser.extractComp(line, type) << "\t";
            std::cout << "\t jump:" << parser.extractJump(line, type) << "\t";
            std::cout << "C\n";
            break;

        case instructions::L:
            std::cout << "\t" << parser.extractSymbol(line, type) << "\t";
            std::cout << "L\n";
            break;

        case instructions::Comments: std::cout << "Comments\n"; break;

        }
    }
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
