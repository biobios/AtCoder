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
    uint64_t N, Q;
    cin >> N >> Q;
    vector<uint64_t> A(N);

    for (size_t i = 0; i < Q; ++i) {
        uint64_t X;
        cin >> X;
        if (X >= 1) {
            A[X - 1] += 1;
            cout << X << " ";
        }else {
            auto it = min_element(A.begin(), A.end());
            *it += 1;
            cout << (it - A.begin() + 1) << " ";
        }
    }
    
    cout << endl;

    return 0;
}