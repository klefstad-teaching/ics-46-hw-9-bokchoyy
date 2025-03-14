#include "dijkstras.h"

struct NodeComparator {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; 
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    
    distances[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, NodeComparator> pq;
    pq.push(make_pair(source, 0));
    
    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();
        
        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] != INF && 
                distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                
                pq.push(make_pair(v, distances[v]));
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (distances[destination] == INF) {
        return path; 
    }
    
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path exists" << endl;
        return;
    }
    
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
    
    cout << "Total cost is " << total << endl;
}