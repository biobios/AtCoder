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

bool isValid(uint64_t num, uint64_t A)
{
    vector<uint64_t> digits;
    while (num > 0) {
        digits.push_back(num % A);
        num /= A;
    }
    
    for (size_t i = 0; i < digits.size() / 2; ++i) {
        if (digits[i] != digits[digits.size() - 1 - i]) {
            return false;
        }
    }

    return true;
}

int main()
{
    uint64_t A, N;
    cin >> A >> N;
    
    uint64_t ans = 0;
    vector<vector<uint64_t>> numbers;
    numbers.reserve(13);
    numbers.push_back({1, 2, 3, 4, 5, 6, 7, 8, 9});
    numbers.push_back({11, 22, 33, 44, 55, 66, 77, 88, 99});
    
    for (size_t i = 1; i < 3; ++i) {
        auto& vec = numbers[i - 1];
        for (auto num : vec) {
            if (num <= N && isValid(num, A)) {
                ans += num;
            } else if (num > N) {
                cout << ans << endl;
                return 0;
            }
        }
    }
    
    for (size_t i = 3; i <= 13; ++i) {
        vector<uint64_t> newNumbers;
        for (uint64_t j = 1; j < 10; ++j) {
            uint64_t m_zero = j * static_cast<uint64_t>(pow(10, i - 1)) + j;
            newNumbers.push_back(m_zero);
            if (m_zero <= N && isValid(m_zero, A)) {
                ans += m_zero;
            } else if (m_zero > N) {
                cout << ans << endl;
                return 0;
            }
            for (size_t k = 1 - (i % 2); k <= i - 3; k += 2) {
                for (uint64_t num : numbers[k]) {
                    uint64_t newNum = j * static_cast<uint64_t>(pow(10, i - 1)) + num * static_cast<uint64_t>(pow(10, (i - (k + 1)) / 2)) + j;
                    newNumbers.push_back(newNum);
                    if (newNum <= N && isValid(newNum, A)) {
                        ans += newNum;
                    } else if (newNum > N) {
                        cout << ans << endl;
                        return 0;
                    }
                }
            }
        }
        
        numbers.push_back(newNumbers);
    }
    
    cout << ans << endl;
    return 0;
    
}