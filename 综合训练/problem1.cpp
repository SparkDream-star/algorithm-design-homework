#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <vector>
#include <set>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace chrono;

class fun {
private:
    string best_str;
    int best_len;
public:
    fun() {
        best_len = 0;
        best_str = "";
    }

    // 纯回溯
    void backtrack(const string& s1, const string& s2,
        int i, int j, string curr) {
        int remain1 = s1.size() - i;
        int remain2 = s2.size() - j;
        int max_possible_len = curr.size() + min(remain1, remain2);

        if (max_possible_len <= best_len) {
            return;
        }
        if (i == s1.size() || j == s2.size()) {
            if (curr.size() > best_len) {
                best_len = curr.size();
                best_str = curr;
            }
            return;
        }
        if (s1[i] == s2[j]) {
            curr.push_back(s1[i]);
            backtrack(s1, s2, i + 1, j + 1, curr);
            curr.pop_back();
        }
        else {
            backtrack(s1, s2, i + 1, j, curr);
            backtrack(s1, s2, i, j + 1, curr);
        }
    }
    string lcs_backtrack(string s1, string s2) {
        best_str = "";
        best_len = 0;
        backtrack(s1, s2, 0, 0, "");
        return best_str;
    }

    // 纯动态规划
    string lcs_dp(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        string result = "缺点：无法记录字符串 ";
        return result;
    }

    //动态规划+回溯（1条）
    bool backtrack_dp_one(const string& s1, const string& s2,
        const vector<vector<int>>& dp,
        int i, int j, string curr, string& result) {
        if (i == 0 || j == 0) {
            reverse(curr.begin(), curr.end());
            result = curr;
            return true;
        }

        if (s1[i-1] == s2[j-1]) {
            if (backtrack_dp_one(s1, s2, dp, i-1, j-1, curr + s1[i-1], result))
                return true;
        }
        else {
            if (dp[i-1][j] > dp[i][j-1]) {
                if (backtrack_dp_one(s1, s2, dp, i-1, j, curr, result))
                    return true;
            }
            else if (dp[i][j-1] > dp[i-1][j]) {
                if (backtrack_dp_one(s1, s2, dp, i, j-1, curr, result))
                    return true;
            }
            else {
                if (backtrack_dp_one(s1, s2, dp, i, j-1, curr, result))
                    return true;
            }
        }
        return false;
    }

    string lcs_dp_backtrack_one(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (s1[i-1] == s2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

        string res;
        backtrack_dp_one(s1, s2, dp, m, n, "", res);
        return res;
    }
    // 动态规划 + 回溯（所有）
    void backtrack_with_dp(const string& s1, const string& s2,
        const vector<vector<int>>& dp,
        int i, int j, string curr, set<string>& results) {
        if (i == 0 || j == 0) {
            reverse(curr.begin(), curr.end());
            results.insert(curr);
            return;
        }

        if (s1[i - 1] == s2[j - 1]) {
            backtrack_with_dp(s1, s2, dp, i - 1, j - 1, curr + s1[i - 1], results);
        }
        else {
            if (dp[i - 1][j] > dp[i][j - 1])
                backtrack_with_dp(s1, s2, dp, i - 1, j, curr, results);
            else if (dp[i][j - 1] > dp[i - 1][j])
                backtrack_with_dp(s1, s2, dp, i, j - 1, curr, results);
            else {
                backtrack_with_dp(s1, s2, dp, i - 1, j, curr, results);
                backtrack_with_dp(s1, s2, dp, i, j - 1, curr, results);
            }
        }
    }
    pair<string, set<string>> lcs_dp_backtrack(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        set<string> all_lcs;
        backtrack_with_dp(s1, s2, dp, m, n, "", all_lcs);
        string one_lcs = all_lcs.empty() ? "" : *all_lcs.begin();
        return { one_lcs, all_lcs };
    }
};
// 平均值
double calcMean(vector<double> times) {
    sort(times.begin(), times.end());

    double sum = 0;
    for (int i = 1; i < times.size() - 1; i++) {
        sum += times[i];
    }
    return sum / (times.size() - 2);
}
// 方差
double calcVariance(vector<double> times, double mean) {
    sort(times.begin(), times.end());
    double var = 0;
    for (int i = 1; i < times.size() - 1; i++) {
        var += pow(times[i] - mean, 2);
    }
    return var / (times.size()-2);
}
// 变异系数
double calcCV(double mean, double var)
{
    if (mean < 1e-6) return 0.0;
    double stdDev = sqrt(var);
    return (stdDev / mean) * 100.0;
}


void test(int test_count, string s1, string s2) {
    SetConsoleOutputCP(CP_UTF8);
    cout << fixed << setprecision(2);
    fun solver;

    const int TEST_COUNT = test_count;

    // ================== 动态规划 ==================
    vector<double> dp_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_times.push_back(us);
        cout << "DP 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double dp_mean = calcMean(dp_times);
    double dp_var = calcVariance(dp_times, dp_mean);
    double dp_t = calcCV(dp_mean, dp_var);
    cout << "\nDP 平均值: " << dp_mean << " μs\t方差: " << dp_var << "\t变异系数: " << dp_t << "\n" << endl;

    // ================== DP+回溯（只找一条） ==================
    vector<double> dp_one_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack_one(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_one_times.push_back(us);
        cout << "DP+回溯(1条) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double one_mean = calcMean(dp_one_times);
    double one_var = calcVariance(dp_one_times, one_mean);
    double one_t = calcCV(one_mean, one_var);
    cout << "\nDP+回溯(1条) 平均值: " << one_mean << "μs\t方差: " << one_var << "\t变异系数: " << one_t << "\n" << endl;

    // ================== DP+回溯（找全部） ==================
    vector<double> dp_back_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_back_times.push_back(us);
        cout << "DP+回溯(全部) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double db_mean = calcMean(dp_back_times);
    double db_var = calcVariance(dp_back_times, db_mean);
    double db_t = calcCV(db_mean, db_var);
    cout << "\nDP+回溯(全部) 平均值: " << db_mean << " μs\t方差: " << db_var <<"\t变异系数: "<< db_t << "\n" << endl;

    // ================== 纯回溯 ==================
    vector<double> back_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_backtrack(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        back_times.push_back(us);
        cout << "回溯 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double back_mean = calcMean(back_times);
    double back_var = calcVariance(back_times, back_mean);
    double back_t = calcCV(back_mean, back_var);
    cout << "\n回溯 平均值: " << back_mean << " μs\t方差: " << back_var <<"\t变异系数: "<< back_t<< "\n" << endl;

    cout << "长度: " << s1.size() << " + " << s2.size() << "\n" << endl;
    cout << "==================== 测试汇总 ====================" << endl;
    cout << "动态规划            平均: " << dp_mean << " μs\t方差: " << dp_var <<"\t变异系数: "<<dp_t<< endl;
    cout << "动态规划+回溯(1条)  平均: " << one_mean << " μs\t方差: " << one_var << "\t变异系数: "<< one_t<<endl;
    cout << "动态规划+回溯(全部) 平均: " << db_mean << " μs\t方差: " << db_var << "\t变异系数: "<< db_t<<endl;
    cout << "纯回溯              平均: " << back_mean << " μs\t方差: " << back_var << "\t变异系数: "<< back_t<<endl;


    // ================== 输出每个算法的LCS结果 ==================
    string res_dp = solver.lcs_dp(s1, s2);
    string res_dp1 = solver.lcs_dp_backtrack_one(s1, s2);
    auto res_dp_all = solver.lcs_dp_backtrack(s1, s2);
    string res_bt = solver.lcs_backtrack(s1, s2);

    cout << "==================== 各算法求得的LCS ====================" << endl;
    cout << "动态规划 (纯DP)          : " << res_dp << endl;
    cout << "动态规划+回溯 (只找1条)  : " << res_dp1 << endl;
    cout << "动态规划+回溯 (全部解)   : ";
    for (auto s : res_dp_all.second) cout << s << " ";
    cout << endl;
    cout << "纯回溯                   : " << res_bt << "\n" << endl;

}
// 10 50 100 500 1000
// 性能对比实验主函数
// int main() {
//     string s1, s2;
//     // //1000
//     // // 重复率较高
//     // s1 = "dabbddeacabcaadcbceaedbaebaaededcebcedecdabbababdbbbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabeceeaddcbdacceebcaeebddadcdcabaeeebaeeacaddaccbecbcdbbedccabbcbbadbeeabdbaeccdeaacccddeacbebaccbbececaeeeeeacbcabebdcceecdabeccdacceaeaacdbaebcdcccebdbbdbbdaceeabbeeebaeddedaebdeaaacbddbdbceeacbaddbdccaaeececaabedeebbadecdaeeeeeadbeeeebdaeebecbdbaabeebdbeceaeaebacdbdcbcbdaecdddbadbbedbbccbacededbcabccdccbcedaacdbeddbaabceacdadcbdaddacaecabecedeceeddcecedcbbddcdbabbbcabddacccbcecdedbabdeecdcdbbcabdcacadabcadacabbbdbdebaacebddddeaaaadcbddaddaeeaabdebdaddadedaedbcbcbeeaededcdebecccdbeeaebcdbaeabdbedbaeadcdddcdabdbccccdbdbbaaacdabcdecbaabaacbecdaececccaaececadaacbeadddbccceebdddebbdaaaaccbbddcdedddeccdeeaabdcbaddeccaacbbaeeceedbadcdeacdcabbdebdbeeccbbeccedccabdddbcecdaedbaccaeecaecdcbeebcbeceebdcecebbcecacbcccbadcbdaddebdeecacceecccdcdacebddeeebbddeaadeedcadecdeadbbaccdaaedbeacbbaeedacbcdcbeabcbccebedbcddadcebddbdddddededbccdabdaaceceebecedbaeaeedeeebdaccddceeabaecebaeebcaebcaeacddecdacacceabcee";
//     // s2 = "adcebbaaecddcadbacadbbebaeaeaabadaadbbaadcdcdcaceadecceaccdceaadabdcbeccdadedddbcbbccacdbaeaeaadecccbabddededbcbdbaebdceeeeddaeebadbbaeccadadbcbbddcaaaddbdccbdacbdcdabcabbabbadabdceeaeaaeeccdcaabedeeaebccbbbbacacebdeebaadddadcddcecddedaacbbacbcaeaeedcccdecedbcaaaebdcabcccabbcbcddaadbddeebcabedbcebbdededdcdcbbabecbaaeadeeabdabaedeaccdbcbdccbecebeecbbceeeabdecaeebdbeacebcbaacbebaeeddabedadcaabecdcabbacdcaecacbacdbcdaeaccecbcdebadbddddbaceadcddeadcbaaaececbdabdebabedebeccecedadecbadbdcdbaebebeeadbedeaddaadbbcddebdccbdbadcbcbbcebecaececadebbaceededdcabadacbecdabedcdeaedcdbeddaeceaaaabdbeeebdcabccaeadddeceaadcddcdcdbecedbaaccbdbddeeabcbcbbabbdbeabcbdcccbaecebbacedcceceddbccacacdbedaebdbedaccaabccdcbdaedbbecdbebdecdddaceddcdcaddeadaeaabadcdeedaabbdcbaebbdddddabcbebbbdbbedbadbeeeebbdbcbcbcedadcbdcdacdadaceceecaebdeaccdeeaeaeebceeeeacaebecceecaaacbaddcdaeeecadaabbbbdebdaddaabccedbaebdbaaddccccdbbdeacdacacccabcabcacecccacedbedcabaeeaeacddedcebeebddcdbaccdbaabdccebbbedaecdeabaacdadcbbeacbedbcdbb";
//     // // 完全不同
//     // s1 = "bicdamllifgmmikefbejgldjklhmhbdcillbjcdihlcjjhglemammbmgdhclhkegedggbmgklefhcbdmhfbeekgiidkmigckcjglhiaalmijfkdjageiiiggahagdmakiklbbbcgkdfefhmcililjbehaacgfkhlbgacllgaamlhamemhjjfbcdkflejbmjgmafkejmfkadmgemfiibikjbcjijebaeedbcfhfaebhefdfbllmhcebdgaffgaddihcbdmeikeeklmbemcemmdjghdekfbhhhihmgjfdjkkfgidijkamgfglihkelgibjieiamifjmfadgghhffkhgeabfmbmbefcggfjedkbliicmdcchmdfcifahchfjcjkablcefdlgihhhekikjdhbbbdcjgfbecijimhgbefaeabkmggifkgbajddgcfjjhbbkkekajhmbkjdmfekfmkdkhejicbccaedhejddlmibmklmlbldjkjighdffilbgdmemeakjjfieagcfcdkehhgeiabkfblfamcibicmdidelcfdjdijagbciajkmfbaejbelbkjbmbgaifjibfilbbjhemebdbhhhkilidggjdalmgbghgmmmblheijmkaadaakgigfjbgidegckgfikiajjlabffhejjbjjcmgkjcbkdlkakdajhbfeghedbhjcgaldgebmlhljfefjdbeglckmmagdkehachdighgkcljdafdeklmailjbgdgamjbllgjembbbkahfmddekjjedackhccgfgmcedbcikjakebdegidmaffjdgkbakmbkeiihdkaalfblkeafchkfaicccdlaiddfhadbclgikkmkehglgfceclkamgjmmbidklamclkekkchkjlajmhhcmlgegbdcgalcbjlkeahlkllmemfbdbcmkmicmjmkchcdibjmmfmmahlmchmbjdmclbjilfddadbafjmlgehbg";
//     // s2 = "yvvpnxqrznprwuyouutnzpypoppwwwqqqnuxorsqvupnpqoxrstvoupyrsqtpqnwvoruzuuxxstytytoywtyxvvowpzzxoszszvxqyynssrqsyxvtssouwzzuoqtrsrtunqouwnyrqwyynxqqtwoyozsxqsvppxwwyxtprtoyynpxxqsywqxtvonrupyurpywvqspuzyvvqsnxwnyvunqxqzvsrrqtvxsotvxrvuqonzvyqwyqowyxxuvvwvzqssnwupwptxyvtxxypooqxwpvrorwqxrqqytyuznytyrqnyopsuysrwxtvpvnqwpwtwouvszrnprnrxpvvqwrorupxqqwuryzryrpzyspwowuprvnyqtnzvvnvsrutowvqvvquoxowoooppqtpwqntpzrnvyxvootwoqqzqtopnqxrwownyvprsvyoxpszqsyxvxownzpsuxvprrnvxzoyosnqrwvwuuzvrtwovqrvsxuznvpyyyntqznpvsqsxsysotvosunouvqtpvzrnpsuvtvwowprxzqtwnpowwoupzssxwoszxuxsvzottnzxttypuwosuytszywqzzsoswwqwywzvpvqrvzvztwrortuvswxqyxtnovpwpqqxvqwnxoywywuqxxqvzszzrunqvxyxywvwuuxzqpvpptrsuouqrwpornzvvturxrppntstopprrpwtzxznvsyuvzvryzsuqyxrxsnyptzpztnnvxysotwzxvzwosronxuupqsvsnvtvvwuwnzoxqowssvttosxuzovyxwrzuuonutzqwyrsvtppxppxyyzzsuqnowtrovovyrsvquurrsnqpwsxowytrqupuxyouqynnntnusuyuuztxrpxwqttstvyxuptspzvzwtrptnrnpyrtsnzrwtxxqupvrvxtrytryttutopovpprwopxwttppxnnupvnunqpzuunwvqoszypxuxxpvqwrsupsopytsootunxt";
//     // //完全相同
//     // s1 = "bicdamllifgmmikefbejgldjklhmhbdcillbjcdihlcjjhglemammbmgdhclhkegedggbmgklefhcbdmhfbeekgiidkmigckcjglhiaalmijfkdjageiiiggahagdmakiklbbbcgkdfefhmcililjbehaacgfkhlbgacllgaamlhamemhjjfbcdkflejbmjgmafkejmfkadmgemfiibikjbcjijebaeedbcfhfaebhefdfbllmhcebdgaffgaddihcbdmeikeeklmbemcemmdjghdekfbhhhihmgjfdjkkfgidijkamgfglihkelgibjieiamifjmfadgghhffkhgeabfmbmbefcggfjedkbliicmdcchmdfcifahchfjcjkablcefdlgihhhekikjdhbbbdcjgfbecijimhgbefaeabkmggifkgbajddgcfjjhbbkkekajhmbkjdmfekfmkdkhejicbccaedhejddlmibmklmlbldjkjighdffilbgdmemeakjjfieagcfcdkehhgeiabkfblfamcibicmdidelcfdjdijagbciajkmfbaejbelbkjbmbgaifjibfilbbjhemebdbhhhkilidggjdalmgbghgmmmblheijmkaadaakgigfjbgidegckgfikiajjlabffhejjbjjcmgkjcbkdlkakdajhbfeghedbhjcgaldgebmlhljfefjdbeglckmmagdkehachdighgkcljdafdeklmailjbgdgamjbllgjembbbkahfmddekjjedackhccgfgmcedbcikjakebdegidmaffjdgkbakmbkeiihdkaalfblkeafchkfaicccdlaiddfhadbclgikkmkehglgfceclkamgjmmbidklamclkekkchkjlajmhhcmlgegbdcgalcbjlkeahlkllmemfbdbcmkmicmjmkchcdibjmmfmmahlmchmbjdmclbjilfddadbafjmlgehbg";
//     // s2 = "bicdamllifgmmikefbejgldjklhmhbdcillbjcdihlcjjhglemammbmgdhclhkegedggbmgklefhcbdmhfbeekgiidkmigckcjglhiaalmijfkdjageiiiggahagdmakiklbbbcgkdfefhmcililjbehaacgfkhlbgacllgaamlhamemhjjfbcdkflejbmjgmafkejmfkadmgemfiibikjbcjijebaeedbcfhfaebhefdfbllmhcebdgaffgaddihcbdmeikeeklmbemcemmdjghdekfbhhhihmgjfdjkkfgidijkamgfglihkelgibjieiamifjmfadgghhffkhgeabfmbmbefcggfjedkbliicmdcchmdfcifahchfjcjkablcefdlgihhhekikjdhbbbdcjgfbecijimhgbefaeabkmggifkgbajddgcfjjhbbkkekajhmbkjdmfekfmkdkhejicbccaedhejddlmibmklmlbldjkjighdffilbgdmemeakjjfieagcfcdkehhgeiabkfblfamcibicmdidelcfdjdijagbciajkmfbaejbelbkjbmbgaifjibfilbbjhemebdbhhhkilidggjdalmgbghgmmmblheijmkaadaakgigfjbgidegckgfikiajjlabffhejjbjjcmgkjcbkdlkakdajhbfeghedbhjcgaldgebmlhljfefjdbeglckmmagdkehachdighgkcljdafdeklmailjbgdgamjbllgjembbbkahfmddekjjedackhccgfgmcedbcikjakebdegidmaffjdgkbakmbkeiihdkaalfblkeafchkfaicccdlaiddfhadbclgikkmkehglgfceclkamgjmmbidklamclkekkchkjlajmhhcmlgegbdcgalcbjlkeahlkllmemfbdbcmkmicmjmkchcdibjmmfmmahlmchmbjdmclbjilfddadbafjmlgehbg";
//     // //500
//     // //重复率较高
//     // s1 = "dabbddeacabcaadcbceaedbaebaaededcebcedecdabbababdbbbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabeceeaddcbdacceebcaeebddadcdcabaeeebaeeacaddaccbecbcdbbedccabbcbbadbeeabdbaeccdeaacccddeacbebaccbbececaeeeeeacbcabebdcceecdabeccdacceaeaacdbaebcdcccebdbbdbbdaceeabbeeebaeddedaebdeaaacbddbdbceeacbaddbdccaaeececaabedeebbadecdaeeeeeadbeeeebdaeebecbdbaabeebdbeceaeaebacdbdcbcbdaecdddbadbbedbbccbacededbcabccdccbcedaacdbeddbaabceacdadcbdaddacaecabecedeceeddcecedcbbddcdbabbbcabddacccbcecdedbabdeecdcdbbcabdcaca";
//     // s2 = "dabcadacabbbdbdebaacebddddeaaaadcbddaddaeeaabdebdaddadedaedbcbcbeeaededcdebecccdbeeaebcdbaeabdbedbaeadcdddcdabdbccccdbdbbaaacdabcdecbaabaacbecdaececccaaececadaacbeadddbccceebdddebbdaaaaccbbddcdedddeccdeeaabdcbaddeccaacbbaeeceedbadcdeacdcabbdebdbeeccbbeccedccabdddbcecdaedbaccaeecaecdcbeebcbeceebdcecebbcecacbcccbadcbdaddebdeecacceecccdcdacebddeeebbddeaadeedcadecdeadbbaccdaaedbeacbbaeedacbcdcbeabcbccebedbcddadcebddbdddddededbccdabdaaceceebecedbaeaeedeeebdaccddceeabaecebaeebcaebcaeacddecdacacceabcee";
//     // // 完全不同
//     // s1 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgmlajigdibffmldgclldihbjhkgaeamlkdalmbgajjbghdlfchjcemifgbcehccaiclladicbmhgkkcbffgjimbfeldcffddmflhamkmmlcgcfaemdkffmmhjcdmhhjahglcmbchidbldhifhgmcjdfidejafmmacdmlleckjhmiakdimbbbhdhjcidglkbfdakidjhfaallhkhbbelkllcdbklficmlmklajemklkdkbllckfdkcacelmdifmgmbmcmdbfjehgfhdjamgjjieaieeljdeffdbfmilidhadfhigfcglkcbgiekjiccadglaficjgdiajkbfcmgadlfkimhmlhjgkhljgddijgidbddehbdjjafhfcflhjljeaejlmfjhhccfaeifcgb";
//     // s2 = "vnsunvotnrprwrwxqonuzrvxvwzpnoovupwwpuwoxzonrvzswnvvoxyuozxrsrtryxozvxwswzqxttswqyxoyqturnyppxrywqnzowtwvvtxopvquttswrwqqopotwpptwztqopppntqzuwoytyutspnztxsnvnouqzowuxptssyzqvuwzppvppnnsuqqwwsvzxvvzsuvyxnpqwuqovwzttonsrqozxuzzvqnwtvypuvtorrvyrwqzxusrrzstzvusprwvwpuzswozuqpuuozysoxtwtqxzqurytyyqxsztxqquztouruusrpwuqxnwwxsvxztntuyystswsvptzrwvyyyrrwwynnvyzwsovyswynxqrotuxpoyvqyosqqnxyvpsruvsqxpstquuzqzvquvwnutyqxurvvvwvxvyvrsuwoqwpouztyxqxtxwrozozywzzxrxntsvvuxzoqnyuypnxyqsozqtoyosvwzswpsotsznrszy";
//     // // 完全相同
//     // s1 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgmlajigdibffmldgclldihbjhkgaeamlkdalmbgajjbghdlfchjcemifgbcehccaiclladicbmhgkkcbffgjimbfeldcffddmflhamkmmlcgcfaemdkffmmhjcdmhhjahglcmbchidbldhifhgmcjdfidejafmmacdmlleckjhmiakdimbbbhdhjcidglkbfdakidjhfaallhkhbbelkllcdbklficmlmklajemklkdkbllckfdkcacelmdifmgmbmcmdbfjehgfhdjamgjjieaieeljdeffdbfmilidhadfhigfcglkcbgiekjiccadglaficjgdiajkbfcmgadlfkimhmlhjgkhljgddijgidbddehbdjjafhfcflhjljeaejlmfjhhccfaeifcgb";
//     // s2 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgmlajigdibffmldgclldihbjhkgaeamlkdalmbgajjbghdlfchjcemifgbcehccaiclladicbmhgkkcbffgjimbfeldcffddmflhamkmmlcgcfaemdkffmmhjcdmhhjahglcmbchidbldhifhgmcjdfidejafmmacdmlleckjhmiakdimbbbhdhjcidglkbfdakidjhfaallhkhbbelkllcdbklficmlmklajemklkdkbllckfdkcacelmdifmgmbmcmdbfjehgfhdjamgjjieaieeljdeffdbfmilidhadfhigfcglkcbgiekjiccadglaficjgdiajkbfcmgadlfkimhmlhjgkhljgddijgidbddehbdjjafhfcflhjljeaejlmfjhhccfaeifcgb";
//     // //100
//     // // 重复较高
//     // s1 = "dabbddeacabcaadcbceaedbaebaaededcebcedecdabbababdbbbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabecee";
//     // s2 = "addcbdacceebcaeebddadcdcabaeeebaeeacaddaccbecbcdbbedccabbcbbadbeeabdbaeccdeaacccddeacbebaccbbececaee";
//     // // 完全不同
//     // s1 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgml";
//     // s2 = "nwvtqvosszyqtpyyqvuowuxtnrnzyxqnyzotnwwotuqyspuwprzvstopruppnvpyynqvpozutxxposstwvzosryqpssqqzsyunzx";
//     // // 完全相同
//     // s1 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgml";
//     // s2 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdieecdmihcjcemihikkcaedcmleiflfddhdhlfcmgbabikfaemgml";
//     // //50
//     // // 重复率较高
//     // s1 = "dabbddeacabcaadcbceaedbaebaaededcebcedecdabbababdb";
//     // s2 = "bbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabecee";
//     // // 完全不同
//     // s1 = "iadcjilbfacgacihchkakjecmebblhkjgmehkilhjacdbdbdie";
//     // s2 = "rpqzvupwprzvuvxxpnrqpzyrvsysqququyspztonovxsnrztzy";
//     // // 完全相同
//     // s1 = "bbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabecee";
//     // s2 = "bbbeddadabedcdedbabbbeebdbecbbcbcebbecaaaddcabecee";
//     //20
//     // // 重复率较高
//     // s1 = "dabbdddabbddeacabcea";
//     // s2 = "edbaebabcaadcbceadec";
//     // // 完全不同
//     // s1 = "iadcjilbfacgacihchka";
//     // s2 = "xwrpzrooyuxwtzruxvyu";
//     // // 完全相同
//     // s1 = "iadcjilbfacgacihchka";
//     // s2 = "iadcjilbfacgacihchka";
//     //10
//     // // 重复率较高
//     // s1 = "dabbptncat";
//     // s2 = "bcaadcbcea";
//     // // 完全不同
//     // s1 = "iadcjilbfa";
//     // s2 = "ptnpvupuxn";
//     // // 完全相同
//     // s1 = "iadcjilbfa";
//     // s2 = "iadcjilbfa";
//     /*
//      * 使用时先将数据s1、s2前的注释去掉以确定测试的字符串
//      * num_1, num_2
//      * test_count: 测试的次数
//      */
//     int test_count;
//     test_count = 10;
//     string s_1, s_2;
//     s_1 = s1;s_2 = s2;
//     test(test_count, s_1, s_2);
//     return 0;
// }

// 动态规划+回溯法源代码测试主函数
int main() {
    SetConsoleOutputCP(CP_UTF8);
    string s1 = "dabbddeacabcaadcbcea";
    string s2 = "edbaebaaededcebcedec";
    cout << fixed << setprecision(2);
    fun solver;
    const int TEST_COUNT = 10;
    // ================== DP+回溯（只找一条） ==================
    vector<double> dp_one_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack_one(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_one_times.push_back(us);
        cout << "DP+回溯(1条) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double one_mean = calcMean(dp_one_times);
    double one_var = calcVariance(dp_one_times, one_mean);
    double one_t = calcCV(one_mean, one_var);
    cout << "\nDP+回溯(1条) 平均值: " << one_mean << "μs\t方差: " << one_var << "\t变异系数: " << one_t << "\n" << endl;

    // ================== DP+回溯（找全部） ==================
    vector<double> dp_back_times;
    for (int i = 0; i < TEST_COUNT; i++) {
        auto start = high_resolution_clock::now();
        solver.lcs_dp_backtrack(s1, s2);
        auto end = high_resolution_clock::now();
        double us = duration_cast<microseconds>(end - start).count();
        dp_back_times.push_back(us);
        cout << "DP+回溯(全部) 第 " << i + 1 << " 次: " << us << " μs" << endl;
    }
    double db_mean = calcMean(dp_back_times);
    double db_var = calcVariance(dp_back_times, db_mean);
    double db_t = calcCV(db_mean, db_var);
    cout << "\nDP+回溯(全部) 平均值: " << db_mean << " μs\t方差: " << db_var <<"\t变异系数: "<< db_t << "\n" << endl;

    cout << "长度: " << s1.size() << " + " << s2.size() << "\n" << endl;
    cout << "==================== 测试汇总 ====================" << endl;
    cout << "动态规划+回溯(1条)  平均: " << one_mean << " μs\t方差: " << one_var << "\t变异系数: "<< one_t<<endl;
    cout << "动态规划+回溯(全部) 平均: " << db_mean << " μs\t方差: " << db_var << "\t变异系数: "<< db_t<<endl;
    // ================== 输出每个算法的LCS结果 ==================
    string res_dp1 = solver.lcs_dp_backtrack_one(s1, s2);
    auto res_dp_all = solver.lcs_dp_backtrack(s1, s2);

    cout << "==================== 各算法求得的LCS ====================" << endl;
    cout << "动态规划+回溯 (只找1条)  : " << res_dp1 << endl;
    cout << "动态规划+回溯 (全部解)   : ";
    for (auto s : res_dp_all.second) cout << s << " ";
    cout << endl;

}
