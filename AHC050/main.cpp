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
                    cout << k << " " << y << endl;
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
                    cout << k << " " << y << endl;
                }
            }
        }
    }
    
    return 0;
}