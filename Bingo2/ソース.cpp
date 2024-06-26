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
        // :��ǂݔ�΂�
        range_ss.ignore();

        range_ss >> start_minute;
        // -��ǂݔ�΂�
        range_ss.ignore();

        range_ss >> end_hour;
        // :��ǂݔ�΂�
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

        // N��݂Ƃ�
        uint64_t N;
        input_stream >> N;

        // A1 ~ AN��݂Ƃ�
        seat_nums = vector<uint64_t>(N);

        for (size_t i = 0; i < N; i++) {
            input_stream >> seat_nums[i];
        }

        // �c�Ǝ��Ԃ�݂Ƃ�
        string business_hours_str;
        input_stream >> business_hours_str;
        business_hours = new TimeRange(business_hours_str);

        // K��݂Ƃ�
        uint64_t K;
        input_stream >> K;

        business_time_ranges = vector<unique_ptr<TimeRange>>(K);

        // ���ԑ�1 ~ K ��݂Ƃ�
        for (size_t i = 0; i < K; i++) {
            string timerange_str;
            input_stream >> timerange_str;
            business_time_ranges[i] = new TimeRange(timerange_str);
        }
    }
};

int main(int argc, char* argv[]) {
    // ���̃R�[�h�͕W�����͂ƕW���o�͂�p�����T���v���R�[�h�ł��B
    // ���̃R�[�h�͍D���Ȃ悤�ɕҏW�E�폜���Ă�����č\���܂���B
    // ---
    // This is a sample code to use stdin and stdout.
    // Edit and remove this code as you like.



    return 0;
}
