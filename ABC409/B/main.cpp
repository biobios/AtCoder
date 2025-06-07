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
    uint64_t N;
    cin >> N;
    vector<uint64_t> A(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }
    
    uint64_t count_max = 0;
    
    for (uint64_t i = 1; i <= N; ++i)
    {
        uint64_t count = 0;
        for (uint64_t j = 0; j < N; ++j)
        {
            if (A[j] >= i)
            {
                count++;
            }
        }
        
        if (count >= i)
        {
            count_max = i;
        }
    }
    
    cout << count_max << endl;
    return 0;
}