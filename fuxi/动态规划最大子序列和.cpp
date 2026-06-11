#include <iostream>
#include <vector>
using namespace std;

void fun(vector<int>& w) {
    int MAX = w[0], b = w[0], s= 0;
    int start = 0, end = 0;
    for (int i = 1; i < w.size(); i++) {
        if (b >= 0) {
            b += w[i];
        }
        else {
            b = w[i];
            s = i;
        }
        if (b > MAX) {
            MAX = b;
            start = s;
            end = i;
        }
    }
    for (int i = start; i <= end; i++) {
        cout<<w[i]<<" ";
    }
    cout<<endl<<"MAX = "<<MAX<<endl;
}

int main() {
    int n;
    cin>>n;
    vector<int>w(n);
    for (int i = 0; i < n; i++) {
        cin>>w[i];
    }
    fun(w);
    return 0;
}