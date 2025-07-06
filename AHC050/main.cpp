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
    
    vector<string> S(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i % 2; j < N; j += 2) {
            if (S[i][j] == '.') {
                cout << i << " " << j << endl;
            }
        }
    }
    for (size_t k = N; k > 0; --k) {
        size_t i = k - 1;
        for (size_t j = (i + 1) % 2; j < N; j += 2) {
            if (S[i][j] == '.') {
                cout << i << " " << j << endl;
            }
        }
    }
    
    return 0;
}