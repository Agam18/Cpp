#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Node{
   Node* chars[26];
   set<int> charRemaining;
public:
   
   bool containsChar(char c){
     return chars[c-'a']!=NULL;
   }
   
   void put(char c, Node* node){
    chars[c-'a']=node;
   }
   
   Node* get(char c){
    return chars[c-'a'];
   }
   
   void addCharRemaining(int c){
    charRemaining.insert(c);
   }
   
   bool isCharRemaining(int c){
    return charRemaining.find(c)!=charRemaining.end();
   }
};

class Trie{
    Node* root;
public:
    Trie(){
        root = new Node();
    }
    
    void insert(string s){
        Node* node = root;
        for(int i=0;i<s.size();i++){
            if(!node->containsChar(s[i])){
                node->put(s[i],new Node());
            }
            node=node->get(s[i]);
            node->addCharRemaining(s.size()-i-1);
        }
    }
    
    bool performQuery(string s){
        Node* node = root;
        node->addCharRemaining(s.size());
        int j=-1;
        for(int i=0;i<s.size();i++){
            if(s[i]-'a'>25 || s[i]-'a'<0){
                j=i;
                break;
            }
            if(!node->containsChar(s[i])){
                return false;
            }
            node=node->get(s[i]);
        }
        if(j==-1) return false;
        int c=s[j]-'0';
        return node->isCharRemaining(c);
    }
    
    
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}