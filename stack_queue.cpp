#include <iostream>
#include <stdexcept>
using namespace std;

// ─────────────────────────────────────────
//  Stack  (array-based)
// ─────────────────────────────────────────
class Stack {
    int* arr;
    int top;
    int capacity;

public:
    Stack(int cap = 100) : top(-1), capacity(cap) {
        arr = new int[cap];
    }

    ~Stack() { delete[] arr; }

    void push(int val) {
        if (top == capacity - 1)
            throw overflow_error("Stack overflow");
        arr[++top] = val;
    }

    int pop() {
        if (isEmpty())
            throw underflow_error("Stack underflow");
        return arr[top--];
    }

    int peek() {
        if (isEmpty())
            throw underflow_error("Stack is empty");
        return arr[top];
    }

    bool isEmpty() { return top == -1; }
    int  size()    { return top + 1; }

    void print() {
        cout << "Stack (top -> bottom): ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << "\n";
    }
};

// ─────────────────────────────────────────
//  Stack  (linked list-based)
// ─────────────────────────────────────────
struct SNode {
    int data;
    SNode* next;
    SNode(int val) : data(val), next(nullptr) {}
};

class LinkedStack {
    SNode* top;
    int sz;

public:
    LinkedStack() : top(nullptr), sz(0) {}

    ~LinkedStack() {
        while (top) {
            SNode* tmp = top->next;
            delete top;
            top = tmp;
        }
    }

    void push(int val) {
        SNode* node = new SNode(val);
        node->next = top;
        top = node;
        sz++;
    }

    int pop() {
        if (!top) throw underflow_error("Stack underflow");
        int val = top->data;
        SNode* tmp = top;
        top = top->next;
        delete tmp;
        sz--;
        return val;
    }

    int peek()     { return top ? top->data : throw underflow_error("Empty"); }
    bool isEmpty() { return top == nullptr; }
    int  size()    { return sz; }
};

// ─────────────────────────────────────────
//  Queue  (circular array-based)
// ─────────────────────────────────────────
class Queue {
    int* arr;
    int front, rear, sz, capacity;

public:
    Queue(int cap = 100) : front(0), rear(0), sz(0), capacity(cap) {
        arr = new int[cap];
    }

    ~Queue() { delete[] arr; }

    void enqueue(int val) {
        if (sz == capacity)
            throw overflow_error("Queue is full");
        arr[rear] = val;
        rear = (rear + 1) % capacity;
        sz++;
    }

    int dequeue() {
        if (isEmpty())
            throw underflow_error("Queue is empty");
        int val = arr[front];
        front = (front + 1) % capacity;
        sz--;
        return val;
    }

    int peek()     { return arr[front]; }
    bool isEmpty() { return sz == 0; }
    int  size()    { return sz; }

    void print() {
        cout << "Queue (front -> rear): ";
        for (int i = 0; i < sz; i++)
            cout << arr[(front + i) % capacity] << " ";
        cout << "\n";
    }
};

// ─────────────────────────────────────────
//  Deque  (double-ended queue)
// ─────────────────────────────────────────
struct DQNode {
    int data;
    DQNode* prev;
    DQNode* next;
    DQNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class Deque {
    DQNode* front;
    DQNode* rear;
    int sz;

public:
    Deque() : front(nullptr), rear(nullptr), sz(0) {}

    ~Deque() {
        while (front) {
            DQNode* tmp = front->next;
            delete front;
            front = tmp;
        }
    }

    void pushFront(int val) {
        DQNode* node = new DQNode(val);
        if (!front) { front = rear = node; }
        else {
            node->next = front;
            front->prev = node;
            front = node;
        }
        sz++;
    }

    void pushRear(int val) {
        DQNode* node = new DQNode(val);
        if (!rear) { front = rear = node; }
        else {
            node->prev = rear;
            rear->next = node;
            rear = node;
        }
        sz++;
    }

    int popFront() {
        if (!front) throw underflow_error("Deque empty");
        int val = front->data;
        DQNode* tmp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete tmp;
        sz--;
        return val;
    }

    int popRear() {
        if (!rear) throw underflow_error("Deque empty");
        int val = rear->data;
        DQNode* tmp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete tmp;
        sz--;
        return val;
    }

    bool isEmpty() { return sz == 0; }
    int  size()    { return sz; }
};

int main() {
    cout << "=== Array Stack ===\n";
    Stack s;
    s.push(10); s.push(20); s.push(30);
    s.print();
    cout << "Pop: " << s.pop() << "\n";
    cout << "Peek: " << s.peek() << "\n";
    s.print();

    cout << "\n=== Circular Queue ===\n";
    Queue q;
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.enqueue(4);
    q.print();
    cout << "Dequeue: " << q.dequeue() << "\n";
    q.print();

    cout << "\n=== Deque ===\n";
    Deque dq;
    dq.pushRear(2);
    dq.pushRear(3);
    dq.pushFront(1);
    dq.pushFront(0);
    cout << "PopFront: " << dq.popFront() << "\n";
    cout << "PopRear:  " << dq.popRear()  << "\n";
    cout << "Size: " << dq.size() << "\n";

    return 0;
}
