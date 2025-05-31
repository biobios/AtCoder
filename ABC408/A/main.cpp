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
    uint64_t N, S;
    cin >> N >> S;
    uint64_t current_time = S;
    for (uint64_t i = 0; i < N; ++i)
    {
        uint64_t T;
        cin >> T;
        if (current_time < T)
        {
            cout << "No" << endl;
            return 0;
        }
        
        current_time = T + S;
    }
    
    cout << "Yes" << endl;
}