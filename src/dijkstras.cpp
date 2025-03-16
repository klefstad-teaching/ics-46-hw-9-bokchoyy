#include "dijkstras.h"

struct NodeComparator {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; 
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    if (G.numVertices <= 0) {
        return vector<int>();
    }
    if (source < 0 || source >= G.numVertices) {
        return vector<int>(G.numVertices, INF);
    }
    
    int n = G.numVertices;
    
    vector<int> distances(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    
    distances[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, NodeComparator> pq;
    pq.push(make_pair(source, 0));
    
    const int MAX_ITERATIONS = 1000000;
    int iterations = 0;
    
    while (!pq.empty() && iterations < MAX_ITERATIONS) {
        iterations++;
        int u = pq.top().first;
        pq.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        
        for (const Edge& edge : G[u]) {
            if (edge.dst < 0 || edge.dst >= n) {
                continue;
            }
            int v = edge.dst;
            int weight = edge.weight;
            
            if (weight < 0) {
                continue;
            }
            if (distances[u] != INF && 
                distances[u] + weight >= 0 &&  
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
    if (previous.empty() || distances.empty() || destination < 0 || 
        destination >= (int)previous.size() || distances[destination] == INF) {
        return path;
    }
    set<int> visited;
    
    for (int v = destination; v != -1; v = previous[v]) {
        if (visited.find(v) != visited.end()) {
            break;  
        }
        
        visited.insert(v);
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << endl << "Total cost is " << total << endl;
        return;
    }
    
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
    
    cout << "Total cost is " << total << endl;
}