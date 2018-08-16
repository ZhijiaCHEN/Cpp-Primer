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

void ex13_3()
{
    vector<HasPtr> v;
    v.push_back(HasPtr("ccc"));
    v.push_back(HasPtr("b"));
    v.push_back(HasPtr("ab"));
    v.push_back(HasPtr("ba"));
    std::sort(v.begin(), v.end());
    getchar();
}

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(f);
    f.remMsg(this);
}

void Message::add_to_folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

Message::Message(const Message &m): contents(m.contents), folderse(m.folders)
{
    add_to_folders(m);
}

void Message::remove_from_folders()
{
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message()
{
    remove_from_folders();
}

Message& Message::operator=(const Message &rhs)
{
    remove_from_folders():
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
    {
        f->remMsg(&lhs);
        f->addMsg(&rhs);
    }
        
    for (auto f : rhs.folders)
    {    
        f->remMsg(&rhs);
        f->addMsg(&lhs);
    }
    
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
}
int main(int argc, char const *argv[])
{
    ex13_3();
    getchar();
    return 0;
}

