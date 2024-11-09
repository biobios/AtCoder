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
    uint64_t N;
    cin >> N;

    string S;
    cin >> S;

    uint64_t digit_sum = 0;

    for (uint64_t i = 0; i < N; ++i)
    {
        uint64_t c_num = S[i] - '0';
        digit_sum += c_num * (i + 1);
    }

    string result = "";
    uint64_t digit = digit_sum;

    for (uint64_t i = N; i > 0; --i)
    {
        char result_char = '0' + (digit_sum % 10);
        result = result_char + result;
        uint64_t carry = digit_sum / 10;
        digit = digit - i * (S[i - 1] - '0');
        digit_sum = digit + carry;
    }

    while (digit_sum > 0)
    {
        char result_char = '0' + (digit_sum % 10);
        result = result_char + result;
        digit_sum /= 10;
    }

    cout << result << endl;

    return 0;
}