#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include <string>
#include <stdio.h>
#include <fstream>
#include "../mystl/my_vector.h"

enum class CodeTokenType {
    TOKEN_TYPE_IDENTIFIER = 9999,
    TOKEN_TYPE_NUMBER = 10000,
    TOKEN_TYPE_STRING = 10001,
    TOKEN_TYPE_RESERVE_WORD,
    TOKEN_TYPE_OPERATOR_OR_DELIMITER,
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_UNDEFINED,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE,
    TOKEN_TYPE_SPACE
};

//用于将字符串和CodeTokenType互转的函数
std::string CodeTokenTypeToString(CodeTokenType type) {
    switch(type) {
        case CodeTokenType::TOKEN_TYPE_IDENTIFIER:
            return "TOKEN_TYPE_IDENTIFIER";
        case CodeTokenType::TOKEN_TYPE_NUMBER:
            return "TOKEN_TYPE_NUMBER";
        case CodeTokenType::TOKEN_TYPE_STRING:
            return "TOKEN_TYPE_STRING";
        case CodeTokenType::TOKEN_TYPE_RESERVE_WORD:
            return "TOKEN_TYPE_RESERVE_WORD";
        case CodeTokenType::TOKEN_TYPE_OPERATOR_OR_DELIMITER:
            return "TOKEN_TYPE_OPERATOR_OR_DELIMITER";
        case CodeTokenType::TOKEN_TYPE_EOF:
            return "TOKEN_TYPE_EOF";
        case CodeTokenType::TOKEN_TYPE_UNDEFINED:
            return "TOKEN_TYPE_UNDEFINED";
        case CodeTokenType::TOKEN_TYPE_COMMENT:
            return "TOKEN_TYPE_COMMENT";
        case CodeTokenType::TOKEN_TYPE_NEWLINE:
            return "TOKEN_TYPE_NEWLINE";
        case CodeTokenType::TOKEN_TYPE_SPACE:
            return "TOKEN_TYPE_SPACE";
        default:
            return "TOKEN_TYPE_UNDEFINED";
    }
}

CodeTokenType stringToCodeTokenType(std::string str) {
    if(str == "TOKEN_TYPE_IDENTIFIER") {
        return CodeTokenType::TOKEN_TYPE_IDENTIFIER;
    } else if(str == "TOKEN_TYPE_NUMBER") {
        return CodeTokenType::TOKEN_TYPE_NUMBER;
    } else if(str == "TOKEN_TYPE_STRING") {
        return CodeTokenType::TOKEN_TYPE_STRING;
    } else if(str == "TOKEN_TYPE_RESERVE_WORD") {
        return CodeTokenType::TOKEN_TYPE_RESERVE_WORD;
    } else if(str == "TOKEN_TYPE_OPERATOR_OR_DELIMITER") {
        return CodeTokenType::TOKEN_TYPE_OPERATOR_OR_DELIMITER;
    } else if(str == "TOKEN_TYPE_EOF") {
        return CodeTokenType::TOKEN_TYPE_EOF;
    } else if(str == "TOKEN_TYPE_UNDEFINED") {
        return CodeTokenType::TOKEN_TYPE_UNDEFINED;
    } else if(str == "TOKEN_TYPE_COMMENT") {
        return CodeTokenType::TOKEN_TYPE_COMMENT;
    } else if(str == "TOKEN_TYPE_NEWLINE") {
        return CodeTokenType::TOKEN_TYPE_NEWLINE;
    } else if(str == "TOKEN_TYPE_SPACE") {
        return CodeTokenType::TOKEN_TYPE_SPACE;
    } else {
        return CodeTokenType::TOKEN_TYPE_UNDEFINED;
    }
}

struct Token {
    std::string value;
    CodeTokenType type;

    Token() {}
    Token(std::string value, CodeTokenType type) {
        this->value = value;
        this->type = type;
    }
};

static const std::string operatorOrDelimiter[] = {"+", "-", "*", "/", "<", "=", ">", ";", "(", ")", "^", ",", "\'", "#", "&", "|", "%", "~", "[", "]", "{", "}", "\\", ".", "\?", ":", "!", "\"", 
    "<=", ">=", "==", "!=", "&&", "<<", ">>", "||", "++", "--", "+=", "-=", "*=", "/=", "%=", "|=", "&=", "^=", "<<=", ">>=", "::", "->"};

class LexicalAnalysis {
private:
    std::string ruleName;
    MyVector<std::string> reserveWord;
    std::string rawText, preprocessedText;
    MyVector<Token> tokens;
    std::string currentToken = "";
    int reserveWordCount, operatorAndDelimiterCount;
    int syn = -1;

    int searchReserveWord(std::string word) {
        for(size_t i = 0; i < reserveWord.size(); i++) {
            if (word == reserveWord[i]) {
                return i;
            }
        }
        return -1;
    }

    bool isLetter(char c) {
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
            return true;
        }
        return false;
    }

    bool isDigit(char c) {
        if(c >= '0' && c <= '9') {
            return true;
        }
        return false;
    }

    int isOperatorOrDelimiter(std::string str) {
        for(int i = 0; i < operatorAndDelimiterCount; i++) {
            if(str == operatorOrDelimiter[i]) {
                return i + reserveWordCount;
            }
        }
        return -1;
    }

    bool maybeOperatorOrDelimiterWith2Letters(char c) {
        for(int i = 0; i < operatorAndDelimiterCount; i++) {
            if(c == operatorOrDelimiter[i][0] && operatorOrDelimiter[i].size() > 1) {
                return true;
            }
        }
        return false;
    }
    
    void preprocess() {
        preprocessedText = rawText;
        return;
        preprocessedText = "";
        bool inString = false;
        for(int i = 0; i < rawText.size(); i++) {
            if(rawText[i] == '/') {
                if(i < rawText.size() - 1 && rawText[i + 1] == '/')
                    while(i < rawText.size() && rawText[i] != '\n') {
                        ++i;
                    }
            }
            if(rawText[i] == '/') {
                if(i < rawText.size() - 1 && rawText[i + 1] == '*') {
                    i += 2;
                    while(i < rawText.size() - 1 && !(rawText[i] == '*' && rawText[i + 1] == '/')) {
                        ++i;
                    }
                    i += 2;
                }
            }
            if(rawText[i] == '\"') {
                inString = !inString;
            }
            if(!inString && rawText[i] == '\n') {
                preprocessedText += ' ';
                continue;
            }
            if (rawText[i] != '\t' && rawText[i] != '\v' && rawText[i] != '\r') {
                preprocessedText += rawText[i];
            }
        }
    }

    void Scan(size_t & currentIndex) {
        currentToken = "";

        if(preprocessedText[currentIndex] == ' ' || preprocessedText[currentIndex] == '\n' || preprocessedText[currentIndex] == '\t') {
            while(preprocessedText[currentIndex] == ' ' || preprocessedText[currentIndex] == '\n' || preprocessedText[currentIndex] == '\t') {
                currentToken += preprocessedText[currentIndex++];
            }
            syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_SPACE);
            return;
        }
        
        // printf("current letter: [%d]%c\n", currentIndex, preprocessedText[currentIndex]);

        if(isLetter(preprocessedText[currentIndex])) {
            while(isLetter(preprocessedText[currentIndex]) || isDigit(preprocessedText[currentIndex])) {
                currentToken += preprocessedText[currentIndex++];
            }

            syn = searchReserveWord(currentToken);
            syn = syn == -1 ? static_cast<int>(CodeTokenType::TOKEN_TYPE_IDENTIFIER) : syn;
            
            return;
        } else if(isDigit(preprocessedText[currentIndex])) {
            while(isDigit(preprocessedText[currentIndex])) {
                currentToken += preprocessedText[currentIndex++];
            }

            syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_NUMBER);

            return;
        } else if((isOperatorOrDelimiter(std::string(1, preprocessedText[currentIndex])) != -1) && 
                    !maybeOperatorOrDelimiterWith2Letters(preprocessedText[currentIndex])) {
            if(preprocessedText[currentIndex] == '\"') {
                currentToken += preprocessedText[currentIndex++];
                while(preprocessedText[currentIndex] != '\"') {
                    currentToken += preprocessedText[currentIndex++];
                }
                currentToken += preprocessedText[currentIndex++];
                syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_STRING);
                return;
            }
            if(preprocessedText[currentIndex] == '\'') {
                currentToken += preprocessedText[currentIndex++];
                while(preprocessedText[currentIndex] != '\'') {
                    currentToken += preprocessedText[currentIndex++];
                }
                currentToken += preprocessedText[currentIndex++];
                syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_STRING);
                return;
            }
            currentToken += preprocessedText[currentIndex++];
            syn = isOperatorOrDelimiter(currentToken);
            return;
        } else if(maybeOperatorOrDelimiterWith2Letters(preprocessedText[currentIndex])) {
            if(currentIndex < preprocessedText.size() - 2) { // 优先匹配三个字母的符号
                currentToken += preprocessedText[currentIndex];
                currentToken += preprocessedText[currentIndex + 1];
                currentToken += preprocessedText[currentIndex + 2];
                syn = isOperatorOrDelimiter(currentToken);
                if(syn != -1) {
                    currentIndex += 3;
                    return;
                }
            }
            currentToken = "";
            if (currentIndex < preprocessedText.size() - 1) { // 其次匹配两个字母的符号
                currentToken += preprocessedText[currentIndex];
                currentToken += preprocessedText[currentIndex + 1];
                if(currentToken == "//") {
                    syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_COMMENT);
                    currentIndex += 2;
                    while(preprocessedText[currentIndex] != '\n' && currentIndex < preprocessedText.size()) {
                        currentToken += preprocessedText[currentIndex++];
                    }
                    return;
                }
                if(currentToken == "/*") {
                    syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_COMMENT);
                    currentIndex += 2;
                    while(currentIndex < rawText.size() - 1 && !(preprocessedText[currentIndex] == '*' && preprocessedText[currentIndex + 1] == '/')) {
                        currentToken += preprocessedText[currentIndex++];
                    }
                    currentToken += "/*";
                    currentIndex += 2;
                    return;
                }
                syn = isOperatorOrDelimiter(currentToken);
                if(syn != -1) {
                    currentIndex += 2;
                    return;
                }
            }
            currentToken = "";
            currentToken += preprocessedText[currentIndex];
            syn = isOperatorOrDelimiter(currentToken);
            if(syn != -1) {
                currentIndex += 1;
            }
            return;
        } else if (preprocessedText[currentIndex] == '\0' || currentIndex >= preprocessedText.size()) {
            syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_EOF);
            currentIndex++;
            return;
        } else if(preprocessedText[currentIndex] == '\n') {
            syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_NEWLINE);
            currentToken = "\n";
            currentIndex++;
            return;
        } else {
            syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_UNDEFINED);
            currentIndex++;
            return;
        }
    }

public:
    LexicalAnalysis(std::string ruleName) {
        this->ruleName = ruleName;
        std::ifstream file("../data/highlight/" + ruleName + "/keywords.txt"); // Just for unit test
        // std::ifstream file("./data/highlight/" + ruleName + "/keywords.txt");
        if (file.is_open()) {
            // printf("keywords file open\n");
            std::string line;
            while (std::getline(file, line)) {
                reserveWord.push_back(line);
            }
            file.close();
        }
        // printf("keywords size: %llu\n", reserveWord.size());
        // for(int i = 0; i < reserveWord.size(); i++) {
        //     printf("keywords[%d]: %s\n", i, reserveWord[i].c_str());
        // }
        reserveWordCount = reserveWord.size();
        operatorAndDelimiterCount = sizeof(operatorOrDelimiter) / sizeof(operatorOrDelimiter[0]);
    }

    void setRawText(std::string rawText) {
        this->rawText = rawText;
        preprocess();
        // printf("preprocessed text: %s\n", preprocessedText.c_str());
    }

    void printProcessedText() {
        printf("preprocessed text: %s\n", preprocessedText.c_str());
    }

    MyVector<Token> tokenize() {
        syn = -1;
        size_t currentIndex = 0;
        tokens.clear();
        while(syn != static_cast<int>(CodeTokenType::TOKEN_TYPE_EOF) && syn != static_cast<int>(CodeTokenType::TOKEN_TYPE_UNDEFINED)) {
            Scan(currentIndex);
            // printf("currentToken: [%s]\n", currentToken.c_str());
            if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_STRING)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_STRING));
                // printf("string: %s\n", currentToken.c_str());
            } else if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_IDENTIFIER)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_IDENTIFIER));
                // printf("identifier: %s\n", currentToken.c_str());
            } else if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_NUMBER)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_NUMBER));
                // printf("number: %s\n", currentToken.c_str());
            } else if(syn > 0 && syn < reserveWordCount) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_RESERVE_WORD));
                // printf("reserve word: %s\n", currentToken.c_str());
            } else if(syn >= reserveWordCount && syn < reserveWordCount + operatorAndDelimiterCount) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_OPERATOR_OR_DELIMITER));
                // printf("operator or delimiter: %s\n", currentToken.c_str());
            } else if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_COMMENT)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_COMMENT));
                // printf("comment: %s\n", currentToken.c_str());
            } else if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_EOF)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_EOF));
                // printf("EOF: %s\n", currentToken.c_str());
            } else if(syn == static_cast<int>(CodeTokenType::TOKEN_TYPE_NEWLINE)) {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_NEWLINE));
                // printf("newline: %s\n", currentToken.c_str());
            } else {
                tokens.push_back(Token(currentToken, CodeTokenType::TOKEN_TYPE_UNDEFINED));
                // printf("undefined: %s\n", currentToken.c_str());
            }
            if(currentIndex >= preprocessedText.length()) {
                syn = static_cast<int>(CodeTokenType::TOKEN_TYPE_EOF);
            }
        }
        return tokens;
    }
};

#endif // TOKENIZER_H 目前仅支持C/C++