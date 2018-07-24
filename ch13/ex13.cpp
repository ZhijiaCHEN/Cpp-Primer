#include "ex13.h"
#include <stdio.h>
#include <iostream>
#include <vector>

void testX(X x1, const X &x2)
{
    X *xp = new X();
    std::vector<X> xv;
    xv.push_back(x1);
    xv.push_back(x2);
    xv.push_back(*xp);
    return;
}
int main(int argc, char const *argv[])
{
    X *px = new X();
    X x = *px;
    x = *px;
    testX(*px, x);
    return 0;
}

