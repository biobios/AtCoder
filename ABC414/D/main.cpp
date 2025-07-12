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
#include <cstdint>

using namespace std;

int main()
{
    uint64_t N, M;
    cin >> N >> M;
    vector<uint64_t> X(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> X[i];
    }
    
    sort(X.begin(), X.end());
    vector<tuple<uint64_t, uint64_t, uint64_t>> distances;
    for (size_t i = 1; i < N; ++i) {
        distances.emplace_back(X[i] - X[i - 1], X[i - 1], X[i]);
    }
    
    sort(distances.rbegin(), distances.rend());
    uint64_t ans = X[N - 1] - X[0];
    
    for (size_t i = 0; i < M - 1; ++i) {
        ans -= get<0>(distances[i]);
    }
    
    cout << ans << endl;
    return 0;
}