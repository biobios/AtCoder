#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;


class Time {
public:
    uint8_t hour;
    uint8_t minute;

    Time(string time_str) {

        stringstream time_ss(time_str);

        uint64_t buf;
        time_ss >> buf;
        hour = buf;
        // :を読み飛ばす
        time_ss.ignore();

        time_ss >> buf;
        minute = buf;
    }

    Time(istream& time_ss) {
        uint64_t buf;
        time_ss >> buf;
        hour = buf;
        // :を読み飛ばす
        time_ss.ignore();

        time_ss >> buf;
        minute = buf;
    }

    bool lessThan(Time& other) {
        if (hour < other.hour) return true;
        if (hour == other.hour && minute < other.minute) return true;

        return false;
    }

    void print(ostream& output_s) {
        char buf[6];
        sprintf_s(buf, "%02d:%02d", hour, minute);
        output_s << buf;
    }
};

class TimeRange {

public:
    unique_ptr<Time> start_time;
    unique_ptr<Time> end_time;

    TimeRange(string range_str) {

        stringstream range_ss(range_str);

        start_time.reset(new Time(range_ss));

        // -を読み飛ばす
        range_ss.ignore();

        end_time.reset(new Time(range_ss));
    }

    TimeRange(istream& range_ss) {

        start_time.reset(new Time(range_ss));

        // -を読み飛ばす
        range_ss.ignore();

        end_time.reset(new Time(range_ss));
    }

    bool inRange(Time& time) {
        return (!time.lessThan(*start_time)) && time.lessThan(*end_time);
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
        business_hours.reset(new TimeRange(business_hours_str));

        // Kよみとり
        uint64_t K;
        input_stream >> K;

        business_time_ranges = vector<unique_ptr<TimeRange>>(K);

        // 時間帯1 ~ K よみとり
        for (size_t i = 0; i < K; i++) {
            string timerange_str;
            input_stream >> timerange_str;
            business_time_ranges[i].reset(new TimeRange(timerange_str));
        }
    }

    unique_ptr<TimeRange>& getTimeRange(uint64_t range_index) {
        return business_time_ranges[range_index];
    }

    uint64_t getTableCapacity(uint64_t table_index) {
        return seat_nums[table_index];
    }

    uint64_t getTableCount() {
        return seat_nums.size();
    }
};

class Reservations {
public:
    struct ReservationEntry {
        uint64_t Date;
        size_t time_range_index;
        size_t table_index;
        uint64_t reservation_id;
        uint64_t people_count;
    };
private:
    vector<unique_ptr<ReservationEntry>> reservations;
    vector<bool> reservated;
    Restaurant* restaurant;
public:
    Reservations(Restaurant* restaurant) {
        this->restaurant = restaurant;
        reservated = vector<bool>(restaurant->getTableCount(), false);
    }

    bool isReservated(uint64_t table_index) {
        return reservated[table_index];
    }

    void addReservation(ReservationEntry* reservation) {
        reservated[reservation->table_index] = true;
        reservations.push_back(unique_ptr<ReservationEntry>(reservation));
    }

    void printAll(uint64_t current_Date, Time& current_time, ostream& output_stream) {
        for (auto&& reservation : reservations) {
            output_stream << current_Date << " ";
            current_time.print(output_stream);
            output_stream << " table " <<
                reservation->table_index <<
                " = ";

            printID(reservation->reservation_id, output_stream);
            output_stream << endl;
        }
    }

    void clear() {
        reservated = vector<bool>(restaurant->getTableCount(), false);
        reservations.clear();
    }

    static void printID(uint64_t id, ostream& output_stream) {
        char buf[6];
        sprintf_s(buf, "%05d", id);
        output_stream << buf;
    }

};

class ReservationSystem {
    Restaurant* restaurant;
    unique_ptr<Reservations> reservations;
    uint64_t current_date;
    uint64_t current_time_range_index;

    void process_time(uint64_t D, Time& input_time, istream& input_stream, ostream& output_stream) {
        uint64_t x;
        input_stream >> x;

        x--;

        current_date = D;
        current_time_range_index = x;

        //前の時間帯の予約をすべて表示
        reservations->printAll(D, input_time, output_stream);
        //予約をすべて削除
        reservations->clear();
    }

    static constexpr char const* ERROR_CURRENT_SLOT_RESERVATION = "the current slot cannot be specified.";
    static constexpr char const* ERROR_PAST_TIME_RESERVATION = "a past time cannot be specified.";
    static constexpr char const* ERROR_OVER_TABLE_CAPACITY = "the maximum number of people at the table has been exceeded.";
    static constexpr char const* ERROR_RESERVATED_ALREADY = "the table is occupied.";

    void printError(uint64_t D, Time& current_time, const char* message, ostream& output_stream)
    {
        output_stream << D << " ";
        current_time.print(output_stream);
        output_stream << " Error: " << message << endl;
    }

    void printAcceptRequest(uint64_t D, Time& current_time, uint64_t reservation_id, ostream& output_stream) {
        output_stream << D << " ";
        current_time.print(output_stream);
        output_stream << " ";
        Reservations::printID(reservation_id, output_stream);
    }

    void process_issue_specified(uint64_t D, Time input_time, istream& input_stream, ostream& output_stream) {
        uint64_t reservation_id;
        input_stream >> reservation_id;

        uint64_t reservation_date;
        input_stream >> reservation_date;

        uint64_t reservation_time_range_index;
        input_stream >> reservation_time_range_index;

        uint64_t people_count;
        input_stream >> people_count;

        uint64_t table_index;
        input_stream >> table_index;

        unique_ptr<TimeRange>& reservation_time_range = restaurant->getTimeRange(reservation_time_range_index);
        // 現在時刻が、予約時間帯に含まれるなら
        if (reservation_time_range->inRange(input_time)) {
            printError(D, input_time, ERROR_CURRENT_SLOT_RESERVATION, output_stream);
            return;
        }

        // 現在時刻が、予約時間帯の終了時刻および終了時刻以降なら
        if (!input_time.lessThan(*reservation_time_range->end_time)) {
            printError(D, input_time, ERROR_PAST_TIME_RESERVATION, output_stream);
            return;
        }

        // 予約人数がテーブル人数より多いなら
        if (people_count > restaurant->getTableCapacity(table_index)) {
            printError(D, input_time, ERROR_OVER_TABLE_CAPACITY, output_stream);
            return;
        }

        // すでにそのテーブルが予約されているなら
        if (reservations->isReservated(table_index)) {
            printError(D, input_time, ERROR_RESERVATED_ALREADY, output_stream);
            return;
        }

        Reservations::ReservationEntry* reservation = new Reservations::ReservationEntry();
        reservation->Date = D;
        reservation->time_range_index = reservation_time_range_index;
        reservation->table_index = table_index;
        reservation->reservation_id = reservation_id;
        reservation->people_count = people_count;

        reservations->addReservation(reservation);
        printAcceptRequest(D, input_time, reservation_id, output_stream);

    }

public:
    ReservationSystem(Restaurant* restaurant) {
        this->restaurant = restaurant;
        reservations.reset(new Reservations(restaurant));
    }

    void run(istream& input_stream, ostream& output_stream) {
        // eofまで繰り返す
        while (input_stream.peek() != istream::traits_type::eof()) {
            uint64_t D;
            input_stream >> D;

            input_stream.ignore();

            Time input_time(input_stream);

            string signature;
            cin >> signature;

            if (signature == "time") {
                process_time(D, input_time, input_stream, output_stream);
            }
            else if (signature == "issue-specified") {
                process_issue_specified(D, input_time, input_stream, output_stream);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    // このコードは標準入力と標準出力を用いたサンプルコードです。
    // このコードは好きなように編集・削除してもらって構いません。
    // ---
    // This is a sample code to use stdin and stdout.
    // Edit and remove this code as you like.

    Restaurant restaurant(cin);

    ReservationSystem reservation_system(&restaurant);

    reservation_system.run(cin, cout);

    return 0;
}
