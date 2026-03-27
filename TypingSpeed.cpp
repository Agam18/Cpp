#include <bits/stdc++.h>
using namespace std;

/*
Idea:

Compress typing speeds to indices.

Maintain a Fenwick Tree storing frequency of speeds seen so far.

When a new speed x arrives:

Query how many speeds ≤ x exist.

Rank = count of speeds > x + 1.

Time complexity per arrival:
O(log N)


However for dynamic values AVL is better :

        values arrive online and range is unknown

| Method                   | Time     | Needs preprocessing? | Handles dynamic values? |
| ------------------------ | -------- | -------------------- | ----------------------- |
| Fenwick Tree             | O(log N) | Yes (compression)    | No                      |
| AVL Order Statistic Tree | O(log N) | No                   | Yes                     |

*/

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) {
        this->n = n;
        bit.resize(n+1,0);
    }

    void update(int i,int val){
        for(;i<=n;i+=i&-i)
            bit[i]+=val;
    }

    int query(int i){
        int s=0;
        for(;i>0;i-=i&-i)
            s+=bit[i];
        return s;
    }
};

int main(){

    vector<int> speeds = {50,40,60,55};

    vector<int> comp = speeds;
    sort(comp.begin(),comp.end());
    comp.erase(unique(comp.begin(),comp.end()),comp.end());

    Fenwick ft(comp.size());

    for(int s : speeds){

        int idx = lower_bound(comp.begin(),comp.end(),s)-comp.begin()+1;

        int smaller_or_equal = ft.query(idx);
        int total = ft.query(comp.size());

        int rank = total - smaller_or_equal + 1;

        cout<<"Speed "<<s<<" Rank "<<rank<<"\n";

        ft.update(idx,1);
    }
}