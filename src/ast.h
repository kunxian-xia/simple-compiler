#ifndef AST_H
#define AST_H
#include <vector>
using namespace std;

typedef enum
{
    STRUCT_DEF, 
    
    //arithmetic operators
    OP_ADD,
    OP_MINUS,
    OP_MUL,
    
    // logical operators

    //
    OP_NUL
} OperatorType;

struct AST
{
    vector<AST*> children;
    int numofchildren;
    OperatorType op;

    double val;
};
typedef struct AST AST;

double Eval(AST* tree);
#endif