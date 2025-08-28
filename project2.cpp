#include<iostream>
#include<vector>
#include<cmath>
//#include "corelation.h"
using namespace std;
double crelation(vector<int> v, vector<int> u){
    double vmean=0,umean=0;
    for(int i=0;i<v.size();i++){
       vmean+=v[i];umean+=u[i];
    }
    vmean/=v.size();umean/=u.size();
    double vrlt=0,urlt=0,rln=0;
    for(int i=0;i<v.size();i++){
        rln+=(v[i]-vmean)*(u[i]-umean);
        vrlt+=(v[i]-vmean)*(v[i]-vmean);
        urlt+=(u[i]-umean)*(u[i]-umean);
    }
    rln=rln/((sqrt(vrlt)*sqrt(urlt)));
    return rln;
}
double cosine(vector<int> v, vector<int> u){
    double total=0,vmod=0,umod=0;
   for(int i=0;i<v.size();i++){
     total+=v[i]*u[i];
     vmod+=v[i]*v[i];
     umod+=u[i]*u[i];
    } 
    total=total/(pow(vmod, 0.5)*pow(umod, 0.5));
    return total;
}
