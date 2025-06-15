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

void solve()
{
    uint64_t A1, A2, A3;
    cin >> A1 >> A2 >> A3;
    
    if (A1 + A2 < A3)
    {
        cout << "No" << endl;
        return;
    }
    
    uint64_t X1 = 1;
    uint64_t X2 = 1;
    
    while(log10(X1 * 2) < A1 + 1) {
        X1 *= 2;
    }
    
    while(log10(X2 * 3) < A2 + 1) {
        X2 *= 3;
    }
    
    uint64_t gcd = 1;
    while(!(A3 - 1 <= log10(X1 / gcd * X2) && log10(X1 / gcd * X2) < A3)) {
        
    }
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