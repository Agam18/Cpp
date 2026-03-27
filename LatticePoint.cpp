#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/discuss/post/1737556/rubrik-oa-lattice-circles-by-anonymous_u-bqvx/
    Function: countLatticePoints
    --------------------------------
    Returns the total number of integer lattice points covered
    by at least one circle.

    Idea:
    - Fix x-coordinate
    - For each circle, compute valid y-interval at that x
    - Merge intervals to avoid double counting
    - Sum all integer points
*/

long long countLatticePoints(const vector<vector<int>>& circles) {

    // Map: x-coordinate → list of y-intervals covered at this x
    unordered_map<int, vector<pair<int,int>>> xToYIntervals;

    // Step 1: Build intervals for each x
    for (const auto &circle : circles) {
        int centerX = circle[0];
        int centerY = circle[1];
        int radius  = circle[2];

        // Iterate over all x where this circle exists
        for (int x = centerX - radius; x <= centerX + radius; ++x) {

            int dx = x - centerX;

            // Compute remaining value inside sqrt
            long long remaining = 1LL * radius * radius - 1LL * dx * dx;

            // If negative → no valid y exists
            if (remaining < 0) continue;

            // Max vertical reach at this x
            int dy = (int) sqrtl(remaining);

            // Valid y interval
            int yStart = centerY - dy;
            int yEnd   = centerY + dy;

            xToYIntervals[x].push_back({yStart, yEnd});
        }
    }

    long long totalPoints = 0;

    // Step 2: Process each x independently
    for (auto &entry : xToYIntervals) {

        auto &intervals = entry.second;

        // Sort intervals based on starting y
        sort(intervals.begin(), intervals.end());

        // Step 3: Merge overlapping intervals
        int currentStart = intervals[0].first;
        int currentEnd   = intervals[0].second;

        for (int i = 1; i < intervals.size(); i++) {
            int nextStart = intervals[i].first;
            int nextEnd   = intervals[i].second;

            // If overlapping or touching → merge
            if (nextStart <= currentEnd + 1) {
                currentEnd = max(currentEnd, nextEnd);
            }
            else {
                // Add number of integer points in current interval
                totalPoints += (currentEnd - currentStart + 1);

                // Start new interval
                currentStart = nextStart;
                currentEnd   = nextEnd;
            }
        }

        // Add last interval
        totalPoints += (currentEnd - currentStart + 1);
    }

    return totalPoints;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> circles(n, vector<int>(3));

    for (int i = 0; i < n; i++) {
        cin >> circles[i][0] >> circles[i][1] >> circles[i][2];
    }

    cout << countLatticePoints(circles) << endl;

    return 0;
}