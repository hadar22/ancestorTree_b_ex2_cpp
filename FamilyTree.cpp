#include "FamilyTree.hpp"
#include <iostream>
#include <stdexcept>

#define SPACE 5

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
    if (findNode(root, child) != nullptr){
        if (findNode(root, child)->getFather() == nullptr){
            Node *nFather = new Node(father);
            nFather->setCount(findNode(root, child)->getCount() + 1);
            nFather->setRelation(kind);
            findNode(root, child)->setFather(nFather);
            return *this;
        }
        else{
            throw runtime_error("The father already exists");
        }
    }else{
        throw runtime_error("The child does not exist");
    }

   
}

Tree &Tree::addMother(string child, string mother){
    char kind = 'w';
    if (findNode(root, child) != nullptr){
        if (findNode(root, child)->getMother() == nullptr){
            Node *nMother = new Node(mother);
            nMother->setCount(findNode(root, child)->getCount() + 1);
            nMother->setRelation(kind);
            findNode(root, child)->setMother(nMother);
            return *this;
        }
        else{
            throw runtime_error("The mother already exists");
        }
    }else{
        throw runtime_error("The child does not exist");
    }
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


void print2DUtil(Node *root, int space)  {   
    if (root == NULL)  
        return;  
   
    space += SPACE;  
  
    
    print2DUtil(root->getFather(), space);  
   
    cout<<endl;  
    for (int i = SPACE; i < space; i++)  
        cout<<" ";  
    cout<<root->getMyName()<<"\n";  
  
    print2DUtil(root->getMother(), space);  
}  
    
void Tree:: display()  
{  
    
    print2DUtil(root, 0);  
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
