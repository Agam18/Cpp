#include <bits/stdc++.h>
using namespace std;

/*
2. Shuffle the array (Fisher-Yates)

This is the most important part.

Algorithm:

For i = N-1 → 1:

Pick random index j from [0, i]
Swap arr[i] and arr[j]
*/
class RandomGenerator {
private:
    vector<int> arr;
    int n;
    int index;

    void shuffleArray() {
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(arr[i], arr[j]);
        }
    }

public:
    RandomGenerator(int N) {
        n = N;
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }
        index = 0;
        shuffleArray();
    }

    int getRandom() {
        if (index == n) {
            shuffleArray();
            index = 0;
        }
        return arr[index++];
    }
};