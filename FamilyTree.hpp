//FamilyTree.hpp
#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>

using namespace std;

namespace family{
    class Node{
    private:

        string _myName;
        Node* _father;
        Node* _mother;
        string _myRelation;
        char _kind;// u/w/m
        int _count;

    public:
    Node(string myname)
    :_myName(myname),_father(nullptr),_mother(nullptr),_myRelation("me"),_kind('u'),_count(0)
    {};
    Node* getFather();
    void setFather(Node* father);
    Node* getMother();
    void setMother(Node* mother);  
    string getMyName();
    void setRelation(char kind);
    string getRelation();
    void setKind(char kind);
    char getKind();
    void setCount (int count);
    int getCount();
     

    };
    class Tree{
        private:
          Node* root;
        public:
        Tree(string name);
        Tree& addFather (string child,string father);
        Tree& addMother (string child,string mother);
        string relation (string name);
        string find (string name);
        void display();
        void display(Node* child);
        void remove (string name);
        Node *getNode(Node *ptr, string name);
        Node *recRelation(Node *ptr, string rel);
    };
};






