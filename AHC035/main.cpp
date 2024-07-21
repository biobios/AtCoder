#include <iostream>
#include <vector>
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
#include <sstream>

using namespace std;

stringstream *ss;

bool less_than(pair<vector<uint64_t>, size_t> a, pair<vector<uint64_t>, size_t> b)
{

    uint64_t a_sum = 0;
    uint64_t b_sum = 0;

    for (auto aa : a.first)
    {
        a_sum += aa;
    }

    for (auto bb : b.first)
    {
        b_sum += bb;
    }

    return a_sum < b_sum;
}

uint64_t inner_product(vector<uint64_t> &a, vector<uint64_t> &b)
{
    uint64_t sum = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

double standard_deviation(vector<uint64_t> &a, vector<uint64_t> &b)
{
    double sum1 = 0;
    double sum2 = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
        sum1 += a[i] * a[i] + b[i] * b[i];
        sum2 += (a[i] + b[i]) * (a[i] + b[i]);
    }

    sum1 /= 2;
    sum2 /= 4;

    return sqrt(sum1 - sum2);
}

uint64_t sum(vector<uint64_t> &a)
{
    uint64_t sum = 0;
    for (auto aa : a)
    {
        sum += aa;
    }
    return sum;
}

void write_and_read(vector<vector<pair<vector<uint64_t>, size_t>>> &grid, vector<pair<vector<uint64_t>, size_t>> &A)
{

    uint64_t N, M;

    N = grid.size();
    M = grid[0][0].first.size();

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            cout << grid[i][j].second << " ";
        }
        cout << endl;
    }
    cout.flush();

    A.clear();

    for (size_t i = 0; i < 2 * N * (N - 1); i++)
    {
        vector<uint64_t> a(M);
        for (auto &aa : a)
        {
            cin >> aa;
        }
        A.push_back({a, i});
    }

    // テスト用

    // if (ss == nullptr)
    // {
    //     ss = new stringstream();
    // }

    // for (size_t i = 0; i < N; i++)
    // {
    //     for (size_t j = 0; j < N; j++)
    //     {
    //         *ss << grid[i][j].second << " ";
    //     }
    //     *ss << endl;
    // }

    // size_t current_size = 0;

    // A.clear();

    // for (size_t i = 0; i < N; i++)
    // {
    //     for (size_t j = 0; j < N - 1; j++)
    //     {
    //         string u;
    //         cin >> u;

    //         vector<uint64_t> a(M);

    //         for (size_t k = 0; k < M; k++)
    //         {
    //             if (u[k] == '0')
    //             {
    //                 a[k] = grid[i][j].first[k];
    //             }
    //             else
    //             {
    //                 a[k] = grid[i][j + 1].first[k];
    //             }
    //         }

    //         A.push_back({a, current_size});
    //         current_size++;
    //     }
    // }

    // for (size_t i = 0; i < N - 1; i++)
    // {
    //     for (size_t j = 0; j < N; j++)
    //     {
    //         string u;
    //         cin >> u;

    //         vector<uint64_t> a(M);

    //         for (size_t k = 0; k < M; k++)
    //         {
    //             if (u[k] == '0')
    //             {
    //                 a[k] = grid[i][j].first[k];
    //             }
    //             else
    //             {
    //                 a[k] = grid[i + 1][j].first[k];
    //             }
    //         }

    //         A.push_back({a, current_size});
    //         current_size++;
    //     }
    // }
}

constexpr double STANDARD_DEVIATION_MULTIPLIER = 5.0;

int main()
{
    uint64_t N, M, T;
    cin >> N >> M >> T;

    uint64_t middle = (N - 1) / 2;

    vector<pair<vector<uint64_t>, size_t>> A;

    for (size_t i = 0; i < 2 * N * (N - 1); i++)
    {
        vector<uint64_t> a(M);
        for (size_t j = 0; j < M; j++)
        {
            cin >> a[j];
        }
        A.push_back({a, i});
    }

    vector<vector<pair<vector<uint64_t>, size_t>>> grid(N, vector<pair<vector<uint64_t>, size_t>>(N));

    for (size_t turn = 0; turn < T; turn++)
    {
        sort(A.begin(), A.end(), less_than);

        for (size_t i = 0; i < N; i++)
        {
            size_t index;
            if (i % 2 == 1)
            {
                index = middle + (i + 1) / 2;
            }
            else
            {
                index = middle - i / 2;
            }

            grid[middle][index] = A.back();
            A.pop_back();
        }

        size_t i = 1;
        size_t j = 0;
        while (i < N && j < N)
        {
            size_t index_x, index_y;

            if (j % 2 == 1)
            {
                index_x = middle + (j + 1) / 2;
            }
            else
            {
                index_x = middle - j / 2;
            }

            if (i % 2 == 1)
            {
                index_y = middle + (i + 1) / 2;
                uint64_t sum_a = sum(grid[index_y - 1][index_x].first);

                double current_max = 0;
                size_t current_index = 0;

                for (size_t i = 0; i < A.size(); i++)
                {
                    auto &&a = A[i];
                    uint64_t sum_b = sum(a.first);
                    double ave = (sum_a + sum_b) / 2;
                    double sd = standard_deviation(grid[index_y - 1][index_x].first, a.first);
                    double val = ave + sd * STANDARD_DEVIATION_MULTIPLIER;
                    if (val > current_max)
                    {
                        current_max = val;
                        current_index = i;
                    }
                }

                grid[index_y][index_x] = A[current_index];
                A.erase(A.begin() + current_index);

                if (i == N - 1)
                {
                    j++;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                index_y = middle - i / 2;
                uint64_t sum_a = sum(grid[index_y + 1][index_x].first);

                double current_max = 0;
                size_t current_index = 0;

                for (size_t i = 0; i < A.size(); i++)
                {
                    auto &&a = A[i];
                    uint64_t sum_b = sum(a.first);
                    double ave = (sum_a + sum_b) / 2;
                    double sd = standard_deviation(grid[index_y + 1][index_x].first, a.first);
                    double val = ave + sd * STANDARD_DEVIATION_MULTIPLIER;
                    if (val > current_max)
                    {
                        current_max = val;
                        current_index = i;
                    }
                }

                grid[index_y][index_x] = A[current_index];
                A.erase(A.begin() + current_index);

                if (j >= N - 1)
                {
                    i++;
                    j = 0;
                }
                else
                {
                    i--;
                    j++;
                }
            }
        }

        write_and_read(grid, A);
    }

    if (ss != nullptr)
    {
        cout << ss->str() << endl;
    }

    return 0;
}