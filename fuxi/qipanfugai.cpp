#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void chessBoard(vector<vector<int>>& board, int tr, int tc, int dr, int dc, int size, int& tile) {
    if (size == 1) {
        return;
    }
    int t = ++tile;
    int s = size / 2;
    // 左上
    if (dr < tr + s && dc < tc + s) {
        chessBoard(board, tr, tc, dr, dc, s, tile);
    }
    else {
        board[tr + s - 1][tc + s - 1] = t;
        chessBoard(board, tr, tc, tr + s - 1, tc + s - 1, s, tile);
    }
    // 左下
    if (dr >= tr + s && dc < tc + s) {
        chessBoard(board, tr + s, tc, dr, dc, s, tile);
    }
    else {
        board[tr + s][tc + s - 1] = t;
        chessBoard(board, tr + s, tc, tr + s, tc + s - 1, s, tile);
    }
    // 右上
    if (dr < tr + s && dc >= tc + s) {
        chessBoard(board, tr, tc + s, dr, dc, s, tile);
    }
    else {
        board[tr + s - 1][tc + s] = t;
        chessBoard(board, tr, tc + s, tr + s - 1, tc + s, s, tile);
    }
    // 右下
    if (dr >= tr + s && dc >= tc + s) {
        chessBoard(board, tr + s, tc + s, dr, dc, s, tile);
    }
    else {
        board[tr + s][tc + s] = t;
        chessBoard(board, tr + s, tc + s, tr + s, tc + s, s, tile);
    }
}

int main() {
    int k;
    cin>>k;
    int size = pow(2, k);
    vector<vector<int>> board(size, vector<int>(size, 0));
    int dr, dc;
    cin>>dr>>dc;
    board[dr][dc] = -1;
    int a = 0;
    chessBoard(board, 0, 0, dr, dc, size, a);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}