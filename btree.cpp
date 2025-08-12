#include<iostream>
using namespace std;
class Node{
    public:
        int data;
        Node* left;
        Node* right;
        Node(int data){
            this->data=data;
            left=nullptr;
            right=nullptr;
        }

};
class btree{
    public:
    int idx=-1;
    Node* tree(int arr[]){
        idx++;
        if(arr[idx]==-1){
            return nullptr;
        }
        Node* n=new Node(arr[idx]);
        n->left=tree(arr);
        n->right=tree(arr);
        return n;
    }
    void preorder(Node* root){
        if(root==nullptr){
            return;
        }
        cout<<root->data<<" ";
        preorder(root->left);
        preorder(root->right);
    }
    
};
int main(){
    btree b;
    int arr[] = {1, 2, 3, -1, -1, -1, 2, 3, -1, -1, -1};
    Node* root=b.tree(arr);
    cout<<root->data<<endl;
    b.preorder(root);
    return 0;
}