#include <iostream>
#include <vector>
using namespace std;

int findMin(vector<int>& nums) {
    int l = 0;
    int r = nums.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (nums[mid] > nums[r]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return nums[l];
}

int show_17() {
    vector<int> arr = {4,5,6,7,0,1,2};
    cout << findMin(arr) << endl;
    return 0;
}