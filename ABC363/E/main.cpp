#include <iostream>
#include <vector>
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

using namespace std;

class Node
{
public:
    Node *parent = nullptr;
    uint64_t rank = 0;
    uint64_t size = 1;
    uint64_t height = 0;

public:
    Node *getParent(vector<Node *> *nodeList)
    {

        if (parent == nullptr)
        {
            for (auto &&n : *nodeList)
            {
                n->parent = this;
            }
            return this;
        }

        nodeList->push_back(this);
        return parent->getParent(nodeList);
    }

    static Node *Union(Node *a, Node *b)
    {
        vector<Node *> nodeList;
        auto aRoot = a->getParent(&nodeList);
        nodeList.clear();
        auto bRoot = b->getParent(&nodeList);

        if (aRoot->rank > bRoot->rank)
        {
            bRoot->parent = aRoot;
            aRoot->size += bRoot->size;
            return aRoot;
        }
        else if (aRoot->rank < bRoot->rank)
        {
            aRoot->parent = bRoot;
            bRoot->size += aRoot->size;
            return bRoot;
        }
        else if (aRoot != bRoot)
        {
            aRoot->parent = bRoot;
            bRoot->rank++;
            bRoot->size += aRoot->size;
            return bRoot;
        }

        return aRoot;
    }
};

int main()
{
    uint64_t H, W, Y;
    cin >> H >> W >> Y;
    vector<pair<uint64_t, pair<uint64_t, uint64_t>>> A;
    map<pair<uint64_t, uint64_t>, Node *> nodes;
    Node *ocean = new Node();
    ocean->size = 0;

    for (size_t i = 0; i < H; i++)
    {
        for (size_t j = 0; j < W; j++)
        {
            uint64_t a;
            cin >> a;
            A.push_back({a, {i, j}});
            nodes[{i, j}] = new Node();
            nodes[{i, j}]->height = a;
        }
    }

    sort(A.begin(), A.end());

    size_t index = 0;
    uint64_t land = H * W;
    for (size_t i = 1; i <= Y; i++)
    {
        while (index < A.size() && A[index].first <= i)
        {
            auto [a, position] = A[index];
            auto [x, y] = position;
            auto node = nodes[{x, y}];

            if (x == 0 || x == H - 1 || y == 0 || y == W - 1)
            {
                node = Node::Union(ocean, node);
                ocean = node;
            }

            // 上下左右がi以下の場合、Unionする
            if (x > 0 && nodes[{x - 1, y}]->height <= i)
            {
                node = Node::Union(node, nodes[{x - 1, y}]);
            }
            if (x < H - 1 && nodes[{x + 1, y}]->height <= i)
            {
                node = Node::Union(node, nodes[{x + 1, y}]);
            }
            if (y > 0 && nodes[{x, y - 1}]->height <= i)
            {
                node = Node::Union(node, nodes[{x, y - 1}]);
            }
            if (y < W - 1 && nodes[{x, y + 1}]->height <= i)
            {
                node = Node::Union(node, nodes[{x, y + 1}]);
            }

            nodes[{x, y}] = node;

            index++;
        }

        vector<Node *> nodeList;
        ocean = ocean->getParent(&nodeList);

        cout << land - ocean->size << endl;
    }

    return 0;
}