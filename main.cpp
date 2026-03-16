#include <iostream>
#include <cstring>
using namespace std;

class Node{
public:
    char val[10];
    Node* left;
    Node* right;
    Node* next;

    Node(const char* v){
        strcpy(val,v);
        left=NULL;
        right=NULL;
        next=NULL;
    }
};

void push(Node*& top, Node* n){
    n->next=top;
    top=n;
}

Node* pop(Node*& top){
    if(!top) return NULL;
    Node* t=top;
    top=top->next;
    t->next=NULL;
    return t;
}

Node* peek(Node* top){
    return top;
}
