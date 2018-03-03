#include "parser.h"
#include "ast.h"
#include "util.h"
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

static TokenType peek(Parser* parser)
{
    return parser->next->type;
}
static void forward(Parser* parser)
{
    parser->current = parser->next;
    parser->next = NextToken(&(parser->lexer));
}
static bool match(Parser* parser, TokenType expected)
{
    if (peek(parser) != expected) return false;

    forward(parser);
    return true;
}
/*
 * grammar for variable declaration:
 *   declaration -> type NAME ; declaration | \epsilon
 *   type        -> array_type | struct_type
 *   array_type  -> basic_type array_def 
 *   basic_type  -> INT8 | INT16 | INT32 | INT64 | FLOAT | DOUBLE
 *   array_def   -> [ NUM ] array_def | \epsilon
 *   struct_type -> STRUCT NAME
 * 
 * grammar for struct definition:
 *   struct      -> STRUCT NAME { declaration } ;
 */
static void declaration(Parser* parser);

static void struct_type(Parser* parser)
{
    if (match(parser, TOKEN_STRUCT) && match(parser, TOKEN_NAME)) {

    } 
    else {
        //report error
        assert(0);
    }
}

static void array_def(Parser* parser)
{
    if (match(parser, TOKEN_LEFT_BRACKET) &&
        match(parser, TOKEN_NUM) && match(parser, TOKEN_RIGHT_BRACKET))
    {
        array_def(parser);
    }
}
static bool type(Parser* parser)
{
    TokenType t = peek(parser);
    cout << parser->next->type << "\t" << parser->next->lexval << endl;
    switch (t)
    {
        case TOKEN_INT8:
        case TOKEN_INT16:
        case TOKEN_INT32:
        case TOKEN_INT64:
        case TOKEN_FLOAT:
        case TOKEN_DOUBLE:
            forward(parser);
            array_def(parser);
            break;
        case TOKEN_STRUCT:
            struct_type(parser);
            break;
        default:
            //move back
            return false;
    }
    return true;
}

static void declaration(Parser* parser)
{
    if (type(parser)) {
        if (match(parser, TOKEN_NAME) && match(parser, TOKEN_SEMICOLON)) {
            declaration(parser);
        } else {
            assert(0);
        }
    } else {
        return ;        
    }
}

void struct_def(Parser* parser)
{
    if (match(parser, TOKEN_STRUCT) && match(parser, TOKEN_NAME)
        && match(parser, TOKEN_LEFT_BRACE) )
    {
        declaration(parser);
        if (match(parser, TOKEN_RIGHT_BRACE)) {
            //push it into symbol table
        } else {
            assert(0);
        }
    }
    else 
    {
        assert(0);
    }
}

static AST* expression(Parser* parser);
/*
 * the grammar for arithmetic expression is 
 *  expression -> expression + term
 *  expression -> expression - term
 *  expression -> term
 *  term       -> term * factor
 *  term       -> factor
 *  factor     -> ( expression )
 *  factor     -> NUM | NUM . NUM
 * 
 * To eliminate left recursion, the above grammar is turned into
 *  
 *   E   ->  T E'
 *   E'  ->  + T E' | - T E' | \epsilon
 *   T   ->  F T' 
 *   T'  ->  * F T' | / F T' | \epsilon
 *   F   ->  ( E )  | NUM  | NUM . NUM
 *   
 */

static AST* factor(Parser* parser)
{
    AST* ast = new AST();
    if (match(parser, TOKEN_LEFT_PAREN)) {
         ast = expression(parser);
        if(match(parser, TOKEN_RIGHT_PAREN)) {
            return ast;
        } else {
            //report error
            assert(0);
        }     
    } else if (match(parser, TOKEN_NUM)) {
        double val;
        string integral = parser->current->lexval;
        if (match(parser, TOKEN_DOT)) {
            // F -> NUM . NUM
            if (match(parser, TOKEN_NUM)) {
                string fractional = parser->current->lexval;
                int N = parser->current->length;
                val = string_to_double(integral, fractional, N);

                ast->numofchildren = 0;
                ast->children = vector<AST*>();
                ast->op = OP_NUL; //a leaf node
                ast->val = val;
                return ast;
            } 
            else {
                //report error
                assert(0);
                return ast;
            }
        } 
        else {
            // F -> NUM 
            val = stod(integral, nullptr);
            ast->numofchildren = 0;
            ast->children = vector<AST*>();
            ast->op = OP_NUL;
            ast->val = val;
            return ast;
        }
    } 
    else {
        assert(0);
        return ast;
    }
}
static AST* term_prime(Parser* parser, AST* inh)
{
    AST* ast = new AST();
    if (match(parser, TOKEN_MUL)) {
        AST* f = factor(parser);
        ast->children = vector<AST*>(2);
        ast->children[0] = inh;
        ast->children[1] = f;
        ast->numofchildren = 2;
        ast->op = OP_MUL;
        return term_prime(parser, ast);
    } 
    else {
        return inh;
    }
}
static AST* term(Parser* parser)
{
    AST* f = factor(parser);
    return term_prime(parser, f);
}
static AST* expression_prime(Parser* parser, AST* inh)
{
    AST* ast = new AST();
    if (match(parser, TOKEN_ADD)) {
        AST* t = term(parser);
        ast->children = vector<AST*>(2);
        ast->children[0] = inh;
        ast->children[1] = t;
        ast->numofchildren = 2;
        ast->op = OP_ADD;
        return expression_prime(parser, ast);
    }
    else if (match(parser, TOKEN_MINUS)) {
        AST* t = term(parser);
        ast->children = vector<AST*>(2);
        ast->children[0] = inh;
        ast->children[1] = t;
        ast->numofchildren = 2;
        ast->op = OP_MINUS;
        return expression_prime(parser, ast);
    } 
    else {
        return inh;
    }
}
static AST* expression(Parser* parser)
{
    AST* t = term(parser);
    return expression_prime(parser, t);
}

AST* Parse(string& sourceCode)
{
    Parser parser;
    parser.lexer.source = sourceCode;
    parser.lexer.nextPos = 0;
    parser.lexer.startPos = 0;
    parser.next = NULL;
    parser.current = NULL;

    forward(&parser);
    //struct_def(&parser);
    return expression(&parser);
}

double ParseAndEvaluate(string& sourceCode)
{
    AST* ast = Parse(sourceCode);
    cout << "root node has " << ast->numofchildren << " children" << endl;
    return Eval(ast);
}
