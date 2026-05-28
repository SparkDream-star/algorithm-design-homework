#include <iostream>
#include <vector>
using namespace std;

int threefind(vector<int>& a,int l,int r,int x)
{
    if(l>r)
        return -1;
    int mid1=l+(r-l)/3;
    int mid2=r-(r-l)/3;
    if(a[mid1]==x)
        return mid1;
    if(a[mid2]==x)
        return mid2;
    if(x<a[mid1])
        return threefind(a,l,mid1-1,x);
    else if(x>a[mid2])
        return threefind(a,mid2+1,r,x);
    else
        return threefind(a,mid1+1,mid2-1,x);
}

int show_15()
{
    vector<int> a={1,2,3,4,5,6,7,8,9};
    int ans=threefind(a,0,8,5);
    cout<<ans<<endl;
    return 0;
}

