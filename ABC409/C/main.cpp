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
    uint64_t N, L;
    cin >> N >> L;
    vector<uint64_t> D(N - 1);
    for (uint64_t i = 0; i < N - 1; ++i)
    {
        cin >> D[i];
    }
    
    if (L % 3 != 0)
    {
        cout << "0" << endl;
        return 0;
    }
    
    vector<uint64_t> counts(L, 0);
    counts[0] = 1;
    uint64_t current_position = 0;
    for (uint64_t i = 0; i < N - 1; ++i)
    {
        current_position += D[i];
        current_position %= L;
        counts[current_position]++;
    }
    
    uint64_t result = 0;
    uint64_t side_length = L / 3;
    for (uint64_t i = 0; i < side_length; ++i)
    {
        result += counts[i] * counts[(i + side_length)] * counts[(i + 2 * side_length)];
    }
    
    cout << result << endl;
    return 0;
}