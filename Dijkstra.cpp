#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Vertex {
    public:
    int value;

    //Maps vertex ID to edge weight
    std::unordered_map<int, int> edges;

    //For pathfinding
    long d;

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

// Runs Dijkstra's algorithms to compute all SSSP distances
// for directed graph G and source vertex s.
// G must not contain any negative-weight edges, but it may
// contain cycles.
void dijkstra(Graph* graph, int s) {
    //The distance to source is 0
    graph->vertices[s] = 0;
    
    //Storing (distance, vertex ID) pairs
    std::priority_queue<std::pair<int, int>> Q;

    //Storing (vertex ID, visited) pairs
    std::vector<bool> S(graph->vertices.size());

    //Push the source onto the queue
    Q.push({0, s});
    
    //While our queue isn't empty
    while (!Q.empty()) {

        //Pull the top value off the priority queue
        std::pair<int, int> offQueue = Q.top();
        Q.pop();

        //Get the vertex with the given ID from the queue entry
        Vertex u = graph->vertices[offQueue.second];

        //If we've already processed this vertex, skip
        if (S[offQueue.second] == true)
            continue;
                  
        //Push this vertex's ID into the "processed" set
        S[offQueue.second] = true;

        //For every edge (vertex ID, weight) in the current vertex's edges
        for (std::pair<int, int> edge : u.edges) {

            //If the successor vertex's distance is greater than the current vertex plus edge weight
            if (graph->vertices[edge.first].d > offQueue.first + edge.second) {

                //Update this and set the new min
                graph->vertices[edge.first].d = offQueue.first + edge.second;

                //Push a new instance of the edge to the pqueue (negative for minheap)
                Q.push({-(offQueue.first + edge.second), edge.first});
            }
        }
    }
}

// Prints the shortest path from source vertex s to vertex v in
// directed graph G.
// Assumes a SSSP algorithm has already terminated.
void printPath(Vertex* s, Vertex* v, int runningSum) {
    if (v->d == 1000000000) 
        std::cout << "Impossible" << std::endl;
    
    else 
        std::cout << v->d << std::endl;
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

            graph.vertices[u].edges.insert({v, w});
        }

        Vertex* source = &graph.vertices[s];

        dijkstra(&graph, s);

        for (int i = 0; i < queries; i++) {
            int q;
            std::cin >> q;

            printPath(source, &graph.vertices[q], 0);
        }
    }
}