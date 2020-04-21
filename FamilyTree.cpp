#include "FamilyTree.hpp"
#include <iostream>


using namespace family;
    Node* Node:: getFather(){
        return this->_father;
    }
    void Node:: setFather(Node* father){
        this->_father=father;
    }
    Node* Node:: getMother(){
        return this->_mother;
    }
    void Node:: setMother(Node* mother){
        this->_mother=mother;
    } 
    string Node:: getMyName(){
        return this->_myName;
    }
    void Node:: setRelation(char kind){
         string ans="";
         if (kind=='m'){
             ans="father";
         }
         else if(kind=='w'){
             ans="mother";
         }
         if(this->getCount()==1){
             this->_myRelation=ans;
         }
         else if(this->getCount()==2){
             this->_myRelation="grand"+ans;
         }
         else{
             int sumOfGreat=this->getCount() - 2;
             string ansWithGreat=ans;
             for (int i=0; i<sumOfGreat;i++){
                 ansWithGreat="great-"+ansWithGreat;
             }
             this->_myRelation=ansWithGreat;

         }
    }
    string Node:: getRelation(){
        return this->_myRelation;
    }
    void Node:: setKind(char kind){
        this->_kind=kind;
    }
    char Node:: getKind(){
        return this->_kind;
    }
    void Node:: setCount (int count){
        this->_count=count;
    }
    int Node:: getCount(){
        return this->_count;
    }

    Tree::Tree(string name){
       root= new Node(name);
    };
       Tree& Tree:: addFather (string child,string father){
           char kind='m';
           Node *fatherOfChild=getNode(root,child);
           if (fatherOfChild==nullptr){
               throw runtime_error ("The child is not exists");
           }
           else if (fatherOfChild->getFather()!=nullptr){
               throw runtime_error ("The father already exists");
           }
        
                    Node* nFather=new Node(father);
                    nFather->setKind(kind);
                    nFather->setRelation(kind);
                    nFather->setCount(root->getCount()+1);
                    fatherOfChild->setFather(nFather);

                    return *this;
        }
        Tree& Tree:: addMother (string child,string mother){
            char kind='w';
            if(root->getMyName()==child){
                if(root->getMother()==nullptr){
                    Node* nMother=new Node(mother);
                    nMother->setKind(kind);
                    nMother->setRelation(kind);
                    nMother->setCount(root->getCount()+1);
                    root->setMother(nMother);
                    return *this;

                }
                else{
                    throw runtime_error ("The mother already exists");
                }
            }
            else{
                    throw runtime_error ("The child is not exists");
                }
        }
        
        string Tree:: relation (string name){
            Node *ans=getNode(root,name);
            if (ans != nullptr) return ans->getRelation();
            else return "unrelated";

        }
        Node *Tree:: getNode(Node *ptr, string name){
            if(ptr== nullptr) return nullptr;
            if (ptr->getMyName()==name) return ptr;
            if (ptr->getFather()!= nullptr){
                Node *ans=getNode(ptr->getFather(),name);
                if(ans!= nullptr) return ans;
            } 
            if (ptr->getMother()!= nullptr){
                Node *ans=getNode(ptr->getMother(),name);
                if(ans!= nullptr) return ans;
            }
        }
        string Tree:: find (string name){
           Node *ans=recRelation(root,name);
           if(ans==nullptr){
               throw runtime_error("not found");
           }
           else{
               return ans->getMyName();
           }
        }
        Node *Tree:: recRelation(Node *ptr, string rel){
            if (ptr== nullptr) return nullptr;
            if (ptr->getRelation()==rel) return ptr;
            if (ptr->getFather()!= nullptr){
                Node *ans=recRelation(ptr->getFather(),rel);
                if(ans!= nullptr) return ans;
            } 
            if (ptr->getMother()!= nullptr){
                Node *ans=recRelation(ptr->getMother(),rel);
                if(ans!= nullptr) return ans;
            }
        }
        void Tree:: display(){}
        void Tree:: remove (string name){}