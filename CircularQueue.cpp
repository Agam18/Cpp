#include <bits/stdc++.h>
using namespace std;

class CircularQueue {
    vector<int> arr;
    int front, rear, size, capacity;

public:
    CircularQueue(int n) {
        capacity = n;
        arr.resize(n);
        front = 0;
        rear = 0;
        size = 0;
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        arr[rear] = x;
        rear = (rear + 1) % capacity;
        size++;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    int getFront() {
        if (isEmpty()) return -1;
        return arr[front];
    }
};