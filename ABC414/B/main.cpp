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
    string S = "";
    uint64_t length = 0;
    for (size_t i = 0; i < N; ++i) {
        char c;
        uint64_t l;
        cin >> c >> l;
        
        length += l;
        
        if (length > 100) {
            cout << "Too Long" << endl;
            return 0;
        }
        
        for (size_t j = 0; j < l; ++j) {
            S += c;
        }
    }
    
    cout << S << endl;
    return 0;
}