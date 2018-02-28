#include "parser.h"
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

static double expression(Parser* parser);
/*
 * the grammar for arithmetic expression is 
 *  expression -> expression + term
 *  expression -> expression - term
 *  expression -> term
 *  term       -> term * factor
 *  term       -> factor
 *  factor     -> ( expression )
 *  factor     -> digit | digit . digit
 * 
 * To eliminate left recursion, the above grammar is turned into
 *  
 *   E   ->  T E'
 *   E'  ->  + T E' | - T E' | \epsilon
 *   T   ->  F T' 
 *   T'  ->  * F T' | / F T' | \epsilon
 *   F   ->  ( E )  | digit  | digit . digit
 *   
 */
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

static double factor(Parser* parser)
{
    if (match(parser, TOKEN_LEFT_PAREN))
    {
        double expr = expression(parser);
        if(match(parser, TOKEN_RIGHT_PAREN)) 
        {
            return expr;
        }
        else 
        {
            //report error
            assert(0);
        }     
    } 
    else if (match(parser, TOKEN_DIGIT)) 
    {
        double val = (double) stoi(*(parser->current->lexval), nullptr);
        if (match(parser, TOKEN_DOT))
        {
            // F -> digit . digit
            if (match(parser, TOKEN_DIGIT)) 
            {
                double fractional = (double) stoi(*(parser->current->lexval), nullptr);
                int numofdigits = parser->current->length;
                while (numofdigits > 0) 
                {
                    fractional /= 10;
                    numofdigits--;
                }
                val += fractional;
                return val;
            } else {
                //report error
                assert(0);
            }
        } 
        else 
        {
            // F -> digit 
            return val;
        }
    }
    else 
    {
        assert(0);
    }
}
static double term_prime(Parser* parser)
{
    if (match(parser, TOKEN_MUL))
    {
        double f = factor(parser);
        double tp = term_prime(parser);
        return f*tp;
    } 
    else 
    {
        //report error
        return 1;
    }
}
static double term(Parser* parser)
{
    double f = factor(parser);
    double tp = term_prime(parser);
    return f*tp; 
}
static double expression_prime(Parser* parser, double ep)
{
    if (match(parser, TOKEN_ADD))
    {
        double t = term(parser);
        return expression_prime(parser, ep + t);
    }
    else if (match(parser, TOKEN_MINUS))
    {
        double t = term(parser);
        return expression_prime(parser, ep - t);
    }
    else
    {
        return ep;
    }
}
static double expression(Parser* parser)
{
    double t = term(parser);
    return expression_prime(parser, t);
}

double ParseAndEvaluate(char* sourceCode)
{
    Parser parser;
    parser.lexer.source = sourceCode;
    parser.lexer.nextPos = 0;
    parser.lexer.startPos = 0;
    parser.next = NULL;
    parser.current = NULL;

    forward(&parser);
    double expr = expression(&parser);
    if (!match(&parser, TOKEN_EOF))
        assert(0);
    return expr;
}