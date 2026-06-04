#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// 优先队列结点：保存当前状态
struct Node {
    int curCity;          // 当前所在城市
    int cost;             // 当前已走路程
    int lowerBound;       // 预估下界（当前代价+剩余城市最小边和）
    vector<bool> visited; // 标记城市是否走过
    vector<int> path;     // 走过的路径

    // 优先队列：小顶堆，下界小的优先出队
    bool operator>(const Node& other) const {
        return lowerBound > other.lowerBound;
    }
};

// 计算每个城市最小出边，用于下界估算
vector<int> getMinEdge(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<int> minE(n, INT_MAX);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] < minE[i])
                minE[i] = dist[i][j];
        }
    }
    return minE;
}

// 计算当前结点的下界
int calcLower(int curCost, const vector<bool>& vis, const vector<int>& minE, int n) {
    int lb = curCost;
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) lb += minE[i];
    }
    return lb;
}

// 分支限界TSP主函数
int tspBranchBound(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<int> minEdge = getMinEdge(dist);
    // 优先队列：小根堆
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // 初始化起点：从0号城市(原1号)出发
    Node start;
    start.curCity = 0;
    start.cost = 0;
    start.visited.assign(n, false);
    start.visited[0] = true;
    start.path.push_back(0);
    start.lowerBound = calcLower(0, start.visited, minEdge, n);
    pq.push(start);

    int ans = INT_MAX; // 最优解

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        // 剪枝：当前下界已经大于已知最优解，不用继续扩展
        if (cur.lowerBound >= ans) continue;

        // 所有城市已经走完，回到起点
        if (cur.path.size() == n) {
            int total = cur.cost + dist[cur.curCity][0];
            if (total < ans) ans = total;
            continue;
        }

        // 分支：遍历所有未访问城市
        for (int next = 0; next < n; ++next) {
            if (!cur.visited[next]) {
                Node newNode = cur;
                newNode.curCity = next;
                newNode.cost += dist[cur.curCity][next];
                newNode.visited[next] = true;
                newNode.path.push_back(next);
                newNode.lowerBound = calcLower(newNode.cost, newNode.visited, minEdge, n);
                // 下界小于当前最优才入队
                if (newNode.lowerBound < ans)
                    pq.push(newNode);
            }
        }
    }
    return ans;
}

int main() {
    // 样例输入：5个城市距离矩阵
    int n;
    cin>>n;
    // vector<vector<int>> dist = {
    //     {0,14,4,10,20},
    //     {14,0,7,8,7},
    //     {4,5,0,7,16},
    //     {11,7,9,0,2},
    //     {18,7,17,4,0}
    // };
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    int res = tspBranchBound(dist);
    cout << res << endl; // 输出：30，和样例输出一致
    return 0;
}