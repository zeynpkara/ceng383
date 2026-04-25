#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <limits>
#include <chrono>
#include <sys/resource.h>

using namespace std;

const long long INF = numeric_limits<long long>::max();

double getMemoryUsageMB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return (double)usage.ru_maxrss / (1024.0 * 1024.0);
}

struct Edge {
    int to;
    long long weight;
};

class Graph {
public:
    int V;
    int E;
    vector<vector<Edge>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V + 1);
    }

    void addEdge(int u, int v, long long w) {
        adj[u].push_back({v, w});
    }
};

Graph* loadDIMACSGraph(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file -> " << filename << endl;
        return nullptr;
    }

    string line;
    Graph* graph = nullptr;

    while (getline(file, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (line[0] == 'p') {
            string p, sp;
            int V, E;
            stringstream ss(line);
            ss >> p >> sp >> V >> E;
            graph = new Graph(V);
            graph->E = E;
            cout << "[System] Constructing graph structure: " << V << " nodes..." << endl;
        }
        else if (line[0] == 'a') {
            char a;
            int u, v;
            long long w;
            stringstream ss(line);
            ss >> a >> u >> v >> w;
            if (graph != nullptr) {
                graph->addEdge(u, v, w);
            }
        }
    }
    file.close();
    return graph;
}

void runDijkstra(Graph* graph, int source) {
    int V = graph->V;
    vector<long long> dist(V + 1, INF);
    dist[source] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push({0, source});

    auto start_time = chrono::high_resolution_clock::now();

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph->adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end_time - start_time;
    cout << ">> Dijkstra Runtime: " << duration.count() << " ms" << endl;
}

void runBellmanFord(Graph* graph, int source) {
    int V = graph->V;
    vector<long long> dist(V + 1, INF);
    dist[source] = 0;

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 1; i <= V - 1; ++i) {
        bool relaxed = false;
        for (int u = 1; u <= V; ++u) {
            if (dist[u] == INF) continue;
            for (auto& edge : graph->adj[u]) {
                if (dist[u] + edge.weight < dist[edge.to]) {
                    dist[edge.to] = dist[u] + edge.weight;
                    relaxed = true;
                }
            }
        }
        if (!relaxed) break;
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end_time - start_time;
    cout << ">> Bellman-Ford Runtime: " << duration.count() << " ms" << endl;
}

int main() {
    string datasetFile = "/Users/zeynepkara/Downloads/USA-road-d.FLA.gr";

    cout << "=== SSSP Algorithm Performance Analysis ===" << endl;
    cout << "Initial Memory Usage: " << getMemoryUsageMB() << " MB" << endl;

    Graph* g = loadDIMACSGraph(datasetFile);

    if (g != nullptr) {
        cout << "Memory Usage After Graph Load: " << getMemoryUsageMB() << " MB" << endl;
        cout << "----------------------------------------" << endl;

        runDijkstra(g, 1);
        runBellmanFord(g, 1);

        cout << "----------------------------------------" << endl;
        cout << "Final Memory Usage: " << getMemoryUsageMB() << " MB" << endl;

        delete g;
    }

    return 0;
}