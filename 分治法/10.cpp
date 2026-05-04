//
// Created by LENOVO on 2026/5/4.
//
//
// Created by LENOVO on 2026/5/4.
//

#include <iostream>
#include <vector>
#include <windows.h>
#include <climits>
using namespace std;

struct Result {
    int first;   // 最大值
    int second;  // 第二大值

    Result() : first(INT_MIN), second(INT_MIN) {}
    Result(int f, int s) : first(f), second(s) {}
};

Result findSecondMax(vector<int>& arr, int left, int right) {
    Result res;

    // 基本情况：只有一个元素
    if (left == right) {
        res.first = arr[left];
        res.second = INT_MIN;
        return res;
    }

    // 基本情况：只有两个元素
    if (right - left == 1) {
        if (arr[left] > arr[right]) {
            res.first = arr[left];
            res.second = arr[right];
        } else {
            res.first = arr[right];
            res.second = arr[left];
        }
        return res;
    }

    // 分治：将数组分成两半
    int mid = left + (right - left) / 2;
    Result leftRes = findSecondMax(arr, left, mid);
    Result rightRes = findSecondMax(arr, mid + 1, right);

    // 合并：从两个子问题的结果中找出最大值和第二大值
    if (leftRes.first > rightRes.first) {
        res.first = leftRes.first;
        res.second = max(leftRes.second, rightRes.first);
    } else if (rightRes.first > leftRes.first) {
        res.first = rightRes.first;
        res.second = max(rightRes.second, leftRes.first);
    } else {
        // 两个最大值相等
        res.first = leftRes.first;
        res.second = max(leftRes.second, rightRes.second);
    }

    return res;
}

int show_10() {
    SetConsoleOutputCP(CP_UTF8);

    vector<int> arr = {70, 40, 50, 20, 90, 30, 80, 10, 60, 45};

    cout << "数组元素: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    if (arr.size() < 2) {
        cout << "数组元素不足，无法找到第二大元素！" << endl;
        return -1;
    }
    Result result = findSecondMax(arr, 0, arr.size() - 1);
    cout << "最大值: " << result.first << endl;
    cout << "第二大元素: " << result.second << endl;
    return 0;
}
