#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

//repetition
//------------------------------------------
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
// #define ONLINE_JUDGE

int main() {
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif

  ll N, K;
  vector<ll> a;
  const ll MOD = 1000000007;

  cin >> N >> K;
  // indexを1からはじまるようにする
  a.push_back(0);
  REP(i, N) {
    ll n;
    cin >> n;
    a.push_back(n);
  }
  // dp[i][j]
  // i番目の子供までにj個の飴を与えた場合の組み合わせの数
  // 答えはdp[N][K]
  ll dp[N + 1][K + 1];

  REP(i, N + 1) {
    REP(j, K + 1) {
      dp[i][j] = 0;
    }
  }

  dp[0][0] = 1;
  // dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + ... + dp[i - 1][j - a(i)]
  // 素朴な方法 O(NK^2)
  // FOR(i, 1, N + 1)REP(j, K + 1) {
  //   FOR(k, 0, a[i] + 1) {
  //     if (j - k >= 0) {
  //       dp[i][j] += dp[i - 1][j - k] % MOD;
  //     }
  //   }
  // }

  // 累積和を使う
  // dp[i][j] = Σ[k=j-a[i]...j]dp[i-1][k]
  // dp[i][j] = Σ[k=0...j]dp[i-1][k] - Σ[k=0...(j -a[i] - 1)]dp[i-1][k]
  FOR(i, 1, N + 1) {
    ll cum[K + 2];

    // cum[j] = dp[i - 1][0] + ... + dp[i - 1][j - 1]

    // cum[1] = dp[i - 1][0]
    // cum[2] = dp[i - 1][0] + dp[i - 1][i]
    // :
    // cum[j + 1] = dp[i - 1][0] + dp[i - 1][1] + ... + dp[i - 1][j]
    // :
    // cum[K] = dp[i - 1][0] + ... + dp[i - 1][K - 1]
    // cum[K + 1] = dp[i - 1][0] + ... + dp[i - 1][K]
    cum[0] = 0;
    FOR(j, 1, K + 1 + 1) {
      cum[j] = (cum[j - 1] + dp[i - 1][j - 1]) % MOD;
    }

    FOR(j, 0, K + 1) {
      // cum[j - a[i]] = dp[i - 1][0] + dp[i - 1][1] + .... + dp[i - 1][j - a[i] - 1]
      dp[i][j] = (cum[j + 1] - cum[max<ll>(0, j - a[i])] + MOD) % MOD;
    }
  }

  // REP(i, N + 1) {
  //   REP(j, K + 1) {
  //     cout << dp[i][j] << ' ';
  //   }
  //   cout << endl;
  // }

  cout << dp[N][K];
}