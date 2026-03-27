#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int func(int i,int j,string &s1,string&s2,vector<vector<int>>&dp){
    if(dp[i][j]!=-1) return dp[i][j];
    if(i==s1.size() || j==s2.size()) return dp[i][j]=0;
    int ans=0;
    if(s1[i]==s2[j]){
        return dp[i][j]=1+func(i+1,j+1,s1,s2,dp);
    }
    ans=max(ans,max(func(i+1,j,s1,s2,dp),func(i,j+1,s1,s2,dp)));
    return dp[i][j]=ans;

}
int main() {
    string s1,s2;
    cin>>s1>>s2;
    vector<vector<int>>dp(s1.size()+1,vector<int>(s2.size()+1,-1));
    int len=func(0,0,s1,s2,dp);
    vector<int>ind;
    int i=0,j=0;
    while (ind.size()<len) {
        if(s1[i]==s2[j]){
            ind.push_back(i);
            cout<<s1[i];
            i++;
            j++;
        } else{
            if(dp[i+1][j]>=dp[i][j+1]){
                cout<<"-"<<s1[i];
                i++;
            } else{
                cout<<"+"<<s2[j];
                j++;
            }
        }

    }
    while(i<s1.size()){
        cout<<"-"<<s1[i];
        i++;
    }
    while(j<s2.size()){
        cout<<"+"<<s2[j];
        j++;
    }

}