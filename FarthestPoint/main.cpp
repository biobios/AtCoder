#include <iostream>
#include <vector>
#include <cmath>

double distance(std::pair<double, double> p1, std::pair<double, double> p2)
{
	return std::sqrt(std::pow(p1.first - p2.first, 2) + std::pow(p1.second - p2.second, 2));
}

int main()
{
	std::uint64_t N;
	std::cin >> N;
	std::vector<std::pair<double, double>> points(N);
	for (std::uint64_t i = 0; i < N; i++)
	{
		std::cin >> points[i].first >> points[i].second;
	}

	for (std::size_t i = 0; i < N; i++) {
		std::size_t farthest_point = 0;
		double max_distance = 0;
		for (std::size_t j = 0; j < N; j++) {
			double d = distance(points[i], points[j]);
			if (d > max_distance) {
				max_distance = d;
				farthest_point = j;
			}
		}
		std::cout << farthest_point + 1 << std::endl;
	}
	return 0;
}