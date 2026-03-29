#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// ─────────────────────────────────────────
//  Hash Table  (chaining with linked lists)
// ─────────────────────────────────────────
class HashTable {
    int capacity;
    vector<list<pair<int, string>>> table;

    int hash(int key) {
        return key % capacity;
    }

public:
    HashTable(int cap = 11) : capacity(cap), table(cap) {}

    void insert(int key, string value) {
        int idx = hash(key);
        for (auto& kv : table[idx]) {
            if (kv.first == key) {
                kv.second = value; // update if key exists
                return;
            }
        }
        table[idx].push_back({key, value});
    }

    string get(int key) {
        int idx = hash(key);
        for (auto& kv : table[idx]) {
            if (kv.first == key) return kv.second;
        }
        throw runtime_error("Key not found");
    }

    bool remove(int key) {
        int idx = hash(key);
        auto& chain = table[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                return true;
            }
        }
        return false;
    }

    bool contains(int key) {
        int idx = hash(key);
        for (auto& kv : table[idx])
            if (kv.first == key) return true;
        return false;
    }

    void print() {
        cout << "Hash Table:\n";
        for (int i = 0; i < capacity; i++) {
            cout << "  [" << i << "] ";
            for (auto& kv : table[i])
                cout << "{" << kv.first << ": " << kv.second << "} -> ";
            cout << "NULL\n";
        }
    }
};

// ─────────────────────────────────────────
//  Hash Map  (string keys, open addressing / linear probing)
// ─────────────────────────────────────────
class HashMap {
    struct Entry {
        string key;
        int value;
        bool occupied;
        bool deleted;
        Entry() : occupied(false), deleted(false) {}
    };

    int capacity;
    int sz;
    vector<Entry> table;

    int hash(const string& key) {
        int h = 0;
        for (char c : key) h = (h * 31 + c) % capacity;
        return h;
    }

    int probe(const string& key) {
        int idx = hash(key);
        int i = 0;
        while (table[idx].occupied && table[idx].key != key) {
            idx = (idx + 1) % capacity; // linear probe
            if (++i == capacity) return -1;
        }
        return idx;
    }

public:
    HashMap(int cap = 17) : capacity(cap), sz(0), table(cap) {}

    void put(const string& key, int value) {
        if (sz >= capacity / 2) {
            cout << "[Warning] Load factor high, consider resizing\n";
        }
        int idx = hash(key);
        while (table[idx].occupied && table[idx].key != key)
            idx = (idx + 1) % capacity;

        if (!table[idx].occupied) sz++;
        table[idx].key = key;
        table[idx].value = value;
        table[idx].occupied = true;
        table[idx].deleted = false;
    }

    int get(const string& key) {
        int idx = hash(key);
        int i = 0;
        while (table[idx].occupied || table[idx].deleted) {
            if (table[idx].occupied && table[idx].key == key)
                return table[idx].value;
            idx = (idx + 1) % capacity;
            if (++i == capacity) break;
        }
        throw runtime_error("Key not found: " + key);
    }

    bool remove(const string& key) {
        int idx = hash(key);
        int i = 0;
        while (table[idx].occupied || table[idx].deleted) {
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].occupied = false;
                table[idx].deleted = true;
                sz--;
                return true;
            }
            idx = (idx + 1) % capacity;
            if (++i == capacity) break;
        }
        return false;
    }

    bool contains(const string& key) {
        try { get(key); return true; }
        catch (...) { return false; }
    }

    int size() { return sz; }

    void print() {
        cout << "HashMap (string -> int):\n";
        for (int i = 0; i < capacity; i++) {
            if (table[i].occupied)
                cout << "  [" << i << "] " << table[i].key << " -> " << table[i].value << "\n";
        }
    }
};

int main() {
    cout << "=== Hash Table (chaining) ===\n";
    HashTable ht;
    ht.insert(1,  "Alice");
    ht.insert(12, "Bob");
    ht.insert(23, "Charlie");   // same bucket as 1 and 12 (mod 11)
    ht.insert(5,  "Dave");
    ht.print();

    cout << "Get key 12: " << ht.get(12) << "\n";
    cout << "Contains 5: " << (ht.contains(5) ? "yes" : "no") << "\n";

    ht.remove(12);
    cout << "After removing key 12:\n";
    ht.print();

    cout << "\n=== HashMap (open addressing) ===\n";
    HashMap hm;
    hm.put("name",  42);
    hm.put("age",   25);
    hm.put("score", 99);
    hm.put("rank",  3);
    hm.print();

    cout << "Get 'score': " << hm.get("score") << "\n";
    hm.remove("age");
    cout << "After removing 'age', contains: " << (hm.contains("age") ? "yes" : "no") << "\n";
    cout << "Size: " << hm.size() << "\n";

    return 0;
}
