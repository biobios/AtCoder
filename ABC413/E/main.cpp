#include <iostream>
#include <vector>
#include <array>
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
#include <cstdint>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int64_t value;
    size_t size = 1;
    
    Node(int64_t val) : left(nullptr), right(nullptr), value(val) {}
    Node(Node* n1, Node* n2) {
        if (n1->value < n2->value) {
            left = n1;
            right = n2;
        } else {
            left = n2;
            right = n1;
        }
        
        value = left->value;
        size = left->size + 1;
    }
    
    void print() const {
        if (left == nullptr || right == nullptr) {
            cout << value << " ";
        } else {
            left->print();
            right->print();
        }
    }

    ~Node() {
        delete left;
        delete right;
    }
};

void solve()
{
    uint64_t N;
    cin >> N;
    
    size_t pow2N = pow(2, N);

    stack<Node*> nodes;

    for (size_t i = 0; i < pow2N; ++i) {
        uint64_t P;
        cin >> P;
        
        auto node = new Node(P);

        while (!nodes.empty() && nodes.top()->size == node->size) {
            auto topNode = nodes.top();
            nodes.pop();
            node = new Node(topNode, node);
        }
        
        nodes.push(node);
    }
    
    auto root = nodes.top();
    nodes.pop();
    root->print();
    cout << endl;
}

int main()
{
    uint64_t T;
    cin >> T;

    for (uint64_t i = 0; i < T; ++i) {
        solve();
    }

    return 0;
}