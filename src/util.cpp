#include "util.h"

using namespace std;
double string_to_double(string& integral, string& fractional, int N)
{
    double val  = (double)stol(integral, nullptr);
    double frac = (double)stol(fractional, nullptr);
    while (N > 0)
    {
        frac /= 10;
        N--;
    }
    val += frac;
    return val;
}