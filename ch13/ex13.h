#ifndef ex13_h
#define ex13_h

#include <string>

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
private:
    std::string *ps;
    int i;
};

#endif