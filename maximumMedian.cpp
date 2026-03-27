#include <bits/stdc++.h>
using namespace std;

bool isPossible(int mid, vector<int>& a, int n, int k) {
    vector<int> pre(n);

    for (int i = 0; i < n; i++) {
        pre[i] = (a[i] >= mid ? 1 : -1);
    }

    for (int i = 1; i < n; i++) {
        pre[i] += pre[i - 1];
    }

    int minPref = 0;

    for (int i = k - 1; i < n; i++) {

        if (i - k >= 0)
            minPref = min(minPref, pre[i - k]);

        if (pre[i] - minPref > 0)
            return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 1, r = *max_element(a.begin(), a.end());
    int ans = 1;

    while (l <= r) {
        int mid = (l + r) / 2;

        if (isPossible(mid, a, n, k)) {
            ans = mid;
            l = mid + 1;  // try bigger
        } else {
            r = mid - 1;
        }
    }

    cout << ans << "\n";
}