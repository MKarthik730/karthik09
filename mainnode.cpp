#include<iostream>
#include<vector>
//#include "corelation.h"
using namespace std;
double crelation(vector<int>v, vector<int> u);
double cosine(vector<int>v, vector<int> u);
class Node{
    public:
    int id;
    vector<int> v;
    int src,dest;
    Node(int src,int dest,const vector<int> &vec){
        this->v=vec;
        this->src=src;
        this->dest=dest;
    } 
    Node(const vector<int> &vec, int id){
        this->v=vec;
        this->id=id;
    }
};
class graph{
    public:
    vector<Node*> store[5];
    void crtnode(vector<int> vec, int id){
        Node * n=new Node(vec, id);
        store[id].push_back(n);
    }
    void display(){
        for(int i=0;i<5;i++){
            cout<<"node="<<i<<endl;
            for(int j=0;j<store[i].size();j++){
            Node* n=store[i][j];
            cout<<n->src<<" "<<n->dest<<" ";
        }
        cout<<"done"<<endl;
    }
}
void connect(){
    for(int i=0;i<5;i++){
       
        if(store[i].empty())continue;
        Node * n1=store[i][0];
       for(int j=1;j<5;j++){
        if(i==j||store[j].empty())continue;
        Node* n2=store[j][0];
        cout<<i<<j<<" "<<crelation(n1->v, n2->v)<<" "<<cosine(n1->v, n2->v)<<endl;
            
        if(crelation(n1->v, n2->v)>=0.9 || cosine(n1->v, n2->v)>=0.9){
            Node* n= new Node(i,j, n2->v);
            store[i].push_back(n);
               
                
          
        }
       }
      }
}
};
int main(){
    graph *gr=new graph();
    gr->crtnode({1,2,3},1);
    gr->crtnode({2,4,6},2);
    gr->crtnode({1,9,5},3);
    gr->crtnode({1,2,5},4);
   gr->connect();
    gr->display();
    return 0;
}
