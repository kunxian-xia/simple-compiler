#include <string>

//token type definition
typedef enum {
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_EQUAL,
    TOKEN_ASSIGN,
    TOKEN_ADD,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DOT,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_NEWLINE,

    TOKEN_NUM,
    TOKEN_NAME,

    TOKEN_STRUCT,
    TOKEN_CLASS,
    TOKEN_NEW,
    TOKEN_INT8,
    TOKEN_INT16,
    TOKEN_INT32,
    TOKEN_INT64,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_CHAR,

    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_EOF
} TokenType;

//token definition
typedef struct
{
    TokenType type;
    std::string lexval;
    int length;
} Token;

typedef struct
{
    std::string identifier;
    int length;
    TokenType type;
} Keyword;

typedef struct 
{
    std::string source;
    unsigned int nextPos;
    unsigned int startPos;
} Lexer;

Token* NextToken(Lexer* lexer);