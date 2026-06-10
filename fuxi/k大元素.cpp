#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int pos (vector<int>& a, int low, int high) {
    int base = a[low];
    int i = low;
    int j = high;
    while (i < j) {
        while (i < j && a[j] >= base) {
            j--;
        }
        a[i] = a[j];
        while (i < j && a[i] <= base) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = base;
    return i;
}

void quick_sort(vector<int>&a, int low, int high, int k) {
    int i = pos(a, low, high);
    while (true) {
        if (i == k - 1) {
            cout<<"第"<<k<<"大元素为"<<a[i]<<endl;
            break;
        }
        else if (i > k) {
            i = pos(a, low, i - 1);
        }
        else {
            i = pos(a, i + 1, high);
        }
    }
    for (int j = 0; j < a.size(); j++) {
        cout<<a[j]<<" ";
    }
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> a;
    int k;
    for (int i = 0; i < 3; i++) {
        cin>>k;
        a.push_back(k);
    }
    int m;
    cin>>m;
    quick_sort(a, 0, a.size() - 1, m);
    return 0;
}