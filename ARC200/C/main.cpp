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
#include <numeric>

using namespace std;

void solve()
{
    uint64_t N;
    cin >> N;
    vector<tuple<size_t, bool>> events(2 * N);
    vector<uint64_t> L(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> L[i];
        events[L[i] - 1] = make_tuple(i, true);
    }
    vector<uint64_t> R(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> R[i];
        events[R[i] - 1 + N] = make_tuple(i, false);
    }
    
    vector<size_t> indices(N);
    iota(indices.begin(), indices.end(), 0);
    
    sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        if (L[b] < L[a] && R[a] < L[b]) {
            return true;
        }
        
        return L[a] < L[b];
    });
    
    vector<size_t> result(N, 0);
    for (size_t i = 0; i < N; ++i)
    {
        result[indices[i]] = i + 1;
    }
    
    for (size_t i = 0; i < N; ++i)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}

int main()
{
    uint64_t T;
    cin >> T;
    for (uint64_t i = 0; i < T; ++i)
    {
        solve();
    }
    return 0;
}