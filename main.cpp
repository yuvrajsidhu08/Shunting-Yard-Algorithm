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
