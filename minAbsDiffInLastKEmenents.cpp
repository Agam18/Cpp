#include <bits/stdc++.h>
using namespace std;

vector<int> minAbsDiffStream(vector<int>& nums, int k) {

    multiset<int> window;
    multiset<int> diffs;

    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        int x = nums[i];

        // Insert into window
        auto it = window.insert(x);

        // Check neighbors
        auto prevIt = (it == window.begin()) ? window.end() : prev(it);
        auto nextIt = next(it);

        // Remove old diff between prev and next
        if (prevIt != window.end() && nextIt != window.end()) {
            diffs.erase(diffs.find(abs(*nextIt - *prevIt)));
        }

        // Add new diffs
        if (prevIt != window.end()) {
            diffs.insert(abs(*it - *prevIt));
        }
        if (nextIt != window.end()) {
            diffs.insert(abs(*nextIt - *it));
        }

        // Maintain window size
        if (window.size() > k) {
            int removeVal = nums[i - k];

            auto itRem = window.find(removeVal);

            auto prevIt = (itRem == window.begin()) ? window.end() : prev(itRem);
            auto nextIt = next(itRem);

            // Remove diffs involving itRem
            if (prevIt != window.end()) {
                diffs.erase(diffs.find(abs(*itRem - *prevIt)));
            }
            if (nextIt != window.end()) {
                diffs.erase(diffs.find(abs(*nextIt - *itRem)));
            }

            // Add back diff between neighbors
            if (prevIt != window.end() && nextIt != window.end()) {
                diffs.insert(abs(*nextIt - *prevIt));
            }

            window.erase(itRem);
        }

        // Answer for this step
        if (window.size() < 2) result.push_back(0);
        else result.push_back(*diffs.begin());
    }

    return result;
}