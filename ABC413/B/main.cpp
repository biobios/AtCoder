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

    vector<string> S(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    set<string> unique_strings;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i == j) continue;

            string combined = S[i] + S[j];
            unique_strings.insert(combined);
        }
    }
    
    cout << unique_strings.size() << endl;
    return 0;
}