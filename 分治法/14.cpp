#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int find(vector<int>& a) {
    int l = 0;
    int r = a.size() - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] == mid) return mid;
        else if (a[mid] > mid) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int show_14() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr = {-1, 0, 2, 4, 7};
    int res = find(arr);
    if (res != -1) cout << "找到下标：" << res << endl;
    else cout << "不存在" << endl;
    return 0;
}