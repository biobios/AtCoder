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

    uint64_t N;
    cin >> N;
    vector<int64_t> A(N);
    
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }
    vector<int64_t> B(N);
    for (uint64_t i = 0; i < N; ++i)
    {
        cin >> B[i];
    }

    if (N == 1)
    {
        cout << "No" << endl;
        return;
    }
    
    bool isPossible = false;
    size_t difference_index = 0;
    
    for (size_t i = 1; i < N; ++i)
    {
        if (A[0] * B[i] != A[i] * B[0]) {
            isPossible = true;
            difference_index = i;
            break;
        }
    }
    
    if (!isPossible)
    {
        cout << "No" << endl;
        return;
    }
    vector<int64_t> C(N);
    
    if (B[0] * -A[difference_index] + B[difference_index] * A[0] < 0)
    {
        C[0] = -A[difference_index];
        C[difference_index] = A[0];
    } else
    {
        C[0] = A[difference_index];
        C[difference_index] = -A[0];
    }
    
    if (A[0] * -B[difference_index] + A[difference_index] * B[0] > 0)
    {
        C[0] += -B[difference_index];
        C[difference_index] += B[0];
    } else
    {
        C[0] += B[difference_index];
        C[difference_index] += -B[0];
    }
    
    cout << "Yes" << endl;
    
    for (size_t i = 0; i < N; ++i)
    {
        cout << C[i] << " ";
    }
    
    cout << endl;
}

int main()
{
    uint64_t T;
    cin >> T;
    
    for (uint64_t t = 0; t < T; ++t)
    {
        solve();
    }
    
    return 0;
}