#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int qufen(vector<int>& a, int left, int right) {
    int key = a[left];
    while (left < right) {
        while (left < right && a[right] >= key)
            right--;
        a[left] = a[right];

        while (left < right && a[left] <= key)
            left++;
        a[right] = a[left];
    }
    a[left] = key;
    return left;
}

void getSmall(vector<int>& a, int l, int r, int k) {
    if (l >= r) return;
    int pos = qufen(a, l, r);
    int num = pos - l + 1;

    if (num > k)
        getSmall(a, l, pos - 1, k);
    else
        getSmall(a, pos + 1, r, k - num);
}

int show_12() {
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr = {3,1,4,1,5,9,2,6};
    int k;
    cout<<"请指定k值";
    cin>>k;
    getSmall(arr, 0, arr.size()-1, k);

    cout << "前k个最小元素：";
    for (int i=0; i<k; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}