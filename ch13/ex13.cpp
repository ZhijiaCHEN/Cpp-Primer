#include "ex13.h"
#include <stdio.h>
#include <iostream>
#include <vector>
using std::cout, std::endl;

void testX(X x1, const X &x2)
{
    X *xp = new X();
    std::vector<X> xv;
    xv.push_back(x1);
    xv.push_back(x2);
    xv.push_back(*xp);
    return;
}

void printSN(Numbered n)
{
    std::cout<<n.mysn<<std::endl;
}

void printSN_ref(const Numbered &n)
{
    std::cout<<n.mysn<<std::endl;
}

void printSN(Numbered_13_15 n)
{
    std::cout<<n.mysn<<std::endl;
}

void printSN_ref(const Numbered_13_15 &n)
{
    std::cout<<n.mysn<<std::endl;
}

void ex13_1_3()
{
    X *px = new X();
    X x = *px;
    x = *px;
    testX(*px, x);
    return;
}

void ex13_1_4()
{
    //13.14
    Numbered a, b=a, c=b;
    printSN(a);printSN(b);printSN(c);
    //13.15
    Numbered_13_15 d, e=d, f=e;
    printSN(d);printSN(e);printSN(f);
    //13.16
    printSN_ref(d);printSN_ref(e);printSN_ref(f);

}

int Employee::idGen = 0;
Employee::Employee()
{
    ID = ++idGen;
}

Employee::Employee(const string &nm)
{
    ID = ++idGen;
    name = nm;
}

StrBlob& StrBlob::operator=(const StrBlob &sb)
{
    data = std::make_shared<vector<string>>(*sb.data);
    return *this;
}

void ex13_1_6()
{
    Employee a, b("foobar");
    cout<<a.ID<<endl;
    cout<<b.ID<<endl;
}

void ex13_2_2()
{
    HasPtrActsPtr a("hello world");
    HasPtrActsPtr b(a);
    HasPtrActsPtr c;
    c = c;
    c = a;

    BinStrTree t1("hello world");
    BinStrTree t2("hello world2");
    t2 = t1;
    t1 = t1;
    return;
}

int main(int argc, char const *argv[])
{
    ex13_2_2();
    getchar();
    return 0;
}

