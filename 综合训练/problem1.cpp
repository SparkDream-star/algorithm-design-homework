#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <set>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace chrono;

class fun {
private:
    string best_str;
    int best_len;

    bool backtrack_dp_one(const string& s1, const string& s2,
        const vector<vector<int>>& dp,
        int i, int j, string curr, string& result) {
        if (i == 0 || j == 0) {
            reverse(curr.begin(), curr.end());
            result = curr;
            return true;
        }

        if (s1[i-1] == s2[j-1]) {
            if (backtrack_dp_one(s1, s2, dp, i-1, j-1, curr + s1[i-1], result))
                return true;
        }
        else {
            if (dp[i-1][j] > dp[i][j-1]) {
                if (backtrack_dp_one(s1, s2, dp, i-1, j, curr, result))
                    return true;
            }
            else if (dp[i][j-1] > dp[i-1][j]) {
                if (backtrack_dp_one(s1, s2, dp, i, j-1, curr, result))
                    return true;
            }
            else {
                if (backtrack_dp_one(s1, s2, dp, i-1, j, curr, result))
                    return true;
                if (backtrack_dp_one(s1, s2, dp, i, j-1, curr, result))
                    return true;
            }
        }
        return false;
    }

public:
    fun() {
        best_len = 0;
        best_str = "";
    }

    void backtrack(const string& s1, const string& s2,
        int i, int j, string curr) {
        int remain1 = s1.size() - i;
        int remain2 = s2.size() - j;
        int max_possible_len = curr.size() + min(remain1, remain2);

        if (max_possible_len <= best_len) {
            return;
        }

        if (i == s1.size() || j == s2.size()) {
            if (curr.size() > best_len) {
                best_len = curr.size();
                best_str = curr;
            }
            return;
        }

        if (s1[i] == s2[j]) {
            curr.push_back(s1[i]);
            backtrack(s1, s2, i + 1, j + 1, curr);
            curr.pop_back();
        }
        else {
            backtrack(s1, s2, i + 1, j, curr);
            backtrack(s1, s2, i, j + 1, curr);
        }
    }

    string lcs_backtrack(string s1, string s2) {
        best_str = "";
        best_len = 0;
        backtrack(s1, s2, 0, 0, "");
        return best_str;
    }

    string lcs_dp(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        string result = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                result = s1[i - 1] + result;
                i--; j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) i--;
            else j--;
        }
        return result;
    }

    string lcs_dp_backtrack_one(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (s1[i-1] == s2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

        string res;
        backtrack_dp_one(s1, s2, dp, m, n, "", res);
        return res;
    }

    void backtrack_with_dp(const string& s1, const string& s2,
        const vector<vector<int>>& dp,
        int i, int j, string curr, set<string>& results) {
        if (i == 0 || j == 0) {
            reverse(curr.begin(), curr.end());
            results.insert(curr);
            return;
        }

        if (s1[i - 1] == s2[j - 1]) {
            backtrack_with_dp(s1, s2, dp, i - 1, j - 1, curr + s1[i - 1], results);
        }
        else {
            if (dp[i - 1][j] > dp[i][j - 1])
                backtrack_with_dp(s1, s2, dp, i - 1, j, curr, results);
            else if (dp[i][j - 1] > dp[i - 1][j])
                backtrack_with_dp(s1, s2, dp, i, j - 1, curr, results);
            else {
                backtrack_with_dp(s1, s2, dp, i - 1, j, curr, results);
                backtrack_with_dp(s1, s2, dp, i, j - 1, curr, results);
            }
        }
    }

    pair<string, set<string>> lcs_dp_backtrack(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        set<string> all_lcs;
        backtrack_with_dp(s1, s2, dp, m, n, "", all_lcs);
        string one_lcs = all_lcs.empty() ? "" : *all_lcs.begin();
        return { one_lcs, all_lcs };
    }
};

char getRandomLower() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 25);
    return 'a' + dist(gen);
}

string getRandomStr(int n) {
    string res;
    for (int i = 0; i < n; i++) res += getRandomLower();
    return res;
}

double calcMean(const vector<double>& times) {
    double sum = 0;
    for (double t : times) sum += t;
    return sum / times.size();
}

double calcVariance(const vector<double>& times, double mean) {
    double var = 0;
    for (double t : times) var += pow(t - mean, 2);
    return var / times.size();
}

void test(int num_1, int num_2) {
    SetConsoleOutputCP(CP_UTF8);

    vector<double>list_dp_mean;
    vector<double>list_dp_one_mean;
    vector<double>list_dp_back_mean;
    vector<double>list_back_mean;

    cout << fixed << setprecision(2);

    string s1 = getRandomStr(num_1);
    string s2 = getRandomStr(num_2);
    fun solver;

    cout << "长度: " << s1.size() << " + " << s2.size() << "\n" << endl;

    // ================== 输出每个算法的LCS结果 ==================
    string res_dp = solver.lcs_dp(s1, s2);
    string res_dp1 = solver.lcs_dp_backtrack_one(s1, s2);
    auto res_dp_all = solver.lcs_dp_backtrack(s1, s2);
    string res_bt = solver.lcs_backtrack(s1, s2);

    cout << "==================== 各算法求得的LCS ====================" << endl;
    cout << "动态规划 (纯DP)          : " << res_dp << endl;
    cout << "动态规划+回溯 (只找1条)  : " << res_dp1 << endl;
    cout << "动态规划+回溯 (全部解)   : ";
    for (auto s : res_dp_all.second) cout << s << " ";
    cout << endl;
    cout << "纯回溯                   : " << res_bt << "\n" << endl;

    const int TEST_COUNT = 5;

    // ================== 动态规划 ==================
    vector<double> dp_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_times.push_back(us);
        cout << "DP 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double dp_mean = calcMean(dp_times);
    list_dp_mean.push_back(dp_mean);
    double dp_var = calcVariance(dp_times, dp_mean);
    cout << "\nDP 平均值: " << dp_mean << " μs\t方差: " << dp_var << "\n" << endl;

    // ================== DP+回溯（只找一条） ==================
    vector<double> dp_one_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack_one(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_one_times.push_back(us);
        cout << "DP+回溯(1条) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double one_mean = calcMean(dp_one_times);
    list_dp_one_mean.push_back(one_mean);
    double one_var = calcVariance(dp_one_times, one_mean);
    cout << "\nDP+回溯(1条) 平均值: " << one_mean << " μs\t方差: " << one_var << "\n" << endl;

    // ================== DP+回溯（找全部） ==================
    vector<double> dp_back_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_back_times.push_back(us);
        cout << "DP+回溯(全部) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double db_mean = calcMean(dp_back_times);
    list_dp_back_mean.push_back(db_mean);
    double db_var = calcVariance(dp_back_times, db_mean);
    cout << "\nDP+回溯(全部) 平均值: " << db_mean << " μs\t方差: " << db_var << "\n" << endl;

    // ================== 纯回溯 ==================
    vector<double> back_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_backtrack(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        back_times.push_back(us);
        cout << "回溯 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double back_mean = calcMean(back_times);
    list_back_mean.push_back(back_mean);
    double back_var = calcVariance(back_times, back_mean);
    cout << "\n回溯 平均值: " << back_mean << " μs\t方差: " << back_var << "\n" << endl;

    cout << "==================== 测试汇总 ====================" << endl;
    cout << "动态规划            平均: " << dp_mean << " μs\t方差: " << dp_var << endl;
    cout << "动态规划+回溯(1条)  平均: " << one_mean << " μs\t方差: " << one_var << endl;
    cout << "动态规划+回溯(全部) 平均: " << db_mean << " μs\t方差: " << db_var << endl;
    cout << "纯回溯              平均: " << back_mean << " μs\t方差: " << back_var << endl;

}

int main() {
    test(10, 8);
    return 0;
}
