#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll N;
ll A[3000];
ll dp[3000 + 1][3000 + 1];

ll taro(ll i, ll j);
ll jiro(ll i, ll j);

ll taro(ll i, ll j) {
    // cout << "taro: " << i << " : " << j << endl;
    if (i > j) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = max(A[i] + jiro(i + 1, j), A[j] + jiro(i, j - 1));

    return dp[i][j];
}

ll jiro(ll i, ll j) {
    // cout << "jiro: " << i << " : " << j << endl;
    if (i > j) {
        return 0;
    }

    return min(taro(i + 1, j) - A[i], taro(i, j - 1) - A[j]);
}

int main() {
    cin >> N;

    for (ll i = 0; i < N; i++) {
        ll a;
        cin >> a;
        A[i] = a;
    }

    for (ll i = 0; i < N; i++) {
        for (ll j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }

    cout << taro(0, N - 1) << endl;
}