#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

class Vertex {
    public:
    int value;

    // Maps vertex ID to edge weight
    std::vector<std::pair<int, int>> edges;

    // For pathfinding
    long d;
    std::vector<int> pi;

    Vertex(int _value) {
        this->value = _value;

        this->d = 1000000000;
    }
};

class Graph {
    public:
    std::vector<Vertex> vertices;

    Graph() {
        vertices = std::vector<Vertex>();
    }
};

struct VertexComparator {
    bool operator()(const std::pair<long, Vertex*>& a, const std::pair<long, Vertex*>& b) const {
        return a.first > b.first;
    }
};

// Runs Dijkstra's algorithms to compute all SSSP distances
// for directed graph G and source vertex s.
// G must not contain any negative-weight edges, but it may
// contain cycles.
void dijkstra(Graph* graph, Vertex* s) {
    s->d = 0;
    
    std::priority_queue<std::pair<long, Vertex*>, std::vector<std::pair<long, Vertex*>>, VertexComparator> Q;
    std::set<int> S;

    Q.push({s->d, s});
    
    while (!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();

        if (S.find(u->value) != S.end())
            continue;

        for (std::pair<int, int> edge : u->edges) {
            if (graph->vertices[edge.first].d < u->d + edge.second) continue;

            //New shortest path, reset
            if (graph->vertices[edge.first].d > u->d + edge.second)
                graph->vertices[edge.first].pi.clear();

            graph->vertices[edge.first].d = u->d + edge.second;

            Q.push({graph->vertices[edge.first].d, &graph->vertices[edge.first]});

            graph->vertices[edge.first].pi.push_back(u->value);
        }
        
        S.insert(u->value);
    }
}

// Prints the shortest path from source vertex s to vertex v in
// directed graph G.
// Assumes a SSSP algorithm has already terminated.
// void printPath(Vertex* s, Vertex* v, int runningSum) {
//     if (v->d == 1000000000) 
//         std::cout << "Impossible" << std::endl;
    
//     else 
//         std::cout << v->d << std::endl;
// }
int printPath(Graph* g, int s, int v) {
    int sum = 0;

    //End of the line
    if (v == s) 
        return 0;
    
    //Keep going
    else {
        std::cout << "_" << v << " ";

        for (int i = 0; i < g->vertices[v].pi.size(); i++) {
            std::cout << g->vertices[v].pi[i] << " ";

            sum += g->vertices[v].edges[g->vertices[v].pi[i]].second;

            sum += printPath(g, s, g->vertices[v].pi[i]);
        }
    }
    
    return sum;
}

int main() {
    int nodes, edges;
    std::cin >> nodes >> edges;

    Graph graph;

    for (int i = 0; i < nodes; i++)
        graph.vertices.push_back(Vertex(i));

    for (int i = 0; i < edges; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;

        graph.vertices[u].edges.push_back(std::pair<int, int>(v, w * 2));
        graph.vertices[v].edges.push_back(std::pair<int, int>(u, w * 2));
    }

    Vertex* source = &graph.vertices[0];

    dijkstra(&graph, source);

    std::cout << printPath(&graph, 0, nodes - 1);

    // printPath(source, &graph.vertices[nodes - 1], 0);

    // for (int i = 0; i < graph.vertices.size(); i++) {
    //     std::cout << graph.vertices[i].d << std::endl;
    // }
}