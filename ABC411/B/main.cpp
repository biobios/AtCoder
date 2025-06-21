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
    for (uint64_t i = 0; i < N - 1; ++i) {
        uint64_t a;
        cin >> a;
        A[i + 1] = A[i] + a;
    }
    
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = i + 1; j < N; ++j) {
            cout << A[j] - A[i] << " ";
        }
        cout << endl;
    }
    
    return 0;
}