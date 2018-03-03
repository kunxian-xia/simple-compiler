#include "../parser.h"
#include <iostream>

using namespace std;

int main()
{
    string code1 = "(1+1)*3*5-2";
    string code2 = "2-5";
    string code3 = "1.1 * 3";
    double r1 = 28;
    double r2 = -3;
    double r3 = 3.3;

    if ((ParseAndEvaluate(code1) == r1)
        && (ParseAndEvaluate(code2) == r2))
    {
        cout << "test passed" << endl;
    }
    else 
    {
        cout << "test failed" << endl;
    }
    cout << ParseAndEvaluate(code1) << endl;
    cout << ParseAndEvaluate(code2) << endl;
    cout << ParseAndEvaluate(code3) << endl;
    /*
    string code = "struct point { int8 x; int8 y; } ;";
    Parse(code);
    */
}