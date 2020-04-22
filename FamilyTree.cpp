#include "FamilyTree.hpp"
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

string Node::getMyName(){

    return _myName;
}
void Node::setCount(int count){

    _count = count;
}
int Node::getCount(){

    return _count;
}

string Node::getRelation(){

    return _myRelation;
}

void Node::setRelation(char kind){
    string ans = "";
    if (kind == 'm'){

        ans = "father";
    }
    else if (kind == 'w'){

        ans = "mother";
    }
    if (this->getCount() == 1){

        _myRelation = ans;
    }
    else if (this->getCount() == 2){

        _myRelation = "grand" + ans;
    }
    else{

        ans= "grand" + ans;

          int sumOfGreat=this->getCount() - 2;

             string ansWithGreat = ans;

             for (int i=0; i < sumOfGreat ; i++){

                 ansWithGreat="great-"+ansWithGreat;
             }
             _myRelation=ansWithGreat;
    }
}
Node ::Node (string name) :
 _myName(name), _father(nullptr), _mother(nullptr), _count(0), _myRelation("me"){};

Tree::Tree(string name){

    root = new Node(name);
   
}
Tree &Tree::addFather(string child, string father){
    
    char gender = 'm';
    Node *fNode = findNode(root, child);

    if (fNode == nullptr){
        throw runtime_error("The child is not exists");
    }
    else if (fNode->getFather() != nullptr) {
        throw runtime_error("The father already exists");
    }
    Node *nFather = new Node(father);
    nFather->setCount(fNode->getCount() + 1);
    nFather->setRelation(gender);
    fNode->setFather(nFather);
    return *this;
}

Tree &Tree::addMother(string child, string mother){
    
    char gender = 'w';
    Node *fNode = findNode(root, child);

    if (fNode == nullptr){
        throw runtime_error("The child is not exists");
    }
    else if (fNode->getMother() != nullptr){
        throw runtime_error("The nother already exists");
    }
    Node *nMother = new Node(mother);
    nMother->setCount(fNode->getCount() + 1);
    nMother->setRelation(gender);
    fNode->setMother(nMother);
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
    
    Node *ans = findNode(root, name);
    if (ans != nullptr) return ans->getRelation();
    return "unrelated";

   
}
string Tree::find(string relation){
    Node *ans = findRelation(root, relation);
    
    if (ans != nullptr) return ans->getMyName();
    else
        throw runtime_error("not found");
    
    
}

Node *Tree::findRelation(Node *root, string relation){
    if (root == nullptr) return nullptr;

    if (root->getRelation() == relation)
        return root;
    
    Node* father=findRelation(root->getFather(), relation);
   

    if (father != nullptr) return father;

    return findRelation(root->getMother(), relation);
}


void Tree::display(Node *node){
    if (node == nullptr) return;

    cout << node->getMyName() <<"|"<< node->getRelation() <<"-------------";
    display(node->getFather());
    display(node->getMother());
}
void Tree::display(){
    
    display(root);
    cout << endl;
}


void Tree:: remove(string name){
    Node* node=findNode(root,name);
    if(node==nullptr){
        throw runtime_error("The person not exists");
    }
    if(root->getMyName()==name){
        throw runtime_error("Cannot remove");
    }
    if(node->getFather() != nullptr && node->getFather()->getMyName()==name){
        if(node->getFather()==nullptr) return;
        remove(node->getFather()->getMyName());
        remove(node->getMother()->getMyName());
        //delete node;
        node->setFather(nullptr);

    }
    if(node->getMother() != nullptr && node->getMother()->getMyName()==name){
        if(node->getMother()==nullptr) return;
        remove(node->getFather()->getMyName());
        remove(node->getMother()->getMyName());
        //delete node;
        node->setMother(nullptr);

    }
    delete node;
}
