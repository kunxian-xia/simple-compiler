#include "lexer.h"

typedef struct 
{
    Lexer lexer;
    Token* next;
    Token* current;
} Parser;
//parse and evaluate an arithmetic expression
double ParseAndEvaluate(char* sourceCode);