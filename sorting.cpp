#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printArr(const vector<int>& arr, const string& label = "") {
    if (!label.empty()) cout << label << ": ";
    for (int x : arr) cout << x << " ";
    cout << "\n";
}

// ─────────────────────────────────────────
//  Bubble Sort  O(n²)
// ─────────────────────────────────────────
void bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // already sorted
    }
    printArr(arr, "Bubble Sort");
}

// ─────────────────────────────────────────
//  Selection Sort  O(n²)
// ─────────────────────────────────────────
void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
    printArr(arr, "Selection Sort");
}

// ─────────────────────────────────────────
//  Insertion Sort  O(n²) / O(n) best
// ─────────────────────────────────────────
void insertionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    printArr(arr, "Insertion Sort");
}

// ─────────────────────────────────────────
//  Merge Sort  O(n log n)
// ─────────────────────────────────────────
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < (int)left.size() && j < (int)right.size())
        arr[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];

    while (i < (int)left.size())  arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSortHelper(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortHelper(arr, l, m);
    mergeSortHelper(arr, m + 1, r);
    merge(arr, l, m, r);
}

void mergeSort(vector<int> arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
    printArr(arr, "Merge Sort");
}

// ─────────────────────────────────────────
//  Quick Sort  O(n log n) avg / O(n²) worst
// ─────────────────────────────────────────
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int pi = partition(arr, low, high);
    quickSortHelper(arr, low, pi - 1);
    quickSortHelper(arr, pi + 1, high);
}

void quickSort(vector<int> arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
    printArr(arr, "Quick Sort");
}

// ─────────────────────────────────────────
//  Counting Sort  O(n + k)
// ─────────────────────────────────────────
void countingSort(vector<int> arr) {
    if (arr.empty()) return;
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0);
    for (int x : arr) count[x]++;

    int idx = 0;
    for (int i = 0; i <= maxVal; i++)
        while (count[i]-- > 0)
            arr[idx++] = i;

    printArr(arr, "Counting Sort");
}

// ─────────────────────────────────────────
//  Shell Sort  O(n log² n)
// ─────────────────────────────────────────
void shellSort(vector<int> arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
    printArr(arr, "Shell Sort");
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11, 90, 3, 47};
    printArr(arr, "Original");
    cout << "\n";

    bubbleSort(arr);
    selectionSort(arr);
    insertionSort(arr);
    mergeSort(arr);
    quickSort(arr);
    countingSort(arr);
    shellSort(arr);

    return 0;
}
