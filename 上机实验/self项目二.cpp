#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int curcity;//当前城市
    int cost;//当前已走路程
    int lowerbound;//预估下界（当前代价+剩余城市最小边和）
    vector<int> path;//走过的路径
    vector<bool> visited;//标记城市是否走过
    bool operator>(const Node& other) const {
        return lowerbound > other.lowerbound;
    }
};

//计算城市出边最小
vector<int> getminE(int n, const vector<vector<int>>& dist) {
    vector<int>minE;
    int min = dist[0][1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] < min) {
                min = dist[i][j];
            }
        }
        minE.push_back(min);
    }
    return minE;
}

// 计算当前结点的下界
int lower(int curcost, const vector<bool>&visited, const vector<int>&minE, int n) {
    int lowercost = curcost;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            curcost += minE[i];
        }
    }
    lowercost = curcost;
    return lowercost;
}

int tsp(const vector<vector<int>>& dist, int n) {
    vector<int>minE = getminE(n, dist);
    priority_queue<Node, vector<Node>, greater<Node>> pq;//小根堆
    Node start;
    start.path.push_back(0);
    start.curcity = 0;
    start.cost = 0;
    start.visited.assign(n, false);
    start.visited[0] = true;
    start.lowerbound = lower(0, start.visited, minE, n);
    pq.push(start);
    int ans = INT_MAX;

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        //剪枝
        if (cur.lowerbound >= ans) {
            continue;
        }
        // 所有城市已经走完，回到起点
        if (cur.path.size() == n) {
            int total = cur.cost + dist[cur.curcity][0];
            if (total < ans) {
                ans = total;
            }
            continue;
        }
        // 分支：遍历所有未访问城市
        for (int next = 0; next < n; next++) {
            if (!cur.visited[next]) {
                Node newNode = cur;
                newNode.curcity = next;
                newNode.visited[next] = true;
                newNode.cost += dist[cur.curcity][next];
                newNode.lowerbound = lower(newNode.cost,
                    newNode.visited, minE, n);
                newNode.path.push_back(next);
                if (newNode.lowerbound < ans) {
                    pq.push(newNode);
                }
            }
        }
    }
    return ans;
}

int main() {
    int n;
    cin>>n;
    vector<vector<int>>dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin>>dist[i][j];
        }
    }
    int res = tsp(dist, n);
    cout << res << endl; // 输出：30，和样例输出一致
    return 0;
}