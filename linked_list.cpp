#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* curr = head;
        while (curr) {
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }

    void append(int val) {
        Node* node = new Node(val);
        if (!head) { head = node; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }

    void prepend(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }

    void remove(int val) {
        if (!head) return;
        if (head->data == val) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
        Node* curr = head;
        while (curr->next) {
            if (curr->next->data == val) {
                Node* tmp = curr->next;
                curr->next = tmp->next;
                delete tmp;
                return;
            }
            curr = curr->next;
        }
    }

    bool search(int val) {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        head = prev;
    }

    void print() {
        Node* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << " -> NULL\n";
    }
};

// ---------- Doubly Linked List ----------

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    DNode* head;
    DNode* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        DNode* curr = head;
        while (curr) {
            DNode* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }

    void append(int val) {
        DNode* node = new DNode(val);
        if (!tail) { head = tail = node; return; }
        node->prev = tail;
        tail->next = node;
        tail = node;
    }

    void prepend(int val) {
        DNode* node = new DNode(val);
        if (!head) { head = tail = node; return; }
        node->next = head;
        head->prev = node;
        head = node;
    }

    void remove(int val) {
        DNode* curr = head;
        while (curr) {
            if (curr->data == val) {
                if (curr->prev) curr->prev->next = curr->next;
                else head = curr->next;

                if (curr->next) curr->next->prev = curr->prev;
                else tail = curr->prev;

                delete curr;
                return;
            }
            curr = curr->next;
        }
    }

    void printForward() {
        DNode* curr = head;
        cout << "NULL <-> ";
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " <-> ";
            curr = curr->next;
        }
        cout << " <-> NULL\n";
    }

    void printBackward() {
        DNode* curr = tail;
        cout << "NULL <-> ";
        while (curr) {
            cout << curr->data;
            if (curr->prev) cout << " <-> ";
            curr = curr->prev;
        }
        cout << " <-> NULL\n";
    }
};

int main() {
    cout << "=== Singly Linked List ===\n";
    LinkedList ll;
    ll.append(10);
    ll.append(20);
    ll.append(30);
    ll.prepend(5);
    ll.print();

    ll.remove(20);
    cout << "After removing 20: ";
    ll.print();

    cout << "Search 10: " << (ll.search(10) ? "found" : "not found") << "\n";

    ll.reverse();
    cout << "Reversed: ";
    ll.print();

    cout << "\n=== Doubly Linked List ===\n";
    DoublyLinkedList dll;
    dll.append(1);
    dll.append(2);
    dll.append(3);
    dll.prepend(0);
    dll.printForward();
    dll.printBackward();

    return 0;
}
