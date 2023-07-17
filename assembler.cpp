// assembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Parser.h"
#include "CodeGenerator.h"

void testSymbolLessAssembler() {
    Parser parser("..\\pong\\pongL.asm");
    CodeGenerator cg(parser);
    std::ofstream outFile;
    outFile.open("pongL.hack");
    cg.build(outFile);
    Parser binaryParser("pongl.hack");
    Parser testParser("..\\pong\\PongL.hack");
    bool correct = true;
    while (testParser.hasNextLine() && binaryParser.hasNextLine()) {
        std::string correctLine = testParser.getNextLine();
        std::string generatedLine = binaryParser.getNextLine();
        if (correctLine != generatedLine) {
            std::cout << correctLine << ", " << generatedLine << std::endl;
            correct = false;
        }
    }
    if (correct) {
        std::cout << "comparison successful" << std::endl;
    }
}
int main()
{
    //testSymbolLessAssembler();
    Parser parser("..\\pong\\pong.asm");
    CodeGenerator cg(parser);
    cg.fillSymbolTable();
    std::ofstream outFile("pong.hack");
    cg.build(outFile);
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
