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
    
    void setBlock(size_t r, size_t c)
    {
        if (r < N && c < N) {
            grid[r][c] = true;
            probabilities[r][c] = 0.0;
        }
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
    
    for (size_t i = 0; i < N; ++i) {
        size_t center = N / 2;
        if (i % 2 == 0) {
            for (size_t j = 1; j <= N / 2; ++j) {
                size_t y;
                if (j % 2 == 0) {
                    y = center + j;
                } else {
                    y = center - j;
                }            
                
                if (S[i][y] == '.') {
                    cout << i << " " << y << endl;
                    field.setBlock(i, y);
                    field.simulation();
                }
            }
        }else {
            for (size_t j = 0; j <= N / 2; ++j) {
                size_t y;
                if (j % 2 == 0) {
                    y = center - j;
                } else {
                    y = center + j;
                }
                if (S[i][y] == '.') {
                    cout << i << " " << y << endl;
                    field.setBlock(i, y);
                    field.simulation();
                }
            }
        }
    }
    
    vector<tuple<double, size_t, size_t>> positions;
    for (size_t i = N; i > 0; --i) {
        size_t k = i - 1;
        size_t center = N / 2;
        if (k % 2 == 0) {
            for (size_t j = 0; j <= N / 2; ++j) {
                size_t y;
                if (j % 2 == 0) {
                    y = center - j;
                } else {
                    y = center + j;
                }
                if (S[k][y] == '.') {
                    positions.emplace_back(field.probabilities[k][y], k, y);
                }
            }
        } else {
            for (size_t j = 1; j <= N / 2; ++j) {
                size_t y;
                if (j % 2 == 0) {
                    y = center + j;
                } else {
                    y = center - j;
                }            
                
                if (S[k][y] == '.') {
                    positions.emplace_back(field.probabilities[k][y], k, y);
                }
            }
        }
    }
    
    sort(positions.begin(), positions.end());
    
    for (const auto& [prob, r, c] : positions) {
        cout << r << " " << c << endl;
    }
    
    return 0;
}