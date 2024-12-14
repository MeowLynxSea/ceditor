#ifndef SYNTAX_HIGHLIGHTER_H
#define SYNTAX_HIGHLIGHTER_H

#include "Color.h"
#include "RichText.h"
#include <string>
#include "../mystl/my_vector.h"
#include <fstream>
#include "LexicalAnalysis.h"

struct HighlightRule {
    CodeTokenType type;
    MColor color;
};

class SyntaxHighlighter {
private:
    std::string ruleName;
    MyVector<HighlightRule> rules;

public:
    SyntaxHighlighter(std::string ruleName) {
        this->ruleName = ruleName;
        std::ifstream file("../data/highlight/" + ruleName + "/rules.txt"); // Just for unit test
        // std::ifstream file("./data/highlight/" + ruleName + "/keywords.txt");
        if (file.is_open()) {
            // printf("keywords file open\n");
            std::string line;
            while (std::getline(file, line)) {
                //every line is like "ruleName(string):color(short)"
                CodeTokenType type = stringToCodeTokenType(line.substr(0, line.find(":")));
                MColor color = static_cast<MColor>(std::stoi(line.substr(line.find(":") + 1)));
                rules.push_back(HighlightRule{type, color});
            }
            file.close();
        }
    }

    RichText highlight(std::string text) {
        LexicalAnalysis lexicalAnalysis(this->ruleName);
        lexicalAnalysis.setRawText(text);
        MyVector<Token> tokens = lexicalAnalysis.tokenize();
        RichText richText;
        for (int i = 0; i < tokens.size(); i++) {
            Token token = tokens[i];
            bool hasMatched = false;
            for (int j = 0; j < rules.size(); j++) {
                HighlightRule rule = rules[j];
                if (token.type == rule.type) {
                    hasMatched = true;
                    richText += RichText(token.value, rule.color);
                }
            }
            if (!hasMatched) {
                richText += RichText(token.value, COLOR_WHITE);
            }
        }
        return richText;
    }
};

#endif // SYNTAX_HIGHLIGHTER_H