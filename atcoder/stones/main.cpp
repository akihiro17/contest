#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

vector<ll> A;

int solve(int dp[], ll k) {
    // bcout << dp[k] << " : " << k << endl;
    if (dp[k] != 0) {
        return dp[k];
    }

    for (ll i = 0; i < A.size(); i++) {
        if (k - A[i] < 0) {
            continue;
        } else {
            if (solve(dp, k - A[i]) == 2) {
                dp[k] = 1;
                return dp[k];
            }
        }
    }

    dp[k] = 2;
    return dp[k];
}

int main() {
    ll N, K;
    cin >> N >> K;

    for (ll i = 0; i < N; i++) {
        ll a;
        cin >> a;
        A.push_back(a);
    }

    int dp[K + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 2;


    if (solve(dp, K) == 1) {
        cout << "First";
    } else {
        cout << "Second";
    }
    return 0;
}