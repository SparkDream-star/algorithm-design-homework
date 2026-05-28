#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int max(int a,int b,int c)
{
    int t=a>b?a:b;
    return t>c?t:c;
}

int getMid(vector<int>& a,int l,int mid,int r,int& cl,int& cr)
{
    int sum=0;
    int lsum=-1e9;
    int ll=mid;
    for(int i=mid;i>=l;i--)
    {
        sum+=a[i];
        if(sum>lsum)
        {
            lsum=sum;
            ll=i;
        }
    }
    sum=0;
    int rsum=-1e9;
    int rr=mid+1;
    for(int i=mid+1;i<=r;i++)
    {
        sum+=a[i];
        if(sum>rsum)
        {
            rsum=sum;
            rr=i;
        }
    }
    cl=ll;
    cr=rr;
    return lsum+rsum;
}

int findMax(vector<int>& a,int l,int r,int& resL,int& resR)
{
    if(l==r)
    {
        resL=l;
        resR=r;
        return a[l];
    }
    int mid=(l+r)/2;
    int ml1,mr1,ml2,mr2,ml3,mr3;
    int left=findMax(a,l,mid,ml1,mr1);
    int right=findMax(a,mid+1,r,ml2,mr2);
    int midSum=getMid(a,l,mid,r,ml3,mr3);
    int m=max(left,right,midSum);
    if(m==left)
    {
        resL=ml1;
        resR=mr1;
    }
    else if(m==right)
    {
        resL=ml2;
        resR=mr2;
    }
    else
    {
        resL=ml3;
        resR=mr3;
    }
    return m;
}

int show_16()
{
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr={-2,1,-3,4,-1,2,1,-5,4};
    int l,r;
    int sum=findMax(arr,0,arr.size()-1,l,r);
    cout<<"最大和："<<sum<<endl;
    cout<<"下标："<<l<<" ~ "<<r<<endl;
    cout<<"子序列：";
    for(int i=l;i<=r;i++)cout<<arr[i]<<" ";
    return 0;
}