#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// ─────────────────────────────────────────
//  Linear Search  O(n)
// ─────────────────────────────────────────
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++)
        if (arr[i] == target) return i;
    return -1;
}

// ─────────────────────────────────────────
//  Binary Search  O(log n)  — array must be sorted
// ─────────────────────────────────────────
int binarySearch(const vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int binarySearchRecursive(const vector<int>& arr, int lo, int hi, int target) {
    if (lo > hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binarySearchRecursive(arr, mid + 1, hi, target);
    return binarySearchRecursive(arr, lo, mid - 1, target);
}

// ─────────────────────────────────────────
//  Jump Search  O(√n)  — sorted array
// ─────────────────────────────────────────
int jumpSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    for (int i = prev; i < min(step, n); i++)
        if (arr[i] == target) return i;

    return -1;
}

// ─────────────────────────────────────────
//  Interpolation Search  O(log log n) avg  — sorted uniform data
// ─────────────────────────────────────────
int interpolationSearch(const vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;
    while (lo <= hi && target >= arr[lo] && target <= arr[hi]) {
        if (lo == hi) {
            if (arr[lo] == target) return lo;
            return -1;
        }
        int pos = lo + ((double)(hi - lo) / (arr[hi] - arr[lo])) * (target - arr[lo]);
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) lo = pos + 1;
        else hi = pos - 1;
    }
    return -1;
}

// ─────────────────────────────────────────
//  Exponential Search  O(log n)  — sorted array, good for unbounded
// ─────────────────────────────────────────
int exponentialSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    if (arr[0] == target) return 0;

    int bound = 1;
    while (bound < n && arr[bound] <= target)
        bound *= 2;

    return binarySearchRecursive(arr, bound / 2, min(bound, n - 1), target);
}

// ─────────────────────────────────────────
//  Ternary Search  O(log₃ n)  — sorted array
// ─────────────────────────────────────────
int ternarySearch(const vector<int>& arr, int lo, int hi, int target) {
    if (lo > hi) return -1;

    int m1 = lo + (hi - lo) / 3;
    int m2 = hi - (hi - lo) / 3;

    if (arr[m1] == target) return m1;
    if (arr[m2] == target) return m2;

    if (target < arr[m1])  return ternarySearch(arr, lo, m1 - 1, target);
    if (target > arr[m2])  return ternarySearch(arr, m2 + 1, hi, target);
    return ternarySearch(arr, m1 + 1, m2 - 1, target);
}

// ─────────────────────────────────────────
//  Find first & last occurrence (Binary Search variant)
// ─────────────────────────────────────────
int firstOccurrence(const vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1, result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) { result = mid; hi = mid - 1; }
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return result;
}

int lastOccurrence(const vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1, result = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) { result = mid; lo = mid + 1; }
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return result;
}

void printResult(const string& name, int idx, int target) {
    if (idx == -1)
        cout << name << ": " << target << " not found\n";
    else
        cout << name << ": found " << target << " at index " << idx << "\n";
}

int main() {
    vector<int> unsorted = {64, 25, 12, 22, 11, 90, 3, 47};
    vector<int> sorted   = {3, 11, 12, 22, 25, 47, 64, 90};
    vector<int> dupes    = {1, 2, 2, 2, 3, 4, 5};

    int target = 22;

    cout << "=== Searching for " << target << " ===\n\n";

    printResult("Linear Search (unsorted)", linearSearch(unsorted, target), target);
    printResult("Binary Search (sorted)",   binarySearch(sorted, target),   target);
    printResult("Binary Search Recursive",  binarySearchRecursive(sorted, 0, sorted.size()-1, target), target);
    printResult("Jump Search",              jumpSearch(sorted, target),              target);
    printResult("Interpolation Search",     interpolationSearch(sorted, target),     target);
    printResult("Exponential Search",       exponentialSearch(sorted, target),       target);
    printResult("Ternary Search",           ternarySearch(sorted, 0, sorted.size()-1, target), target);

    cout << "\n=== First & Last Occurrence (target = 2 in {1,2,2,2,3,4,5}) ===\n";
    cout << "First: index " << firstOccurrence(dupes, 2) << "\n";
    cout << "Last:  index " << lastOccurrence(dupes, 2)  << "\n";

    cout << "\n=== Searching for 99 (not in array) ===\n";
    printResult("Binary Search", binarySearch(sorted, 99), 99);
    printResult("Linear Search", linearSearch(sorted, 99), 99);

    return 0;
}
