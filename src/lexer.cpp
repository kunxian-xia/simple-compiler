#include "lexer.h"
#include <iostream>
using namespace std;

static Keyword keywords[] = 
{
    {"new", 3, TOKEN_NEW}, 
    {"struct", 6, TOKEN_STRUCT},
    {"class", 5, TOKEN_CLASS},
    {"int8", 4, TOKEN_INT8},
    {"int16", 5, TOKEN_INT16},
    {"int32", 5, TOKEN_INT32},
    {"int64", 5, TOKEN_INT64},
    {"for", 3, TOKEN_FOR}
};
static int numofkeywords = 8;

static char peek(Lexer* lexer)
{
    if (lexer->nextPos == lexer->source.size())
        return '\0';
    else 
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
    token->lexval = lexer->source.substr(lexer->startPos, token->length);
   
    return token;
}
static bool isDigit(char c) 
{
    return c >= '0' && c <= '9';
}
static bool isSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

static bool isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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
            case ';':
                token = makeToken(lexer, TOKEN_SEMICOLON); break;
            case ',':
                token = makeToken(lexer, TOKEN_COMMA); break;
            case '{':
                token = makeToken(lexer, TOKEN_LEFT_BRACE); break;
            case '}':
                token = makeToken(lexer, TOKEN_RIGHT_BRACE); break;
            default:
                if (isDigit(c)) 
                {
                    while (isDigit(peek(lexer)))
                    {
                        forward(lexer);
                    }
                    token = makeToken(lexer, TOKEN_NUM);
                    break;
                }
                if (isSpace(c))
                {
                    while (isSpace(peek(lexer)))
                    {
                        forward(lexer);
                    }
                    continue;
                }             
                if (isLetter(c))
                {
                    while (isLetter(peek(lexer)) || 
                            isDigit(peek(lexer)) || c == '_')
                    {
                        forward(lexer);
                    }
                    token = makeToken(lexer, TOKEN_NAME);

                    int i = 0; 
                    for (; i < numofkeywords; i++)
                    {
                        if ((token->length == keywords[i].length) &&
                            token->lexval.compare(keywords[i].identifier) == 0)
                        {
                            token->type = keywords[i].type;
                        }
                    }
                    break;
                }
        }
        return token;
    }
    lexer->startPos = lexer->nextPos;
    return makeToken(lexer, TOKEN_EOF); 
}