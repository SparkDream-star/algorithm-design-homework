#include <iostream>
#include <vector>

using namespace std;
int a[1000][1000] = {0};
int bestx[1000];
int n;
int x[1000];
int cn = 0;
int bestn = 0;

void fun(int i) {
    if (i > n) {
        for (int j = 1; j <= n; j++) {
            bestx[j] = x[j];
        }
        bestn = cn;
        return;
    }
    int OK = 1;
    for (int j = 1; j < i; j++) {
        if (x[j] && a[i][j] == 0) {
            OK = 0;
            break;
        }
    }
    if (OK) {
        x[i] = 1;
        cn++;
        fun(i + 1);
        x[i] = 0;
        cn--;
    }
    if (cn + n - i > bestn) {
        x[i] = 0;
        fun(i + 1);
    }
}

int main() {
    cin>>n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin>>a[i][j];
        }
    }
    fun (1);
    for (int i = 1; i <= n; i++) {
        cout<<bestx[i]<<" ";
    }
    cout<<endl<<bestn;
    return 0;
}