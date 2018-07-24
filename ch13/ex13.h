#ifndef ex13_h
#define ex13_h

#include <string>
#include <iostream>
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) { }

    HasPtr& operator= (const HasPtr &rhs) 
    {
        if(this != &rhs)
        {
            std::string *temp_ps = new std::string(*rhs.ps);
            delete ps;//prevent memory leak
            ps = temp_ps;
            i = rhs.i;
        }
        return *this;
    }

    ~HasPtr () 
    {
        std::cout<<"object destroyed."<<std::endl;
        getchar();
    };
private:
    std::string *ps;
    int i;
};

struct X
{
public:
    X() 
    {
        std::cout << "X()" << std::endl;
    }
    X(const X&)
    {
        std::cout << "X(const X&)" << std::endl;
    }
    X& operator= (const X &rhs)
    {
        std::cout << "X& operator= (const X &rhs)" << std::endl;
        return *this;
    }
    ~X()
    {
        std::cout << "~X()" << std::endl;
    }
};

#endif