#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;

class LL1Parser {
private:
    string nonTerminals[5] = {"E", "E'", "T", "T'", "F"};
    string terminals[7] = {"i", "+", "*", "(", ")", "#"};

    // LL(1)预测分析表
    string parseTable[5][7] = {
        {"TE'",  "",    "",    "TE'",  "",    ""},
        {"",    "+TE'", "",    "",     "ε",   "ε"},
        {"FT'",  "",    "",    "FT'",  "",    ""},
        {"",    "ε",   "*FT'", "",     "ε",   "ε"},
        {"i",    "",    "",    "(E)",  "",    ""}
    };

    // 将产生式右部拆分为符号序列
    vector<string> splitProduction(const string& prod) {
        vector<string> result;
        for (size_t i = 0; i < prod.length(); ) {
            if (prod[i] == 'E' && i + 1 < prod.length() && prod[i+1] == '\'') {
                result.push_back("E'");
                i += 2;
            } else if (prod[i] == 'T' && i + 1 < prod.length() && prod[i+1] == '\'') {
                result.push_back("T'");
                i += 2;
            } else {
                string s(1, prod[i]);
                result.push_back(s);
                i++;
            }
        }
        return result;
    }

    // 判断是否为终结符
    bool isTerminal(const string& symbol) {
        for (const auto& t : terminals) {
            if (t == symbol) return true;
        }
        return false;
    }

    // 获取非终结符在表中的行索引
    int getNonTerminalIndex(const string& symbol) {
        for (int i = 0; i < 5; i++) {
            if (nonTerminals[i] == symbol) return i;
        }
        return -1;
    }

    // 获取终结符在表中的列索引
    int getTerminalIndex(const string& symbol) {
        for (int i = 0; i < 7; i++) {
            if (terminals[i] == symbol) return i;
        }
        return -1;
    }

    // 获取栈内容字符串（从底到顶）
    string getStackContent(stack<string> st) {
        string result;
        vector<string> temp;
        while (!st.empty()) {
            temp.push_back(st.top());
            st.pop();
        }
        for (int i = temp.size() - 1; i >= 0; i--) {
            result += temp[i];
        }
        return result;
    }

    // 获取剩余输入串
    string getRemainingInput(const string& input, size_t pos) {
        return input.substr(pos);
    }

public:
    // 执行语法分析
    bool parse(const string& inputStr) {
        cout << "\n========== LL(1) 语法分析过程 ==========\n";
        cout << "输入串: " << inputStr << endl;
        cout << "----------------------------------------\n";

        // 表头
        cout << left << setw(6) << "步骤"
             << setw(20) << "分析栈"
             << setw(20) << "剩余输入串"
             << setw(20) << "所用产生式"
             << setw(15) << "动作" << endl;
        cout << "----------------------------------------\n";

        // 初始化分析栈
        stack<string> analyzeStack;
        analyzeStack.push("#");
        analyzeStack.push("E");

        string input = inputStr;
        size_t pos = 0;
        int step = 1;

        while (!analyzeStack.empty()) {
            string stackTop = analyzeStack.top();
            string currentInput = (pos < input.length()) ? string(1, input[pos]) : "#";

            string action = "";
            string production = "";

            // 情况1：栈顶和输入都是#，分析成功
            if (stackTop == "#" && currentInput == "#") {
                cout << left << setw(6) << step
                     << setw(20) << getStackContent(analyzeStack)
                     << setw(20) << getRemainingInput(input, pos)
                     << setw(20) << ""
                     << setw(15) << "接受" << endl;
                cout << "----------------------------------------\n";
                cout << "分析结果：该符号串是合法的！\n";
                return true;
            }

            // 情况2：栈顶是终结符
            if (isTerminal(stackTop)) {
                if (stackTop == currentInput) {
                    analyzeStack.pop();
                    pos++;
                    action = "匹配 " + stackTop;
                    production = "";
                } else {
                    cout << left << setw(6) << step
                         << setw(20) << getStackContent(analyzeStack)
                         << setw(20) << getRemainingInput(input, pos)
                         << setw(20) << ""
                         << setw(15) << "错误" << endl;
                    cout << "----------------------------------------\n";
                    cout << "错误：栈顶终结符 '" << stackTop
                         << "' 与当前输入 '" << currentInput << "' 不匹配！\n";
                    return false;
                }
            }
            // 情况3：栈顶是非终结符
            else {
                int row = getNonTerminalIndex(stackTop);
                int col = getTerminalIndex(currentInput);

                if (row == -1 || col == -1) {
                    cout << "错误：未知符号 '" << stackTop << "'\n";
                    return false;
                }

                string prod = parseTable[row][col];

                if (prod.empty()) {
                    cout << left << setw(6) << step
                         << setw(20) << getStackContent(analyzeStack)
                         << setw(20) << getRemainingInput(input, pos)
                         << setw(20) << ""
                         << setw(15) << "错误" << endl;
                    cout << "----------------------------------------\n";
                    cout << "错误：分析表M[" << stackTop << ", " << currentInput
                         << "]为空，无可用产生式！\n";
                    return false;
                }

                // 弹出栈顶非终结符
                analyzeStack.pop();

                // 记录产生式
                production = stackTop + "→" + prod;

                // 处理ε产生式
                if (prod == "ε") {
                    action = "弹出" + stackTop + "，不压入";
                } else {
                    // 将产生式右部逆序压入栈
                    vector<string> symbols = splitProduction(prod);
                    for (int i = symbols.size() - 1; i >= 0; i--) {
                        analyzeStack.push(symbols[i]);
                    }
                    action = "弹出" + stackTop + "，压入" + prod;
                }
            }

            // 输出当前步骤
            cout << left << setw(6) << step
                 << setw(20) << getStackContent(analyzeStack)
                 << setw(20) << getRemainingInput(input, pos)
                 << setw(20) << production
                 << setw(15) << action << endl;
            step++;
        }

        // 栈空但输入未结束
        if (pos < input.length()) {
            cout << "错误：输入串未分析完毕，但分析栈已空！"<<endl;
            return false;
        }

        return true;
    }

    // 打印预测分析表
    void printParseTable() {
        cout << "LL(1) 预测分析表"<<endl;
        cout << "      ";
        for (const auto& t : terminals) {
            cout << setw(10) << t;
        }

		cout << endl;
        cout <<endl;
        cout <<endl;
        cout <<endl;


        for (int i = 0; i < 5; i++) {
            cout << setw(6) << nonTerminals[i];
            for (int j = 0; j < 7; j++) {
                string cell = parseTable[i][j];
                if (cell.empty()) cell = "error";
                cout << setw(10) << cell;
            }
            cout << endl;
        }
        cout << "----------------------------------------"<<endl;
    }

    // 打印文法
    void printGrammar() {
        cout << "\n========== 文法 G' =========="<<endl;
        cout << "E  → T E'\n";
        cout << "E' → + T E' | ε\n";
        cout << "T  → F T'\n";
        cout << "T' → * F T' | ε\n";
        cout << "F  → ( E ) | i\n";
        cout << "=============================="<<endl;
    }
};

int main() {
    LL1Parser parser;
    parser.printGrammar();
    parser.printParseTable();

    cout << "请输入待分析的符号串（以#结束，包含 i + * ( ) ）："<<endl;
    cout << "输入: ";

    string input;
    cin >> input;

    bool result = parser.parse(input);

    if (!result) {
        cout << "\n分析结果：该符号串是非法的！"<<endl;
    }

    return 0;
}


