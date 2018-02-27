#include <string>

//token type definition
typedef enum {
    TOKEN_ADD,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DOT,
    TOKEN_DIGIT,

    TOKEN_EOF
} TokenType;

//token definition

typedef struct
{
    TokenType type;
    std::string* lexval;
    int length;
} Token;

typedef struct 
{
    char* source;
    unsigned int nextPos;
    unsigned int startPos;
} Lexer;

Token* NextToken(Lexer* lexer);