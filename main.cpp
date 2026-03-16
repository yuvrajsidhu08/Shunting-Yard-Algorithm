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

void enqueue(Node*& f, Node*& r, Node* n){
    if(!r) f=r=n;
    else{
        r->next=n;
        r=n;
    }
}

Node* dequeue(Node*& f, Node*& r){
    if(!f) return NULL;
    Node* t=f;
    f=f->next;
    if(!f) r=NULL;
    t->next=NULL;
    return t;
}

bool op(char* t){
    return !strcmp(t,"+")||!strcmp(t,"-")||!strcmp(t,"*")||!strcmp(t,"/")||!strcmp(t,"^");
}

int prec(char* o){
    if(!strcmp(o,"^")) return 3;
    if(!strcmp(o,"*")||!strcmp(o,"/")) return 2;
    if(!strcmp(o,"+")||!strcmp(o,"-")) return 1;
    return 0;
}

void shunt(char in[], Node*& f, Node*& r){
    Node* stack=NULL;
    char* t=strtok(in," ");

    while(t){
        if(isdigit(t[0])) enqueue(f,r,new Node(t));

        else if(op(t)){
            while(stack && op(peek(stack)->val) && prec(peek(stack)->val)>=prec(t))
                enqueue(f,r,pop(stack));
            push(stack,new Node(t));
        }

        else if(!strcmp(t,"(")) push(stack,new Node(t));

        else if(!strcmp(t,")")){
            while(stack && strcmp(peek(stack)->val,"("))
                enqueue(f,r,pop(stack));
            pop(stack);
        }

        t=strtok(NULL," ");
    }

    while(stack) enqueue(f,r,pop(stack));
}
