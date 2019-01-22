#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

//c.f https://tdpc.contest.atcoder.jp/submissions/3713678

//dp[i][j]:区間[i,j)で"iwi"を取り除ける回数の最大値
ll dp[301][301];
string s;

// [i, j)
ll iwi(size_t i, size_t j) {
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    if (j - i < 3) {
        dp[i][j] = 0;
        return dp[i][j];
    }

    if (j - i == 3) {
        if (s[i] == 'i' && s[i + 1] == 'w' && s[i + 2] == 'i') {
            dp[i][j] = 1;
            return dp[i][j];
        } else {
            dp[i][j] = 0;
            return dp[i][j];
        }
    }


    // [i, mid), [mid, j)に分ける
    // それぞれ分けた区間の最大値
    // e.g i = 0, j = 4, s = iiwi
    // [0, 1), [1, 4): i, iwi
    // [0, 2), [2, 4): ii, wi
    // [0, 3), [3, 4): iiw, i
    ll max = 0;
    for (size_t mid = i + 1; mid < j; mid++) {
        ll tmp = iwi(i, mid) + iwi(mid, j);
        if (max < tmp) {
            max = tmp;
        }
    }

    // "iwi"を取り除いてさらに"iwi"ができる
    // pattern 1: i(iwi)wi
    // pattern 2: iw(iwi)i

    // pattern 1
    if (iwi(i + 1, j - 2) * 3 == j - i - 3) {
        if (s[i] == 'i' && s[j - 2] == 'w' && s[j - 1] == 'i') {
            if (max < iwi(i + 1, j - 2) + 1) {
                max = iwi(i + 1, j - 2) + 1;
            }
        }
    }

    // pattern 2
    if (iwi(i + 2, j - 1) * 3 == j - i - 3) {
        if (s[i] == 'i' && s[i + 1] == 'w' && s[j - 1] == 'i') {
            if (max < iwi(i + 2, j - 1) + 1) {
                max = iwi(i + 2, j - 1) + 1;
            }
        }
    }

    dp[i][j] = max;
    return dp[i][j];
}

int main() {
    cin >> s;

    for (size_t i = 0; i < 301; i++) {
        for (size_t j = 0; j < 301; j++) {
            dp[i][j] = -1;
        }
    }

    cout << iwi(0, s.size());

    return 0;
}