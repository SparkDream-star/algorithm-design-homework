#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int countNum(vector<int>& a, int l, int r, int x) {
    if (l == r) {
        return 1;
    }
    int mid = (l + r) / 2;
    int left = countNum(a, l, mid, x);
    int right = countNum(a, mid + 1, r, x);

    if (left == x) return a[l];
    if (right == x) return a[mid + 1];

    int cnt = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == a[l]) cnt++;
    }
    if (cnt == x) return a[l];

    cnt = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] == a[mid + 1]) cnt++;
    }
    if (cnt == x) return a[mid + 1];

    return -1;
}

int findX(vector<int>& a, int x) {
    return countNum(a, 0, a.size() - 1, x);
}

int show_11() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr = {1, 2, 3, 2, 2, 4};
    int x ;
    cout<<"请指定出现次数";
    cin>>x;
    int res = findX(arr, x);
    cout << "出现指定次数的元素：" << res << endl;
    return 0;
}