#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Edge
{
    size_t from;
    size_t to;
    long long weight;

    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};

size_t myFind(size_t x, vector<size_t>& parent)
{
    if (x == parent[x])
        return x;

    return parent[x] = myFind(parent[x], parent);
}

bool myUnion(size_t x, size_t y, vector<size_t>& parent, vector<size_t>& depth, vector<long long>& weights, long long weight)
{
    size_t p1 = myFind(x, parent);
    size_t p2 = myFind(y, parent);
    if (p1 == p2)
    {
        return false;
    }

    if (depth[p1] > depth[p2])
    {
        swap(p1, p2);
    }
    else if (depth[p1] == depth[p2])
    {
        depth[p2]++;
    }

    parent[p1] = p2;
    weights[p2] = max(max(weights[p2],weights[p1]), weight);

    return true;
}

void solve()
{
    size_t V, E, K;
    cin >> V >> E >> K;

    vector<Edge> edges(E);
    for (size_t i = 0; i < E; i++)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }

    vector<size_t> depth(V, 0);
    vector<size_t> parent(V);
    vector<long long> weights(V, 0);
    for (size_t i = 0; i < V; i++)
    {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end());

    size_t components = V;

    for (auto& edge : edges)
    {
        if (components == K)
        {
            break;
        }

        if (myUnion(edge.from, edge.to, parent, depth, weights, edge.weight))
        {
            components--;

        }
    }

    unordered_map<size_t, long long> map;
    for (size_t i = 0; i < V; i++)
    {
        size_t label = myFind(i, parent);
        if (map.count(label) == 0)
        {
            map[label] = weights[label];
        }
    }

    vector<long long> values;
    for (auto& kvp: map)
    {
        values.push_back(kvp.second);
    }
    sort(values.begin(), values.end());

    for (auto& value: values)
    {
        std::cout << value << ' ';
    }

    cout << endl;
}

int main()
{
    solve();
}