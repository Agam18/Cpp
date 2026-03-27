#include <bits/stdc++.h>
using namespace std;


/*
https://leetcode.com/discuss/post/2209740/rubrik-interview-question-by-anonymous_u-ivoz/
Suppose we have a tree. The special property about this tree is that it's properly numbered but in a unique fashion. The root of the tree has number 1 associated with it followed by 2 children which are numbered 2 and 3 respectively. Then 2 has 3 children namely 4, 5, 6. Number 3 also has 3 children namely 7, 8, 9. The on next level containing 4, 5, 6, 7, 8, 9, everyone has 2 children. So basically the number of children keep on alternating according to the parity of each level. If the level is odd then all the numbers will have 2 children otherwise 3 children. You will be given a number n <= 10^18 and you have to print its entire path from root to the number itself.

Example test cases:

Suppose n=2, so path will be 1, 2

Suppose n=6, so path will be 1, 2, 6

Suppose n=16, so path will be 1, 3, 7, 16

Can someone help with this question?*/
int main() {
    long long n;
    cin >> n;

    vector<long long> levelStart, levelEnd;

    long long nodes = 1;
    long long start = 1;

    int level = 1;

    // Step 1: Build levels
    while (start <= n) {
        long long end = start + nodes - 1;

        levelStart.push_back(start);
        levelEnd.push_back(end);

        // decide children count
        if (level % 2 == 1) nodes *= 2;
        else nodes *= 3;

        start = end + 1;
        level++;
    }

    // Step 2: Find level of n
    int L = 0;
    for (int i = 0; i < levelStart.size(); i++) {
        if (levelStart[i] <= n && n <= levelEnd[i]) {
            L = i;
            break;
        }
    }

    vector<long long> path;

    long long curr = n;

    while (true) {
        path.push_back(curr);

        if (curr == 1) break;

        long long startL = levelStart[L];
        long long idx = curr - startL;

        int parentLevel = L - 1;

        long long parentStart = levelStart[parentLevel];

        // children count depends on parent level
        int children = ((parentLevel + 1) % 2 == 1) ? 2 : 3;

        long long parentIdx = idx / children;

        curr = parentStart + parentIdx;

        L = parentLevel;
    }

    reverse(path.begin(), path.end());

    for (auto x : path) cout << x << " ";
}