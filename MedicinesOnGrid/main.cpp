#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <set>


constexpr std::array<std::pair<std::int64_t, std::int64_t>, 4> directions = { { {0, 1}, {0, -1}, {1, 0}, {-1, 0} } };

int main()
{
	std::uint64_t H, W;
	std::cin >> H >> W;
	std::vector<std::vector<char>> grid(H, std::vector<char>(W));
	std::pair<std::uint64_t, std::uint64_t> goal;

	for (std::uint64_t i = 0; i < H; ++i)
	{
		for (std::uint64_t j = 0; j < W; ++j)
		{
			std::cin >> grid[i][j];
			if (grid[i][j] == 'T')
			{
				goal = std::make_pair(i, j);
			}
		}
	}

	std::uint64_t N;
	std::cin >> N;
	std::vector<std::array<std::uint64_t, 3>> medicines(N + 1);
	medicines[N] = { goal.first, goal.second, 0 };

	std::size_t start_index = N;
	std::size_t end_index = N;

	for (std::uint64_t i = 0; i < N; ++i)
	{
		std::uint64_t R, C;
		std::cin >> R >> C >> medicines[i][2];

		medicines[i][0] = R - 1;
		medicines[i][1] = C - 1;

		if (grid[medicines[i][0]][medicines[i][1]] == 'S')
		{
			start_index = i;
		}
	}

	if (start_index == N)
	{
		std::cout << "No" << std::endl;
		return 0;
	}

	std::set<std::uint64_t> not_visited;
	for (std::uint64_t i = 0; i <= N; ++i)
	{
		not_visited.insert(i);
	}

	//start_index delete
	not_visited.erase(start_index);

	std::stack<std::uint64_t> visited;
	visited.push(start_index);

	while (!visited.empty()) {
		std::uint64_t current = visited.top();
		visited.pop();

		std::vector<std::vector<std::int64_t>> distances(H, std::vector<std::int64_t>(W, -1));
		distances[medicines[current][0]][medicines[current][1]] = medicines[current][2];
		std::queue<std::pair<std::uint64_t, std::uint64_t>> q;
		q.push({ medicines[current][0], medicines[current][1] });
		while (!q.empty()) {
			auto [x, y] = q.front();
			q.pop();

			std::uint64_t next_distance = distances[x][y] - 1;
			bool do_push = next_distance != 0;
			
			for (auto [dx, dy] : directions)
			{
				std::uint64_t nx = x + dx;
				std::uint64_t ny = y + dy;
				if (nx < H && ny < W && grid[nx][ny] != '#' && distances[nx][ny] == -1)
				{
					distances[nx][ny] = next_distance;
					if(do_push)q.push({ nx, ny });
				}
			}
		}

		for (auto it = not_visited.begin(); it != not_visited.end();) {
			std::uint64_t next = *it;
			if (distances[medicines[next][0]][medicines[next][1]] != -1) {
				visited.push(next);
				it = not_visited.erase(it);
			}
			else {
				++it;
			}
		}

		if (!not_visited.contains(end_index)) {
			std::cout << "Yes" << std::endl;
			return 0;
		}
	}

	std::cout << "No" << std::endl;
	return 0;
}