#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int fenqu(vector<int>& a, int left, int right)
{
    int key = a[left];
    while(left < right)
    {
        while(left < right && a[right] <= key)
            right--;
        a[left] = a[right];

        while(left < right && a[left] >= key)
            left++;
        a[right] = a[left];
    }
    a[left] = key;
    return left;
}

int zhaoDa(vector<int>& a, int l, int r, int k)
{
    int pos = fenqu(a, l, r);
    int bigNum = pos - l + 1;

    if(bigNum == k)
        return a[pos];
    else if(bigNum > k)
        return zhaoDa(a, l, pos - 1, k);
    else
        return zhaoDa(a, pos + 1, r, k - bigNum);
}

int show_10()
{
    SetConsoleOutputCP(CP_UTF8);
    vector<int> arr = {5, 2, 9, 8, 1, 3};
    int second = zhaoDa(arr, 0, arr.size()-1, 2);
    cout << "数组第二大元素：" << second << endl;
    return 0;
}