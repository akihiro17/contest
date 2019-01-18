#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

class Factory {
public:
    ll a, b, s;
    Factory(ll a, ll b): a(a), b(b), s(1) {};

    ll assemble() {
        return this->a + (this->s++ - 1) * this->b;
    }

    ll assembleTime() {
        return this->a + (this->s - 1) * this->b;
    }
};

int main() {
    ll N, K;
    cin >> N >> K;

    auto c = [](Factory l, Factory r) { return l.assembleTime() > r.assembleTime(); };
    std::priority_queue<Factory, std::vector<Factory>, decltype(c)> q(c);

    for (int i = 0; i < N; i++) {
        ll a, b;
        cin >> a >> b;
        q.push(Factory(a, b));
    }

    ll totalTime = 0;
    for (int i = 0; i < K; i++) {
        Factory f = q.top();
        totalTime += f.assemble();
        q.pop();
        q.push(f);
    }

    cout << totalTime;
    return 0;
}