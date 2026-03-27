#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SGT{
public:
    
    vector<int>seg;
    SGT(int n){
        seg.resize(4*n+1);
    }
    
    void build(int i,int low,int high,vector<int>&a){
        if(low==high){
            seg[i]=a[low];
            return;
        }
        int mid=(low+high)/2;
        build(2*i+1,low,mid,a);
        build(2*i+2,mid+1,high,a);
        seg[i]=min(seg[2*i+1],seg[2*i+2]);
    }
    
    int query(int i,int low,int high,int l,int r){
        if(r<low || l>high) return INT_MAX;
        if(l<=low && r>=high) return seg[i];
        int mid=(low+high)/2;
        int left = query(2*i+1,low,mid,l,r);
        int right = query(2*i+2,mid+1,high,l,r);
        return min(left,right);
    }
    
    void update(int ind,int low, int high,int i, int val){
        if(low==high){
            seg[ind]=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid) update(2*ind+1,low,mid,i,val);
        else update(2*ind+2,mid+1,high,i,val);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
};
int main() {
    int n,q;
    cin>>n>>q;
    SGT seg(n);
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    seg.build(0,0,n-1,a);
    while(q--){
        int b,c,d;
        cin>>b>>c>>d;
        if(b==1){
            seg.update(0,0,n-1,c-1,d);
        }else{
            cout<<seg.query(0,0,n-1,c-1,d-1)<<endl;
        }
    }
	return 0;
}
