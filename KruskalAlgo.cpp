#include <iostream>
#include <math.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
//#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

struct node
{
    int u;
    int v;
    int wt;
    node(int first, int second, int weight)
    {
        u = first;
        v = second;
        wt = weight;
    }
};

bool mycomp(node a, node b)
{
    return a.wt < b.wt;
}

int findpar(int a, vector<int> &parent)
{
    if (a == parent[a])
    {
        return a;
    }
    return parent[a] = findpar(parent[a], parent);
}
void uni(int u, int v, vector<int> &rank, vector<int> &parent)
{
    u = findpar(u, parent);
    v = findpar(v, parent);
    if (rank[v] < rank[u])
    {
        parent[v] = u;
    }
    else if (rank[v] > rank[u])
    {
        parent[u] = v;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}
int main()
{
    
    
    int n, m;
    cin >> n >> m;
    vector<node> edges;
    vector<int> parent(n+1);
    vector<int> rank(n+1, 0);
    vector<pair<int, int>> mst;
    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges.push_back(node(u, v, wt));
    }
    sort(edges.begin(), edges.end(), mycomp);
    int cost = 0;
    for (auto x : edges)
    {
        if (findpar(x.u, parent) != findpar(x.v, parent))
        {
            cost += x.wt;
            mst.push_back({x.u, x.v});
            uni(x.u, x.v, rank, parent);         
        }
    }
    cout << cost << "\n";
    for (auto it : mst)
    {
        cout << it.first << "->" << it.second << "\n";
    }

    return 0;
}
