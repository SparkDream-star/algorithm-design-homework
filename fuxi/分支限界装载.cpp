#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

struct node {
    int w;// 当前装载重量
    int i;// 当前层
    int remain;// 剩余物品总重量
    vector<int> bestx;// 当前路径
    int priority;// 优先级
    bool operator < (const node& other) const {
        return priority < other.priority;
    }
};

pair<int, vector<int>>fun(vector<int>& w, priority_queue<node, vector<node>>& Q, int n, int c) {
    int bestw = 0;
    while (true) {
        node cur_node = Q.top();
        Q.pop();
        if (cur_node.i == n) {
            return {cur_node.w, cur_node.bestx};
        }
        if (cur_node.w + w[cur_node.i] <= c) {
            node left = cur_node;
            left.remain = left.remain - w[left.i];
            left.bestx.push_back(1);
            left.w = left.w + w[left.i];
            left.priority = left.w + left.remain;
            left.i++;
            Q.push(left);
            if (left.w > bestw) {
                bestw = left.w;;
            }
        }
        if (cur_node.w + cur_node.remain - w[cur_node.i] >= bestw) {
            node right = cur_node;
            right.remain = right.remain - w[right.i];
            right.priority = right.w + right.remain;
            right.bestx.push_back(0);
            right.i++;
            Q.push(right);
        }
    }
}

int main() {
    int n, c;// 物品数，载重
    cin>>n>>c;
    vector<int> w(n);
    int remain = 0;
    for (int i = 0; i < n; i++) {
        cin>>w[i];
        remain += w[i];
    }
    node start;
    start.w = 0;
    start.i = 0;
    start.priority = remain;
    start.remain = remain;
    priority_queue<node, vector<node>>Q;
    Q.push(start);
    auto [num, best] = fun(w, Q, n, c);
    cout<<"max = "<<num<<endl;
    for (int i = 0;i < best.size(); i++) {
        cout<<best[i]<<" ";
    }
    return 0;
}