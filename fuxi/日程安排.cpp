#include <iostream>
using namespace std;

const int MAX = 1025; // 根据需要改大，比如 1024 / 2048

int a[MAX][MAX];

// 分治构造：生成 n 个选手的赛程表
void build(int n) {
    // base case：2个选手
    a[1][1] = 1; a[1][2] = 2;
    a[2][1] = 2; a[2][2] = 1;

    int size = 2;

    // 每次规模扩大一倍
    while (size < n) {
        int half = size;
        size *= 2;

        // 左下角：原矩阵 + half
        for (int i = half + 1; i <= size; i++) {
            for (int j = 1; j <= half; j++) {
                a[i][j] = a[i - half][j] + half;
            }
        }

        // 右下角：复制左上角
        for (int i = half + 1; i <= size; i++) {
            for (int j = half + 1; j <= size; j++) {
                a[i][j] = a[i - half][j - half];
            }
        }

        // 右上角：复制左下角（关键：不需要取模！！）
        for (int i = 1; i <= half; i++) {
            for (int j = half + 1; j <= size; j++) {
                a[i][j] = a[i + half][j - half];
            }
        }
    }
}

// 打印赛程表
void print(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int k;
    cin >> k;

    int n = 1 << k; // n = 2^k

    build(n);
    print(n);

    return 0;
}