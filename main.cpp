#include <iostream>
#include <cstring>
using namespace std;

// Node used for stack, queue, and expression tree
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

// Push onto stack
void push(Node*& top, Node* n){
    n->next=top;
    top=n;
}

// Pop from stack
Node* pop(Node*& top){
    if(!top) return NULL;
    Node* t=top;
    top=top->next;
    t->next=NULL;
    return t;
}

// Peek top of stack
Node* peek(Node* top){
    return top;
}

// Add to queue
void enqueue(Node*& f, Node*& r, Node* n){
    if(!r) f=r=n;
    else{
        r->next=n;
        r=n;
    }
}

// Remove from queue
Node* dequeue(Node*& f, Node*& r){
    if(!f) return NULL;
    Node* t=f;
    f=f->next;
    if(!f) r=NULL;
    t->next=NULL;
    return t;
}

// Check if token is operator
bool op(char* t){
    return !strcmp(t,"+")||!strcmp(t,"-")||!strcmp(t,"*")||!strcmp(t,"/")||!strcmp(t,"^");
}

// Operator precedence
int prec(char* o){
    if(!strcmp(o,"^")) return 3;
    if(!strcmp(o,"*")||!strcmp(o,"/")) return 2;
    if(!strcmp(o,"+")||!strcmp(o,"-")) return 1;
    return 0;
}

// Convert infix to postfix using Shunting Yard
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

// Build expression tree from postfix
Node* build(Node*& f, Node*& r){
    Node* s=NULL;
    Node* t;

    while((t=dequeue(f,r))){
        if(op(t->val)){
            Node* a=pop(s);
            Node* b=pop(s);
            t->right=a;
            t->left=b;
        }
        push(s,t);
    }

    return pop(s);
}

// Print prefix (root left right)
void pre(Node* n){
    if(!n) return;
    cout<<n->val<<" ";
    pre(n->left);
    pre(n->right);
}

// Print infix (left root right)
void in(Node* n){
    if(!n) return;
    if(op(n->val)) cout<<"( ";
    in(n->left);
    cout<<n->val<<" ";
    in(n->right);
    if(op(n->val)) cout<<") ";
}

// Print postfix (left right root)
void post(Node* n){
    if(!n) return;
    post(n->left);
    post(n->right);
    cout<<n->val<<" ";
}

int main(){
    char input[200];

    cout<<"Enter expression: ";
    cin.getline(input,200);

    Node* f=NULL;
    Node* r=NULL;

    shunt(input,f,r);

    cout<<"Postfix: ";
    for(Node* t=f;t;t=t->next) cout<<t->val<<" ";
    cout<<endl;

    Node* root=build(f,r);

    cout<<"Prefix: ";
    pre(root);
    cout<<endl;

    cout<<"Infix: ";
    in(root);
    cout<<endl;

    cout<<"Postfix: ";
    post(root);
    cout<<endl;
}
