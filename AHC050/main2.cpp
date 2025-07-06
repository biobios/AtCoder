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
    uint64_t N, M;
    cin >> N >> M;
    
    vector<string> S(N);
    for (uint64_t i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    vector<vector<double>> weight(N, vector<double>(N, 0.0));
    for (size_t i = 0; i < N; ++i) {
        double bias = 1.0 + pow(i / 20.0, 3);
        for (size_t j = 0; j < N; ++j) {
            weight[i][j] = 1.0;
            if (i > 0) {
                weight[i][j] += 1.0 * (S[i - 1][j] == '#');
            }
            
            if (i + 1 < N) {
                weight[i][j] += 1.0 * (S[i + 1][j] == '#');
            }

            if (j > 0) {
                weight[i][j] += 1.0 * (S[i][j - 1] == '#');
            }

            if (j + 1 < N) {
                weight[i][j] += 1.0 * (S[i][j + 1] == '#');
            }
            
            if (i > 0 && j > 0) {
                weight[i][j] += 1.0 * (S[i - 1][j - 1] == '#');
            }
            
            if (i > 0 && j + 1 < N) {
                weight[i][j] += 1.0 * (S[i - 1][j + 1] == '#');
            }

            if (i + 1 < N && j > 0) {
                weight[i][j] += 1.0 * (S[i + 1][j - 1] == '#');
            }

            if (i + 1 < N && j + 1 < N) {
                weight[i][j] += 1.0 * (S[i + 1][j + 1] == '#');
            }
            weight[i][j] /= bias;
        }
    }
    
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
                }
            }
        }
    }
    
    priority_queue<pair<double, pair<size_t, size_t>>, vector<pair<double, pair<size_t, size_t>>>, greater<>> pq;
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
                    pq.push({weight[k][y], {k, y}});
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
                    pq.push({weight[k][y], {k, y}});
                }
            }
        }
    }
    
    while(!pq.empty()) {
        auto [w, pos] = pq.top();
        pq.pop();
        auto [r, c] = pos;
        
        cout << r << " " << c << endl;
    }
    
    return 0;
}