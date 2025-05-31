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
    vector<int64_t> wall_protected_count(N + 1, 0);

    for (size_t i = 0; i < M; ++i)
    {
        uint64_t L, R;
        cin >> L >> R;
        L--; // Convert to 0-based index
        wall_protected_count[L]++;
        wall_protected_count[R]--;
    }
    
    uint64_t current_protected = 0;
    uint64_t min_protected = UINT64_MAX;
    for (size_t i = 0; i < N; ++i)
    {
        current_protected += wall_protected_count[i];
        if (current_protected < min_protected)
        {
            min_protected = current_protected;
        }
    }
    cout << min_protected << endl;

    return 0;
}