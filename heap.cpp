#include <iostream>
#include <vector>
#include <climits>
#include <stdexcept>
using namespace std;

// ─────────────────────────────────────────
//  Max Heap
// ─────────────────────────────────────────
class MaxHeap {
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int l = left(i), r = right(i);
        int n = heap.size();

        if (l < n && heap[l] > heap[largest]) largest = l;
        if (r < n && heap[r] > heap[largest]) largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.empty()) throw underflow_error("Heap is empty");
        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return maxVal;
    }

    int getMax() {
        if (heap.empty()) throw underflow_error("Heap is empty");
        return heap[0];
    }

    void deleteAt(int i) {
        heap[i] = INT_MAX;
        heapifyUp(i);
        extractMax();
    }

    bool isEmpty() { return heap.empty(); }
    int  size()    { return heap.size(); }

    void print() {
        cout << "Heap: ";
        for (int x : heap) cout << x << " ";
        cout << "\n";
    }
};

// ─────────────────────────────────────────
//  Min Heap
// ─────────────────────────────────────────
class MinHeap {
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i), r = right(i);
        int n = heap.size();

        if (l < n && heap[l] < heap[smallest]) smallest = l;
        if (r < n && heap[r] < heap[smallest]) smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMin() {
        if (heap.empty()) throw underflow_error("Heap is empty");
        int minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return minVal;
    }

    int getMin()   { return heap.empty() ? throw underflow_error("Empty") : heap[0]; }
    bool isEmpty() { return heap.empty(); }
    int  size()    { return heap.size(); }

    void print() {
        cout << "MinHeap: ";
        for (int x : heap) cout << x << " ";
        cout << "\n";
    }
};

// ─────────────────────────────────────────
//  Priority Queue  (wraps MinHeap with priority)
// ─────────────────────────────────────────
struct PQItem {
    int priority;
    string value;
    bool operator>(const PQItem& o) const { return priority > o.priority; }
};

class PriorityQueue {
    vector<PQItem> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)].priority > heap[i].priority) {
            swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i), r = right(i);
        int n = heap.size();

        if (l < n && heap[l].priority < heap[smallest].priority) smallest = l;
        if (r < n && heap[r].priority < heap[smallest].priority) smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void push(int priority, string value) {
        heap.push_back({priority, value});
        heapifyUp(heap.size() - 1);
    }

    PQItem pop() {
        if (heap.empty()) throw underflow_error("PQ is empty");
        PQItem top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return top;
    }

    PQItem top()   { return heap[0]; }
    bool isEmpty() { return heap.empty(); }
    int  size()    { return heap.size(); }
};

// Heap sort using MaxHeap logic in-place
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        int largest = i;
        while (true) {
            int l = 2 * largest + 1, r = 2 * largest + 2, next = largest;
            if (l < n && arr[l] > arr[next]) next = l;
            if (r < n && arr[r] > arr[next]) next = r;
            if (next == largest) break;
            swap(arr[largest], arr[next]);
            largest = next;
        }
    }

    // extract one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        int j = 0, size = i;
        while (true) {
            int l = 2 * j + 1, r = 2 * j + 2, next = j;
            if (l < size && arr[l] > arr[next]) next = l;
            if (r < size && arr[r] > arr[next]) next = r;
            if (next == j) break;
            swap(arr[j], arr[next]);
            j = next;
        }
    }
}

int main() {
    cout << "=== Max Heap ===\n";
    MaxHeap mh;
    for (int v : {15, 10, 20, 8, 25, 5})
        mh.insert(v);
    mh.print();
    cout << "Max: " << mh.getMax() << "\n";
    cout << "ExtractMax: " << mh.extractMax() << "\n";
    mh.print();

    cout << "\n=== Min Heap ===\n";
    MinHeap minh;
    for (int v : {15, 10, 20, 8, 25, 5})
        minh.insert(v);
    minh.print();
    cout << "ExtractMin: " << minh.extractMin() << "\n";
    minh.print();

    cout << "\n=== Priority Queue ===\n";
    PriorityQueue pq;
    pq.push(3, "Low task");
    pq.push(1, "Critical task");
    pq.push(2, "Medium task");

    while (!pq.isEmpty()) {
        auto item = pq.pop();
        cout << "Priority " << item.priority << ": " << item.value << "\n";
    }

    cout << "\n=== Heap Sort ===\n";
    vector<int> arr = {64, 25, 12, 22, 11};
    heapSort(arr);
    cout << "Sorted: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    return 0;
}
