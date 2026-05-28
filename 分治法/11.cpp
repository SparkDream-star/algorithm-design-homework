#include <iostream>
#include <vector>
using namespace std;

int countNum(vector<int>& a, int l, int r, int x) {
    if (l > r) return 0;
    if (l == r) {
        if (a[l] == x) return 1;
        else return 0;
    }
    int mid = (l + r) / 2;
    int left = countNum(a, l, mid, x);
    int right = countNum(a, mid + 1, r, x);
    return left + right;
}

int findCount(vector<int>& a, int x) {
    return countNum(a, 0, a.size() - 1, x);
}

int show_11() {
    vector<int> arr = {1, 2, 3, 2, 2, 4, 2};
    cout << findCount(arr, 2) << endl;
    return 0;
}