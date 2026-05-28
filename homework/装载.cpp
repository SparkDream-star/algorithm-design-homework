#include<iostream>
#include<vector>
using namespace std;
int n, c;//n：集装箱个数  v：船载重
vector<int>w;//集装箱重量
int bestW = 0;//当前最大重量
vector<int>bestX;//方案
//k：当前集装箱；curw当前装上的重量；remainW：未处理的重量；x当前方案
void fun(int k, int curW, int remainW, vector<int>&x){
    //剪支
    if(curW + remainW <= bestW){
        return;
    }
    if(k > n){
        if(curW > bestW){
            bestW = curW;
            bestX = x;
        }
        return;
    }
    //放
    if(curW+w[k-1]<=c){
        x[k-1] = 1;
        fun(k+1,curW+w[k-1],remainW-w[k-1],x);
    }
    //撤回
    x[k-1] = 0;
    fun(k+1,curW,remainW-w[k-1],x);
}


int main(){

    cin>>n>>c;
    int m;
    for(int i = 0;i<n;i++){
        cin>>m;
        w.push_back(m);
    }
    int Remain = 0;
    for(int i = 0;i<n;i++){
        Remain += w[i];
    }
    vector<int>x(n, 0);
    fun(1, 0, Remain, x);
    cout<<bestW<<endl;
    for(int i = 0;i < n; i++){
        cout<<bestX[i]<<" ";
    }
    cout<<endl;
    return 0;
}