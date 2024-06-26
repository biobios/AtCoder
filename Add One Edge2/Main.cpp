#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <queue> // std::priority_queue
#include <functional> // std::greater

using namespace std;

constexpr long long INF = (1LL << 60);

// 辺の情報
struct Edge
{
	// 行先
	int to;

	// コスト
	int cost;
};

using Graph = vector<vector<Edge>>;

// { distance, from }
using Pair = std::pair<uint64_t, uint64_t>;

// ダイクストラ法 (1.1 基本実装)
// distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
void Dijkstra(const Graph& graph, std::vector<uint64_t>& distances, uint64_t startIndex)
{
	// 「現時点での最短距離, 頂点」の順に取り出す priority_queue
	// デフォルトの priority_queue は降順に取り出すため std::greater を使う
	std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> q;
	q.emplace((distances[startIndex] = 0), startIndex);

	while (!q.empty())
	{
		const long long distance = q.top().first;
		const int from = q.top().second;
		q.pop();

		// 最短距離でなければ処理しない
		if (distances[from] < distance)
		{
			continue;
		}

		// 現在の頂点からの各辺について
		for (const auto& edge : graph[from])
		{
			// to までの新しい距離
			const long long d = (distances[from] + edge.cost);

			// d が現在の記録より小さければ更新
			if (d < distances[edge.to])
			{
				q.emplace((distances[edge.to] = d), edge.to);
			}
		}
	}
}

int main() {
	uint64_t N1, N2, M;
	cin >> N1 >> N2 >> M;

	Graph group1{N1};
	Graph group2{N2};

	for (size_t i = 0; i < M; i++) {
		uint64_t a, b;
		cin >> a >> b;
		
		if (a <= N1) {
			Edge atob;
			atob.cost = 1;
			atob.to = b - 1;
			Edge btoa;
			btoa.cost = 1;
			btoa.to = a - 1;
			group1[a - 1].push_back(atob);
			group1[b - 1].push_back(btoa);
		}
		else {
			Edge atob;
			atob.cost = 1;
			atob.to = b - N1 - 1;
			Edge btoa;
			btoa.cost = 1;
			btoa.to = a - N1 - 1;

			group2[a - N1 - 1].push_back(atob);
			group2[b - N1 - 1].push_back(btoa);
		}
	}

	vector<uint64_t> distances1(N1, INF);
	vector<uint64_t> distances2(N2, INF);

	Dijkstra(group1, distances1, 0);
	Dijkstra(group2, distances2, N2 - 1);

	uint64_t max1 = 0;
	uint64_t max2 = 0;

	for (size_t i = 0; i < N1; i++) {
		if (max1 < distances1[i]) {
			max1 = distances1[i];
		}
	}

	for (size_t i = 0; i < N2; i++) {
		if (max2 < distances2[i]) {
			max2 = distances2[i];
		}
	}

	cout << (max1 + max2 + 1) << endl;

	return 0;
}