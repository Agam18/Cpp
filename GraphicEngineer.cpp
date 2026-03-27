#include <bits/stdc++.h>
using namespace std;

int solve1D(vector<int>& moves) {
    int n = moves.size();
    vector<int> pref(n+1, 0);

    for (int i = 0; i < n; i++) {
        pref[i+1] = pref[i] + moves[i];
    }

    int mx = *max_element(pref.begin(), pref.end());
    int mn = *min_element(pref.begin(), pref.end());

    int firstMin = -1, lastMin = -1;
    int firstMax = -1, lastMax = -1;

    for (int i = 0; i <= n; i++) {
        if (pref[i] == mn) {
            if (firstMin == -1) firstMin = i;
            lastMin = i;
        }
        if (pref[i] == mx) {
            if (firstMax == -1) firstMax = i;
            lastMax = i;
        }
    }

    int span = mx - mn;

    if (lastMax < firstMin || lastMin < firstMax) {
        span--;
    }

    return span;
}

int main() {
    string s;
    cin >> s;

    vector<int> xMoves, yMoves;

    for (char c : s) {
        if (c == 'D') xMoves.push_back(1);
        if (c == 'A') xMoves.push_back(-1);
        if (c == 'W') yMoves.push_back(1);
        if (c == 'S') yMoves.push_back(-1);
    }

    int width = solve1D(xMoves);
    int height = solve1D(yMoves);

    // original spans
    int origWidth = solve1D(xMoves);   // without reduction logic you'd store separately
    int origHeight = solve1D(yMoves);

    cout << min(width * origHeight, origWidth * height) << endl;
}