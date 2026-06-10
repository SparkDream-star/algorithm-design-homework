#include <iostream>
#include <windows.h>
using namespace std;
void hanoi(int n, char x, char y, char z) {
    if (n == 1) {
        cout<<"将"<<n<<"盘子从"<<x<<"移动到"<<z<<endl;
        return;
    }
    else {
        hanoi(n-1, x, z, y);
        cout<<"将"<<n<<"盘子从"<<x<<"移动到"<<z<<endl;
        hanoi(n-1, y, x, z);
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n = 5;
    hanoi(n, 'x', 'y', 'z');
    return 0;
}