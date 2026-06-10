#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 节点结构体
struct node{
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
        // 第一次到达叶子即最优
        if (cur_node.i == n){
            return { cur_node.w, cur_node.bestx };
        }
        if (cur_node.w + w[cur_node.i] <= c){
            node left = cur_node;
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
        node right = cur_node;
        right.remain -= w[right.i];
        if (right.remain + right.w >= bestw) {
            right.bestx.push_back(0);
            right.i++;
            right.priority = right.w + right.remain;
            Q.push(right);
        }
    }
    return {0, {}};
}
int main(){
    int n, c;
    cin >> n >> c;
    vector<int> w(n);
    int remain = 0;
    for (int i = 0; i < n; i++){
        cin >> w[i];
        remain += w[i];
    }
    priority_queue<node, vector<node>> Q;
    node start;
    start.w = 0;
    start.i = 0;
    start.remain = remain;
    start.priority = remain;
    Q.push(start);
    auto [maxW, best] = fun(Q, w, n, c);
    cout << "max = " << maxW << endl;
    cout << "bestx : ";
    for (int x : best){
        cout << x << " ";
    }
    cout << endl;
    return 0;
}