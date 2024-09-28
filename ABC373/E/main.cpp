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

using namespace std;

int main()
{
    uint64_t N, M, K;
    cin >> N >> M >> K;

    vector<pair<uint64_t, size_t>> A(N);
    uint64_t voted_count = 0;

    for(size_t i = 0; i < N; ++i){
        cin >> A[i].first;
        A[i].second = i;

        voted_count += A[i].first;
    }

    sort(A.begin(), A.end());

    vector<uint64_t> need_votes(N, 0);
    uint64_t rest_of_votes = K - voted_count;

    for(size_t i = N - M; i < N; ++i){

    }
}