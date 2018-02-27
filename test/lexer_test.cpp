#include "../lexer.h"
#include <iostream>

using namespace std;

int main()
{
    char* sourceCode = "1+1*3";
    Lexer* lexer = new Lexer();
    lexer->nextPos = 0;
    lexer->source = sourceCode;
    lexer->startPos = 0;

    while (1) 
    {
        Token* token = NextToken(lexer);
        if (token == NULL || token->type == TOKEN_EOF) break;

        if (token->type == TOKEN_DIGIT) 
        {
            cout << stoi(*token->lexval, nullptr) << endl;
        }
            
    }
}