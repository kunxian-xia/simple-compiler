#include "../lexer.h"
#include <iostream>

using namespace std;

int main()
{
    string sourceCode = "struct point { int8 x; int8 y; } ;";
    Lexer* lexer = new Lexer();
    lexer->nextPos = 0;
    lexer->source = sourceCode;
    lexer->startPos = 0;

    while (1) 
    {
        Token* token = NextToken(lexer);
        if (token == NULL || token->type == TOKEN_EOF) break;

        cout << token->type << "\t" << token->lexval << endl;
            
    }
}