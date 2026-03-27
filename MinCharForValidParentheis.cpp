#include <bits/stdc++.h>
using namespace std;
/*
Time	O(2^(N+k))
Space	O(N + result size)
*/
void dfs(string &s, int index,
         int openNeeded, int closeNeeded,
         int balance,
         string curr,
         unordered_set<string> &result) {

    // invalid case
    if (balance < 0) return;

    // end of string
    if (index == s.size()) {

        // add remaining brackets if possible
        if (openNeeded == 0 && closeNeeded == 0 && balance == 0) {
            result.insert(curr);
        }
        return;
    }

    char c = s[index];

    // case 1: normal character
    if (c != '(' && c != ')') {
        dfs(s, index + 1, openNeeded, closeNeeded, balance, curr + c, result);
        return;
    }

    // case 2: try inserting '(' if needed
    if (closeNeeded > 0) {
        dfs(s, index, openNeeded, closeNeeded - 1, balance + 1, curr + '(', result);
    }

    // case 3: try inserting ')'
    if (openNeeded > 0 && balance > 0) {
        dfs(s, index, openNeeded - 1, closeNeeded, balance - 1, curr + ')', result);
    }

    // case 4: use current character
    if (c == '(') {
        dfs(s, index + 1, openNeeded, closeNeeded, balance + 1, curr + c, result);
    } else {
        dfs(s, index + 1, openNeeded, closeNeeded, balance - 1, curr + c, result);
    }
}

vector<string> makeValid(string s) {
    int openNeeded = 0, closeNeeded = 0;

    // Step 1: compute needed brackets
    for (char c : s) {
        if (c == '(') {
            openNeeded++;
        } else if (c == ')') {
            if (openNeeded > 0) openNeeded--;
            else closeNeeded++;
        }
    }

    unordered_set<string> result;

    dfs(s, 0, openNeeded, closeNeeded, 0, "", result);

    return vector<string>(result.begin(), result.end());
}