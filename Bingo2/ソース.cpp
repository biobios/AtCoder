#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

class TimeRange {
    uint8_t start_hour;
    uint8_t start_minute;
    uint8_t end_hour;
    uint8_t end_minute;
public:
    TimeRange(string range_str) {
        stringstream range_ss(range_str);

        range_ss >> start_hour;
        // :を読み飛ばす
        range_ss.ignore();

        range_ss >> start_minute;
        // -を読み飛ばす
        range_ss.ignore();

        range_ss >> end_hour;
        // :を読み飛ばす
        range_ss.ignore();

        range_ss >> end_minute;
    }
};

class Restaurant {
    vector<uint64_t> seat_nums;
    unique_ptr<TimeRange> business_hours;
    vector<unique_ptr<TimeRange>> business_time_ranges;
public:
    Restaurant(istream& input_stream) {

        // Nよみとり
        uint64_t N;
        input_stream >> N;

        // A1 ~ ANよみとり
        seat_nums = vector<uint64_t>(N);

        for (size_t i = 0; i < N; i++) {
            input_stream >> seat_nums[i];
        }

        // 営業時間よみとり
        string business_hours_str;
        input_stream >> business_hours_str;
        business_hours = new TimeRange(business_hours_str);

        // Kよみとり
        uint64_t K;
        input_stream >> K;

        business_time_ranges = vector<unique_ptr<TimeRange>>(K);

        // 時間帯1 ~ K よみとり
        for (size_t i = 0; i < K; i++) {
            string timerange_str;
            input_stream >> timerange_str;
            business_time_ranges[i] = new TimeRange(timerange_str);
        }
    }
};

int main(int argc, char* argv[]) {
    // このコードは標準入力と標準出力を用いたサンプルコードです。
    // このコードは好きなように編集・削除してもらって構いません。
    // ---
    // This is a sample code to use stdin and stdout.
    // Edit and remove this code as you like.



    return 0;
}
