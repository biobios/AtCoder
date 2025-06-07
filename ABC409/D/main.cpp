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

void process()
{
    uint64_t N;
    cin >> N;
    string S;
    cin >> S;
    char removed_char = '\0';
    size_t remove_index = 0;
    for (size_t i = 1; i < N; ++i)
    {
        if (S[i - 1] > S[i])
        {
            removed_char = S[i - 1];
            remove_index = i - 1;
            S.erase(i - 1, 1);
            break;
        }
    }
    
    if (removed_char == '\0')
    {
        cout << S << endl;
        return;
    }
    
    for (size_t i = remove_index + 1; i < S.size(); ++i)
    {
        if (S[i] > removed_char)
        {
            // 0 ~ i-1　まで出力
            cout << S.substr(0, i);
            cout << removed_char;
            // i ~ end まで出力
            cout << S.substr(i) << endl;
            return;
        }
    }
    
    cout << S;
    cout << removed_char << endl;
    return;
}

int main()
{
    uint64_t T;
    cin >> T;
    
    for (uint64_t i = 0; i < T; ++i)
    {
        process();
    }
    return 0;
}