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
    uint64_t sum = 0;
    for (size_t i = 0; i < N; ++i) {
        uint64_t A;
        cin >> A;
        sum += A;
    }
    
    if (sum <= M) {
        cout << "Yes" << endl;
    }else {
        cout << "No" << endl;
    }
    
    return 0;
}