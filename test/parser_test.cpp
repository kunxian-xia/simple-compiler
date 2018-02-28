#include "../parser.h"
#include <iostream>

using namespace std;

int main()
{
    char* code = "(1+1)*3*5-2";
    cout << ParseAndEvaluate(code) << endl;
}