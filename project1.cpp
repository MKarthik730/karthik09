#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class User{
    public:
    string usrname;
    string frnd;
    int intrest;
    User(string usrname){
        this->usrname=usrname;
    }
    User(string usrname, string frnd, int intrest){
        this->usrname=usrname;
        this->frnd=frnd;
        this->intrest=intrest;
    }
};
class Network{
    public:
    vector<User*> v[6];
    int count=0;
    
    void adduser(string name){
        User* u=new User(name);
      
        v[count++].push_back(u);
    }
    void printusers(){
      
       for (int i = 0; i < count; i++) {
            cout << "User: " << v[i][0]->usrname << endl;
            cout << "Friends: ";
            for (int j = 1; j < v[i].size(); j++) {
                cout << "(" << v[i][j]->frnd << ", interest: " << v[i][j]->intrest << ") ";
            }
            cout<<endl;
         }
    }
   void connect(string usr, string frnd, int intrest){
   
   for(int i=0;i<6;i++){
    
    if (v[i].size() > 0 && v[i][0]->usrname == usr) {
        v[i].push_back(new User(usr ,frnd, intrest));
         break;
   }
   }
   
}
void printh(int l, int k){
  cout << "suggestions for " << v[l][0]->usrname << ":" << endl;
  for(int i=0;i<6;i++){
    if(v[l][k]->frnd == v[i][0]->usrname){
      for(int j=1; j < v[i].size(); j++){
        if (v[i][j]->frnd != v[l][0]->usrname) {
          cout << v[i][j]->frnd << endl;
        }
      }
    }
  }
  cout << endl;  
}

void suggest(){
  for(int i=0;i<6;i++){
    for(int j=1;j<v[i].size();j++){
      if(v[i][j]->intrest>=3){
       printh(i,j);
      }
    }
  }
}
};
int main(){
    Network* nwt=new Network();
    nwt->adduser("a");
    nwt->adduser("b");
    nwt->adduser("c");
    nwt->adduser("d");
    nwt->adduser("e");
    nwt->adduser("f");
    nwt->connect("a", "b",4);
    nwt->connect("a", "f",2);
    nwt->connect("b", "a",1);
    nwt->connect("b", "c",2);
    nwt->connect("b", "d",3);
    nwt->connect("c", "b",4);
    nwt->connect("c", "e",3);
    nwt->connect("d", "b",3);
    nwt->connect("e", "c",1);
    nwt->connect("f", "a", 3);
  // nwt->printusers();
  nwt->suggest();
return 0;
}


