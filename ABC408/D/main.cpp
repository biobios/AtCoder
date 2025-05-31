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
    uint64_t T;
    cin >> T;

    for (size_t i = 0; i < T; ++i)
    {
        uint64_t N;
        string S;
        cin >> N >> S;
        vector<size_t> change_indices;
        for (size_t j = 1; j < N; ++j)
        {
            if (S[j] != S[j - 1])
            {
                change_indices.push_back(j);
            }
        }
        
        if (change_indices.size() < 2)
        {
            cout << "0" << endl;
            continue;
        }
        
        vector<uint64_t> change_dp(3, UINT64_MAX);
        if (S[0] == '0')
        {
            change_dp[0] = 0;
            change_dp[1] = change_indices[0];
        } else
        {
            change_dp[0] = change_indices[0];
            change_dp[1] = 0;
        }

        size_t prev_index = change_indices[0];
        for (size_t i = 1; i < change_indices.size(); ++i)
        {
            auto index = change_indices[i];
            
            if (S[prev_index] == '0')
            {
                change_dp[2] = min(change_dp[2], change_dp[1]);
                change_dp[1] += index - prev_index;
            }else{
                change_dp[1] = min(change_dp[1], change_dp[0]);
                change_dp[0] += index - prev_index;
                change_dp[2] += index - prev_index;
            }
            prev_index = index;
        }
        
        if (S[N - 1] == '0')
        {
            change_dp[2] = min(change_dp[2], change_dp[1]);
            change_dp[1] += N - prev_index;
        }else {
            change_dp[1] = min(change_dp[1], change_dp[0]);
            change_dp[0] += N - prev_index;
            change_dp[2] += N - prev_index;
        }
        
        uint64_t result = UINT64_MAX;
        for (size_t j = 0; j < 3; ++j)
        {
            result = min(result, change_dp[j]);
        }
        
        cout << result << endl;

    }
    return 0;
}