#include "ex13.h"
#include <stdio.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    HasPtr a("hello world");
    HasPtr b("foobar");
    b = a;
    return 0;
}

