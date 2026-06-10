#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int c, n;
vector<int> w;

// ---------------- EnQueue（对应教材函数） ----------------
template<class Type>
void EnQueue(queue<Type> &Q, Type wt, Type &bestw, int i, int n) {
    if (i == n) {
        if (wt > bestw) bestw = wt;
        // 叶子结点不入队
    } else {
        Q.push(wt);
    }
}

// ---------------- 主算法 ----------------
int main() {
    cin >> n >> c;

    w.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    queue<int> Q;

    int Ew = 0;
    int bestw = 0;

    Q.push(-1);   // 层结束标志
    int i = 1;

    while (true) {

        // ---------- 左孩子（选） ----------
        if (Ew + w[i] <= c) {
            EnQueue(Q, Ew + w[i], bestw, i, n);
        }

        // ---------- 右孩子（不选） ----------
        EnQueue(Q, Ew, bestw, i, n);

        // ---------- 出队 ----------
        Ew = Q.front();
        Q.pop();

        // ---------- 层结束 ----------
        if (Ew == -1) {

            if (Q.empty())
                break;   // 或 return bestw;

            Q.push(-1);  // 下一层结束标志
            Ew = Q.front();
            Q.pop();
            i++; // 进入下一层
        }
    }

    cout << bestw << endl;
    return 0;
}