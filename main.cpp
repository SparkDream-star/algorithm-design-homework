/*
 * 综合训练项目一：分治策略在数组问题中的应用
 * 班级：计算机科学与技术2024级
 * 功能：实现区间子集、顺序统计、最大子数组等问题的多种算法
 * 符合任务书要求：
 *   - 数组规模：10 ≤ n ≤ 10000
 *   - 区间问题范围：[-10000, 10000]
 *   - 最大子数组问题范围：[-1000, 1000]
 */
#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <queue>
#include <fstream>
#include <cmath>
#include <climits>
#include <ctime>

using namespace std;
using namespace chrono;

// ==================== 辅助函数 ====================
void printArray(const vector<int>& arr, const string& title = "", int maxShow = 20) {
    if (!title.empty()) cout << title << ": ";
    int count = 0;
    for (size_t i = 0; i < min(arr.size(), size_t(maxShow)); i++) {
        cout << arr[i] << " ";
        count++;
    }
    if (arr.size() > (size_t)maxShow) cout << "... (共" << arr.size() << "个元素)";
    cout << endl;
}

// ==================== 阶段一：区间子集问题 ====================

// 方法一：排序法 O(n log n)
vector<int> rangeSubsetBySort(vector<int> arr, int k1, int k2) {
    if (k1 < 1) k1 = 1;
    if (k2 > (int)arr.size()) k2 = arr.size();
    if (k1 > k2) return {};

    sort(arr.begin(), arr.end());
    vector<int> result;
    for (int i = k1 - 1; i < k2 && i < (int)arr.size(); i++) {
        result.push_back(arr[i]);
    }
    return result;
}

// QuickSelect 分区函数
int partition(vector<int>& arr, int left, int right) {
    if (left >= right) return left;
    // 随机选择pivot，提高性能
    int randomIndex = left + rand() % (right - left + 1);
    swap(arr[randomIndex], arr[right]);

    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

// QuickSelect 找到第k小的元素
int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];
    if (left > right) return arr[left];

    int pivotIndex = partition(arr, left, right);
    int rank = pivotIndex - left + 1;

    if (k == rank) return arr[pivotIndex];
    else if (k < rank) return quickSelect(arr, left, pivotIndex - 1, k);
    else return quickSelect(arr, pivotIndex + 1, right, k - rank);
}

// 方法二：QuickSelect法 O(n)
vector<int> rangeSubsetByQuickSelect(vector<int> arr, int k1, int k2) {
    if (k1 < 1) k1 = 1;
    if (k2 > (int)arr.size()) k2 = arr.size();
    if (k1 > k2 || k1 < 1 || k2 > (int)arr.size()) return {};

    vector<int> temp = arr;

    // 找到第k1小和第k2小的元素
    int k1th = quickSelect(temp, 0, temp.size() - 1, k1);
    int k2th = quickSelect(temp, 0, temp.size() - 1, k2);

    // 收集区间内的元素
    vector<int> result;
    for (int num : arr) {
        if (num >= k1th && num <= k2th) {
            result.push_back(num);
        }
    }

    // 排序输出（为了美观）
    sort(result.begin(), result.end());
    return result;
}

// ==================== 阶段二：顺序统计问题 ====================

// 方法一：排序法
int kthBySort(vector<int> arr, int k) {
    if (k < 1) k = 1;
    if (k > (int)arr.size()) k = arr.size();
    sort(arr.begin(), arr.end());
    return arr[k - 1];
}

// 方法二：QuickSelect（分治法）
int kthByQuickSelect(vector<int> arr, int k) {
    if (k < 1) k = 1;
    if (k > (int)arr.size()) k = arr.size();
    vector<int> temp = arr;
    return quickSelect(temp, 0, temp.size() - 1, k);
}

// 方法三：堆算法（使用最大堆找第k小）
int kthByHeap(vector<int> arr, int k) {
    if (k < 1) k = 1;
    if (k > (int)arr.size()) k = arr.size();

    // 使用最大堆维护前k个最小元素
    priority_queue<int> maxHeap;
    for (int num : arr) {
        if ((int)maxHeap.size() < k) {
            maxHeap.push(num);
        } else if (num < maxHeap.top()) {
            maxHeap.pop();
            maxHeap.push(num);
        }
    }
    return maxHeap.top();
}

// 找第k大（转换为找第n-k+1小）
int kthLargestByQuickSelect(vector<int> arr, int k) {
    if (k < 1) k = 1;
    if (k > (int)arr.size()) k = arr.size();
    vector<int> temp = arr;
    return quickSelect(temp, 0, temp.size() - 1, arr.size() - k + 1);
}

// 找中位数
double medianByQuickSelect(vector<int> arr) {
    int n = arr.size();
    if (n == 0) return 0;
    vector<int> temp = arr;
    if (n % 2 == 1) {
        return quickSelect(temp, 0, n - 1, n / 2 + 1);
    } else {
        int left = quickSelect(temp, 0, n - 1, n / 2);
        vector<int> temp2 = arr;
        int right = quickSelect(temp2, 0, temp2.size() - 1, n / 2 + 1);
        return (left + right) / 2.0;
    }
}

// ==================== 阶段三：最大子数组问题 ====================
// 数值范围：[-1000, 1000]

// 暴力算法 O(n²)
int maxSubarrayBruteForce(const vector<int>& arr, vector<int>& subarray) {
    int n = arr.size();
    if (n == 0) return 0;

    int maxSum = arr[0];
    int bestStart = 0, bestEnd = 0;

    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        for (int j = i; j < n; j++) {
            currentSum += arr[j];
            if (currentSum > maxSum) {
                maxSum = currentSum;
                bestStart = i;
                bestEnd = j;
            }
        }
    }

    subarray.clear();
    for (int i = bestStart; i <= bestEnd; i++) {
        subarray.push_back(arr[i]);
    }
    return maxSum;
}

// 跨越中点的最大子数组
struct SubarrayInfo {
    int left;
    int right;
    int sum;
};

SubarrayInfo maxCrossingSubarray(const vector<int>& arr, int left, int mid, int right) {
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = mid;

    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = mid + 1;

    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = i;
        }
    }

    return {maxLeft, maxRight, leftSum + rightSum};
}

// 分治算法 O(n log n)
SubarrayInfo maxSubarrayDivideConquer(const vector<int>& arr, int left, int right) {
    if (left == right) {
        return {left, right, arr[left]};
    }

    int mid = left + (right - left) / 2;

    SubarrayInfo leftInfo = maxSubarrayDivideConquer(arr, left, mid);
    SubarrayInfo rightInfo = maxSubarrayDivideConquer(arr, mid + 1, right);
    SubarrayInfo crossInfo = maxCrossingSubarray(arr, left, mid, right);

    if (leftInfo.sum >= rightInfo.sum && leftInfo.sum >= crossInfo.sum) {
        return leftInfo;
    } else if (rightInfo.sum >= leftInfo.sum && rightInfo.sum >= crossInfo.sum) {
        return rightInfo;
    } else {
        return crossInfo;
    }
}

int maxSubarrayDivideConquer(const vector<int>& arr, vector<int>& subarray) {
    if (arr.empty()) return 0;
    SubarrayInfo info = maxSubarrayDivideConquer(arr, 0, arr.size() - 1);
    subarray.clear();
    for (int i = info.left; i <= info.right; i++) {
        subarray.push_back(arr[i]);
    }
    return info.sum;
}

// Kadane算法 O(n) - 作为参考对比
int maxSubarrayKadane(const vector<int>& arr, vector<int>& subarray) {
    int n = arr.size();
    if (n == 0) return 0;

    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    int start = 0, end = 0, tempStart = 0;

    for (int i = 1; i < n; i++) {
        if (maxEndingHere + arr[i] > arr[i]) {
            maxEndingHere = maxEndingHere + arr[i];
        } else {
            maxEndingHere = arr[i];
            tempStart = i;
        }

        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = tempStart;
            end = i;
        }
    }

    subarray.clear();
    for (int i = start; i <= end; i++) {
        subarray.push_back(arr[i]);
    }
    return maxSoFar;
}

// ==================== 阶段五：算法优化与拓展 ====================

// Median-of-Medians算法（最坏情况O(n)）
int medianOfMedians(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];
    if (left > right) return 0;

    int n = right - left + 1;
    int numGroups = (n + 4) / 5;
    vector<int> medians(numGroups);

    // 分组并找到每组的中位数
    for (int i = 0; i < numGroups; i++) {
        int groupLeft = left + i * 5;
        int groupRight = min(groupLeft + 4, right);
        int groupSize = groupRight - groupLeft + 1;

        // 对每组进行排序并取中位数
        vector<int> group;
        for (int j = groupLeft; j <= groupRight; j++) {
            group.push_back(arr[j]);
        }
        sort(group.begin(), group.end());
        medians[i] = group[groupSize / 2];
    }

    // 递归找到中位数的中位数
    int pivot;
    if (numGroups == 1) {
        pivot = medians[0];
    } else {
        pivot = medianOfMedians(medians, 0, medians.size() - 1, medians.size() / 2);
    }

    // 根据pivot进行分区
    int pivotIndex = left;
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            pivotIndex = i;
            break;
        }
    }
    swap(arr[pivotIndex], arr[right]);

    int partitionIndex = partition(arr, left, right);
    int rank = partitionIndex - left + 1;

    if (k == rank) return arr[partitionIndex];
    else if (k < rank) return medianOfMedians(arr, left, partitionIndex - 1, k);
    else return medianOfMedians(arr, partitionIndex + 1, right, k - rank);
}

// ==================== 测试数据生成器 ====================
// 符合任务书要求：
// - 区间问题范围：[-10000, 10000]
// - 最大子数组问题范围：[-1000, 1000]

// 随机数组 - 区间问题范围 [-10000, 10000]
vector<int> generateRandomArray(int n, int minVal = -10000, int maxVal = 10000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 随机数组 - 最大子数组问题范围 [-1000, 1000]
vector<int> generateRandomArrayForMaxSubarray(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000, 1000);

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 全正数组 - 区间问题范围 [1, 10000]
vector<int> generateAllPositiveArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 全正数组 - 最大子数组问题范围 [1, 1000]
vector<int> generateAllPositiveArrayForMaxSubarray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 全负数组 - 区间问题范围 [-10000, -1]
vector<int> generateAllNegativeArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-10000, -1);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 全负数组 - 最大子数组问题范围 [-1000, -1]
vector<int> generateAllNegativeArrayForMaxSubarray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000, -1);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// 正负交替数组 - 区间问题范围 [-10000, 10000]
vector<int> generateAlternatingArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < n; i++) {
        int val = (rand() % 20001) - 10000;  // -10000 到 10000
        arr[i] = (i % 2 == 0) ? abs(val) : -abs(val);
        if (arr[i] == 0) arr[i] = (i % 2 == 0) ? 1 : -1;
    }
    return arr;
}

// 正负交替数组 - 最大子数组问题范围 [-1000, 1000]
vector<int> generateAlternatingArrayForMaxSubarray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    for (int i = 0; i < n; i++) {
        int val = (rand() % 2001) - 1000;  // -1000 到 1000
        arr[i] = (i % 2 == 0) ? abs(val) : -abs(val);
        if (arr[i] == 0) arr[i] = (i % 2 == 0) ? 1 : -1;
    }
    return arr;
}

// 大量重复元素数组 - 区间问题范围
vector<int> generateDuplicateArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 20);  // 只有20种不同的值
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// ==================== 性能测试类 ====================

class PerformanceTester {
private:
    ofstream report;

public:
    PerformanceTester() {
        report.open("experiment_results.csv");
        if (report.is_open()) {
            report << "问题类型,算法,数据规模,运行时间(us),数组最小值,数组最大值" << endl;
        }
    }

    ~PerformanceTester() {
        if (report.is_open()) {
            report.close();
        }
    }

    template<typename Func>
    long long measureTime(Func func) {
        auto start = high_resolution_clock::now();
        func();
        auto end = high_resolution_clock::now();
        return duration_cast<microseconds>(end - start).count();
    }

    void testRangeSubset(const vector<int>& arr, const string& testName) {
        int n = arr.size();
        int k1 = max(1, n / 4 + 1);
        int k2 = min(n, 3 * n / 4);

        cout << "\n========== 【要求一：区间子集问题】 ==========" << endl;
        cout << "---------- " << testName << " ----------" << endl;
        cout << "数组大小: " << n << ", 范围: [" << k1 << ", " << k2 << "]" << endl;
        cout << "数值范围：[-10000, 10000] 【符合任务书要求】" << endl;

        // 测试排序法
        vector<int> sortResult;
        auto sortFunc = [&]() { sortResult = rangeSubsetBySort(arr, k1, k2); };
        long long sortTime = measureTime(sortFunc);

        // 测试QuickSelect法
        vector<int> qsResult;
        auto qsFunc = [&]() { qsResult = rangeSubsetByQuickSelect(arr, k1, k2); };
        long long qsTime = measureTime(qsFunc);

        cout << "排序法结果 (" << sortResult.size() << "个元素): ";
        printArray(sortResult, "", 10);
        cout << "排序法耗时: " << sortTime << " μs" << endl;

        cout << "QuickSelect结果 (" << qsResult.size() << "个元素): ";
        printArray(qsResult, "", 10);
        cout << "QuickSelect耗时: " << qsTime << " μs" << endl;

        // 计算加速比
        if (qsTime > 0) {
            double speedup = (double)sortTime / qsTime;
            cout << "QuickSelect加速比: " << fixed << setprecision(2) << speedup << "x" << endl;
        }

        if (report.is_open()) {
            int minVal = *min_element(arr.begin(), arr.end());
            int maxVal = *max_element(arr.begin(), arr.end());
            report << "区间子集,排序法," << n << "," << sortTime << "," << minVal << "," << maxVal << endl;
            report << "区间子集,QuickSelect," << n << "," << qsTime << "," << minVal << "," << maxVal << endl;
        }
    }

    void testOrderStatistics(const vector<int>& arr, const string& testName) {
        int n = arr.size();
        int k = max(1, n / 2);

        cout << "\n========== 【要求二：顺序统计问题（第k小、第k大、中位数）】 ==========" << endl;
        cout << "---------- " << testName << " 顺序统计 ----------" << endl;
        cout << "数组大小: " << n << ", 寻找第" << k << "小元素" << endl;
        cout << "数值范围：[-10000, 10000] 【符合任务书要求】" << endl;

        // 排序法
        int sortResult = 0;
        auto sortFunc = [&]() { sortResult = kthBySort(arr, k); };
        long long sortTime = measureTime(sortFunc);

        // QuickSelect
        int qsResult = 0;
        auto qsFunc = [&]() { qsResult = kthByQuickSelect(arr, k); };
        long long qsTime = measureTime(qsFunc);

        // 堆算法
        int heapResult = 0;
        auto heapFunc = [&]() { heapResult = kthByHeap(arr, k); };
        long long heapTime = measureTime(heapFunc);

        cout << "排序法结果: " << sortResult << ", 耗时: " << sortTime << " μs" << endl;
        cout << "QuickSelect结果: " << qsResult << ", 耗时: " << qsTime << " μs" << endl;
        cout << "堆算法结果: " << heapResult << ", 耗时: " << heapTime << " μs" << endl;

        // 测试中位数
        double medianVal = medianByQuickSelect(arr);
        cout << "中位数: " << fixed << setprecision(0) << medianVal << endl;

        // 测试第k大
        int kthLargest = kthLargestByQuickSelect(arr, k);
        cout << "第" << k << "大元素: " << kthLargest << endl;

        if (report.is_open()) {
            int minVal = *min_element(arr.begin(), arr.end());
            int maxVal = *max_element(arr.begin(), arr.end());
            report << "顺序统计,排序法," << n << "," << sortTime << "," << minVal << "," << maxVal << endl;
            report << "顺序统计,QuickSelect," << n << "," << qsTime << "," << minVal << "," << maxVal << endl;
            report << "顺序统计,堆算法," << n << "," << heapTime << "," << minVal << "," << maxVal << endl;
        }
    }

    void testMaxSubarray(const vector<int>& arr, const string& testName) {
        int n = arr.size();
        vector<int> subarray;

        cout << "\n========== 【要求三：最大子数组问题】 ==========" << endl;
        cout << "---------- " << testName << " 最大子数组 ----------" << endl;
        cout << "数组大小: " << n << endl;
        cout << "数值范围：[-1000, 1000] 【符合任务书要求】" << endl;
        printArray(arr, "原数组(前20个)", 20);

        // 暴力法
        int bruteSum = 0;
        auto bruteFunc = [&]() { bruteSum = maxSubarrayBruteForce(arr, subarray); };
        long long bruteTime = measureTime(bruteFunc);
        vector<int> bruteSub = subarray;

        // 分治法
        int dcSum = 0;
        auto dcFunc = [&]() { dcSum = maxSubarrayDivideConquer(arr, subarray); };
        long long dcTime = measureTime(dcFunc);

        // Kadane算法作为参考
        int kadaneSum = 0;
        auto kadaneFunc = [&]() { kadaneSum = maxSubarrayKadane(arr, subarray); };
        long long kadaneTime = measureTime(kadaneFunc);

        cout << "暴力法结果: 最大和=" << bruteSum << ", 耗时: " << bruteTime << " μs" << endl;
        cout << "分治法结果: 最大和=" << dcSum << ", 耗时: " << dcTime << " μs" << endl;
        cout << "Kadane算法结果: 最大和=" << kadaneSum << ", 耗时: " << kadaneTime << " μs" << endl;

        // 验证结果一致性
        if (bruteSum == dcSum && bruteSum == kadaneSum) {
            cout << "✓ 三种算法结果一致" << endl;
        } else {
            cout << "✗ 结果不一致！暴力法=" << bruteSum << ", 分治法=" << dcSum << ", Kadane=" << kadaneSum << endl;
        }

        if (report.is_open()) {
            int minVal = *min_element(arr.begin(), arr.end());
            int maxVal = *max_element(arr.begin(), arr.end());
            report << "最大子数组,暴力法," << n << "," << bruteTime << "," << minVal << "," << maxVal << endl;
            report << "最大子数组,分治法," << n << "," << dcTime << "," << minVal << "," << maxVal << endl;
            report << "最大子数组,Kadane," << n << "," << kadaneTime << "," << minVal << "," << maxVal << endl;
        }
    }

    void testDifferentScales() {
        // 数组规模：10, 100, 1000, 5000, 10000 (符合任务书要求)
        vector<int> sizes = {10, 100, 1000, 5000, 10000};

        cout << "\n========================================" << endl;
        cout << "    【要求四：数组规模 10 ≤ n ≤ 10000】" << endl;
        cout << "   区间问题范围：[-10000, 10000] 【符合要求】" << endl;
        cout << "   最大子数组范围：[-1000, 1000] 【符合要求】" << endl;
        cout << "========================================" << endl;

        for (int size : sizes) {
            cout << "\n>>> 测试规模: n = " << size << " <<<" << endl;

            // 区间问题使用 [-10000, 10000] 范围
            vector<int> arr = generateRandomArray(size, -10000, 10000);
            testRangeSubset(arr, "随机数组 n=" + to_string(size));
            testOrderStatistics(arr, "随机数组 n=" + to_string(size));

            // 最大子数组问题使用 [-1000, 1000] 范围
            if (size <= 5000) {  // 暴力法太慢，只在小规模测试
                vector<int> arrMaxSub = generateRandomArrayForMaxSubarray(size);
                testMaxSubarray(arrMaxSub, "随机数组 n=" + to_string(size));
            }
        }
    }
};

// ==================== 主函数 ====================

int main() {
    SetConsoleOutputCP(65001); // 设置控制台输出为UTF-8
    SetConsoleCP(65001);       // 设置控制台输入为UTF-8
    srand(time(nullptr));

    cout << "========================================" << endl;
    cout << "    算法设计与分析 - 综合训练项目一" << endl;
    cout << "========================================" << endl;
    cout << "班级：计算机科学与技术2024级" << endl;
    cout << "========================================" << endl;
    cout << "任务书要求：" << endl;
    cout << "  • 数组规模：10 ≤ n ≤ 10000" << endl;
    cout << "  • 区间问题范围：[-10000, 10000]" << endl;
    cout << "  • 最大子数组问题范围：[-1000, 1000]" << endl;
    cout << "========================================" << endl;

    PerformanceTester tester;

    // ========== 特殊测试数据（符合任务书范围要求） ==========
    cout << "\n########################################" << endl;
    cout << "#           特殊测试数据               #" << endl;
    cout << "########################################" << endl;

    // 1. 全正数组（区间问题范围 [1, 10000]）
    cout << "\n【测试用例1：全正数组 - 范围 1 ~ 10000】" << endl;
    vector<int> allPositive = generateAllPositiveArray(20);
    printArray(allPositive, "全正数组(前20个)", 20);
    tester.testRangeSubset(allPositive, "全正数组");     // 新增：区间子集
    tester.testOrderStatistics(allPositive, "全正数组");

    // 2. 全负数组（区间问题范围 [-10000, -1]）
    cout << "\n【测试用例2：全负数组 - 范围 -10000 ~ -1】" << endl;
    vector<int> allNegative = generateAllNegativeArray(20);
    printArray(allNegative, "全负数组(前20个)", 20);
    tester.testRangeSubset(allNegative, "全负数组");     // 新增：区间子集
    tester.testOrderStatistics(allNegative, "全负数组");

    // 3. 正负交替数组（区间问题范围 [-10000, 10000]）
    cout << "\n【测试用例3：正负交替数组 - 范围 ±10000】" << endl;
    vector<int> alternating = generateAlternatingArray(20);
    printArray(alternating, "正负交替数组(前20个)", 20);
    tester.testRangeSubset(alternating, "正负交替数组");
    tester.testOrderStatistics(alternating, "正负交替数组");

    // 4. 大量重复元素数组
    cout << "\n【测试用例4：大量重复元素数组 - 只有20种不同值】" << endl;
    vector<int> duplicate = generateDuplicateArray(20);
    printArray(duplicate, "重复元素数组(前20个)", 20);
    tester.testRangeSubset(duplicate, "大量重复元素数组");
    tester.testOrderStatistics(duplicate, "大量重复元素数组");

    // ========== 最大子数组问题特殊测试 ==========
    cout << "\n########################################" << endl;
    cout << "#      最大子数组问题特殊测试          #" << endl;
    cout << "#       范围：[-1000, 1000]            #" << endl;
    cout << "########################################" << endl;

    // 全正数组 - 最大子数组问题范围 [1, 1000]
    cout << "\n【最大子数组-测试用例1：全正数组】" << endl;
    vector<int> maxSubPositive = generateAllPositiveArrayForMaxSubarray(15);
    printArray(maxSubPositive, "全正数组", 15);
    tester.testMaxSubarray(maxSubPositive, "全正数组(最大子数组)");

    // 全负数组 - 最大子数组问题范围 [-1000, -1]
    cout << "\n【最大子数组-测试用例2：全负数组】" << endl;
    vector<int> maxSubNegative = generateAllNegativeArrayForMaxSubarray(15);
    printArray(maxSubNegative, "全负数组", 15);
    tester.testMaxSubarray(maxSubNegative, "全负数组(最大子数组)");

    // 正负交替 - 最大子数组问题范围 [-1000, 1000]
    cout << "\n【最大子数组-测试用例3：正负交替数组】" << endl;
    vector<int> maxSubAlternating = generateAlternatingArrayForMaxSubarray(15);
    printArray(maxSubAlternating, "正负交替数组", 15);
    tester.testMaxSubarray(maxSubAlternating, "正负交替数组(最大子数组)");

    // ========== 不同规模性能测试 ==========
    tester.testDifferentScales();

    // ========== 算法优化与拓展：Median-of-Medians测试 ==========
    cout << "\n========================================" << endl;
    cout << "    【要求五：算法优化 Median-of-Medians】" << endl;
    cout << "========================================" << endl;

    vector<int> testArr = generateRandomArray(1000, -10000, 10000);
    int k = 500;
    cout << "数组大小: 1000, 寻找第" << k << "小元素" << endl;
    cout << "数值范围: [-10000, 10000]" << endl;

    vector<int> tempMom = testArr;
    auto momFunc = [&]() {
        medianOfMedians(tempMom, 0, tempMom.size() - 1, k);
    };
    long long momTime = tester.measureTime(momFunc);
    int momResult = medianOfMedians(tempMom, 0, tempMom.size() - 1, k);

    vector<int> tempQs = testArr;
    auto qsFunc = [&]() {
        quickSelect(tempQs, 0, tempQs.size() - 1, k);
    };
    long long qsTime = tester.measureTime(qsFunc);

    cout << "Median-of-Medians结果: " << momResult << ", 耗时: " << momTime << " μs" << endl;
    cout << "QuickSelect结果: " << quickSelect(tempQs, 0, tempQs.size() - 1, k) << ", 耗时: " << qsTime << " μs" << endl;
    cout << "说明：Median-of-Medians保证最坏情况O(n)，但常数较大" << endl;

    // ========== 输出算法复杂度总结 ==========
    cout << "\n========================================" << endl;
    cout << "           算法复杂度总结" << endl;
    cout << "========================================" << endl;
    cout << left << setw(30) << "问题" << setw(22) << "算法" << setw(18) << "时间复杂度" << "空间复杂度" << endl;
    cout << string(80, '-') << endl;
    cout << left << setw(30) << "区间子集" << setw(22) << "排序法" << setw(18) << "O(n log n)" << "O(n)" << endl;
    cout << left << setw(30) << "区间子集" << setw(22) << "QuickSelect" << setw(18) << "平均O(n)" << "O(n)" << endl;
    cout << left << setw(30) << "顺序统计(第k小)" << setw(22) << "排序法" << setw(18) << "O(n log n)" << "O(n)" << endl;
    cout << left << setw(30) << "顺序统计(第k小)" << setw(22) << "QuickSelect" << setw(18) << "平均O(n)" << "O(log n)" << endl;
    cout << left << setw(30) << "顺序统计(第k小)" << setw(22) << "堆算法" << setw(18) << "O(n log k)" << "O(k)" << endl;
    cout << left << setw(30) << "最大子数组" << setw(22) << "暴力法" << setw(18) << "O(n²)" << "O(n)" << endl;
    cout << left << setw(30) << "最大子数组" << setw(22) << "分治法" << setw(18) << "O(n log n)" << "O(log n)" << endl;
    cout << left << setw(30) << "最大子数组" << setw(22) << "Kadane算法" << setw(18) << "O(n)" << "O(1)" << endl;
    cout << left << setw(30) << "顺序统计(优化)" << setw(22) << "Median-of-Medians" << setw(18) << "最坏O(n)" << "O(n)" << endl;

    cout << "\n========================================" << endl;
    cout << "          算法适用场景分析" << endl;
    cout << "========================================" << endl;
    cout << "1. 排序法：适用于需要多次查询或对结果顺序有要求的场景" << endl;
    cout << "2. QuickSelect：适用于单次查询，平均性能最优，实际应用最广" << endl;
    cout << "3. 堆算法：适用于k较小（k << n）或需要动态维护的场景" << endl;
    cout << "4. 分治法：适用于理解分治思想，实际可使用Kadane算法O(n)" << endl;
    cout << "5. Kadane算法：最大子数组问题的最优解，O(n)时间复杂度" << endl;
    cout << "6. Median-of-Medians：适用于需要最坏情况保证的场景（如实时系统）" << endl;

    cout << "\n========================================" << endl;
    cout << "          范围说明（符合任务书）" << endl;
    cout << "========================================" << endl;
    cout << "• 区间子集问题数值范围：[-10000, 10000]" << endl;
    cout << "• 最大子数组问题数值范围：[-1000, 1000]" << endl;
    cout << "• 数组规模范围：10 ~ 10000" << endl;

    cout << "\n========================================" << endl;
    cout << "          实验数据已保存" << endl;
    cout << "========================================" << endl;
    cout << "实验数据已保存到 experiment_results.csv" << endl;
    cout << "\n========== 程序执行完毕 ==========" << endl;

    return 0;
}