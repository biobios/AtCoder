#include <iostream>
#include <queue>
#include <vector>
#include <functional>

int main() {
	std::uint64_t N;
	std::cin >> N;
	
	std::vector<std::vector<char>> grid(N, std::vector<char>(N));

	for (std::size_t i = 0; i < N; i++) {
		for (std::size_t j = 0; j < N; j++) {
			std::cin >> grid[i][j];
		}
	}

	std::vector<std::vector<std::uint64_t>> cost(N, std::vector<std::uint64_t>(N, (std::uint64_t)1 << 62));
	using pii = std::pair<std::uint64_t, std::pair<std::uint64_t, std::uint64_t>>;
	using pq_type = std::priority_queue<pii, std::vector<pii>, std::greater<std::vector<pii>::value_type>>;
	pq_type pq;

	cost[0][0] = 0;
	pq.push({0, {0, 0}});

	std::uint64_t result;

	while (!pq.empty()) {
		auto [c, p] = pq.top();
		pq.pop();

		if (p.first == N - 1 && p.second == N - 1) {
			result = c;
			break;
		}

		// 移動先がRならコストは0、そうでなければ1
		std::uint64_t next_cost = grid[p.first][p.second] == 'R' ? 0 : 1;


		if (p.first > 0 && cost[p.first - 1][p.second] > c + next_cost) {
			cost[p.first - 1][p.second] = c + next_cost;
			pq.push({cost[p.first - 1][p.second], {p.first - 1, p.second}});
		}

		if (p.first < N - 1 && cost[p.first + 1][p.second] > c + next_cost) {
			cost[p.first + 1][p.second] = c + next_cost;
			pq.push({cost[p.first + 1][p.second], {p.first + 1, p.second}});
		}

		if (p.second > 0 && cost[p.first][p.second - 1] > c + next_cost) {
			cost[p.first][p.second - 1] = c + next_cost;
			pq.push({cost[p.first][p.second - 1], {p.first, p.second - 1}});
		}

		if (p.second < N - 1 && cost[p.first][p.second + 1] > c + next_cost) {
			cost[p.first][p.second + 1] = c + next_cost;
			pq.push({cost[p.first][p.second + 1], {p.first, p.second + 1}});
		}

	}

	cost = std::vector<std::vector<std::uint64_t>>(N, std::vector<std::uint64_t>(N, (std::uint64_t)1 << 62));
	pq = pq_type();

	cost[0][N - 1] = 0;
	pq.push({0, {0, N - 1}});

	while (!pq.empty()) {
		auto [c, p] = pq.top();
		pq.pop();

		if (p.first == N - 1 && p.second == 0) {
			result += c;
			break;
		}

		// 移動先がBならコストは0、そうでなければ1
		std::uint64_t next_cost = grid[p.first][p.second] == 'B' ? 0 : 1;

		if (p.first > 0 && cost[p.first - 1][p.second] > c + next_cost) {
			cost[p.first - 1][p.second] = c + next_cost;
			pq.push({cost[p.first - 1][p.second], {p.first - 1, p.second}});
		}

		if (p.first < N - 1 && cost[p.first + 1][p.second] > c + next_cost) {
			cost[p.first + 1][p.second] = c + next_cost;
			pq.push({cost[p.first + 1][p.second], {p.first + 1, p.second}});
		}

		if (p.second > 0 && cost[p.first][p.second - 1] > c + next_cost) {
			cost[p.first][p.second - 1] = c + next_cost;
			pq.push({cost[p.first][p.second - 1], {p.first, p.second - 1}});
		}

		if (p.second < N - 1 && cost[p.first][p.second + 1] > c + next_cost) {
			cost[p.first][p.second + 1] = c + next_cost;
			pq.push({cost[p.first][p.second + 1], {p.first, p.second + 1}});
		}


	}

	std::cout << result << std::endl;

	return 0;

}