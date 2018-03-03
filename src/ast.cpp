#include "ast.h"
#include <cassert>

double Eval(AST* tree)
{
    int i; double ret;
    vector<double> intermediates = vector<double>(tree->numofchildren);
    for (i=0; i < tree->numofchildren; i++) {
        intermediates[i] = Eval(tree->children[i]);
    }
    switch (tree->op) {
        case OP_ADD:
            for (ret=0, i = 0; i < tree->numofchildren; i++)
                ret += intermediates[i];
            break;
        case OP_MUL:
            for (ret=1, i =0; i < tree->numofchildren; i++)
                ret *= intermediates[i];
            break;
        case OP_MINUS:
            assert(tree->numofchildren == 2);
            ret = intermediates[0] - intermediates[1];
            break;
        case OP_NUL:
            ret = tree->val;
            break;
        default:
            assert(0);
    }
    return ret;
}