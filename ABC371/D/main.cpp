#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <bitset>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;

    vector<int64_t> X(N);
    vector<uint64_t> P(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> X[i];
    }

    for (size_t i = 0; i < N; ++i)
    {
        cin >> P[i];
    }

    vector<pair<int64_t, uint64_t>> X_P(N + 1);

    X_P[0] = {-1000000001, 0};

    for (size_t i = 0; i < N; ++i)
    {
        X_P[i + 1] = {X[i], X_P[i].second + P[i]};
    }

    uint64_t Q;
    cin >> Q;

    for (size_t i = 0; i < Q; ++i)
    {
        int64_t L, R;
        cin >> L >> R;

        auto it_L = lower_bound(X_P.begin(), X_P.end(), make_pair(L, (uint64_t)0));
        auto it_R = upper_bound(X_P.begin(), X_P.end(), make_pair(R, (uint64_t)-1ull));

        --it_L;
        --it_R;

        cout << it_R->second - it_L->second << endl;
    }

    return 0;
}