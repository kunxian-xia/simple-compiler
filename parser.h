#include "lexer.h"
#include "ast.h"
typedef struct 
{
    Lexer lexer;
    Token* next;
    Token* current;
} Parser;
//parse and evaluate an arithmetic expression
double ParseAndEvaluate(std::string& sourceCode);
AST* Parse(std::string& sourceCode);