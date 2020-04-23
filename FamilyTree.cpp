#include "FamilyTree.hpp"
#include <iostream>
#include <stdexcept>

using namespace family;

void Node::setFather(Node *father){
    _father = father;
}
Node *Node::getFather(){
    return _father;
}
void Node::setMother(Node *mother){
    _mother = mother;
}

Node *Node::getMother(){
    return _mother;
}
void Node::setCount(int count){
    _count = count;
}
int Node::getCount(){
    return _count;
}
string Node::getMyName(){
    return _myName;
}
string Node::getRelation(){
    return _myRelation;
}
void Node::setRelation(char kind){
    string ans= "";
    if (kind == 'm'){
        ans= "father";
    }
    else if (kind == 'w'){
        ans = "mother";
    }
    if (getCount() == 1){
        _myRelation= ans;
    }
    else if (getCount() == 2){
        _myRelation= "grand" + ans;
    }
    else{
           ans= "grand" + ans;
           int sumOfGreat=getCount() - 2;
           string ansWithGreat = ans;
           for (int i=0; i < sumOfGreat ; i++){
                ansWithGreat="great-"+ansWithGreat;
                 ans="great-"+ans;
             }
             _myRelation=ans;
    }
}
Tree::Tree(string name){
    root = new Node(name);
   
}
Node::Node(string name) : 
_myName(name),_father(nullptr), _mother(nullptr), _count(0), _myRelation("me"){};

Tree &Tree::addFather(string child, string father){

    char kind = 'm';

    if (findNode(root, child) == nullptr){
        throw runtime_error("The child does not exist");
    }
    else if (findNode(root, child)->getFather() != nullptr){
        throw runtime_error("The father already exists");
    }
    Node *new_father = new Node(father);
    new_father->setCount(findNode(root, child)->getCount() + 1);
    new_father->setRelation(kind);
    findNode(root, child)->setFather(new_father);
    return *this;
}

Tree &Tree::addMother(string child, string mother){
    char kind = 'w';

    if (findNode(root, child)== nullptr){
        throw runtime_error("The child does not exist");
    }
    else if (findNode(root, child)->getMother() != nullptr){
        throw runtime_error("The mother already exists");
    }
    Node *new_mother = new Node(mother);
    new_mother->setCount(findNode(root, child)->getCount() + 1);
    new_mother->setRelation(kind);
    findNode(root, child)->setMother(new_mother);
    return *this;
}

Node *Tree::findNode(Node *root, string child){
     if (root == nullptr) return nullptr;

    if (root->getMyName() == child)return root;

    Node* father= findNode(root->getFather(), child);

    if (father!= nullptr) return father;
    
    return findNode(root->getMother(), child);
}


string Tree::relation(string name){

  
    if (findNode(root, name) == nullptr){
        return "unrelated";
    }
    else {
        return findNode(root, name)->getRelation();
    }
}
string Tree::find(string relation){

    if (findRelation(root, relation) == nullptr) {
        throw runtime_error(" not found");
    }
    else{
        return findRelation(root, relation)->getMyName();
    }
}

Node *Tree::findRelation(Node *root, string relation){
    if (root == nullptr) return nullptr;

    if (root->getRelation() == relation)
        return root;
    
    Node* father=findRelation(root->getFather(), relation);
   

    if (father != nullptr) return father;

    return findRelation(root->getMother(), relation);
}

void Tree::display(Node *r)
{
    if (r == nullptr)
        return;
    cout << r->getMyName() <<"|"<<r->getRelation() <<",";
    display(r->getFather());
    display(r->getMother());
}
void Tree::display()
{
    display(root);
    cout << endl;
}


void Tree:: remove(string name){
   
     if(!findNode(root,name)){
          throw runtime_error("The person not exists");
     }
   
    if(root->getMyName()==name){
        throw runtime_error("Cannot remove");
    }
    if(root->getFather() != nullptr && root->getFather()->getMyName()==name){
        
            freeTree(root->getFather());
        root->setFather(nullptr);
        
        

    }
    if(root->getMother() !=nullptr && root->getMother()->getMyName()==name){
        
            freeTree(root->getFather());
            root->setMother(nullptr);
        }
    
  
    
}
    void Tree:: freeTree(Node* node){
    if(node->getFather()) freeTree(node->getFather());
        
    if(node->getMother()) freeTree(node->getMother()); 
        
    if(node->getFather()==nullptr && node->getMother()==nullptr)
        delete(node);



}
