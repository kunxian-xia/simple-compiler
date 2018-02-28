#include "lexer.h"
#include <string>
#include <iostream>
using namespace std;

static char peek(Lexer* lexer)
{
    return lexer->source[lexer->nextPos];
}
static char forward(Lexer* lexer)
{
    char c = peek(lexer);
    lexer->nextPos += 1;
    return c;
}
static Token* makeToken(Lexer* lexer, TokenType type)
{
    Token* token = new Token();
    token->type = type;
    token->length = lexer->nextPos - lexer->startPos;
    token->lexval = new string(&(lexer->source[lexer->startPos]), token->length);
   
    return token;
}
static bool isDigit(char c) 
{
    return c >= '0' && c <= '9';
}

Token* NextToken(Lexer* lexer)
{
    while (peek(lexer) != '\0') 
    {
        lexer->startPos = lexer->nextPos;
        char c = forward(lexer);
        Token* token = NULL;
        
        switch (c) 
        {
            case '+':
                token = makeToken(lexer, TOKEN_ADD); break;
            case '-':
                token = makeToken(lexer, TOKEN_MINUS); break;
            case '*':
                token = makeToken(lexer, TOKEN_MUL); break;
            case '.':
                token = makeToken(lexer, TOKEN_DOT); break;
            case '(':
                token = makeToken(lexer, TOKEN_LEFT_PAREN); break;
            case ')':
                token = makeToken(lexer, TOKEN_RIGHT_PAREN); break;
            default:
                if (isDigit(c)) 
                {
                    while (isDigit(peek(lexer)))
                    {
                        forward(lexer);
                    }
                    token = makeToken(lexer, TOKEN_DIGIT);
                }
                break;
        }
        return token;
    }
    lexer->startPos = lexer->nextPos;
    return makeToken(lexer, TOKEN_EOF); 
}