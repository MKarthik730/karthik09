#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data)      node->left  = insert(node->left,  val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (val == node->data) return true;
        return val < node->data ? search(node->left, val) : search(node->right, val);
    }

    Node* minNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (!node->left) {
                Node* tmp = node->right;
                delete node;
                return tmp;
            }
            if (!node->right) {
                Node* tmp = node->left;
                delete node;
                return tmp;
            }
            Node* successor = minNode(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val)        { root = insert(root, val); }
    void remove(int val)        { root = remove(root, val); }
    bool search(int val)        { return search(root, val); }
    int  height()               { return height(root); }

    void inorder()   { inorder(root);   cout << "\n"; }
    void preorder()  { preorder(root);  cout << "\n"; }
    void postorder() { postorder(root); cout << "\n"; }

    void levelOrder() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                Node* curr = q.front(); q.pop();
                cout << curr->data << " ";
                if (curr->left)  q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            cout << "\n";
        }
    }
};

int main() {
    BST tree;
    for (int val : {50, 30, 70, 20, 40, 60, 80})
        tree.insert(val);

    cout << "Inorder:   "; tree.inorder();
    cout << "Preorder:  "; tree.preorder();
    cout << "Postorder: "; tree.postorder();
    cout << "Level Order:\n"; tree.levelOrder();
    cout << "Height: " << tree.height() << "\n";

    cout << "Search 40: " << (tree.search(40) ? "found" : "not found") << "\n";
    cout << "Search 99: " << (tree.search(99) ? "found" : "not found") << "\n";

    tree.remove(30);
    cout << "After removing 30 (inorder): "; tree.inorder();

    return 0;
}
