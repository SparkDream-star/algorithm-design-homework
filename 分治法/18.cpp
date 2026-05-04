#include <iostream>
#include <vector>
using namespace std;

long long merge(vector<int>& A, vector<int>& temp, int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    long long cnt = 0;
    while (i <= mid && j <= r) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
            cnt += mid - i + 1;
        }
    }
    while (i <= mid) temp[k++] = A[i++];
    while (j <= r) temp[k++] = A[j++];
    for (int p = l; p <= r; p++) A[p] = temp[p];
    return cnt;
}

long long mergeSort(vector<int>& A, vector<int>& temp, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    long long left = mergeSort(A, temp, l, mid);
    long long right = mergeSort(A, temp, mid + 1, r);
    long long cross = merge(A, temp, l, mid, r);
    return left + right + cross;
}

long long reversePairs(vector<int>& A) {
    vector<int> temp(A.size());
    return mergeSort(A, temp, 0, A.size() - 1);
}

// 测试
int show_18() {
    vector<int> A = {2,4,1,3,5};
    cout << reversePairs(A) << endl;
    return 0;
}