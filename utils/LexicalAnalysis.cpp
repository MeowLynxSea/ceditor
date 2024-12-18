#include "LexicalAnalysis.h"
#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::string input = "int main()\n\
{\n\
    int a=-5,b=4,j; //this is an inline comment\n\
if(a >= b)\n\
j++;\n\
/*\n\
This is a block comment\n\
*/\n\
string str=\"test str\";\n\
j = a - b;\n\
else  j=b-a;\n\
    return j;\n\
}";
    std::string ruleName = "cpp";
    LexicalAnalysis lexicalAnalysis = LexicalAnalysis(ruleName);
    lexicalAnalysis.setRawText(input);
    lexicalAnalysis.printProcessedText();
    MyVector<Token> tokens = lexicalAnalysis.tokenize();
    std::cout << "Tokenized text: " << std::endl;
    for (size_t i = 0; i < tokens.size(); i++) {
        if(tokens[i].type == CodeTokenType::TOKEN_TYPE_IDENTIFIER) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Identifier: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_NUMBER) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Number: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_OPERATOR_OR_DELIMITER) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Operator or Delimiter: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_STRING) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "String: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_RESERVE_WORD) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Reserve word: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_EOF) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "End of file.";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_COMMENT) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Comment: ";
        } else if(tokens[i].type == CodeTokenType::TOKEN_TYPE_NEWLINE) {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Newline  ";
        } else {
            std::cout << std::fixed << std::setw(25) << std::setfill(' ') << std::right << "Unknown token: ";
        }
        std::cout << " " << tokens[i].value << std::endl;
    }
    for (size_t i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].value;
    }

    return 0;
}