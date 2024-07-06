#include <iostream>
#include <vector>

using namespace std;

class Plan {
private:
	uint64_t paramater_count;
	uint64_t cost;
	vector<uint64_t> paramaters;
public:
	Plan(uint64_t param_count) {
		paramater_count = param_count;
		paramaters = vector<uint64_t>(param_count);
	}

	void load(istream& input) {
		input >> cost;
		for (size_t i = 0; i < paramater_count; i++) {
			input >> paramaters[i];
		}
	}

	uint64_t add(uint64_t& cost, vector<uint64_t>& paramaters) {
		cost += this->cost;
		for (size_t i = 0; i < paramater_count; i++) {
			paramaters[i] += this->paramaters[i];
		}
	}

	uint64_t sub(uint64_t& cost, vector<uint64_t>& paramaters) {
		cost -= this->cost;
		for (size_t i = 0; i < paramater_count; i++) {
			paramaters[i] -= this->paramaters[i];
		}
	}

	bool operator<(const Plan& other) const {
		return cost < other.cost;
	}

	bool operator>(const Plan& other) const {
		return cost > other.cost;
	}
};

int main()
{
	uint64_t N, param_count, P;
	cin >> N >> param_count >> P;

	vector<Plan> plans;

	for (size_t i = 0; i < N; i++) {
		plans.push_back(Plan(param_count));
		plans[i].load(cin);
	}

	uint64_t sum_of_costs = 0;
	vector<uint64_t> paramaters(param_count);

	for (size_t i = 0; i < N; i++) {
		plans[i].add(sum_of_costs, paramaters);
	}

	for (size_t i = 0; i < param_count; i++) {
		if (paramaters[i] < P) {
			cout << -1 << endl;
			return 0;
		}
	}

}