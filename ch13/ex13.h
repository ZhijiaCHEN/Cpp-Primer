#ifndef ex13_h
#define ex13_h

#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <exception>

using std::string; using std::vector;

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

unsigned int genSN()
{
    static unsigned int sn = 0;
    return ++sn;
}

class Numbered
{
public:
    Numbered():mysn(genSN()){}
    unsigned int mysn;
};

class Numbered_13_15
{
public:
    Numbered_13_15():mysn(genSN()){}
    Numbered_13_15(const Numbered_13_15& n):mysn(genSN()){}
    unsigned int mysn;
};

class Employee
{
public:
    Employee();
    Employee(const string &nm);
    Employee(const Employee &a) = delete;
    Employee& operator= (const Employee &rhs) = delete;
    string name;
    int ID;
private:
    static int idGen;

};

class ConstStrBlobPtr;

class StrBlob
{
public:
    using size_type = vector<string>::size_type;
    friend class ConstStrBlobPtr;

    ConstStrBlobPtr begin() const;
    ConstStrBlobPtr end() const;

    StrBlob():data(std::make_shared<vector<string>>()) {}
    StrBlob(std::initializer_list<string> il):data(std::make_shared<vector<string>>(il)){}
    StrBlob& operator=(const StrBlob& sb);

    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}

    void push_back(const string &t){data->push_back(t);}
    void pop_back()
    {
        check(0, "pop_back on empty StrBlob");
        return data->pop_back();
    }
    string &front()
    {
        check(0, "fron on empty StrBlob");
        return data->front();
    }
    string &back()
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    const string& back() const
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    const string& front() const
    {
        check(0, "fron on empty StrBlob");
        return data->front();
    }
private:
    std::shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const
    {
        if(i >= data->size()) throw std::out_of_range(msg);
    }
};
#endif