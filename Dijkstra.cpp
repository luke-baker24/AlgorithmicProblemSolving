#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Vertex {
    public:
    int value;
    std::unordered_map<Vertex*, int> edges;

    //For pathfinding
    long d;
    Vertex* pi;

    Vertex(int _value) {
        value = _value;

        pi = nullptr;
        d = 1000000000;
    }

    bool operator< (Vertex const& obj) const {
        return this->d < obj.d ? 1 : 0;
    }
};

class Graph {
    public:
    std::vector<Vertex> vertices;

    Graph() {
        vertices = std::vector<Vertex>();
    }
};

// Relax the edge from u to v,
// updating v's shortest path estimate and predecessor
// if travelling through u gives a shorter path.
void relax(Graph g, Vertex* u, Vertex* v) {
    if (v->d > u->d + u->edges.at(v)) {
        v->d = u->d + u->edges.at(v);
        v->pi = u;
    }
}

// Runs Dijkstra's algorithms to compute all SSSP distances
// for directed graph G and source vertex s.
// G must not contain any negative-weight edges, but it may
// contain cycles.
void dijkstra(Graph g, Vertex* s) {
    s->d = 0;

    std::priority_queue<Vertex> Q;

    for (int i = 0; i < g.vertices.size(); i++)
        Q.push(g.vertices[i]);
    
    while (!Q.empty()) {
        Vertex u = Q.top();
        Q.pop();

        for (const auto& edge : u.edges)
            relax(g, &u, edge.first);
    }
}

// Prints the shortest path from source vertex s to vertex v in
// directed graph G.
// Assumes a SSSP algorithm has already terminated.
void printPath(Graph g, Vertex* s, Vertex* v) {
    if (s->value == v->value)  {
        std::cout << s->value << std::endl;
    }
    else if (v->pi == nullptr) {
        std::cout << "Impossible" << std::endl;
    }
    else {
        printPath(g, s, v->pi);
        std::cout << v->value << std::endl;
    }
}

int main() {
    while (true) {
        int nodes, edges, queries, s;
        std::cin >> nodes >> edges >> queries >> s;

        //End case
        if (nodes == 0 && edges == 0 && queries == 0 && s == 0) break;

        Graph graph;

        for (int i = 0; i < nodes; i++) {
            graph.vertices.push_back(Vertex(i));
        }

        for (int i = 0; i < edges; i++) {
            int u, v, w;
            std::cin >> u >> v >> w;

            graph.vertices[u].edges.insert({&graph.vertices[v], w});
        }

        dijkstra(graph, &graph.vertices[s]);

        for (int i = 0; i < queries; i++) {
            int q;
            std::cin >> q;

            printPath(graph, &graph.vertices[s], &graph.vertices[q]);
        }
    }
}