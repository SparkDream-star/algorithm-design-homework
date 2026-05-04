#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int tile = 1;
void chessBoard(vector<vector<int>>& board, int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }

    int t = tile++;
    int s = size / 2;
    if (dr < tr + s && dc < tc + s) {
        chessBoard(board, tr, tc, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s - 1] = t;
        chessBoard(board, tr, tc, tr + s - 1, tc + s - 1, s);
    }

    if (dr < tr + s && dc >= tc + s) {
        chessBoard(board, tr, tc + s, dr, dc, s);
    } else {

        board[tr + s - 1][tc + s] = t;
        chessBoard(board, tr, tc + s, tr + s - 1, tc + s, s);
    }


    if (dr >= tr + s && dc < tc + s) {

        chessBoard(board, tr + s, tc, dr, dc, s);
    } else {

        board[tr + s][tc + s - 1] = t;
        chessBoard(board, tr + s, tc, tr + s, tc + s - 1, s);
    }


    if (dr >= tr + s && dc >= tc + s) {
        chessBoard(board, tr + s, tc + s, dr, dc, s);
    } else {

        board[tr + s][tc + s] = t;
        chessBoard(board, tr + s, tc + s, tr + s, tc + s, s);
    }
}


int show_9() {
    SetConsoleOutputCP(CP_UTF8);
    int size = 8;
    vector<vector<int>> board(size, vector<int>(size, 0));

    int dr = 5, dc = 6;
    board[dr][dc] = -1;

    chessBoard(board, 0, 0, dr, dc, size);

    // 输出结果
    cout << "L型骨牌棋盘覆盖结果：" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}



