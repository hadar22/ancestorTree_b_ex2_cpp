#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace family
{
class Node
{

private:
    string _myName;
    Node *_father;
    Node *_mother;
    int _count;
    string _myRelation;
    char _kind;

public:
    Node(string name); 
    void setFather(Node *father);
    void setMother(Node *mother);
    void setCount(int count);
    void setRelation(char kind);
    string getRelation();
    string getMyName();
    Node *getFather();
    Node *getMother();
    int getCount();
    //char getKind();
    //void setKind(char v);
};

class Tree
{
private:
    Node *root;

public:
    Tree(string name);
    Node *findNode(Node *root, string child);
    Node *findRelation(Node *root, string relation);
    Tree &addFather(string child, string father);
    Tree &addMother(string child, string mother);
    string relation(string name);
    string find(string relation);
    void display();
    void display(Node *r);
    void remove(string name);
    
};
};