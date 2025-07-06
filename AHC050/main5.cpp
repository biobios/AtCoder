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

struct Field {
    vector<vector<bool>> grid;
    vector<vector<double>> probabilities;
    size_t N;
    
    Field(size_t n, const vector<string>& S)
        : N(n), grid(n, vector<bool>(n, false)), probabilities(n, vector<double>(n, 0.0))
    {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (S[i][j] == '#') {
                    grid[i][j] = true;
                } else {
                    probabilities[i][j] = 1.0;
                }
            }
        }
    }
    
    double setBlock(size_t r, size_t c)
    {
        double ret = 0;
        if (r < N && c < N) {
            grid[r][c] = true;
            ret = probabilities[r][c];
            probabilities[r][c] = 0.0;
        }
        
        return ret;
    }
    
    void simulation()
    {
        vector<vector<double>> nextProbabilities(N, vector<double>(N, 0.0));
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (grid[i][j]) continue;
                
                double prob = probabilities[i][j];
                size_t r;
                size_t c;
                for (r = i; r < N - 1; ++r) {
                    if (grid[r + 1][j]) break;
                }
                nextProbabilities[r][j] += prob / 4.0;
                for (r = i; r > 0; --r) {
                    if (grid[r - 1][j]) break;
                }
                nextProbabilities[r][j] += prob / 4.0;
                for (c = j; c < N - 1; ++c) {
                    if (grid[i][c + 1]) break;
                }
                nextProbabilities[i][c] += prob / 4.0;
                for (c = j; c > 0; --c) {
                    if (grid[i][c - 1]) break;
                }
                nextProbabilities[i][c] += prob / 4.0;
            }
        }
        
        probabilities = move(nextProbabilities);
    }
};

int main()
{
    uint64_t N, M;
    cin >> N >> M;
    
    vector<string> S(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    Field field(N, S);
    field.simulation();
    
    for (size_t i = 0; i < N * 2 - 1; i += 2) {
        Field copyField = field;
        double prob = 0.0;
        for (size_t j = max(0l, (int64_t)(i - N + 1)); j <= i && j < N; ++j) {
            size_t r = i - j;
            size_t c = j;
            if (S[r][c] == '.') {
                prob += copyField.setBlock(r, c);
                copyField.simulation();
            }
        }     
        copyField = field;
        double prob2 = 0.0;
        for (size_t j = max(0l, (int64_t)(i - N + 1)); j <= i && j < N; ++j) {
            size_t r = i - j;
            size_t c = j;
            size_t temp = r;
            r = c;
            c = temp;
            if (S[r][c] == '.') {
                prob2 += copyField.setBlock(r, c);
                copyField.simulation();
            }
        } 
        
        if (prob2 < prob) {
            for (size_t j = max(0l, (int64_t)(i - N + 1)); j <= i && j < N; ++j) {
                size_t r = i - j;
                size_t c = j;
                size_t temp = r;
                r = c;
                c = temp;
                if (S[r][c] == '.') {
                    cout << r << " " << c << endl;
                    field.setBlock(r, c);
                    field.simulation();
                }
            }
        } else {
            for (size_t j = max(0l, (int64_t)(i - N + 1)); j <= i && j < N; ++j) {
                size_t r = i - j;
                size_t c = j;
                if (S[r][c] == '.') {
                    cout << r << " " << c << endl;
                    field.setBlock(r, c);
                    field.simulation();
                }
            }
        }
    }
    // 確率が低い順
    vector<tuple<double, size_t, size_t>> positions;
    for (size_t i = N * 2 - 2; i > 0; i -= 2) {
        size_t k = i - 1;
        for (size_t j = max(0l, (int64_t)(k - N + 1)); j <= k && j < N; ++j) {
            size_t r = k - j;
            size_t c = j;
            if (S[r][c] == '.') {
                // cout << r << " " << c << endl;
                positions.emplace_back(field.probabilities[r][c], r, c);
            }
        }        
    }
    
    sort(positions.begin(), positions.end());
    for (const auto& [prob, r, c] : positions) {
        cout << r << " " << c << endl;
    }
    
    return 0;
}