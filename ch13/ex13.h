#ifndef ex13_h
#define ex13_h

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <initializer_list>
#include <memory>
#include <exception>
#include <set>

using std::string;
using std::vector;

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr&, const HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) { }

    HasPtr& operator= (HasPtr rhs) 
    {
        swap(*this, rhs);
        return *this;
    }

    ~HasPtr () 
    {
        delete ps;
    };
private:
    std::string *ps;
    int i;
};
inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "call swap(HasPtr& lhs, HasPtr& rhs)" << std::endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    return lhs.ps->length() < rhs.ps->length();
}
class HasPtrActsPtr {
public:
    HasPtrActsPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0), use(new std::size_t(1)){}
    HasPtrActsPtr(const HasPtrActsPtr &p):
        ps(p.ps), i(p.i), use(p.use) {++*use;}
    HasPtrActsPtr& operator=(const HasPtrActsPtr &rhs)
    {
        ++*rhs.use;
        if (--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this;
    }
    ~HasPtrActsPtr()
    {
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
private:
    string *ps;
    int i;
    size_t *use;
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

class TreeNode
{
public:
    TreeNode(const string &s = string()): value(s), count(new int(1)), left(nullptr), right(nullptr){}
    TreeNode(const TreeNode &n): value(n.value), count(n.count), left(n.left), right(n.right)
    {
        ++*count;
    }
    TreeNode &operator=(const TreeNode &rhs)
    {
        ++*rhs.count;
        if(--*count == 0)
        {
            delete count;
            delete left;
            delete right;
        }
        value = rhs.value;
        left = rhs.left;
        right = rhs.right;
        count = rhs.count;
        return *this;
    }
    ~TreeNode()
    {
        if(--*count == 0)
        {
            delete left;
            delete right;
            delete count;
        }
    }
private:
    string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree
{
public:
    BinStrTree(const string &s = string()): root(new TreeNode(s)){}
    BinStrTree(const BinStrTree &bst): root(new TreeNode(*bst.root)){}
    BinStrTree &operator=(const BinStrTree &rhs)
    {
        TreeNode *new_root = new TreeNode(*rhs.root); 
        delete root;
        root = new_root;
        return *this;
    }
    ~BinStrTree()
    {
        delete root;
    }
private:
    TreeNode *root;
};


class Folder;

class Message
{
    friend class Folder;
private:
    string contents;
    std::set<Folder*> folders;
    void add_to_folders(const Message&);
    void remove_from_folder();
public:
    // folders is implicitly initialized to the empty set
    explicit Message(const string &str = ""): contents(str){}
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
};

void swap(Message &lhs, Message &rhs);
#endif