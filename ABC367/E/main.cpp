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
    uint64_t N, K;
    cin >> N >> K;

    vector<size_t> X(N);
    vector<uint64_t> A(N);

    for (size_t i = 0; i < N; ++i)
    {
        cin >> X[i];
        X[i]--;
    }

    for (size_t i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    vector<pair<vector<size_t>, size_t>> loops;
    vector<pair<size_t, uint64_t>> loop_position(N, {-1ull, 0});

    vector<uint64_t> result(N, 0);

    for (size_t i = 0; i < N; i++)
    {
        if (loop_position[i].first < loops.size())
            continue;

        map<size_t, size_t> visited;
        size_t current_loop = X[i];
        vector<size_t> loop = {i};

        loop_position[i] = {loops.size(), 0};

        while (!visited.contains(current_loop))
        {
            visited[current_loop] = loop.size();
            loop.push_back(current_loop);
            loop_position[current_loop] = {loops.size(), loop.size() - 1};
            current_loop = X[current_loop];
        }

        loops.push_back({loop, visited[current_loop]});
    }

    for (size_t i = 0; i < N; i++)
    {

        auto &[loop, loop_start] = loops[loop_position[i].first];
        uint64_t loop_size = loop.size() - loop_start;
        auto &[loop_vector, loop_pos] = loop_position[i];

        uint64_t ope_count = K;
        if (loop_pos < loop_start)
        {
            if (ope_count < loop_start - loop_pos)
            {
                result[i] = A[loop[ope_count + loop_pos]];
                continue;
            }
            ope_count -= loop_start - loop_pos;
        }

        ope_count %= loop_size;

        result[i] = A[loop[loop_start + ope_count]];
    }

    for (size_t i = 0; i < N; i++)
    {
        cout << result[i] << " ";
    }

    cout << endl;

    return 0;
}