#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int wt;      // 当前重量
    int i;       // 当前层
    int parent;  // 父节点下标
    int x;       // 0/1选择（从父到当前）
};

int n, c;
vector<int> w;

vector<Node> nodes;  // 存所有节点
int bestw = 0;
int bestNode = -1;

// 计算剩余上界（用于右剪枝）
vector<int> suffix;

void buildSuffix() {
    suffix.resize(n + 2, 0);
    for (int i = n; i >= 1; i--) {
        suffix[i] = suffix[i + 1] + w[i];
    }
}

void bfs() {
    queue<int> Q;

    // root节点
    nodes.push_back({0, 0, -1, -1});
    Q.push(0);

    while (!Q.empty()) {
        int id = Q.front();
        Q.pop();

        Node cur = nodes[id];

        int i = cur.i + 1;
        if (i > n) continue;

        // ---------------- 左孩子（选） ----------------
        int lw = cur.wt + w[i];
        if (lw <= c) {
            Node left = {lw, i, id, 1};
            nodes.push_back(left);
            int lid = nodes.size() - 1;
            Q.push(lid);

            if (i == n && lw > bestw) {
                bestw = lw;
                bestNode = lid;
            }
        }

        // ---------------- 右孩子（不选 + 剪枝） ----------------
        if (cur.wt + suffix[i + 1] > bestw) {
            Node right = {cur.wt, i, id, 0};
            nodes.push_back(right);
            int rid = nodes.size() - 1;
            Q.push(rid);

            if (i == n && cur.wt > bestw) {
                bestw = cur.wt;
                bestNode = rid;
            }
        }
    }
}

// ---------------- 回溯构造最优解 ----------------
vector<int> getBestX() {
    vector<int> bestx(n + 1, 0);

    int id = bestNode;

    for (int j = n; j >= 1; j--) {
        bestx[j] = nodes[id].x;  // 当前选择
        id = nodes[id].parent;   // 回父节点
    }

    return bestx;
}

int main() {
    cin >> n >> c;

    w.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    buildSuffix();

    bfs();

    vector<int> ans = getBestX();

    cout << "bestw = " << bestw << endl;
    cout << "bestx = ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}

// 节点结构体
struct node
{
    int w;                  // 当前装载重量
    int i;                  // 当前层
    int remain;             // 剩余物品总重量
    vector<int> bestx;      // 当前路径
    int priority;           // 上界

    bool operator<(const node& other) const
    {
        return priority < other.priority;   // 大根堆
    }
};

pair<int, vector<int>> fun(priority_queue<node, vector<node>>& Q, vector<int>& w,
    int n, int c){

    int bestw = 0;

    while (true){
        node cur_node = Q.top();
        Q.pop();
        node right = cur_node;
        node left = cur_node;
        // 第一次到达叶子即最优
        if (cur_node.i == n){
            return { cur_node.w, cur_node.bestx };
        }
        if (left.w + w[cur_node.i] <= c){

            left.w += w[left.i];
            left.remain -= w[left.i];
            left.bestx.push_back(1);
            left.i++;
            left.priority = left.w + left.remain;
            if (left.w > bestw) {
                bestw = left.w;
            }
            Q.push(left);
        }

        right.remain -= w[right.i];
        if (right.remain + right.w > bestw) {
            right.bestx.push_back(0);
            right.i++;
            right.priority = right.w + right.remain;
            Q.push(right);
        }
    }
    return {0, {}};
}