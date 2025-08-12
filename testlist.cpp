#include<iostream>
#include<algorithm>
using namespace std;
class llist{
    public:
    int data;
    llist* next;
    llist(){}
    llist(int data){
        this->data=data;
        next=nullptr;
    }
};
class lnode{
public:
    llist* head=nullptr;

    void addfirst(int data){
        llist* node =new llist(data);
        if(head==nullptr){
            head=node;
            return;
        }
        node->next=head;
        head=node;
    }
    void addlast(int data){
           llist* node =new llist(data);
        if(head==nullptr){
            head=node;
            return;
        }
        llist* temp=head;
        while(temp->next!=nullptr){
            temp=temp->next;
        }
        temp->next=node;
    }
llist* reverse(llist* head){
      llist* current =head;
    llist* prev=nullptr;
        while(current!=nullptr){
                llist* next=current->next;
                current->next=prev;
                prev=current;
                current=next;
        }
        return prev;
    }
    void print(){
        llist* temp=head;
        while(temp!=nullptr){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
 int number(){
      char s[10];int i=0;
        llist* hh=head;
        while(hh!=nullptr){
            s[i++]=hh->data+'0';
            hh=hh->next;
        }
         s[i]='\0';
        if(head->data==0){
        string str(s);
     reverse(str.begin(), str.end());
        int x=stoi(str);
        return x;
        }
        else{
          string str(s);
          int x=stoi(str);
        return x;
        }
    }
};
lnode getllist(int s){
  
  lnode l;
     if (s == 0) {
        l.addlast(0);
        return l;
    }
  while(s!=0){
    
    int x=s%10;
    
    l.addlast(x);
    s=s/10;
  }
  return l;
}
int main(){
lnode l;
    l.addfirst(8);
    l.addlast(9);
    l.addlast(2);
    l.addlast(3);
    lnode m;
    m.addfirst(8);
    m.addlast(9);
    m.addlast(2);
    m.addlast(3);
    //l.print();
 //   l.head=l.reverse(l.head);
//l.print();
int x=l.number();
int y=m.number();
lnode v=getllist(x+y);
v.print();
    return 0;
}

