#include <iostream>
#include <vector>

using namespace std;

struct Node {
	uint64_t distance = ~0;
	vector<Node*> connection;
	void update(uint64_t a) {
		if (a < distance) {
			distance = a;
			for (size_t i = 0; i < connection.size(); i++) {
				connection[i]->update(distance + 1);
			}
		}
	}
	static void connect(Node* a, Node* b) {
		a->connection.push_back(b);
		b->connection.push_back(a);
	}
};

int main() {
	uint64_t N1, N2, M;
	cin >> N1 >> N2 >> M;

	vector<Node> group1{N1};
	vector<Node> group2{N2};

	for (size_t i = 0; i < M; i++) {
		uint64_t a, b;
		cin >> a >> b;
		if (a <= N1) {
			Node::connect(&group1[a - 1], &group1[b - 1]);
		}
		else {
			Node::connect(&group2[a - N1 - 1], &group2[b - N1 - 1]);
		}
	}

	group1[0].update(0);
	group2[N2 - 1].update(0);

	uint64_t max1 = 0;
	uint64_t max2 = 0;

	for (size_t i = 0; i < N1; i++) {
		if (max1 < group1[i].distance) {
			max1 = group1[i].distance;
		}
	}

	for (size_t i = 0; i < N2; i++) {
		if (max2 < group2[i].distance) {
			max2 = group2[i].distance;
		}
	}

	cout << (max1 + max2 + 1) << endl;

	return 0;
}