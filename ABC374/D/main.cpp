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
#include <cfloat>
#include <iomanip>

using namespace std;

int main()
{
    uint64_t N;
    cin >> N;

    uint64_t S, T;
    cin >> S >> T;

    vector<tuple<int64_t, int64_t, int64_t, int64_t>> lines(N);

    for (size_t i = 0; i < N; ++i)
    {
        int64_t A, B, C, D;
        cin >> A >> B >> C >> D;

        lines[i] = make_tuple(A, B, C, D);
    }

    double result = DBL_MAX;

    vector<size_t> indices(N);
    for (size_t i = 0; i < N; ++i)
    {
        indices[i] = i;
    }

    do
    {
        double x1 = 0;
        double y1 = 0;
        double distance1 = 0;

        double x2 = 0;
        double y2 = 0;
        double distance2 = 0;

        for (auto i : indices)
        {
            auto [A, B, C, D] = lines[i];

            auto next_distance1 = distance1 + sqrt((A - x1) * (A - x1) + (B - y1) * (B - y1)) / S + sqrt((C - A) * (C - A) + (D - B) * (D - B)) / T;
            next_distance1 = min(next_distance1, distance2 + sqrt((A - x2) * (A - x2) + (B - y2) * (B - y2)) / S + sqrt((C - A) * (C - A) + (D - B) * (D - B)) / T);

            auto next_distance2 = distance1 + sqrt((C - x1) * (C - x1) + (D - y1) * (D - y1)) / S + sqrt((A - C) * (A - C) + (B - D) * (B - D)) / T;
            next_distance2 = min(next_distance2, distance2 + sqrt((C - x2) * (C - x2) + (D - y2) * (D - y2)) / S + sqrt((A - C) * (A - C) + (B - D) * (B - D)) / T);

            x1 = C;
            y1 = D;
            distance1 = next_distance1;

            x2 = A;
            y2 = B;
            distance2 = next_distance2;
        }

        result = min({result, distance1, distance2});
    } while (next_permutation(indices.begin(), indices.end()));

    cout << fixed << setprecision(23);
    cout << result << endl;

    return 0;
}