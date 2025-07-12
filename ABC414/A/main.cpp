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
    uint64_t N, L, R;
    
    cin >> N >> L >> R;
    
    size_t count = 0;
    
    for (size_t i = 0; i < N; ++i) {
        uint64_t X, Y;
        cin >> X >> Y;
        
        if (X <= L && R <= Y) {
            count++;
        }
    }
    
    cout << count << endl;
    
    return 0;
}