#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int fenqu(vector<int>& a,vector<int>& b,int l,int r)
{
    int m=a[l];
    int p=b[l];
    while(l<r)
    {
        while(l<r&&a[r]>=m) r--;
        a[l]=a[r];
        b[l]=b[r];
        while(l<r&&a[l]<=m) l++;
        a[r]=a[l];
        b[r]=b[l];
    }
    a[l]=m;
    b[l]=p;
    return l;
}

bool find(vector<int>& a,vector<int>& b,int l,int r,int t,int& x,int& y)
{
    if(r-l+1<2) return false;
    int p=fenqu(a,b,l,r);
    int i=l,j=r;
    while(i<j)
    {
        if(a[i]+a[j]==t)
        {
            x=b[i];
            y=b[j];
            return true;
        }
        else if(a[i]+a[j]<t) i++;
        else j--;
    }
    bool le=find(a,b,l,p-1,t,x,y);
    bool ri=find(a,b,p+1,r,t,x,y);
    return le||ri;
}

bool check(vector<int>& a,int k,int& x,int& y)
{
    vector<int> b;
    for(int i=0;i<a.size();i++) b.push_back(i);
    return find(a,b,0,a.size()-1,k,x,y);
}

int show_13()
{
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr={1,4,2,6,5};
    int t=7;
    int x,y;
    if(check(arr,t,x,y))
    {
        cout<<"存在"<<endl;
        cout<<"下标："<<x<<" "<<y<<endl;
    }
    else cout<<"不存在"<<endl;
    return 0;
}